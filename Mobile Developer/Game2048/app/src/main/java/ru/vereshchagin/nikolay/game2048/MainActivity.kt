package ru.vereshchagin.nikolay.game2048

import android.animation.ValueAnimator
import android.content.Intent
import android.os.Bundle
import android.os.Parcel
import android.os.Parcelable
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.view.animation.LinearInterpolator
import android.widget.FrameLayout
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.app.AppCompatDelegate
import kotlinx.android.synthetic.main.activity_main.*
import ru.surname.name.game2048.R
import ru.vereshchagin.nikolay.game2048.model.GameModel
import ru.vereshchagin.nikolay.game2048.setting.ApplicationSettings
import ru.vereshchagin.nikolay.game2048.setting.GameSettings
import ru.vereshchagin.nikolay.game2048.view.GameView
import ru.vereshchagin.nikolay.game2048.view.OnGameListener

class MainActivity : AppCompatActivity() {

    private lateinit var container: FrameLayout
    private lateinit var themeImageView: ImageView

    private lateinit var scoreView: TextView
    private lateinit var gameView: GameView
    private lateinit var gameAction: TextView

    private val scoreAnimator = ValueAnimator().apply {
        interpolator = LinearInterpolator()
        duration = 300
        addUpdateListener { value ->
            scoreView.text = (value.animatedValue as Int).toString()
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        if (ApplicationSettings.isDarkMode(this)) {
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES)
        } else {
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO)
        }

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        container = findViewById(R.id.container)
        themeImageView = findViewById(R.id.theme_image)

        scoreView = findViewById(R.id.score)

        gameView = findViewById(R.id.game)
        gameAction = findViewById(R.id.game_action)

        gameAction.setOnClickListener {
            gameView.reset()
            gameAction.visibility = View.GONE
        }

        if (savedInstanceState == null) {
            gameView.model.restoreFromCache(this)
        }

        gameView.setOnGameListener(object : OnGameListener {
            override fun onScoreChanged(score: Int) {
                setScoreValue(score)
            }

            override fun onGameStateChanged(state: GameModel.GameState) {
                this@MainActivity.onGameStateChanged(state)
            }
        })
    }

    override fun onStop() {
        super.onStop()
        gameView.model.saveToCache(this)
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_activity_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.game_score_view -> {
                startActivity(Intent(this, ScoreActivity::class.java))
                return true
            }
            R.id.restart_game -> {
                gameView.reset()
                return true
            }
            R.id.dark_mode -> {
                updateTheme()
                return true
            }
        }
        return super.onOptionsItemSelected(item)
    }

    private fun onGameStateChanged(state: GameModel.GameState) {

        if (state == GameModel.GameState.LOST) {
            gameAction.visibility = View.VISIBLE
            gameAction.setText(R.string.game_lose)
            GameSettings.writeScore(this, gameView.model.score)
        }
        else if (state == GameModel.GameState.WIN) {
            gameAction.visibility = View.VISIBLE
            gameAction.setText(R.string.game_win)
            GameSettings.writeScore(this, gameView.model.score)
        }
    }

    private fun setScoreValue(score: Int) {
        if (scoreView.text.toString().isEmpty()) {
            scoreView.text = score.toString()
            return
        }

        if (scoreAnimator.isRunning) {
            scoreAnimator.cancel()
        }

        val currentScore = scoreView.text.toString().toInt()
        scoreAnimator.setIntValues(currentScore, score)
        scoreAnimator.start()
    }

    private fun updateTheme() {
        val darkMode = !ApplicationSettings.isDarkMode(this)
        ApplicationSettings.setDarkMode(this, darkMode)

        finish()
        startActivity(Intent(this, javaClass))
        overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out)
    }
}