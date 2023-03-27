package com.justfeed.justfeedandroid;

import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

public class DistributeurViewHolder extends RecyclerView.ViewHolder {
    private final TextView identifiant;
    private final TextView typeProduit;

    private final TextView prixProduit;
    private final TextView poidsTotal;
    private final TextView poidsActuel;
    private final TextView hydrometrie;

    private Distributeur distributeur;

    public DistributeurViewHolder(final View itemView){
        super(itemView);

        identifiant = ((TextView)itemView.findViewById(R.id.identifiant));
        typeProduit = ((TextView)itemView.findViewById(R.id.typeProduit));
        prixProduit = ((TextView)itemView.findViewById(R.id.prixProduit));
        poidsTotal = ((TextView)itemView.findViewById(R.id.poidsTotal));
        poidsActuel = ((TextView)itemView.findViewById(R.id.poidsActuel));
        hydrometrie = ((TextView)itemView.findViewById(R.id.hydrometrie));
    }

    public void afficherDistributeur(Distributeur distributeur){
        this.distributeur = distributeur;

        identifiant.setText(distributeur.getIdentifiant());
        typeProduit.setText("Produit : " + distributeur.getProduit().getNom());
        prixProduit.setText(distributeur.getProduit().getPrix() + " €");
        poidsTotal.setText(distributeur.getPoidsTotal() + " kg");
        poidsActuel.setText(distributeur.getPoidsActuel() + " kg");
    }
}
