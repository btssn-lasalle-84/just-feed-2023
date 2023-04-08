package com.justfeed.justfeedandroid;

import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class DistributeurAdapter extends RecyclerView.Adapter<DistributeurViewHolder>
{
    private List<Distributeur> distributeurs = null;

    public DistributeurAdapter(List<Distributeur> distributeurs)
    {
        if(distributeurs != null)
        {
            this.distributeurs = distributeurs;
        }
    }

    @NonNull
    @Override
    public DistributeurViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View           view     = inflater.inflate(R.layout.distributeur, parent, false);

        return new DistributeurViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull DistributeurViewHolder holder, int position)
    {
        Distributeur distributeur = distributeurs.get(position);
        holder.afficherDistributeur(distributeur);
    }

    @Override
    public int getItemCount()
    {
        if(distributeurs != null)
        {
            return distributeurs.size();
        }
        return 0;
    }
}
