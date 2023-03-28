package com.justfeed.justfeedandroid;

import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.RecyclerView.ViewHolder;

public class InterventionViewHolder extends ViewHolder
{
    private final TextView numeroIntervention;
    private final TextView heureIntervention;
    private final TextView tempsTrajet;
    private final TextView poidsARemplir;
    private final TextView aIntervenir;

    private Intervention intervention;

    public InterventionViewHolder(final View itemView)
    {
        super(itemView);

        numeroIntervention = ((TextView)itemView.findViewById(R.id.numeroIntervention));
        heureIntervention = ((TextView)itemView.findViewById(R.id.heureIntervention));
        tempsTrajet = ((TextView)itemView.findViewById(R.id.tempsTrajet));
        poidsARemplir = ((TextView)itemView.findViewById(R.id.poidsARemplir));
        aIntervenir = ((TextView)itemView.findViewById(R.id.aIntervenir));
    }

    public void afficherInterventions(Intervention intervention)
    {
        this.intervention = intervention;

        numeroIntervention.setText(intervention.getNumeroIntervention());
        heureIntervention.setText(intervention.getHeureIntervention());
        tempsTrajet.setText(intervention.getTempsTrajet());
        poidsARemplir.setText(intervention.getPoidsARemplir() + " kg");
        if (intervention.interventionTerminee())
        {
            aIntervenir.setText("Distributeur en état de marche");
        }
        else
        {
            aIntervenir.setText("Distributeur à intervenir");
        }
    }
}
