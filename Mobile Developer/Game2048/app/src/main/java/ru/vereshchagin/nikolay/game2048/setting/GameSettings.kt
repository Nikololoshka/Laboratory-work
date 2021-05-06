package ru.vereshchagin.nikolay.game2048.setting

import android.content.Context
import android.content.SharedPreferences
import android.preference.PreferenceManager
import com.google.gson.Gson
import com.google.gson.reflect.TypeToken
import java.io.File

object GameSettings {

    private const val TOP_SCORES = "top_scores.json"

    fun writeScore(context: Context, score: Int) {
        val cacheDir = context.cacheDir
        val scores = readTopScores(context)
        scores.add(score)
        scores.sortDescending()

        if (scores.size > 10) {
            scores.removeLast()
        }

        File(cacheDir, TOP_SCORES).bufferedWriter().use {
            Gson().toJson(scores, it)
        }
    }

    fun readTopScores(context: Context): ArrayList<Int> {
        var scores: ArrayList<Int> = arrayListOf()
        try {
            File(context.cacheDir, TOP_SCORES).reader().buffered().use {
                val type = object : TypeToken<ArrayList<Int>>() {}.type
                scores = Gson().fromJson(it, type)
            }
        } catch (ignored: Exception) {

        }

        scores.sortDescending()
        return scores
    }
}