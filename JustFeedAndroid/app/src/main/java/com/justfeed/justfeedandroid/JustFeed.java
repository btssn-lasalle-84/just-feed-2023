/**
 * @file JustFeed.java
 * @brief Déclaration de l'activité principale JustFeed
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;

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
    private static final String TAG = "_JustFeed"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private List<Distributeur>   listeDistributeurs;    //!< Liste des distributeurs
    private BaseDeDonnees        baseDeDonnees;         //!< Identifiants pour la base de données
    private Handler              handler = null;        //<! Le handler utilisé par l'activité
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
        setContentView(R.layout.justfeed);
        Log.d(TAG, "onCreate()");

        initialiserHandler();

        // Récupère l'instance de BaseDeDonnees
        baseDeDonnees      = BaseDeDonnees.getInstance(handler);
        listeDistributeurs = baseDeDonnees.recupererDistributeurs();

        initialiserGUI();

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

    /**
     * @brief Initialise la vue de l'activité
     */
    private void initialiserGUI()
    {
        boutonInterventions = (Button)findViewById(R.id.boutonInterventions);
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
        this.adapteurDistributeur = new AdaptateurDistributeur(this.listeDistributeurs);
        this.vueListeDistributeurs.setAdapter(this.adapteurDistributeur);
    }

    /**
     * @brief Met à jour l'affichage de la liste des distributeurs
     */
    private void afficherDistributeurs()
    {
        // this.adapteurDistributeur.notifyDataSetChanged();
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
                Log.d(TAG, "[Handler] id message = " + message.what);
                Log.d(TAG, "[Handler] message = " + message.obj.toString());

                switch(message.what)
                {
                    case BaseDeDonnees.CONNEXION_OK:
                        Log.d(TAG, "[Handler] CONNEXION_OK");
                        /**
                         * Exemples de requêtes
                         *
                         * baseDeDonnees.executerRequete("UPDATE Distributeur SET hygrometrie = '18'
                         * WHERE Distributeur.idDistributeur = '1'");
                         * baseDeDonnees.selectionner("SELECT * FROM Distributeur");
                         */
                        break;
                    case BaseDeDonnees.CONNEXION_ERREUR:
                        Log.d(TAG, "[Handler] CONNEXION_ERREUR");
                        break;
                    case BaseDeDonnees.DECONNEXION_OK:
                        Log.d(TAG, "[Handler] DECONNEXION_OK");
                        break;
                    case BaseDeDonnees.DECONNEXION_ERREUR:
                        Log.d(TAG, "[Handler] DECONNEXION_ERREUR");
                        break;
                    case BaseDeDonnees.REQUETE_SQL_OK:
                        Log.d(TAG, "[Handler] REQUETE_SQL_OK");
                        break;
                    case BaseDeDonnees.REQUETE_SQL_ERREUR:
                        Log.d(TAG, "[Handler] REQUETE_SQL_ERREUR");
                        break;
                    case BaseDeDonnees.REQUETE_SQL_SELECT:
                        Log.d(TAG, "[Handler] REQUETE_SQL_SELECT");
                        /**
                         * Exemple de traitement d'une requête SELECT
                         *
                         * ResultSet resultatRequete = (ResultSet)message.obj;
                         * try
                         * {
                         *    while(resultatRequete.next())
                         *    {
                         *        int numero = resultatRequete.getRow();
                         *        Log.v(TAG, "[Handler] resultatRequete numéro = " + numero);
                         *    }
                         * }
                         * catch(SQLException e)
                         * {
                         *    e.printStackTrace();
                         * }
                         */
                        break;
                }
            }
        };
    }
}