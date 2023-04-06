package com.justfeed.justfeedandroid;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class BacAdapter extends RecyclerView.Adapter<BacViewHolder>
{
    private List<Bac> listeBacs = null;

    public BacAdapter(List<Bac> listeBacs)
    {
        if(listeBacs != null)
        {
            this.listeBacs = listeBacs;
        }
    }

    @NonNull
    @Override
    public BacViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View vue                = inflater.inflate(R.layout.bac, parent, false);

        return new BacViewHolder(vue);
    }

    @Override
    public void onBindViewHolder(@NonNull BacViewHolder holder, int position)
    {
        Bac bac = listeBacs.get(position);
        holder.afficherBac(bac);
    }

    @Override
    public int getItemCount()
    {
        if(listeBacs != null)
        {
            return listeBacs.size();
        }

        return 0;
    }
}
