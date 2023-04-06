package com.justfeed.justfeedandroid;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.RecyclerView.ViewHolder;

import java.util.Dictionary;
import java.util.List;
import java.util.Map;

public class InterventionViewHolder extends ViewHolder
{
    /**
     * Constantes
     */
    private static final String TAG = "_InterventionViewHolder";
    /**
     * Ressources GUI
     */
    private final TextView identifiantDistributeur;
    private final TextView heureIntervention;
    private final TextView aRemplir;
    private final TextView aDepanner;

    public InterventionViewHolder(final View itemView)
    {
        super(itemView);
        Log.d(TAG, "InterventionViewHolder()");

        identifiantDistributeur = ((TextView)itemView.findViewById(R.id.identifiantDistributeur));
        heureIntervention       = ((TextView)itemView.findViewById(R.id.heureIntervention));
        aRemplir                = ((TextView)itemView.findViewById(R.id.aRemplir));
        aDepanner               = ((TextView)itemView.findViewById(R.id.aDepanner));
    }

    public void afficherInterventions(Intervention intervention)
    {
        identifiantDistributeur.setText(Integer.toString(intervention.getIdentifiantDistribteur()));
        aDepanner.setText(intervention.bacsADepanner());
        aRemplir.setText(intervention.bacsARemplir());
        heureIntervention.setText(intervention.getHeureIntervention());
    }
}