package com.justfeed.justfeedandroid;

import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.ColorInt;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.core.content.res.ResourcesCompat;
import androidx.recyclerview.widget.RecyclerView;
/**
 * @brief Définition de la classe BacViewHolder.
 * @details La classe BacViewHolder \c BacViewHolder permet de gérer les vues des bacs.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class BacViewHolder extends RecyclerView.ViewHolder
{
    /**
     * Constantes
     */
    private final int MOITIE   = 2; //!< constante utilisée pour calculer la moitié d'un bac.
    private final int CRITIQUE = 3; //!< constante utilisée pour calculer l'état critique d'un bac (si celui-ci est vide au 3/4).

    /**
     * @brief Attributs GUI
     * @details Attributs qui s'occupent de l'affichage des paramètres d'un bac.
     */
    private final TextView remplissageBac; //!< attributs GUI qui affiche une barre de remplissage du bac.
    private final TextView produit; //!< attributs GUI qui affiche un texte qui contient le nom du produit.
    private final TextView hydrometrie; //!< attributs GUI qui affiche l'hygrométrie du bac.
    private final TextView prix; //!< attributs GUI qui affiche le prix du produit.

    /**
     * @brief Constructeur d'initialisation de la classe BacViewHolder.
     * @details Le constructeur BacViewHolder() initialise les attributs qui seront chargés d'afficher les vues
     * décritent dans le layout bac.xml.
     * @param itemView
     */
    public BacViewHolder(final View itemView)
    {
        super(itemView);

        remplissageBac = ((TextView)itemView.findViewById(R.id.remplissageBac));
        produit        = ((TextView)itemView.findViewById(R.id.produit));
        hydrometrie    = ((TextView)itemView.findViewById(R.id.hydrometrie));
        prix           = ((TextView)itemView.findViewById(R.id.prix));
    }

    /**
     * @brief Méthode qui affiche les bacs.
     * @details afficherBac(), affiche le bac qui lui est passé en paramètre.
     * @param bac
     */
    public void afficherBac(Bac bac)
    {
        if(bac.getPoidsActuel() < (bac.getPoidsTotalBac() / MOITIE) )
        {
            remplissageBac.setBackgroundColor(Color.parseColor("#FFF200"));
        }
        if(bac.getPoidsActuel() < (bac.getPoidsTotalBac() / CRITIQUE) )
        {
            remplissageBac.setBackgroundColor(Color.parseColor("#FF0000"));
        }

        produit.setText(bac.getTypeProduit().getNom());
        hydrometrie.setText(Integer.toString(bac.getHydrometrie())+" %");
        prix.setText(String.format("%.2f €", bac.getTypeProduit().getPrix()));
    }
}
