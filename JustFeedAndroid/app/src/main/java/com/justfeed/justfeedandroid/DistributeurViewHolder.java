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
    private static final String   TAG                       = "_DistributeurViewHolder"; //!< TAG pour les logs
    private final double          AUCUNE_QUANTITE_A_REMPLIR = 0.0; //!< Le bac n'a pas besoin d'être rempli

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
        /**
         * @todo changer l'affichage des distributeurs
         */
        String  identifiant     = "Identifiant : ".concat(Integer.toString(distributeur.getIdentifiant()));
        String  listeProduits   = "Produits : ";
        String  prixProduits    = "Prix : ";
        String  poidsTotalBacs  = "Poids Total : ";
        String  poidsActuelBacs = "Poids Actuel : ";
        String  hydrometrie     = "Hydrometrie : ";

        this.distributeur = distributeur;
        Log.d(TAG, "afficherDistributeur() : " + distributeur.getIdentifiant());

        for (Bac bac : distributeur.getListeBacs())
        {
            Produit produit = bac.getTypeProduit();
            listeProduits   = listeProduits.concat(produit.getNom()).concat(" ");
            prixProduits    = prixProduits.concat(String.format("%.2f", produit.getPrix())).concat(" ");
            poidsTotalBacs  = poidsTotalBacs.concat(String.format("%.2f", bac.getPoidsTotalBac())).concat(" kg ");
            poidsActuelBacs = poidsActuelBacs.concat(String.format("%.2f", bac.getPoidsActuel())).concat(" kg ");
            hydrometrie     = hydrometrie.concat(Integer.toString(bac.getHydrometrie()));
        }

        this.identifiant.setText(identifiant);
        typeProduit.setText(listeProduits);
        prixProduit.setText(prixProduits);
        poidsTotal.setText(poidsTotalBacs);
        poidsActuel.setText(poidsActuelBacs);
        this.hydrometrie.setText(hydrometrie);
    }
}
