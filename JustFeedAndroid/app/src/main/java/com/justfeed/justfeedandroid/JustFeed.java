/**
 * @file JustFeed.java
 * @brief Déclaration de l'activité principale JustFeed
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @class JustFeed
 * @brief L'activité principale
 */
public class JustFeed extends AppCompatActivity
{
    /**
     * Constantes
     */
    private static final String TAG = "_JustFeed"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private List<Distributeur>   listeDistributeurs;    //!< Liste des distributeurs
    private BaseDeDonnees        baseDeDonnees;         //!< Identifiants pour la base de données
    private RecyclerView         vueListeDistributeurs; //!< Affichage de la liste des distributeurs
    private RecyclerView.Adapter adapteurDistributeur;  //!< Remplit les vues des distributeurs
    private RecyclerView.LayoutManager layoutVueListeDistributeurs; //!< Positionne les vues
    /**
     * Ressources GUI
     */
    private Button boutonInterventions; //!< Bouton pour démarrer une nouvelle activity qui liste
                                        //!< les interventions

    /**
     * @brief Méthode appelée à la création de l'activité
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d(TAG, "onCreate()");

        boutonInterventions = (Button)findViewById(R.id.boutonInterventions);
        baseDeDonnees       = new BaseDeDonnees();
        listeDistributeurs  = baseDeDonnees.recupererDistributeurs();

        boutonInterventions.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View vue)
            {
                Intent activiteIntervention =
                  new Intent(JustFeed.this, ActiviteInterventions.class);
                startActivity(activiteIntervention);
            }
        });

        initialiserVueListeDistributeurs();
        afficherDistributeurs();
    }

    /**
     * @brief Méthode appelée au démarrage après le onCreate() ou un restart
     * après un onStop()
     */
    @Override
    protected void onStart()
    {
        super.onStart();
        Log.d(TAG, "onStart()");
    }

    /**
     * @brief Méthode appelée après onStart() ou après onPause()
     */
    @Override
    protected void onResume()
    {
        super.onResume();
        Log.d(TAG, "onResume()");
    }

    /**
     * @brief Méthode appelée après qu'une boîte de dialogue s'est affichée (on
     * reprend sur un onResume()) ou avant onStop() (activité plus visible)
     */
    @Override
    protected void onPause()
    {
        super.onPause();
        Log.d(TAG, "onPause()");
    }

    /**
     * @brief Méthode appelée lorsque l'activité n'est plus visible
     */
    @Override
    protected void onStop()
    {
        super.onStop();
        Log.d(TAG, "onStop()");
    }

    /**
     * @brief Méthode appelée à la destruction de l'application (après onStop()
     * et détruite par le système Android)
     */
    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        Log.d(TAG, "onDestroy()");
    }

    public void visualiserInterventions()
    {
        /**
         * @todo méthode qui invoque la méthode afficherInterventions() pour créer une seconde
         * activité
         */
    }

    /**
     * @brief Initialise la vue pour afficher la liste des distributeurs
     */
    private void initialiserVueListeDistributeurs()
    {
        this.vueListeDistributeurs = (RecyclerView)findViewById(R.id.listeDistributeurs);
        this.vueListeDistributeurs.setHasFixedSize(true);
        this.layoutVueListeDistributeurs = new LinearLayoutManager(this);
        this.vueListeDistributeurs.setLayoutManager(this.layoutVueListeDistributeurs);
        this.adapteurDistributeur = new DistributeurAdapter(this.listeDistributeurs);
        this.vueListeDistributeurs.setAdapter(this.adapteurDistributeur);
    }

    /**
     * @brief Met à jour l'affichage de la liste des distributeurs
     */
    private void afficherDistributeurs()
    {
        // this.adapteurDistributeur.notifyDataSetChanged();
    }
}