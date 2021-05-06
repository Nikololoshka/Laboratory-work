package ru.vereshchagin.nikolay.game2048

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.RecyclerView
import ru.surname.name.game2048.R
import ru.vereshchagin.nikolay.game2048.setting.GameSettings
import ru.vereshchagin.nikolay.game2048.ui.ScoreAdapter

class ScoreActivity : AppCompatActivity() {

    private lateinit var scores: RecyclerView
    private lateinit var adapter: ScoreAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_score)

        scores = findViewById(R.id.scores)
        adapter = ScoreAdapter()
        scores.adapter = adapter

        updateScoreList()
    }

    private fun updateScoreList() {
        val scoreList = GameSettings.readTopScores(this)
        if (scoreList.isEmpty()) {
            scoreList.add(0)
        }

        adapter.submitData(scoreList)
    }
}