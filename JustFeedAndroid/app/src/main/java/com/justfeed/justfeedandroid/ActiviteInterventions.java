package com.justfeed.justfeedandroid;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;

import java.util.List;
/**
 * @brief Définition de la classe ActiviteIntervention.
 * @details La classe ActiviteIntervention \c ActiviteIntervention permet de lancer une seconde activité
 * pour l'application Android.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class ActiviteInterventions extends AppCompatActivity
{
    /**
     * Attributs
     */
    List<Intervention> listeInterventions; //!< Liste des interventions à afficher
    BaseDeDonnees baseDeDonnees; //!< objet BaseDeDonnees pour pouvoir retrouver les informations sur les interventions dans une BDD.
    private RecyclerView vueListeInterventions; //!< Affichage des Interventions
    private RecyclerView.Adapter adapteurIntervention;  //!< Remplit les vues des Interventions
    private RecyclerView.LayoutManager layoutVueListeInterventions; //!< Positionne les vues

    /**
     * @brief Méthode appelé à la création d'une seconde activité
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_interventions);

        baseDeDonnees      = new BaseDeDonnees();
        listeInterventions = baseDeDonnees.recupererInterventions();

        initialiserVueInterventions();
    }

    /**
     * @brief Méthode appelée au démarrage après le onCreate() ou un restart
     * après un onStop()
     */
    @Override
    protected void onStart()
    {
        super.onStart();
    }

    /**
     * @brief Méthode appelée après onStart() ou après onPause()
     */
    @Override
    protected void onResume()
    {
        super.onResume();
    }

    /**
     * @brief Méthode appelée après qu'une boîte de dialogue s'est affichée (on
     * reprend sur un onResume()) ou avant onStop() (activité plus visible)
     */
    @Override
    protected void onPause()
    {
        super.onPause();
    }

    /**
     * @brief Méthode appelée lorsque l'activité n'est plus visible
     */
    @Override
    protected void onStop()
    {
        super.onStop();
    }

    /**
     * @brief Méthode appelée à la destruction de l'application (après onStop()
     * et détruite par le système Android)
     */
    @Override
    protected void onDestroy()
    {
        super.onDestroy();
    }

    /**
     * @brief Méthode qui initialise la vue des Interventions
     * @details initialiserVueInterventions() initialise les attributs chargés
     * d'afficher les interventions, de placer les interventions et de remplir les vues
     * des interventions
     */
    private void initialiserVueInterventions()
    {
        this.vueListeInterventions       = (RecyclerView)findViewById(R.id.listeInterventions);
        this.vueListeInterventions.setHasFixedSize(true);
        this.layoutVueListeInterventions = new LinearLayoutManager(this);
        this.vueListeInterventions.setLayoutManager(this.layoutVueListeInterventions);
        this.adapteurIntervention        = new InterventionAdapter(this.listeInterventions);
        this.vueListeInterventions.setAdapter(this.adapteurIntervention);
    }
}