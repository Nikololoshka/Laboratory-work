package ru.vereshchagin.nikolay.game2048.ui

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import ru.surname.name.game2048.R

class ScoreAdapter : RecyclerView.Adapter<ScoreItemViewHolder>() {

    private var data = emptyList<Int>()

    fun submitData(data: List<Int>) {
        this.data = data
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ScoreItemViewHolder {
        return ScoreItemViewHolder(
            LayoutInflater.from(parent.context).inflate(R.layout.item_score, parent, false)
        )
    }

    override fun onBindViewHolder(holder: ScoreItemViewHolder, position: Int) {
        holder.bind(position + 1, data[position])
    }

    override fun getItemCount(): Int {
        return data.size
    }
}