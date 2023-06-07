/**
 * @file VueDistributeur.java
 * @brief Déclaration de la classe VueDistributeur
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import android.location.Location;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.List;
import java.util.Locale;

/**
 * @brief Définition de la classe VueDistributeur.
 * @details La classe VueDistributeur \c VueDistributeur permet de gérer les vues
 * pour afficher des distributeurs.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class VueDistributeur extends RecyclerView.ViewHolder
{
    /**
     * Constantes
     */
    private static final String TAG = "_VueDistributeur"; //!< TAG pour les logs

    /**
     * Ressources GUI
     */
    private TextView identifiant;   //!< attribut GUI qui affiche l'identifiant du distributeur.
    private TextView localisation;  //!< attribut GUI qui affiche la localisation du distributeur.
    private TextView
      coordGeographiques;           //!< attribut GUI qui affiche les coordonnées géographiques du distributeur.
    private TextView intervention;  //!< attribut GUI qui affiche l'état du distributeur.
    private RecyclerView
      vueListeBacs; //!< attribut GUI qui afficher la liste des bacs du distributeur.

    /**
     * @brief Constructeur d'initialisation de la classe DistributeurViewHolder.
     * @details initialise les attributs GUI.
     * @param itemView
     */
    public VueDistributeur(final View itemView)
    {
        super(itemView);

        identifiant         = ((TextView)itemView.findViewById(R.id.identifiant));
        localisation        = ((TextView)itemView.findViewById(R.id.localisation));
        coordGeographiques  = ((TextView)itemView.findViewById(R.id.coordGeographiques));
        intervention        = ((TextView)itemView.findViewById(R.id.intervention));
        vueListeBacs        = itemView.findViewById(R.id.listeBacs);
    }

    /**
     * @brief Méthode qui affiche les distributeurs.
     * @param distributeur
     */
    public void afficherDistributeur(Distributeur distributeur)
    {
        Location coordGeographiques = distributeur.getCoordGeographiques();
        this.identifiant.setText(distributeur.getNom() + " ("+distributeur.getIdMachine()+")");
        if(distributeur.estARemplir() || distributeur.estADepanner())
        {
            this.intervention.setText("À intervenir");
        }
        this.localisation.setText(distributeur.getLocalisation() + "\n");
        // En Degrés décimaux (DD) généralement avec quatre décimales
        // avec un point '.' pour la partie décimale
        // et la virgule ',' pour séparer les deux valeurs
        // La latitude doit être indiquée avant la longitude
        DecimalFormatSymbols symbolesUS  = DecimalFormatSymbols.getInstance(Locale.US);
        DecimalFormat        formateurUS = new DecimalFormat("###.#####", symbolesUS);
        this.coordGeographiques.setText(formateurUS.format(coordGeographiques.getLatitude()) + ", " +
                                     formateurUS.format(coordGeographiques.getLongitude()));
        Log.d(TAG, "afficherDistributeur() coordGeographiques = " + coordGeographiques.toString());
    }

    public RecyclerView modifierVueListeBacs()
    {
        return this.vueListeBacs;
    }
}
