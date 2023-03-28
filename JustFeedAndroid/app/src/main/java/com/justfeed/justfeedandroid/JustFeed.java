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

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.Arrays;
import java.util.List;

/**
 * @class JustFeed
 * @brief L'activité principale
 */
public class JustFeed extends AppCompatActivity
{
    /**
     * Constantes
     */
    private static final String TAG = "_JustFeed_"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private List<Intervention> vueListeInterventions; //!< Liste des interventions
    private List<Distributeur> vueListeDistributeurs; //!< Liste des distributeurs
    private BaseDeDonnees baseDeDonnees; //!< Identifiants pour la base de données
    private RecyclerView recyclerView;
    private RecyclerView.Adapter adapter;
    private RecyclerView.LayoutManager layoutVueListeDistributeurs;
    /**
     * Ressources GUI
     */

    /**
     * @brief Méthode appelée à la création de l'activité
     */
    @Override protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        vueListeDistributeurs = recupererDistributeurs();
        recyclerView = (RecyclerView) findViewById(R.id.listeDistributeurs);
        recyclerView.setHasFixedSize(true);
        layoutVueListeDistributeurs = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutVueListeDistributeurs);
        adapter = new DistributeurAdapter(vueListeDistributeurs);
        recyclerView.setAdapter(adapter);
        Log.d(TAG, "onCreate()");
    }

    /**
     * @brief Méthode appelée au démarrage après le onCreate() ou un restart
     * après un onStop()
     */
    @Override protected void onStart()
    {
        super.onStart();
        Log.d(TAG, "onStart()");
    }

    /**
     * @brief Méthode appelée après onStart() ou après onPause()
     */
    @Override protected void onResume()
    {
        super.onResume();
        Log.d(TAG, "onResume()");
    }

    /**
     * @brief Méthode appelée après qu'une boîte de dialogue s'est affichée (on
     * reprend sur un onResume()) ou avant onStop() (activité plus visible)
     */
    @Override protected void onPause()
    {
        super.onPause();
        Log.d(TAG, "onPause()");
    }

    /**
     * @brief Méthode appelée lorsque l'activité n'est plus visible
     */
    @Override protected void onStop()
    {
        super.onStop();
        Log.d(TAG, "onStop()");
    }

    /**
     * @brief Méthode appelée à la destruction de l'application (après onStop()
     * et détruite par le système Android)
     */
    @Override protected void onDestroy()
    {
        super.onDestroy();
        Log.d(TAG, "onDestroy()");
    }

    private List<Distributeur> recupererDistributeurs()
    {
        /**
         * @todo récupérer les informations des distributeurs sur la base de données
         */
        List<Distributeur> distributeurs = Arrays.asList(
                new Distributeur(8456, 5, 3, 2, new Produit(2, 2, "cacahuètes")),
                new Distributeur(8457, 10, 8, 4, new Produit(3, 1, "riz")),
                new Distributeur(8458, 8, 8, 2, new Produit(4, 2, "fèves"))
        );

        return distributeurs;
    }
}