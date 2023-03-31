package com.justfeed.justfeedandroid;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.RecyclerView.ViewHolder;

import java.util.List;
import java.util.Map;

public class InterventionViewHolder extends ViewHolder
{
    /**
     * Constantes
     */
    private static final String TAG = "_InterventionViewHolder";

    /**
     * Attributs
     */
    private Intervention intervention;

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

    public void afficherInterventions(List<Distributeur> listeDistributeurs)
    {
        String interventionsARealiser = "";
        boolean aIntervenir           = false;

        for(Distributeur distributeur: listeDistributeurs)
        {
            List<Bac> listeBacs = distributeur.getListeBacs();
            for(Bac bac: listeBacs)
            {
                if(bac.getIntervention().estARemplir())
                {
                    double poidsARemplir = bac.getIntervention().getPoidsARemplir();
                    aIntervenir = true;
                    interventionsARealiser.concat("Remplir Bac ").concat(bac.getTypeProduit().getNom()).concat(" de ").concat(String.format("%.2f kg\n", poidsARemplir));
                }
                if(bac.getIntervention().estADepanner())
                {
                    aIntervenir = true;
                    interventionsARealiser.concat("Dépannage nécessaire Bac ").concat(bac.getTypeProduit().getNom()).concat(" taux humidité > 0%\n");
                }
                if(aIntervenir)
                {
                    heureIntervention.setText(bac.getIntervention().getHeureIntervention());
                    identifiantDistributeur.setText(Integer.toString(distributeur.getIdentifiant()));
                }
            }
        }
    }
}
