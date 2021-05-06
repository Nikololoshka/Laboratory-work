package ru.vereshchagin.nikolay.game2048.ui

import android.view.View
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import ru.surname.name.game2048.R

class ScoreItemViewHolder(
    itemView: View
) : RecyclerView.ViewHolder(itemView) {

    private val indexView = itemView.findViewById<TextView>(R.id.index)
    private val scoreView = itemView.findViewById<TextView>(R.id.score)

    fun bind(index: Int, score: Int) {
        indexView.text = index.toString()
        scoreView.text = score.toString()
    }
}