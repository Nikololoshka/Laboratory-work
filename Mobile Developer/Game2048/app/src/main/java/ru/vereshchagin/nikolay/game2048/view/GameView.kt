package ru.vereshchagin.nikolay.game2048.view

import android.animation.ValueAnimator
import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.Typeface
import android.os.Parcel
import android.os.Parcelable
import android.text.TextPaint
import android.util.AttributeSet
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.view.animation.AccelerateDecelerateInterpolator
import android.view.animation.LinearInterpolator
import androidx.core.animation.doOnEnd
import com.google.android.material.math.MathUtils
import ru.vereshchagin.nikolay.game2048.model.GameModel
import kotlin.math.abs
import kotlin.math.max

/**
 * Графический компонент игры 2048.
 */
class GameView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : View(context, attrs, defStyleAttr) {
    /**
     * Логическая модель игры.
     */
    var model = GameModel()
        private set

    /**
     * Список с передвижением клеток (для анимации).
     */
    private var moves: List<GameModel.MoveItem>? = null

    /**
     * Объект для проведения анимации перемещения клеток.
     */
    private val animator = ValueAnimator().apply {
        duration = 100
        interpolator = LinearInterpolator()
        setFloatValues(0F, 1F)
        addUpdateListener {
            animateProgress = it.animatedValue as Float
            invalidate()
        }
        doOnEnd {
            moves = null
            animateProgress = 0F
        }
    }

    /**
     * Текущий прогресс анимации (от 0 до 1)
     */
    private var animateProgress = 0F

    /**
     * Размер ячеек на поле.
     */
    private var cellSize: Float = 0F

    /**
     * Перо, которым рисуются линии на поле.
     */
    private val linePaint = Paint(Paint.ANTI_ALIAS_FLAG)

    /**
     * Перо, которым рисуется текст в ячейках.
     */
    private val textPaint = TextPaint(Paint.ANTI_ALIAS_FLAG)

    /**
     * Перо, которым рисуется фон ячейки.
     */
    private val cellPaint = Paint(Paint.ANTI_ALIAS_FLAG)

    // переменные для фиксации жеста по Viwe
    private var downX = 0f
    private var downY = 0f
    private var upX = 0f
    private var upY = 0f

    /**
     * Слушатель состояния игры.
     */
    private var listener: OnGameListener? = null

    init {
        linePaint.strokeWidth = 6F
        textPaint.color = Color.parseColor("#222222")
        textPaint.textSize = 60F
        textPaint.typeface = Typeface.create(Typeface.DEFAULT, Typeface.BOLD);
        cellPaint.color = Color.parseColor("#ffd078")
    }

    /**
     * Метод, в которым происходит определения размеров View.
     */
    override fun onMeasure(widthMeasureSpec: Int, heightMeasureSpec: Int) {
        val widthSize = resolveSize(100, widthMeasureSpec)
        val heightSize = resolveSize(100, heightMeasureSpec)

        val minSize = max(widthSize, heightSize)
        cellSize = minSize.toFloat() / model.mapSize

        setMeasuredDimension(minSize, minSize)
    }

    /**
     * Метод, в котором происходит рисование View.
     */
    override fun onDraw(maybeCanvas: Canvas?) {
        val canvas = maybeCanvas ?: return super.onDraw(maybeCanvas)

        // есть ли список ч передвижениями
        val currentMoves = moves
        if (currentMoves != null) {
            // если да, то отрисоваваем прогресс анимации

            // рисуем фон
            for (i in 0 until model.mapSize) {
                for (j in 0 until model.mapSize) {
                    val value = model.currentMap[j][model.mapSize - 1 - i]
                    cellPaint.color = computeCellColor(value)
                    canvas.drawRect(
                        cellSize * i,
                        cellSize * j,
                        cellSize * i + cellSize,
                        cellSize * j + cellSize,
                        cellPaint
                    )
                }
            }

            // рисуем текст
            for (i in 0 until model.mapSize) {
                for (j in 0 until model.mapSize) {
                    val value = model.currentMap[j][model.mapSize - 1 - i]
                    // с значением
                    if (value != GameModel.EMPTY_CELL) {
                        var isFind = false
                        for (move in currentMoves) {
                            if (move.toX == j && move.toY == model.mapSize - 1 - i) {
                                drawCenterText(
                                    canvas,
                                    move.value.toString(),
                                    cellSize * (model.mapSize - 1 - MathUtils.lerp(
                                        move.fromY.toFloat(),
                                        move.toY.toFloat(),
                                        animateProgress
                                    )),
                                    cellSize * (MathUtils.lerp(
                                        move.fromX.toFloat(),
                                        move.toX.toFloat(),
                                        animateProgress
                                    )),
                                    cellSize,
                                    cellSize
                                )
                                isFind = true
                            }
                        }
                        // если ячейка не сдвинута, то просто отрисовываем ее
                        if (!isFind) {
                            drawCenterText(
                                canvas,
                                value.toString(),
                                cellSize * i,
                                cellSize * j,
                                cellSize,
                                cellSize
                            )
                        }
                    }
                }
            }
        } else {
            // просто отрисовка поля

            for (i in 0 until model.mapSize) {
                for (j in 0 until model.mapSize) {
                    val value = model.currentMap[j][model.mapSize - 1 - i]
                    cellPaint.color = computeCellColor(value)
                    canvas.drawRect(
                        cellSize * i,
                        cellSize * j,
                        cellSize * i + cellSize,
                        cellSize * j + cellSize,
                        cellPaint
                    )
                    // с значением
                    if (value != GameModel.EMPTY_CELL) {
                        drawCenterText(
                            canvas,
                            value.toString(),
                            cellSize * i,
                            cellSize * j,
                            cellSize,
                            cellSize
                        )
                    }
                }
            }
        }

        // горизонтальные и вертикальные линии между полем
        for (i in 0 until model.mapSize + 1) {
            canvas.drawLine(0F, cellSize * i, measuredWidth.toFloat(), cellSize * i, linePaint)
            for (j in 0 until model.mapSize + 1) {
                canvas.drawLine(cellSize * j, 0F, cellSize * j, measuredHeight.toFloat(), linePaint)
            }
        }
    }

    /**
     * Сбросить прогресс игры.
     */
    fun reset() {
        model.reset()
        moves = null
        animator.cancel()
        animateProgress = 0F
        invalidate()
        checkGameState()
    }

    /**
     * Метод, для отрисовки текста по центу заданной областию
     */
    private fun drawCenterText(
        canvas: Canvas,
        text: String,
        x: Float,
        y: Float,
        w: Float,
        h: Float
    ) {
        val xx = x + w / 2 - textPaint.measureText(text) / 2
        val yy = y + h / 2 - (textPaint.descent() + textPaint.ascent()) / 2

        canvas.drawText(text, xx, yy, textPaint)
    }

    /**
     * Возвращает цвет фона ячейки исходя из ее значения.
     */
    private fun computeCellColor(value: Int): Int {
        return Color.parseColor(
            when (value) {
                4 -> "#f7f6d5"
                8 -> "#fffdb5"
                16 -> "#f5db8c"
                32 -> "#face48"
                64 -> "#ffca29"
                128 -> "#fae64d"
                256 -> "#ffe72e"
                512 -> "#ffe72e"
                1024 -> "#ff9b61"
                2048 -> "#ff6c47"
                else -> "#DDDDDD"
            }
        )
    }

    /**
     * Метод для возможности обработки нажатия.
     */
    override fun performClick(): Boolean {
        return super.performClick()
    }

    /**
     * Метод, в который приходят события взаимодействия с View.
     */
    override fun onTouchEvent(maybeEvent: MotionEvent?): Boolean {
        val event = maybeEvent ?: return super.onTouchEvent(maybeEvent)

        when (event.action) {
            // прикоснулись к нашей view
            MotionEvent.ACTION_DOWN -> {
                downX = event.x
                downY = event.y
                return true
            }
            // отжали касание от view
            MotionEvent.ACTION_UP -> {
                upX = event.x
                upY = event.y

                val deltaX = downX - upX
                val deltaY = downY - upY

                // горизонтальный свайп
                if (abs(deltaX) > abs(deltaY)) {
                    if (abs(deltaX) > MIN_DISTANCE) {
                        // лево и право
                        if (deltaX > 0) {
                            swipeTo(GameModel.Direction.RIGHT)
                            return true
                        }
                        if (deltaX < 0) {
                            swipeTo(GameModel.Direction.LEFT)
                            return true
                        }
                    } else {
                        return false
                    }
                }
                // вертикальный свайп vertical?
                else {
                    if (abs(deltaY) > MIN_DISTANCE) {
                        // верх или низ
                        if (deltaY < 0) {
                            swipeTo(GameModel.Direction.DOWN)
                            return true
                        }
                        if (deltaY > 0) {
                            swipeTo(GameModel.Direction.UP)
                            return true
                        }
                    } else {
                        return false
                    }
                }

                performClick()
                return true
            }
        }
        return super.onTouchEvent(event)
    }

    /**
     * Передает событие перемещение в логику игры.
     * Если передвижение было осуществлено, то вызывается процесс анимации.
     */
    private fun swipeTo(direction: GameModel.Direction) {
        Log.d(TAG, "BEFORE swipeTo: ${model.currentMap}")
        val newMoves = model.swipeTo(direction)
        if (newMoves.isNotEmpty()) {
            moves = newMoves
            Log.d(TAG, "swipeTo: $moves")
            Log.d(TAG, "AFTER swipeTo: ${model.currentMap}")

            val tt = MutableList(4) { MutableList(4) { GameModel.EMPTY_CELL } }
            var v = 0
            for (i in 0 until 4) {
                for (j in 0 until 4) {
                    tt[j][4 - 1 - i] = v++
                }
            }
            Log.d(TAG, "swipeTo: $tt")


            if (animator.isRunning) {
                animator.cancel()
            }
            animator.start()
        } else {
            invalidate()
        }
        checkGameState()
    }

    /**
     * Проверяет статус игры и уведомляет о нем слушателей.
     */
    private fun checkGameState() {
        listener?.apply {
            onScoreChanged(model.score)
            onGameStateChanged(model.currentGameState())
        }
    }

    /**
     * Устанавливает слушатель статуса игры.
     */
    fun setOnGameListener(listener: OnGameListener) {
        this.listener = listener
        checkGameState()
    }

    /**
     * Метод, в котором сохраняется состояние View.
     */
    override fun onSaveInstanceState(): Parcelable? {
        val superstate = super.onSaveInstanceState()
        if (superstate != null) {
            val state = SavedState(superstate)
            state.model = model
            return state
        }
        return superstate
    }
    /**
     * Метод, где загружается состояние View.
     */
    override fun onRestoreInstanceState(state: Parcelable?) {
        if (state is SavedState) {
            super.onRestoreInstanceState(state.superState)
            state.model?.let {
                this.model = it
            }
            checkGameState()
        } else {
            super.onRestoreInstanceState(state)
        }
    }

    /**
     * Вспомогательный класс для сохранения состояния View.
     */
    internal class SavedState : BaseSavedState {

        var model: GameModel? = null

        constructor(superState: Parcelable) : super(superState)

        constructor(source: Parcel) : super(source) {
            model = source.readParcelable(GameModel::class.java.classLoader)
        }

        override fun writeToParcel(out: Parcel?, flags: Int) {
            super.writeToParcel(out, flags)
            out?.writeParcelable(model, flags)
        }

        companion object {
            @JvmField
            val CREATOR: Parcelable.Creator<SavedState> = object : Parcelable.Creator<SavedState> {
                override fun createFromParcel(source: Parcel): SavedState {
                    return SavedState(source)
                }

                override fun newArray(size: Int): Array<SavedState> {
                    return newArray(size)
                }
            }
        }
    }

    companion object {
        private const val TAG = "GameViewLog"
        private const val MIN_DISTANCE = 100
    }
}