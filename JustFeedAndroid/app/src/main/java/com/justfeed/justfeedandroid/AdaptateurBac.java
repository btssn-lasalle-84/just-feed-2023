/**
 * @file AdaptateurBac.java
 * @brief Déclaration de la classe AdaptateurBac
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

/**
 * @brief Définition de la classe AdaptateurBac.
 * @details La classe AdaptateurBac \c AdaptateurBac permet de créer une instance de la classe
 * BacViewHolder (cf. BacViewHolder) et elle remplit les vues de la classe VueBac.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class AdaptateurBac extends RecyclerView.Adapter<VueBac>
{
    private List<Bac> listeBacs = null; //!< Liste des bacs à afficher

    /**
     * @brief Constructeur par défaut de la classe BacAdapter.
     * @param listeBacs
     */
    public AdaptateurBac(List<Bac> listeBacs)
    {
        if(listeBacs != null)
        {
            this.listeBacs = listeBacs;
        }
    }

    /**
     * @brief Méthode chargé de créer une instance de la classe BacViewHolder.
     * @details onCreateViewHolder() créer une instance de la classe BacViewHolder
     * et lui passe en paramètre le contexte de l'activité actuelle (UID).
     * @param parent   The ViewGroup into which the new View will be added after it is bound to
     *                 an adapter position.
     * @param viewType The view type of the new View.
     * @return BacViewHolder , une instance de la classe BacViewHolder.
     */
    @NonNull
    @Override
    public VueBac onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View           vue      = inflater.inflate(R.layout.bac, parent, false);

        return new VueBac(vue);
    }

    /**
     * @brief Méthode qui remplie les vues de la classe BacViewHolder.
     * @param holder   The ViewHolder which should be updated to represent the contents of the
     *                 item at the given position in the data set.
     * @param position The position of the item within the adapter's data set.
     */
    @Override
    public void onBindViewHolder(@NonNull VueBac holder, int position)
    {
        Bac bac = listeBacs.get(position);
        holder.afficherBac(bac);
    }

    /**
     * @brief Méthode qui compte le nombre d'items dans la liste listeBacs.
     * @return la taille de la liste de bacs.
     */
    @Override
    public int getItemCount()
    {
        if(listeBacs != null)
        {
            return listeBacs.size();
        }

        return 0;
    }
}
