package com.justfeed.justfeedandroid;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.text.DecimalFormat;

public class DistributeurViewHolder extends RecyclerView.ViewHolder
{
    /**
     * Constantes
     */
    private static final String   TAG = "_DistributeurViewHolder"; //!< TAG pour les logs
    /**
     * Ressources GUI
     */
    private TextView     identifiant;
    private RecyclerView vueListeBacs;

    public DistributeurViewHolder(final View itemView)
    {
        super(itemView);
        Log.d(TAG, "DistributeurViewHolder()");

        identifiant   = ((TextView)itemView.findViewById(R.id.identifiant));
        vueListeBacs = itemView.findViewById(R.id.listeBacs);
    }

    public void afficherDistributeur(Distributeur distributeur)
    {
        Log.d(TAG, "afficherDistributeur() : " + distributeur.getIdentifiant());

        this.identifiant.setText(Integer.toString(distributeur.getIdentifiant()));
    }

    public RecyclerView modifierVueListeBacs()
    {
        return this.vueListeBacs;
    }
}
