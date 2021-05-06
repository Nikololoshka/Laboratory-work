package ru.vereshchagin.nikolay.game2048.model

import android.content.Context
import android.os.Parcel
import android.os.Parcelable
import android.util.Log
import android.view.View
import com.google.gson.Gson
import kotlinx.android.parcel.Parcelize
import java.io.File

@Parcelize
class GameModel(
    var mapSize: Int = 4
) : Parcelable {

    enum class Direction {
        UP,
        LEFT,
        RIGHT,
        DOWN
    }

    enum class GameState {
        WIN,
        NOT_OVER,
        LOST
    }

    private var board = emptyMap()
    val currentMap: List<List<Int>> get() = board

    var score: Int = 0
        private set

    init {
        generateCells(2)
    }

    private fun emptyMap(): MutableList<MutableList<Int>> {
        return MutableList(mapSize) { MutableList(mapSize) { EMPTY_CELL } }
    }

    fun reset() {
        board = emptyMap()
        score = 0
        generateCells(2)
    }

    fun currentGameState(): GameState {
        // есть 2048
        for (i in 0 until mapSize) {
            for (j in 0 until mapSize) {
                if (board[i][j] == 2048) {
                    return GameState.WIN
                }
            }
        }

        // есть пустые ячейки
        for (i in 0 until mapSize) {
            for (j in 0 until mapSize) {
                if (board[i][j] == EMPTY_CELL) {
                    return GameState.NOT_OVER
                }
            }
        }

        // можно куда то сходить (по горизонтали)
        for (i in 0 until mapSize) {
            for (j in 0 until mapSize) {
                if (i + 1 < mapSize && board[i][j] == board[i + 1][j]) {
                    return GameState.NOT_OVER
                }
                if (j + 1 < mapSize && board[i][j] == board[i][j + 1]) {
                    return GameState.NOT_OVER
                }
            }
        }
        // можно куда то сходить (по вертикали)
        for (j in 0 until mapSize) {
            if (j + 1 < mapSize && board[mapSize - 1][j] == board[mapSize - 1][j + 1]) {
                return GameState.NOT_OVER
            }
        }
        for (i in 0 until mapSize) {
            if (i + 1 < mapSize && board[i][mapSize - 1] == board[i + 1][mapSize - 1]) {
                return GameState.NOT_OVER
            }
        }

        return GameState.LOST
    }

    fun swipeTo(direction: Direction): List<MoveItem> {
        Log.d(TAG, "swipeTo: $direction")

        val (isValidMove, moves11) = moveTo(direction)
        val isValidCombine = combine(direction)

        Log.d(TAG, "swipeTo: $isValidMove - $isValidCombine")

        if (isValidMove || isValidCombine) {
            val (_, moves2) = moveTo(direction)
            generateCells()
            return moves11 + moves2
        }

        return moves11
    }

    private fun moveTo(direction: Direction): Pair<Boolean, ArrayList<MoveItem>> {
        var isValid = false
        val moves = arrayListOf<MoveItem>()

        when (direction) {
            Direction.UP -> {
                for (j in 0 until mapSize) {
                    for (i in 0 until mapSize) {
                        if (board[i][j] == EMPTY_CELL) {
                            for (k in i + 1 until mapSize) {
                                if (board[k][j] != EMPTY_CELL) {
                                    isValid = true
                                    board[i][j] = board[k][j]
                                    board[k][j] = EMPTY_CELL
                                    moves.add(MoveItem(k, j, i, j, board[i][j]))
                                    break
                                }
                            }
                        }
                    }
                }
            }
            Direction.LEFT -> {
                for (i in 0 until mapSize) {
                    for (j in 0 until mapSize) {
                        if (board[i][j] == EMPTY_CELL) {
                            for (k in j + 1 until mapSize) {
                                if (board[i][k] != EMPTY_CELL) {
                                    isValid = true
                                    board[i][j] = board[i][k]
                                    board[i][k] = EMPTY_CELL
                                    moves.add(MoveItem(i, k, i, j, board[i][j]))
                                    break
                                }
                            }
                        }
                    }
                }
            }
            Direction.RIGHT -> {
                for (i in 0 until mapSize) {
                    for (j in mapSize - 1 downTo 0) {
                        if (board[i][j] == EMPTY_CELL) {
                            for (k in j - 1 downTo 0) {
                                if (board[i][k] != EMPTY_CELL) {
                                    isValid = true
                                    board[i][j] = board[i][k]
                                    board[i][k] = EMPTY_CELL
                                    moves.add(MoveItem(i, k, i, j, board[i][j]))
                                    break
                                }
                            }
                        }
                    }
                }
            }
            Direction.DOWN -> {
                for (j in 0 until mapSize) {
                    for (i in mapSize - 1 downTo 0) {
                        if (board[i][j] == EMPTY_CELL) {
                            for (k in i - 1 downTo 0) {
                                if (board[k][j] != EMPTY_CELL) {
                                    isValid = true
                                    board[i][j] = board[k][j]
                                    board[k][j] = EMPTY_CELL
                                    moves.add(MoveItem(k, j, i, j, board[i][j]))
                                    break
                                }
                            }
                        }
                    }
                }
            }
        }

        return isValid to moves
    }

    private fun combine(direction: Direction): Boolean {
        var isValid = false

        when (direction) {
            Direction.UP -> {
                for (j in 0 until mapSize) {
                    for (i in 0 until mapSize - 1) {
                        if (board[i][j] != EMPTY_CELL && (board[i][j] == board[i + 1][j])) {
                            isValid = true
                            board[i][j] *= 2
                            board[i + 1][j] = 0
                            score += board[i][j]
                        }
                    }
                }
            }
            Direction.LEFT -> {
                for (i in 0 until mapSize) {
                    for (j in 0 until mapSize - 1) {
                        if (board[i][j] != EMPTY_CELL && (board[i][j] == board[i][j + 1])) {
                            isValid = true
                            board[i][j] *= 2
                            board[i][j + 1] = 0
                            score += board[i][j]
                        }
                    }
                }
            }
            Direction.RIGHT -> {
                for (i in 0 until mapSize) {
                    for (j in mapSize - 1 downTo 1) {
                        if (board[i][j] != EMPTY_CELL && (board[i][j] == board[i][j - 1])) {
                            isValid = true
                            board[i][j] *= 2
                            board[i][j - 1] = 0
                            score += board[i][j]
                        }
                    }
                }
            }
            Direction.DOWN -> {
                for (j in 0 until mapSize) {
                    for (i in mapSize - 1 downTo 1) {
                        if (board[i][j] != EMPTY_CELL && (board[i][j] == board[i - 1][j])) {
                            isValid = true
                            board[i][j] *= 2
                            board[i - 1][j] = 0
                            score += board[i][j]
                        }
                    }
                }
            }
        }

        return isValid
    }

    private fun moveUp() {
        transpose()
        moveLeft()
        transpose()
    }

    private fun moveLeft() {
        compress()
        merge()
        compress()
    }

    private fun moveRight() {
        reverse()
        moveLeft()
        reverse()
    }

    private fun moveDown() {
        transpose()
        moveRight()
        transpose()
    }

    private fun compress(): Boolean {
        val newMap = emptyMap()

        var changed = false
        for (i in 0 until mapSize) {
            var pos = 0
            for (j in 0 until mapSize) {
                if (board[i][j] != EMPTY_CELL) {
                    newMap[i][pos] = board[i][j]
                    if (j != pos) {
                        changed = true
                    }
                    pos++
                }
            }
        }

        board = newMap
        return changed
    }

    private fun merge(): Boolean {
        var changed = false
        for (i in 0 until mapSize) {
            for (j in 0 until mapSize - 1) {
                if (board[i][j] == board[i][j + 1] && board[i][j] != EMPTY_CELL) {
                    board[i][j] *= 2
                    board[i][j + 1] = 0
                    changed = true
                }
            }
        }
        return changed
    }

    private fun reverse() {
        val newMap = emptyMap()
        for (i in 0 until mapSize) {
            for (j in 0 until mapSize) {
                newMap[i][j] = board[i][mapSize - 1 - j]
            }
        }
        board = newMap
    }

    private fun transpose() {
        val newMap = emptyMap()
        for (i in 0 until mapSize) {
            for (j in 0 until mapSize) {
                newMap[i][j] = board[j][i]
            }
        }
        board = newMap
    }

    private fun generateCells(count: Int = 1) {
        val emptyCells = ArrayList<Pair<Int, Int>>()
        for (i in 0 until mapSize) {
            for (j in 0 until mapSize) {
                if (board[i][j] == EMPTY_CELL) {
                    emptyCells.add(i to j)
                }
            }
        }

        emptyCells.shuffle()
        for (index in 0 until count) {
            if (index < emptyCells.size) {
                val (i, j) = emptyCells[index]
                board[i][j] = START_CELL_VALUE
            }
        }
    }

    fun saveToCache(context: Context) {
        val cache = context.cacheDir
        val file = File(cache, MODEL_CACHE)
        file.bufferedWriter().use {
            Gson().toJson(this, it)
            Log.d(TAG, "saveToCache: " + Gson().toJson(this))
        }
    }

    fun restoreFromCache(context: Context) {
        val cache = context.cacheDir
        val file = File(cache, MODEL_CACHE)
        if (file.exists()) {
            file.bufferedReader().use {
                val other = Gson().fromJson(it, GameModel::class.java)
                Log.d(TAG, "saveToCache: " + other)
                if (other != null) {
                    this.score = other.score
                    this.board = other.board
                }
            }
        }
    }

    class MoveItem(
        val fromX: Int,
        val fromY: Int,
        val toX: Int,
        val toY: Int,
        val value: Int
    ) {
        override fun toString(): String {
            return "MoveItem(fromX=$fromX, fromY=$fromY, toX=$toX, toY=$toY, value=$value)"
        }
    }

    override fun toString(): String {
        return "GameModel(mapSize=$mapSize, board=$board, score=$score)"
    }

    companion object {

        private const val START_CELL_VALUE = 2
        const val EMPTY_CELL = 0

        private const val MODEL_CACHE = "game_model.json"

        private const val TAG = "GameModelLog"
    }
}