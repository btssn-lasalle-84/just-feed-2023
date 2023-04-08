package com.justfeed.justfeedandroid;

import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;
/**
 * @brief Définition de la classe DistributeurAdapter.
 * @details La classe DistributuerAdapter \c DistributeurAdapter permet de remplir les vues
 * définies par la classe DistributeurViewHolder.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class DistributeurAdapter extends RecyclerView.Adapter<DistributeurViewHolder>
{
    private List<Distributeur> distributeurs         = null; //!< Liste des distributeurs à afficher.
    private RecyclerView.RecycledViewPool partageVue = new RecyclerView.RecycledViewPool(); //!< partage des vues entre plusieurs recyclerview.

    /**
     * @brief Constructeur d'initialisation de la classe DistributeurAdapter.
     * @param distributeurs
     */
    public DistributeurAdapter(List<Distributeur> distributeurs)
    {
        if(distributeurs != null)
        {
            this.distributeurs = distributeurs;
        }
    }

    /**
     * @brief Méthode onCreateViewHolder.
     * @details onCreateViewHolder() instancie un nouvel objet de classe DistributeurViewHolder.
     * @param parent   The ViewGroup into which the new View will be added after it is bound to
     *                 an adapter position.
     * @param viewType The view type of the new View.
     * @return une instance de la classe DistributeurViewHolder.
     */
    @NonNull
    @Override
    public DistributeurViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View view = inflater.inflate(R.layout.distributeur, parent, false);

        return new DistributeurViewHolder(view);
    }

    /**
     * @brief Méthode qui remplie la vues de l'instance de la classe DistributeurViewHolder.
     * @param holder   The ViewHolder which should be updated to represent the contents of the
     *                 item at the given position in the data set.
     * @param position The position of the item within the adapter's data set.
     */
    @Override
    public void onBindViewHolder(@NonNull DistributeurViewHolder holder, int position)
    {
        Distributeur distributeur = distributeurs.get(position);
        holder.afficherDistributeur(distributeur);
        LinearLayoutManager layoutVueListesBacs = new LinearLayoutManager(
                holder.modifierVueListeBacs().getContext(),
                LinearLayoutManager.HORIZONTAL,
                false
        );
        layoutVueListesBacs.setInitialPrefetchItemCount(distributeur.getListeBacs().size());
        BacAdapter adapteurBacs = new BacAdapter(distributeur.getListeBacs());
        holder.modifierVueListeBacs().setLayoutManager(layoutVueListesBacs);
        holder.modifierVueListeBacs().setAdapter(adapteurBacs);
        holder.modifierVueListeBacs().setRecycledViewPool(partageVue);
    }

    /**
     * @brief Méthode qui compte le nombre d'items de la liste distributeurs.
     * @return la taille de la liste distributeurs.
     */
    @Override
    public int getItemCount()
    {
        if(distributeurs != null)
        {
            return distributeurs.size();
        }
        return 0;
    }
}
