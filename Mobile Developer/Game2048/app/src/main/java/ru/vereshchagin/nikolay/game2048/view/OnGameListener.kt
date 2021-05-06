package ru.vereshchagin.nikolay.game2048.view

import ru.vereshchagin.nikolay.game2048.model.GameModel

interface OnGameListener {
    fun onScoreChanged(score: Int)
    fun onGameStateChanged(state: GameModel.GameState)
}