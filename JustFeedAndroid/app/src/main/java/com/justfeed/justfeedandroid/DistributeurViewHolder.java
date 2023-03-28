package com.justfeed.justfeedandroid;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

public class DistributeurViewHolder extends RecyclerView.ViewHolder
{
    /**
     * Constantes
     */
    private static final String TAG = "_DistributeurViewHolder"; //!< TAG pour les logs

    /**
     * Attributs
     */
    private Distributeur distributeur;

    /**
     * Ressources GUI
     */
    private TextView identifiant;
    private TextView typeProduit;
    private TextView prixProduit;
    private TextView poidsTotal;
    private TextView poidsActuel;
    private TextView hydrometrie;

    public DistributeurViewHolder(final View itemView)
    {
        super(itemView);
        Log.d(TAG, "DistributeurViewHolder()");

        identifiant = ((TextView)itemView.findViewById(R.id.identifiant));
        typeProduit = ((TextView)itemView.findViewById(R.id.typeProduit));
        prixProduit = ((TextView)itemView.findViewById(R.id.prixProduit));
        poidsTotal = ((TextView)itemView.findViewById(R.id.poidsTotal));
        poidsActuel = ((TextView)itemView.findViewById(R.id.poidsActuel));
        hydrometrie = ((TextView)itemView.findViewById(R.id.hydrometrie));
    }

    public void afficherDistributeur(Distributeur distributeur)
    {
        String listeProduits   = "";
        String prixProduits    = "";
        String poidsTotalBacs  = "";
        String poidsActuelBacs = "";

        this.distributeur = distributeur;
        Log.d(TAG, "afficherDistributeur() : " + distributeur.getIdentifiant());

        for (Produit produit: distributeur.getProduits())
        {
            listeProduits.concat(produit.getNom()+" ");
            prixProduits.concat(produit.getPrix()+" € ");
            poidsTotalBacs.concat(distributeur.getPoidsTotalBac(produit)+" kg ");
            poidsActuelBacs.concat(" "+distributeur.getPoidsActuel(produit)+" kg ");
        }

        identifiant.setText(String.valueOf(distributeur.getIdentifiant()));
        typeProduit.setText("Produits : " + listeProduits);
        prixProduit.setText(prixProduits);
        poidsTotal.setText(poidsTotalBacs);
        poidsActuel.setText(poidsActuelBacs);
        hydrometrie.setText(distributeur.getHydrometrie());
    }
}
