/**
 * @file JustFeed.java
 * @brief Déclaration de l'activité principale JustFeed
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import static android.app.usage.UsageEvents.Event.NONE;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.SpannableString;
import android.text.style.ForegroundColorSpan;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.SubMenu;
import android.widget.Button;
import android.widget.PopupMenu;

import java.util.ArrayList;
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
    private static final String TAG = "_JustFeed";      //!< TAG pour les logs (cf. Logcat)
    private static final int INDEX_CLIENT_ID = 0; //!< Index de l'id client dans la liste des identifiants pour MQTT
    private static final int INDEX_MENU_OPERATEURS = 0; //!< Index de l'item Opérateurs dans le menu
    private static final int INDEX_MDP = 1; //!< Index du mot de passe dans la liste des identifiants pour MQTT
    private static final int INDEX_HOSTNAME = 2; //!< Index du hostname dans la liste des identifiants pour MQTT
    public static final String PREFERENCES         = "justfeed"; //!< Clé pour le titre du stockage
    public static final String PREFERENCES_ID_OPERATEUR =
      "idOperateur"; //!< Clé pour l'id de l'opérateur
    public static final int OPERATEUR_NON_DEFINI =
      -1; //!< L'id de l'opérateur actif n'est pas défini

    /**
     * Attributs
     */
    private List<Distributeur> listeDistributeurs;                 //!< Liste des distributeurs
    private List<Operateur>    listeOperateurs;                    //!< Liste des opérateurs
    private int                idOperateur = OPERATEUR_NON_DEFINI; //!< Identifiant de l'opérateur
    private ClientMQTT         clientMQTT; //!< Client MQTT pour communiquer avec le broker MQTT
    private BaseDeDonnees      baseDeDonnees;         //!< Identifiants pour la base de données
    private Handler            handler = null;        //<! Le handler utilisé par l'activité
    private RecyclerView       vueListeDistributeurs; //!< Affichage de la liste des distributeurs
    private RecyclerView.Adapter       adapteurDistributeur; //!< Remplit les vues des distributeurs
    private RecyclerView.LayoutManager layoutVueListeDistributeurs; //!< Positionne les vues
    private SharedPreferences          preferencesPartagees =
      null; //!< système de persistance des données pour l'application

    /**
     * Ressources GUI
     */
    private Button boutonInterventions; //!< Bouton pour démarrer une nouvelle activity qui liste
                                        //!< les interventions
    private Menu menu;                  //!< Menu de l'application

    /**
     * @brief Méthode appelée à la création de l'activité
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.justfeed);
        Log.d(TAG, "onCreate()");

        chargerPreferences();

        initialiserVueListeDistributeurs();
        initialiserHandler();
        initialiserBaseDeDonnees();

        baseDeDonnees.recupererOperateurs();
        baseDeDonnees.recupererDistributeurs();
        baseDeDonnees.recupererIdentifiantsTTS();
    }

    /**
     * @brief Méthode appelée pour initialiser le menu
     */
    public boolean onCreateOptionsMenu(Menu menu)
    {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);

        return true;
    }

    /**
     * @brief Initialise le sous menu
     */
    @Override
    public boolean onPrepareOptionsMenu(Menu menu)
    {
        SubMenu sousMenu = menu.getItem(INDEX_MENU_OPERATEURS).getSubMenu();
        sousMenu.clear();

        if(listeOperateurs != null)
        {
            int index = 0;
            for(Operateur operateur: listeOperateurs)
            {
                sousMenu.add(NONE, operateur.getIdOperateur(), NONE, operateur.getIdentifiant());
                if(operateur.getIdOperateur() == idOperateur)
                {
                    sousMenu.getItem(index).setChecked(true);
                    SpannableString s =
                      new SpannableString(sousMenu.getItem(index).getTitle().toString());
                    s.setSpan(new ForegroundColorSpan(Color.RED), 0, s.length(), 0);
                    sousMenu.getItem(index).setTitle(s);
                }
                ++index;
            }
        }

        return super.onPrepareOptionsMenu(menu);
    }

    /**
     * @brief Méthode appelée quand on sélectionne une entrée du menu
     * @return boolean
     */
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch(item.getItemId())
        {
            case R.id.interventions:
                lancerActiviteIntervention();
                return true;
            case R.id.aPropos:
                afficherAPropos();
                return true;
            default:
                idOperateur = item.getItemId();
                sauvegarderIdOperateur();
        }

        return super.onOptionsItemSelected(item);
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
        Log.d(TAG, "onDestroy()");
        enregistrerPreferences();
        super.onDestroy();
    }
    /**
     * @brief Initialise l'accès à la base de données MySQL
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
     * @brief Méthode utilisée pour initier la communication avec le broker MQTT
     */
    private void initialiserCommunicationMQTT(ArrayList<String> identifiants)
    {
        String clientId   = identifiants.get(INDEX_CLIENT_ID);
        String motDePasse = identifiants.get(INDEX_MDP);
        String hostname   = identifiants.get(INDEX_HOSTNAME);
        Log.d(TAG, "Mot de passe : "+motDePasse+" clientId : "+clientId);

        this.clientMQTT = new ClientMQTT(getApplicationContext(), handler);
        clientMQTT.changerClientId(clientId);
        clientMQTT.changerMotDePasse(motDePasse);
        clientMQTT.changerHostname(hostname);
        clientMQTT.creerClientMQTTT();
        clientMQTT.connecter();
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
                    case BaseDeDonnees.REQUETE_SQL_SELECT_OPERATEURS:
                        Log.d(TAG, "[Handler] REQUETE_SQL_SELECT_OPERATEURS");
                        listeOperateurs = (ArrayList)message.obj;
                        invalidateOptionsMenu();
                        break;
                    case BaseDeDonnees.REQUETE_SQL_SELECT_TTS:
                        Log.d(TAG, "[Handler] REQUETE_SQL_SELECT_TTS");
                        initialiserCommunicationMQTT((ArrayList<String>) message.obj);
                        break;
                    case ClientMQTT.TTN_CONNECTE:
                        Log.d(TAG, "[Handler] TTS connecté");
                        break;
                    case ClientMQTT.TTN_DECONNECTE:
                        Log.d(TAG, "[Handler] TTS déconnecté");
                        break;
                    case ClientMQTT.TTN_MESSAGE:
                        Log.d(TAG, "[Handler] TTS message");
                        break;
                }
            }
        };
    }

    /**
     * @brief Méthode utilisée pour lancer l'activité ActiviteInterventions
     */
    private void lancerActiviteIntervention()
    {
        if(idOperateur != OPERATEUR_NON_DEFINI)
        {
            Intent activiteIntervention = new Intent(JustFeed.this, ActiviteInterventions.class);
            activiteIntervention.putExtra("idOperateur", idOperateur);
            startActivity(activiteIntervention);
        }
        else
        {
            afficherMessage("JustFeed", "Il faut sélectionner un opérateur dans le menu !");
        }
    }

    /**
     * @brief Récupère l'id de l'opérateur qui utilise l'application
     */
    private void recupererIdOperateur()
    {
        if(preferencesPartagees.contains(PREFERENCES_ID_OPERATEUR))
        {
            idOperateur =
              preferencesPartagees.getInt(PREFERENCES_ID_OPERATEUR, OPERATEUR_NON_DEFINI);
            Log.d(TAG, "recupererIdOperateur() idOperateur = " + idOperateur);
        }
    }
    /**
     * @brief Sauvegarde l'id de l'opérateur qui utilise l'application
     */
    private void sauvegarderIdOperateur()
    {
        Log.d(TAG, "sauvegarderIdOperateur() idOperateur = " + idOperateur);
        preferencesPartagees.edit().putInt(PREFERENCES_ID_OPERATEUR, idOperateur).apply();
    }

    /**
     * @brief Charge les préfèrences de l'application
     */
    private void chargerPreferences()
    {
        if(preferencesPartagees == null)
            preferencesPartagees = getBaseContext().getSharedPreferences(PREFERENCES, MODE_PRIVATE);
        recupererIdOperateur();
    }

    /**
     * @brief Enregistre les préfèrences de l'application
     */
    private void enregistrerPreferences()
    {
        if(preferencesPartagees == null)
            preferencesPartagees = getBaseContext().getSharedPreferences(PREFERENCES, MODE_PRIVATE);
        sauvegarderIdOperateur();
    }

    /**
     * @brief Affiche la fenêtre A propos
     */
    private void afficherAPropos()
    {
        afficherMessage("JustFeed 2023", "BTS SN LaSalle Avignon\nFARGIER Mayeul");
    }

    /**
     * @brief Affiche un message dans une boîte de dialogue
     */
    private void afficherMessage(String titre, String message)
    {
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(JustFeed.this);
        alertDialog.setTitle(titre);
        alertDialog.setMessage(message);
        alertDialog.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which)
            {
            }
        });
        AlertDialog alert = alertDialog.create();
        alert.setCanceledOnTouchOutside(true);
        alert.show();
    }
}