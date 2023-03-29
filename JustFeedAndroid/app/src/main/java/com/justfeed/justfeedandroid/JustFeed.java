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
        this.vueListeDistributeurs = (RecyclerView) findViewById(R.id.listeDistributeurs);
        this.vueListeDistributeurs.setHasFixedSize(true);
        this.layoutVueListeDistributeurs = new LinearLayoutManager(this);
        this.vueListeDistributeurs.setLayoutManager(this.layoutVueListeDistributeurs);
        this.adapteurDistributeur = new DistributeurAdapter(this.listeDistributeurs);
        this.vueListeDistributeurs.setAdapter(this.adapteurDistributeur);
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
        Log.d(TAG, "recupererDistributeurs()");
        List<Produit> listeProduits1 = Arrays.asList(
                new Produit(0.70, 0.001, 0.004, "cacahuètes"),
                new Produit(0.35, 0.00005, 0.0003, "riz"),
                new Produit(0.50, 0.002, 0.003,"fèves")
        );

        List<Produit> listeProduits2 = Arrays.asList(
                new Produit(3.10, 0.003, 0.002, "Banane séchée"),
                new Produit(3.20, 0.008, 0.004, "Abricot sec"),
                new Produit(2.15, 0.002, 0.001,"raisin sec")
        );

        List<Produit> listeProduits3 = Arrays.asList(
                new Produit(3.55, 0.0006, 0.0005, "pistache"),
                new Produit(1.45, 0.00035, 0.0004, "maïs séché"),
                new Produit(4.49, 0.00006, 0.0005,"graine de café")
        );

        Map<Produit, Double> bacsDistributeur1 = new HashMap<Produit, Double>();
        bacsDistributeur1.put(listeProduits1.get(0), 1.5);
        bacsDistributeur1.put(listeProduits1.get(1), 0.8);
        bacsDistributeur1.put(listeProduits1.get(2), 1.5);

        Map<Produit, Double> bacsDistributeur2 = new HashMap<Produit, Double>();
        bacsDistributeur2.put(listeProduits2.get(0), 5.0);
        bacsDistributeur2.put(listeProduits2.get(1), 14.0);
        bacsDistributeur2.put(listeProduits2.get(2), 10.5);

        Map<Produit, Double> bacsDistributeur3 = new HashMap<Produit, Double>();
        bacsDistributeur3.put(listeProduits3.get(0), 9.6);
        bacsDistributeur3.put(listeProduits3.get(1), 4.5);
        bacsDistributeur3.put(listeProduits3.get(2), 1.0);

        this.listeDistributeurs = Arrays.asList(
                new Distributeur(8456, bacsDistributeur1, 2, listeProduits1),
                new Distributeur(8457, bacsDistributeur2, 4, listeProduits2),
                new Distributeur(8458, bacsDistributeur3, 2, listeProduits3)
        );
    }

    private void recupererInterventions()
    {
        /**
         * @todo récupérer les informations des interventions sur la base de données
         */
    }
}