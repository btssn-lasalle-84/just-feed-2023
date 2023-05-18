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
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.io.Serializable;
import java.sql.Array;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
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
    public static final String PREFERENCES = "justfeed"; //!< Clé pour le titre du stockage
    public static final String PREFERENCES_NOM_OPERATEUR = "nomOperateur"; //!< Clé pour le nom de l'opérateur
    public static final String PREFERENCES_PRENOM_OPERATEUR = "prenomOperateur"; //!< Clé pour le prénom de l'opérateur
    public static final String PREFERENCES_ID_OPERATEUR = "idOperateur"; //!< Clé pour l'id de l'opérateur
    public static final String PREFERENCES_IDENTIFIANT = "identifiant"; //!< Clé pour l'identifiant de l'opérateur
    public static final String PREFERENCES_EMAIL = "email"; //!< Clé pour l'email de l'opérateur


    /**
     * Attributs
     */
    private List<Distributeur>   listeDistributeurs;    //!< Liste des distributeurs
    private BaseDeDonnees        baseDeDonnees;         //!< Identifiants pour la base de données
    private Handler              handler = null;        //<! Le handler utilisé par l'activité
    private RecyclerView         vueListeDistributeurs; //!< Affichage de la liste des distributeurs
    private RecyclerView.Adapter adapteurDistributeur;  //!< Remplit les vues des distributeurs
    private RecyclerView.LayoutManager layoutVueListeDistributeurs; //!< Positionne les vues
    private Operateur operateur; //!< Opérateur qui va être utilisé
    private String nomOperateur; //!< Nom de l'opérateur
    private String prenomOperateur; //!< Prénom de l'opérateur
    private String identifiantOperateur; //!< Identifiant de l'opérateur
    private String emailOperateur; //!< Email de l'opérateur
    private int idOperateur; //!< numéro de  l'opérateur
    private SharedPreferences preferencesPartagees; //!< système de persistance des données pour l'application

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

        initialiserGUI();
        initialiserHandler();
        initialiserBaseDeDonnees();

        baseDeDonnees.recupererDistributeurs();
        //TODO baseDeDonnees.recupererOperateurs();
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
        baseDeDonnees.setHandler(handler);
        baseDeDonnees.recupererDistributeurs();
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

        preferencesPartagees.edit().putString(PREFERENCES_NOM_OPERATEUR, operateur.getNom()).apply();
        preferencesPartagees.edit().putString(PREFERENCES_PRENOM_OPERATEUR, operateur.getPrenom()).apply();
        preferencesPartagees.edit().putInt(PREFERENCES_ID_OPERATEUR, operateur.getIdOperateur()).apply();
        preferencesPartagees.edit().putString(PREFERENCES_IDENTIFIANT, operateur.getIdentifiant()).apply();
        preferencesPartagees.edit().putString(PREFERENCES_EMAIL, operateur.getEmail()).apply();
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
        /**
         * TODO condition pour vérifier si l'opérateur a été récupéré localement
         * sinon on instancie operateur avec l'opérateur choisie dans la liste
         */
    }

    /**
     * @brief Initialise laccès à la base de données MySQL
     */
    private void initialiserBaseDeDonnees()
    {
        // Récupère l'instance de BaseDeDonnees
        baseDeDonnees = BaseDeDonnees.getInstance(handler);
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
    }

    /**
     * @brief Met à jour l'affichage de la liste des distributeurs
     */
    private void afficherDistributeurs(List<Distributeur> distributeurs)
    {
        Log.d(TAG, "afficherDistributeurs() nb distributeurs = " + distributeurs.size());
        this.listeDistributeurs = distributeurs;
        if(this.adapteurDistributeur == null)
        {
            this.adapteurDistributeur = new AdaptateurDistributeur(this.listeDistributeurs);
            this.vueListeDistributeurs.setAdapter(this.adapteurDistributeur);
        }
        adapteurDistributeur.notifyDataSetChanged();
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
                        break;
                    case BaseDeDonnees.REQUETE_SQL_SELECT_DISTRIBUTEURS:
                        Log.d(TAG, "[Handler] REQUETE_SQL_SELECT_DISTRIBUTEURS");
                        afficherDistributeurs((ArrayList)message.obj);
                        break;
                }
            }
        };
    }

    private boolean operateurLocalExiste() {
        preferencesPartagees = getBaseContext().getSharedPreferences(PREFERENCES, MODE_PRIVATE);
        if(preferencesPartagees.contains(PREFERENCES_NOM_OPERATEUR))
        {
            nomOperateur = preferencesPartagees.getString(PREFERENCES_NOM_OPERATEUR, "");
        }
        if(preferencesPartagees.contains(PREFERENCES_PRENOM_OPERATEUR))
        {
            prenomOperateur = preferencesPartagees.getString(PREFERENCES_PRENOM_OPERATEUR, "");
        }
        if(preferencesPartagees.contains(PREFERENCES_ID_OPERATEUR))
        {
            idOperateur = preferencesPartagees.getInt(PREFERENCES_ID_OPERATEUR, -1);
        }
        if(preferencesPartagees.contains(PREFERENCES_IDENTIFIANT))
        {
            identifiantOperateur = preferencesPartagees.getString(PREFERENCES_IDENTIFIANT, "");
        }
        if(preferencesPartagees.contains(PREFERENCES_EMAIL))
        {
            emailOperateur = preferencesPartagees.getString(PREFERENCES_EMAIL,"");
        }
        if(idOperateur != -1) {
            operateur = new Operateur(
                    nomOperateur,
                    prenomOperateur,
                    identifiantOperateur,
                    emailOperateur,
                    idOperateur);

            return true;
        }
        else
        {
            return false;
        }
    }
}