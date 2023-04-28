/**
 * @file VueIntervention.java
 * @brief Déclaration de la classe VueIntervention
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import android.graphics.Color;
import android.view.View;
import android.widget.TextView;

import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView.ViewHolder;

/**
 * @brief Définition de la classe VueIntervention.
 * @details La classe VueIntervention \c VueIntervention permet de gérer les vues
 * pour afficher des interventions.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class VueIntervention extends ViewHolder
{
    /**
     * Constantes
     */
    private final static String ROUGE = "#ed3734"; //!< L'intervention n'a pas été effectuée
    private final static String VERT  = "#4eea48";
    /**
     * Ressources GUI
     */
    private final TextView identifiantDistributeur; //!< attribut GUI qui affiche l'identifiant du
                                                    //!< distributeur où intervenir.
    private final TextView
      dateIntervention; //!< attribut GUI qui affiche l'heure de l'intervention.
    private final TextView
      aRemplir; //!< attribut GUI qui affiche si le distributeur doit être rempli.
    private final TextView
      aDepanner; //!< attribut GUI qui affiche si le distributeur doit être dépanné.
    private final CardView carteIntervention; //!< attribut GUI qui contient les informations sur une intervention.

    public VueIntervention(final View itemView)
    {
        super(itemView);

        identifiantDistributeur = ((TextView)itemView.findViewById(R.id.identifiantDistributeur));
        dateIntervention        = ((TextView)itemView.findViewById(R.id.dateIntervention));
        aRemplir                = ((TextView)itemView.findViewById(R.id.aRemplir));
        aDepanner               = ((TextView)itemView.findViewById(R.id.aDepanner));
        carteIntervention       = ((CardView)itemView.findViewById(R.id.carteIntervention));
    }

    public void afficherInterventions(Intervention intervention)
    {
        if(!intervention.estEffectuee())
        {
            carteIntervention.setCardBackgroundColor(Color.parseColor(ROUGE));
        }
        else
        {
            carteIntervention.setCardBackgroundColor(Color.parseColor(VERT));
        }
        identifiantDistributeur.setText("Distributeur : " + intervention.getNomDistribteur());
        if(intervention.estADepanner())
        {
            aDepanner.setText("Bacs à dépanner (Hygrométrie > " + Intervention.SEUIL_HUMIDITE + "%) : \n" +
                    intervention.recupererBacsADepanner());
        }
        if(intervention.estARemplir())
        {
            aRemplir.setText("Bac(s) à remplir : \n" + intervention.recupererBacsARemplir());
        }
        dateIntervention.setText("Date de l'intervention : " + Intervention.formaterDate(intervention.getDateIntervention()));
    }
}