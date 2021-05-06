package ru.vereshchagin.nikolay.game2048.setting

import android.content.Context
import androidx.preference.PreferenceManager

object ApplicationSettings {

    private const val DARK_MODE = "dark_mode"

    fun isDarkMode(context: Context): Boolean {
        val preferences = PreferenceManager.getDefaultSharedPreferences(context)
        return preferences.getBoolean(DARK_MODE, false)
    }

    fun setDarkMode(context: Context, isDark: Boolean) {
        val preferences = PreferenceManager.getDefaultSharedPreferences(context)
        preferences.edit()
            .putBoolean(DARK_MODE, isDark)
            .apply()
    }
}