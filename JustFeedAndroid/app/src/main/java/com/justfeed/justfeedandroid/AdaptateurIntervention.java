/**
 * @file AdaptateurIntervention.java
 * @brief Déclaration de la classe AdaptateurIntervention
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
 * @brief Définition de la classe AdaptateurIntervention.
 * @details La classe AdaptateurIntervention \c InterventionAdapter permet de remplir les vues gérer
 * par la classe VueIntervention.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class AdaptateurIntervention extends RecyclerView.Adapter<VueIntervention>
{
    private List<Intervention> interventions = null; //!< Liste des interventions à afficher.
    private int idOperateur; //!< Identifiant de l'opérateur

    /**
     * @brief Constructeur d'initialisation de la classe InterventionAdapter
     * @param interventions
     */
    public AdaptateurIntervention(List<Intervention> interventions)
    {
        if(interventions != null)
        {
            this.interventions = interventions;
        }
    }

    /**
     * @brief Méthode qui créer une nouvelle instance de la classe InterventionViewHolder.
     * @param parent   The ViewGroup into which the new View will be added after it is bound to
     *                 an adapter position.
     * @param viewType The view type of the new View.
     * @return l'instance d'une classe InterventionViewHolder.
     */
    @NonNull
    @Override
    public VueIntervention onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View           view     = inflater.inflate(R.layout.intervention, parent, false);

        return new VueIntervention(view);
    }

    /**
     * @brief Méthode qui remplie les vues de l'instance de la classe InterventionViewHolder.
     * @param holder   The ViewHolder which should be updated to represent the contents of the
     *                 item at the given position in the data set.
     * @param position The position of the item within the adapter's data set.
     */
    @Override
    public void onBindViewHolder(@NonNull VueIntervention holder, int position)
    {
        Intervention intervention = interventions.get(position);
        holder.afficherInterventions(intervention);
    }

    /**
     * @brief Méthode qui compte le nombre d'items de la liste d'interventions.
     * @return la taille de la liste des interventions.
     */
    @Override
    public int getItemCount()
    {
        if(interventions != null)
        {
            return interventions.size();
        }
        return 0;
    }
}