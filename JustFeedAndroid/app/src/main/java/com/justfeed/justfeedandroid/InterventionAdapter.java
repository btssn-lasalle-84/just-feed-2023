package com.justfeed.justfeedandroid;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class InterventionAdapter extends RecyclerView.Adapter<InterventionViewHolder>
{
    private List<Intervention> interventions = null;

    public InterventionAdapter(List<Intervention> interventions)
    {
        if(interventions != null)
        {
            this.interventions = interventions;
        }
    }

    @NonNull
    @Override
    public InterventionViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View view = inflater.inflate(R.layout.intervention, parent, false);

        return new InterventionViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull InterventionViewHolder holder, int position)
    {
        Intervention intervention = interventions.get(position);
        holder.afficherInterventions(intervention);
    }

    @Override
    public int getItemCount()
    {
        if(interventions != null)
        {
            return interventions.size();
        }
        return 0;
    }
}
