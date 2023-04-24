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
    private static final String TAG = "_ActiviteInterventions"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private List<Intervention> listeInterventions; //!< Liste des interventions à afficher
    private Handler              handler;               //!< Le handler utilisé par l'activité
    private BaseDeDonnees        baseDeDonnees;         //!< Identifiants pour la base de données
    private RecyclerView         vueListeInterventions; //!< Affichage des Interventions
    private RecyclerView.Adapter adapteurIntervention;  //!< Pour remplir les vues des Interventions
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

        initialiserVueInterventions();
        initialiserHandler();

        baseDeDonnees = BaseDeDonnees.getInstance(handler);
        baseDeDonnees.setHandler(handler);
        baseDeDonnees.recupererInterventions();
    }

    /**
     * @brief Méthode appelée au démarrage après le onCreate() ou un restart
     * après un onStop()
     */
    @Override
    protected void onStart()
    {
        super.onStart();
        baseDeDonnees.setHandler(handler);
    }

    /**
     * @brief Méthode appelée après onStart() ou après onPause()
     */
    @Override
    protected void onResume()
    {
        super.onResume();
        baseDeDonnees.setHandler(handler);
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
    }

    /**
     * @brief Affiche les interventions
     */
    private void afficherInterventions(List<Intervention> interventions)
    {
        Log.d(TAG, "afficherInterventions() nb interventions = " + interventions.size());
        this.listeInterventions = interventions;
        if(this.adapteurIntervention == null)
        {
            this.adapteurIntervention = new AdaptateurIntervention(this.listeInterventions);
            this.vueListeInterventions.setAdapter(this.adapteurIntervention);
        }
        adapteurIntervention.notifyDataSetChanged();
    }

    /**
     * @brief Initialise la gestion des messages en provenance des threads
     */
    private void initialiserHandler()
    {
        this.handler = new Handler(this.getMainLooper()) {
            @Override
            public void handleMessage(@NonNull Message message)
            {
                //Log.d(TAG, "[Handler] id message = " + message.what);
                //Log.d(TAG, "[Handler] message = " + message.obj.toString());

                if(message.what == BaseDeDonnees.REQUETE_SQL_SELECT_INTERVENTIONS)
                {
                    Log.d(TAG, "[Handler] REQUETE_SQL_SELECT_INTERVENTIONS");
                    afficherInterventions((ArrayList)message.obj);
                }
            }
        };
    }
}