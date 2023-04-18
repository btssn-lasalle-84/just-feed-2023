/**
 * @file ActiviteInterventions.java
 * @brief Déclaration de l'activité ActiviteInterventions
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @brief Définition de la classe ActiviteInterventions.
 * @details La classe ActiviteIntervention \c ActiviteIntervention permet de lancer une seconde
 * activité pour l'application Android.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class ActiviteInterventions extends AppCompatActivity
{
    /**
     * Constantes
     */
    private static final String TAG = "_Interventions"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    List<Intervention>                 listeInterventions; //!< Liste des interventions à afficher
    BaseDeDonnees                      baseDeDonnees; //!< objet BaseDeDonnees pour pouvoir retrouver les informations
                                                       //!< sur les interventions dans une BDD.
    private RecyclerView               vueListeInterventions; //!< Affichage des Interventions
    private RecyclerView.Adapter       adapteurIntervention;  //!< Pour remplir les vues des Interventions
    private RecyclerView.LayoutManager layoutVueListeInterventions; //!< Positionnement des vues

    /**
     * @brief Méthode appelé à la création d'une seconde activité
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.interventions);

        // Récupère l'instance de BaseDeDonnees
        baseDeDonnees      = BaseDeDonnees.getInstance();
        baseDeDonnees.recupererInterventions();

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
        this.vueListeInterventions = (RecyclerView)findViewById(R.id.listeInterventions);
        this.vueListeInterventions.setHasFixedSize(true);
        this.layoutVueListeInterventions = new LinearLayoutManager(this);
        this.vueListeInterventions.setLayoutManager(this.layoutVueListeInterventions);
        this.adapteurIntervention = new AdaptateurIntervention(this.listeInterventions);
        this.vueListeInterventions.setAdapter(this.adapteurIntervention);
    }
}