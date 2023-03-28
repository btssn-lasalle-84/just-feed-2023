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
    private List<Intervention> listeInterventions; //!< Liste des interventions
    private List<Distributeur> listeDistributeurs; //!< Liste des distributeurs
    private BaseDeDonnees baseDeDonnees; //!< Identifiants pour la base de données
    private RecyclerView vueListeDistributeurs; //!< Affichage de la liste des distributeurs
    private RecyclerView.Adapter adapteurDistributeur; //!< Remplit les vues des distributeurs
    private RecyclerView.LayoutManager layoutVueListeDistributeurs; //!< Positionne les vues
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
        recupererDistributeurs();
        vueListeDistributeurs = (RecyclerView) findViewById(R.id.listeDistributeurs);
        vueListeDistributeurs.setHasFixedSize(true);
        layoutVueListeDistributeurs = new LinearLayoutManager(this);
        vueListeDistributeurs.setLayoutManager(layoutVueListeDistributeurs);
        adapteurDistributeur = new DistributeurAdapter(listeDistributeurs);
        vueListeDistributeurs.setAdapter(adapteurDistributeur);
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

    public void visualiserInterventions()
    {
        /**
         * @todo méthode qui invoque la méthode afficherInterventions() pour créer une seconde activité
         */
    }

    private void recupererDistributeurs()
    {
        /**
         * @todo récupérer les informations des distributeurs sur la base de données
         */
        List<Produit> produits = Arrays.asList(
                new Produit(2, 0.005, 0.00003, "cacahuètes"),
                new Produit(3, 0.001, 0.00001, "riz"),
                new Produit(4, 0.004, 0.00003,"fèves")
        );

        Map<Produit, String> bacs = new HashMap<Produit, String>();
        bacs.put(produits.get(0), "1.3");
        bacs.put(produits.get(1), "0.8");
        bacs.put(produits.get(2), "1.06");

        this.listeDistributeurs = Arrays.asList(
                new Distributeur(8456, bacs, 2, produits),
                new Distributeur(8457, bacs, 4, produits),
                new Distributeur(8458, bacs, 2, produits)
        );
    }

    private void recupererInterventions()
    {
        /**
         * @todo récupérer les informations des interventions sur la base de données
         */
    }
}