/**
 * @file JustFeed.java
 * @brief Déclaration de l'activité principale JustFeed
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import java.util.ArrayList;
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
    private static final String TAG         = "_JustFeed"; //!< TAG pour les logs (cf. Logcat)
    public static final String  PREFERENCES = "justfeed";  //!< Clé pour le titre du stockage
    public static final String  PREFERENCES_ID_OPERATEUR =
      "idOperateur"; //!< Clé pour l'id de l'opérateur
    public static final int OPERATEUR_NON_DEFINI =
      -1; //!< L'id de l'opérateur actif n'est pas défini

    /**
     * Attributs
     */
    private List<Distributeur> listeDistributeurs;     //!< Liste des distributeurs
    private BaseDeDonnees      baseDeDonnees;          //!< L'accès à la base de données
    private List<Operateur>    listeOperateurs = null; //!< Liste des opérateurs
    private String[] nomsOperateurs;                   //!< Les noms d'opérateurs
    private int     operateurSelectionne = OPERATEUR_NON_DEFINI; //!< L'opérateur sélectionné
    private Handler handler              = null;        //<! Le handler utilisé par l'activité
    private RecyclerView         vueListeDistributeurs; //!< Affichage de la liste des distributeurs
    private RecyclerView.Adapter adapteurDistributeur;  //!< Remplit les vues des distributeurs
    private RecyclerView.LayoutManager layoutVueListeDistributeurs; //!< Positionne les vues
    private SharedPreferences
      preferences; //!< système de persistance des données pour l'application

    /**
     * Ressources GUI
     */

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
        chargerPreferences();

        baseDeDonnees.recupererOperateurs();
        baseDeDonnees.recupererDistributeurs();
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

        enregistrerPreferences();
    }

    /**
     * @brief Initialise la vue de l'activité
     */
    private void initialiserGUI()
    {
        initialiserVueListeDistributeurs();
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
                    case BaseDeDonnees.REQUETE_SQL_SELECT_OPERATEURS:
                        Log.d(TAG, "[Handler] REQUETE_SQL_SELECT_OPERATEURS");
                        creerListeOperateurs((ArrayList)message.obj);
                        break;
                }
            }
        };
    }

    /**
     * @brief Charge les préfèrences de l'application
     */
    private boolean chargerPreferences()
    {
        int idOperateur = OPERATEUR_NON_DEFINI;

        preferences = getBaseContext().getSharedPreferences(PREFERENCES, MODE_PRIVATE);
        if(preferences.contains(PREFERENCES_ID_OPERATEUR))
        {
            idOperateur = preferences.getInt(PREFERENCES_ID_OPERATEUR, OPERATEUR_NON_DEFINI);
        }
        Log.d(TAG, "chargerPreferences() idOperateur = " + idOperateur);
        if(idOperateur != OPERATEUR_NON_DEFINI)
        {
            if(listeOperateurs != null)
            {
                operateurSelectionne = OPERATEUR_NON_DEFINI;
                for(int i = 0; i < listeOperateurs.size(); ++i)
                {
                    if(idOperateur == listeOperateurs.get(i).getIdOperateur())
                    {
                        operateurSelectionne = i;
                        Log.d(TAG,
                              "chargerPreferences() operateurSelectionne = " +
                                operateurSelectionne);
                        break;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Enregistre les préfèrences de l'application
     */
    private void enregistrerPreferences()
    {
        if(operateurSelectionne != OPERATEUR_NON_DEFINI)
        {
            Log.d(TAG,
                  "enregistrerPreferences() idOperateur = " +
                    listeOperateurs.get(operateurSelectionne).getIdOperateur());
            preferences.edit()
              .putInt(PREFERENCES_ID_OPERATEUR,
                      listeOperateurs.get(operateurSelectionne).getIdOperateur())
              .apply();
        }
    }

    /**
     * @brief Méthode appelée au démarrage de l'activité principale
     * @return void
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return true;
    }

    /**
     * @brief Méthode appelée quand on sélectionne une entrée du menu
     * @return boolean
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch(item.getItemId())
        {
            case R.id.operateurs:
                selectionnerOperateur();
                return true;
            case R.id.interventions:
                demarrerActiviteInterventions();
                return true;
            case R.id.aPropos:
                afficherAPropos();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * @brief Démarre l'activité ActiviteInterventions
     */
    private void demarrerActiviteInterventions()
    {
        Intent activiteIntervention = new Intent(JustFeed.this, ActiviteInterventions.class);
        startActivity(activiteIntervention);
    }

    /**
     * @brief Crée une liste d'opérateurs
     */
    private void creerListeOperateurs(List<Operateur> listeOperateurs)
    {
        this.listeOperateurs = listeOperateurs;
        nomsOperateurs       = new String[listeOperateurs.size()];
        for(int i = 0; i < listeOperateurs.size(); ++i)
        {
            nomsOperateurs[i] =
              listeOperateurs.get(i).getNom() + " " + listeOperateurs.get(i).getPrenom();
        }
    }

    /**
     * @brief Sélectionne l'opérateur
     */
    private void selectionnerOperateur()
    {
        chargerPreferences();
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(JustFeed.this);
        alertDialog.setTitle("Sélectionner l'opérateur :");
        final int[] checkedItem = { operateurSelectionne };
        alertDialog.setSingleChoiceItems(nomsOperateurs,
                                         operateurSelectionne,
                                         new DialogInterface.OnClickListener() {
                                             @Override
                                             public void onClick(DialogInterface dialog, int which)
                                             {
                                                 checkedItem[0] = which;
                                             }
                                         });
        alertDialog.setPositiveButton("Valider", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which)
            {
                operateurSelectionne = checkedItem[0];
                Log.d(TAG,
                      "selectionnerOperateur() " + operateurSelectionne + " -> " +
                        nomsOperateurs[operateurSelectionne]);
                enregistrerPreferences();
            }
        });
        alertDialog.setNegativeButton("Annuler", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which)
            {
            }
        });
        AlertDialog alert = alertDialog.create();
        alert.setCanceledOnTouchOutside(false);
        alert.show();
    }

    /**
     * @brief Affiche la fenêtre A propos
     */
    private void afficherAPropos()
    {
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(JustFeed.this);
        alertDialog.setTitle("JustFeed 2023");
        alertDialog.setMessage("BTS SN LaSalle Avignon\nFARGIER Mayeul");
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