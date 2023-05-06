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
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import java.util.ArrayList;
import java.util.List;

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
    private final String TOUTES   = "Toutes";    //!< Constante utilisée pour configurer le filtre.
    private final String A_FAIRE = "A faire"; //!< Constante utilisée pour configurer le filtre.
    private final String EN_COURS = "En cours";  //!< Constante utilisée pour configurer le filtre.
    private final String VALIDEES = "Validé";    //!< Constante utilisée pour configurer le filtre.

    /**
     * Attributs
     */
    private Intervention.Etats   etat;               //!< Etat qui sert à trier les interventions
    private List<Intervention>   listeInterventions; //!< Liste des interventions à afficher
    private Handler              handler;            //!< Le handler utilisé par l'activité
    private BaseDeDonnees        baseDeDonnees;      //!< Identifiants pour la base de données
    private RecyclerView         vueListeInterventions; //!< Affichage des Interventions
    private RecyclerView.Adapter adapteurIntervention = null;  //!< Pour remplir les vues des Interventions
    private RecyclerView.LayoutManager layoutVueListeInterventions; //!< Positionnement des vues
    private Spinner                    menuEtats;      //!< Menu pour trier les interventions
    private SwipeRefreshLayout         rafraichisseur; //!< Pull-to-refresh

    /**
     * @brief Méthode appelé à la création d'une seconde activité
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.interventions);

        initialiserHandler();
        this.menuEtats = (Spinner)findViewById(R.id.menuEtats);
        this.menuEtats.setAdapter(
          new ArrayAdapter<Intervention.Etats>(this,
                                               android.R.layout.simple_spinner_item,
                                               Intervention.Etats.values()));
        etat          = Intervention.Etats.A_FAIRE;
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
    private void initialiserVueInterventions(List<Intervention> interventions)
    {
        this.vueListeInterventions = (RecyclerView)findViewById(R.id.listeInterventions);
        this.vueListeInterventions.setHasFixedSize(true);
        this.layoutVueListeInterventions = new LinearLayoutManager(this);
        this.vueListeInterventions.setLayoutManager(this.layoutVueListeInterventions);
        menuEtats.setSelection(1); // Intervention.Etats.A_FAIRE
        menuEtats.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View vue, int position, long id)
            {
                String nouvelEtat = parent.getItemAtPosition(position).toString();
                switch(nouvelEtat)
                {
                    case A_FAIRE:
                        etat = Intervention.Etats.A_FAIRE;
                        break;
                    case EN_COURS:
                        etat = Intervention.Etats.EN_COURS;
                        break;
                    case VALIDEES:
                        etat = Intervention.Etats.VALIDEES;
                        break;
                    case TOUTES:
                        etat = Intervention.Etats.TOUTES;
                        break;
                }
                Log.d(TAG, "onItemSelected() - état : " + etat);
                VueIntervention.changerEtatAFiltrer(etat);
                afficherInterventions(interventions);
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView)
            {
            }
        });
        this.rafraichisseur = (SwipeRefreshLayout)findViewById(R.id.rafraichisseur);
        rafraichisseur.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh()
            {
                Log.d(TAG, "_onRefresh()");
                rafraichisseur.setRefreshing(false);
                baseDeDonnees.recupererInterventions();
            }
        });
    }

    /**
     * @brief Affiche les interventions
     */
    private void afficherInterventions(List<Intervention> interventions)
    {
        Log.d(TAG, "afficherInterventions() nb interventions = " + interventions.size());
        vueListeInterventions.removeAllViews();
        this.listeInterventions   = interventions;
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
                // Log.d(TAG, "[Handler] id message = " + message.what);
                // Log.d(TAG, "[Handler] message = " + message.obj.toString());

                if(message.what == BaseDeDonnees.REQUETE_SQL_SELECT_INTERVENTIONS)
                {
                    Log.d(TAG, "[Handler] REQUETE_SQL_SELECT_INTERVENTIONS");
                    initialiserVueInterventions((ArrayList)message.obj);
                }
            }
        };
    }
}