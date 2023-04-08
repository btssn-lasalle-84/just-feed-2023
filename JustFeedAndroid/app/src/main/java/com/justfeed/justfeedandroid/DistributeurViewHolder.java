package com.justfeed.justfeedandroid;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.text.DecimalFormat;
/**
 * @brief Définition de la classe DistributeurViewHolder.
 * @details La classe DistributeurViewHolder \c DistributeurViewHolder permet de gérer les vues
 * pour afficher des distributeurs.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class DistributeurViewHolder extends RecyclerView.ViewHolder
{
    /**
     * Ressources GUI
     */
    private TextView     identifiant; //!< attribut GUI qui affiche l'identifiant du distributeur.
    private RecyclerView vueListeBacs; //!< attribut GUI qui afficher la liste des bacs du distributeur.

    /**
     * @brief Constructeur d'initialisation de la classe DistributeurViewHolder.
     * @details initialise les attributs GUI.
     * @param itemView
     */
    public DistributeurViewHolder(final View itemView)
    {
        super(itemView);

        identifiant   = ((TextView)itemView.findViewById(R.id.identifiant));
        vueListeBacs = itemView.findViewById(R.id.listeBacs);
    }

    /**
     * @brief Méthode qui affiche les distributeurs.
     * @param distributeur
     */
    public void afficherDistributeur(Distributeur distributeur)
    {
        this.identifiant.setText("Identifant : "+Integer.toString(distributeur.getIdentifiant()));
    }

    public RecyclerView modifierVueListeBacs()
    {
        return this.vueListeBacs;
    }
}
