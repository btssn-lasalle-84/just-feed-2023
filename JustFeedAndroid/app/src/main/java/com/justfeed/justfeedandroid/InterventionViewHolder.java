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
     * Ressources GUI
     */
    private final TextView identifiantDistributeur;
    private final TextView heureIntervention;
    private final TextView aRemplir;
    private final TextView aDepanner;

    public InterventionViewHolder(final View itemView)
    {
        super(itemView);

        identifiantDistributeur = ((TextView)itemView.findViewById(R.id.identifiantDistributeur));
        heureIntervention       = ((TextView)itemView.findViewById(R.id.heureIntervention));
        aRemplir                = ((TextView)itemView.findViewById(R.id.aRemplir));
        aDepanner               = ((TextView)itemView.findViewById(R.id.aDepanner));
    }

    public void afficherInterventions(Intervention intervention)
    {
        identifiantDistributeur.setText("Identifiant du distributuer : "+Integer.toString(intervention.getIdentifiantDistribteur()));
        if(!(intervention.bacsADepanner().isEmpty()))
        {
            aDepanner.setText("Bacs à dépanner (Hygrométrie > 0%) : \n"+intervention.bacsADepanner());
        }
        if(!(intervention.bacsARemplir().isEmpty()))
        {
            aRemplir.setText("Bacs à remplir: \n"+intervention.bacsARemplir());
        }
        heureIntervention.setText("Heure de l'intervention : "+intervention.getHeureIntervention());
    }
}