/**
 * @file BaseDeDonnees.java
 * @brief Déclaration de la classe BaseDeDonnees
 * @author FARGIER Mayeul
 * @author Thierry VAIRA
 */

package com.justfeed.justfeedandroid;

import android.location.Location;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @brief Classe BaseDeDonnees.
 * @details La classe BaseDeDonnees permet de créer une interface entre
 * l'application Android et une bose de données distante.
 * @author Fargier Mayeul
 * @author Thierry VAIRA
 * @version 0.1
 * @see https://www.tutorialspoint.com/java_mysql/
 */
public class BaseDeDonnees
{
    /**
     * Constantes
     */
    private static final String TAG                = "_BaseDeDonnees"; //!< TAG pour les logs
    public final static int     CONNEXION_OK       = 0;
    public final static int     CONNEXION_ERREUR   = 1;
    public final static int     DECONNEXION_OK     = 2;
    public final static int     DECONNEXION_ERREUR = 3;
    public final static int     REQUETE_SQL_OK     = 4;
    public final static int     REQUETE_SQL_ERREUR = 5;
    public final static int     REQUETE_SQL_SELECT = 6;
    public final static int     REQUETE_SQL_SELECT_DISTRIBUTEURS = 7;
    public final static int     REQUETE_SQL_SELECT_INTERVENTIONS = 8;
    private static final String NOM_BDD = "justfeed"; //!< Le nom par défaut de la base de données
    private static final String IDENTIFIANT =
      "justfeed"; //!< Le nom de l'utilisateur par défaut de la base de données
    private static final String MOT_DE_PASSE =
      "justfeed"; //!< Le mot de passe par défaut de la base de données
    private static final String HOSTNAME =
      "www.db4free.net"; //!< L'adresse du serveur de base de données par défaut
    // private static final String HOSTNAME = "127.0.0.1"; //!< L'adresse du serveur de base de
    // données par défaut
    private static final int    PORT_DEFAUT = 3306; //!< Le numéro de port par défaut pour MySQL
    private final int           TRUE        = 1; //!< Vérifie si l'intervention a été executée.
    public final static boolean active =
      true; //!< si vrai l'application peut utiliser la base de données MySQL (utile en debug)

    /**
     * Attributs
     */
    private final String     nomBDD;      //!< Nom de la base de données
    private final String     identifiant; //!< Identifiant de l'utilisateur de la base de données
    private final String     motDePasse;  //!< Mot de passe de l'identifiant
    private final String     hostName;    //!< Nom de la machine distante
    private final String     url;         //!< L'URL de connexion à la base de données
    private final int        port; //!< Port sur lequel le processus de la base de données écoute
    public static Connection connexion = null; //!< objet de connexion à MySQL (null par défaut)
    public static final Lock mutex =
      new ReentrantLock(true);               //!< mutex pour l'exécution concurrente de requêtes
    private static BaseDeDonnees bdd = null; //!< l'instance unique de BaseDeDonnees (Singleton)
    private Handler handler = null; //<! Le handler pour l'échange de messages entre les threads
    private List<Distributeur> listeDistributeurs = null; //<! La liste des distributeurs
    private List<Intervention> listeInterventions = null; //<! La liste des interventions

    /**
     * @fn getInstance
     * @brief Retourne l'instance BaseDeDonnees
     */
    public synchronized static BaseDeDonnees getInstance()
    {
        if(bdd == null)
            bdd = new BaseDeDonnees();
        return bdd;
    }

    /**
     * @fn getInstance
     * @brief Retourne l'instance BaseDeDonnees
     * @param nomBase le nom de la base de données
     * @param identifiant le nom d'un utilisateur autorisé sur la base de
     *   données.
     * @param motDePasse le mot de passe de l'utilisateur.
     * @param hostName le nom de la machine distante.
     */
    public synchronized static BaseDeDonnees getInstance(String nomBase,
                                                         String identifiant,
                                                         String motDePasse,
                                                         String hostName)
    {
        if(bdd == null)
            bdd = new BaseDeDonnees(nomBase, identifiant, motDePasse, hostName, PORT_DEFAUT);
        return bdd;
    }

    /**
     * @fn getInstance
     * @brief Retourne l'instance BaseDeDonnees
     * @param handler Le handler pour l'échange de messages entre les threads.
     */
    public synchronized static BaseDeDonnees getInstance(Handler handler)
    {
        if(bdd == null)
            bdd = new BaseDeDonnees(handler);
        return bdd;
    }

    /**
     * @fn getInstance
     * @brief Retourne l'instance BaseDeDonnees
     * @param nomBase le nom de la base de données
     * @param identifiant le nom d'un utilisateur autorisé sur la base de
     *   données.
     * @param motDePasse le mot de passe de l'utilisateur.
     * @param hostName le nom de la machine distante.
     * @param handler Le handler pour l'échange de messages entre les threads.
     */
    public synchronized static BaseDeDonnees getInstance(String  nomBase,
                                                         String  identifiant,
                                                         String  motDePasse,
                                                         String  hostName,
                                                         Handler handler)
    {
        if(bdd == null)
            bdd =
              new BaseDeDonnees(nomBase, identifiant, motDePasse, hostName, PORT_DEFAUT, handler);
        return bdd;
    }

    /**
     * @brief Constructeur par défaut de la classe BaseDeDonnees.
     * @see BaseDeDonnees()
     */
    private BaseDeDonnees()
    {
        this.nomBDD             = NOM_BDD;
        this.identifiant        = IDENTIFIANT;
        this.motDePasse         = MOT_DE_PASSE;
        this.hostName           = HOSTNAME;
        this.port               = PORT_DEFAUT;
        this.listeInterventions = new ArrayList<Intervention>();
        Log.d(TAG,
              "BaseDeDonnees() nom = " + nomBDD + " - identifiant = " + identifiant +
                " - motDePasse = " + motDePasse + " - hostName = " + hostName);

        // Initialise l'url pour la connexion à la base de données MySQL
        // this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD +
        // "?useUnicode=true&characterEncoding=utf8&useSSL=false";
        this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD + "?useSSL=false";
        connecter();
    }

    /**
     * @brief Constructeur par défaut de la classe BaseDeDonnees.
     * @see BaseDeDonnees()
     */
    private BaseDeDonnees(Handler handler)
    {
        this.nomBDD             = NOM_BDD;
        this.identifiant        = IDENTIFIANT;
        this.motDePasse         = MOT_DE_PASSE;
        this.hostName           = HOSTNAME;
        this.port               = PORT_DEFAUT;
        this.handler            = handler;
        this.listeInterventions = new ArrayList<Intervention>();
        Log.d(TAG,
              "BaseDeDonnees() nom = " + nomBDD + " - identifiant = " + identifiant +
                " - motDePasse = " + motDePasse + " - hostName = " + hostName);

        // Initialise l'url pour la connexion à la base de données MySQL
        // this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD +
        // "?useUnicode=true&characterEncoding=utf8&useSSL=false";
        this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD + "?useSSL=false";
        connecter();
    }

    /**
     * @brief Constructeur d'initialisation de la classe BaseDeDonnees.
     * @see BaseDeDonnees(String nomBase, String identifiant, String motDePasse, String
     *     hostName, int port)
     * @param nomBase le nom de la base de données MySQL
     * @param identifiant le nom d'un utilisateur autorisé sur la base de
     *   données.
     * @param motDePasse le mot de passe de l'utilisateur.
     * @param hostName le nom de la machine distante.
     * @param port le numéro de port sur lequel le processus de la base de
     *   données écoute.
     */
    private BaseDeDonnees(String nomBase,
                          String identifiant,
                          String motDePasse,
                          String hostName,
                          int    port)
    {
        Log.d(TAG,
              "BaseDeDonnees() nom = " + nomBase + " - identifiant = " + identifiant +
                " - motDePasse = " + motDePasse + " - hostName = " + hostName);
        this.nomBDD             = nomBase;
        this.identifiant        = identifiant;
        this.motDePasse         = motDePasse;
        this.hostName           = hostName;
        this.port               = port;
        this.handler            = handler;
        this.listeInterventions = new ArrayList<Intervention>();
        // Initialise l'url pour la connexion à la base de données MySQL
        // this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD +
        // "?useUnicode=true&characterEncoding=utf8&useSSL=false";
        this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD + "?useSSL=false";
        connecter();
    }

    /**
     * @brief Constructeur d'initialisation de la classe BaseDeDonnees.
     * @see BaseDeDonnees(String nomBase, String identifiant, String motDePasse, String
     *   hostName, int port)
     * @param nomBase le nom de la base de données
     * @param identifiant le nom d'un utilisateur autorisé sur la base de
     *   données.
     * @param motDePasse le mot de passe de l'utilisateur.
     * @param hostName le nom de la machine distante.
     * @param port le numéro de port sur lequel le processus de la base de
     *   données écoute.
     * @param handler Le handler pour l'échange de messages entre les threads.
     */
    private BaseDeDonnees(String  nomBase,
                          String  identifiant,
                          String  motDePasse,
                          String  hostName,
                          int     port,
                          Handler handler)
    {
        Log.d(TAG,
              "BaseDeDonnees() nom = " + nomBase + " - identifiant = " + identifiant +
                " - motDePasse = " + motDePasse + " - hostName = " + hostName);
        this.nomBDD             = nomBase;
        this.identifiant        = identifiant;
        this.motDePasse         = motDePasse;
        this.hostName           = hostName;
        this.port               = port;
        this.handler            = handler;
        this.listeInterventions = new ArrayList<Intervention>();
        // Initialise l'url pour la connexion à la base de données MySQL
        // this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD +
        // "?useUnicode=true&characterEncoding=utf8&useSSL=false";
        this.url = "jdbc:mysql://" + this.hostName + "/" + this.nomBDD + "?useSSL=false";
        connecter();
    }

    /**
     * @fn setHandler
     * @brief Fixe le gestionnaire de messages du thread UI
     * @param handler Handler le gestionnaire de messages du thread UI
     */
    public void setHandler(Handler handler)
    {
        this.handler = handler;
    }

    /**
     * @fn connecter
     * @brief Connexion à la base de données MySQL si pas déjà connecté
     * @return boolean vrai si la connexion a réussi sinon faux
     */
    public boolean connecter()
    {
        if(!BaseDeDonnees.active)
            return false;

        try
        {
            if(!estConnecte())
            {
                ConnexionMySql connexionMySql = new ConnexionMySql();
                connexionMySql.execute();
                Log.d(TAG, "connecter() retour = " + connexionMySql.get());
                return connexionMySql.get();
            }
            return true;
        }
        catch(InterruptedException e)
        {
            // e.printStackTrace();
            Log.e(TAG, "connecter() InterruptedException = " + e.toString());
            return false;
        }
        catch(ExecutionException e)
        {
            // e.printStackTrace();
            Log.e(TAG, "connecter() ExecutionException = " + e.toString());
            return false;
        }
    }

    /**
     * @fn reconnecter
     * @brief Reconnexion à la base de données MySQL
     * @return boolean vrai si la connexion a réussi sinon faux
     */
    public boolean reconnecter()
    {
        if(!BaseDeDonnees.active)
            return false;
        deconnecter();
        return connecter();
    }

    /**
     * @fn deconnecter
     * @brief Déconnexion de la base de données MySQL
     * @return boolean vrai si la déconnexion a réussi sinon faux
     */
    public boolean deconnecter()
    {
        if(!BaseDeDonnees.active)
            return false;

        try
        {
            if(connexion != null)
            {
                connexion.close();
                Log.d(TAG, "deconnecter() retour = " + connexion.isClosed());
                if(connexion.isClosed())
                {
                    Message message = new Message();
                    message.what    = DECONNEXION_OK;
                    message.obj     = "";
                    if(handler != null)
                        handler.sendMessage(message);
                }
                else
                {
                    Message message = new Message();
                    message.what    = DECONNEXION_ERREUR;
                    message.obj     = "";
                    if(handler != null)
                        handler.sendMessage(message);
                }
                return connexion.isClosed();
            }
            return true;
        }
        catch(SQLException e)
        {
            // e.printStackTrace();
            Log.e(TAG, "deconnecter() ExecutionException = " + e.toString());
            Message message = new Message();
            message.what    = DECONNEXION_ERREUR;
            message.obj     = "";
            if(handler != null)
                handler.sendMessage(message);
            return false;
        }
    }

    /**
     * @fn estConnecte
     * @brief Retourne vrai si on est connecté à la base de données MySQL
     * @return boolean vrai si on est connecté à la base de données MySQL sinon faux
     */
    public boolean estConnecte()
    {
        if(!BaseDeDonnees.active)
            return false;

        try
        {
            if(connexion != null)
                return !connexion.isClosed();
            else
                return false;
        }
        catch(SQLException e)
        {
            // e.printStackTrace();
            Log.e(TAG, "estConnecte() ExecutionException = " + e.toString());
            return false;
        }
    }

    /**
     * @class ConnexionMySql
     * @brief Classe permettant de se connecter à MySQL en arrière-plan
     */
    private class ConnexionMySql extends AsyncTask<Void, Integer, Boolean>
    {
        private String messageConnexion = "";

        /**
         * @fn doInBackground
         * @brief Méthode de connexion qui s’exécute dans un autre thread
         */
        @Override
        protected Boolean doInBackground(Void... unused)
        {
            try
            {
                // chargement du pilote JDBC MySQL
                Class.forName("com.mysql.jdbc.Driver").newInstance();
            }
            catch(Exception e)
            {
                // e.printStackTrace();
                Log.e(TAG, "doInBackground() Exception = " + e.toString());
                messageConnexion = "Erreur connexion MySQL !";
                Message message  = new Message();
                message.what     = CONNEXION_ERREUR;
                message.obj      = messageConnexion;
                if(handler != null)
                    handler.sendMessage(message);
            }
            try
            {
                if(!estConnecte())
                {
                    Log.d(TAG,
                          "DriverManager.getConnection(" + url + ", " + identifiant + ", " +
                            motDePasse + ")");
                    connexion = DriverManager.getConnection(url, identifiant, motDePasse);
                }
                // Log.d(TAG, "doInBackground -> connecte : " + !connexion.isClosed());
                if(!connexion.isClosed())
                {
                    messageConnexion = "Connexion MySQL réussie";
                    Message message  = new Message();
                    message.what     = CONNEXION_OK;
                    message.obj      = messageConnexion;
                    if(handler != null)
                        handler.sendMessage(message);
                }
                return !connexion.isClosed();
            }
            catch(SQLException e)
            {
                // e.printStackTrace();
                Log.e(TAG, "doInBackground() SQLException = " + e.getMessage());
                Log.e(TAG, "doInBackground() SQLState = " + e.getSQLState());
                Log.e(TAG, "doInBackground() VendorError = " + e.getErrorCode());
                messageConnexion = "Erreur connexion MySQL !";
                Message message  = new Message();
                message.what     = CONNEXION_ERREUR;
                message.obj      = messageConnexion;
                if(handler != null)
                    handler.sendMessage(message);
                return false;
            }
        }

        /**
         * @fn onProgressUpdate
         * @brief Méthode permettant d'indiquer la progression de la tâche d'arrière plan (s’exécute
         * dans le thread UI)
         * @details doInBackground peut appeler publishProgress() pour indiquer l'avancement du
         * traitement ce qui aura pour effet d'appeler automatiquement onProgressUpdate()
         */
        @Override
        protected void onProgressUpdate(Integer... progress)
        {
            // Log.v(TAG, "onProgressUpdate() progression = " + progress[0]);
            //  Ici on pourrait accéder à la partie UI d'une activité
            //  et/ou appeler une méthode d'une activité
        }

        /**
         * @fn onPostExecute
         * @brief Méthode appelée lorsque doInBackground a terminé (s’exécute dans le thread UI)
         */
        @Override
        protected void onPostExecute(Boolean result)
        {
            // Log.d(TAG, "onPostExecute() result = " + result);
            // Log.d(TAG, "onPostExecute()) message = " + messageConnexion);
        }
    }

    /**
     * @fn executerRequete
     * @brief Méthode qui exécute une requête UPDATE, INSERT ou DELETE en arrière-plan
     */
    public void executerRequete(final String requete)
    {
        if(!BaseDeDonnees.active)
            return;

        if(estConnecte())
        {
            // Seulement pour les requêtes UPDATE, INSERT ou DELETE
            if(!requete.contains("UPDATE") && !requete.contains("INSERT") &&
               !requete.contains("DELETE"))
                return;

            // Exécute la requête dans un thread
            Thread requeteBDD = new Thread(new Runnable() {
                public void run()
                {
                    mutex.lock();
                    try
                    {
                        Log.d(TAG, "executerRequete() requete = " + requete);
                        Statement statement = connexion.createStatement();
                        int       nb        = statement.executeUpdate(requete);
                        if(nb > 0)
                        {
                            Message message = new Message();
                            message.what    = REQUETE_SQL_OK;
                            message.obj     = Integer.toString(nb);
                            if(handler != null)
                                handler.sendMessage(message);
                        }
                        else
                        {
                            Message message = new Message();
                            message.what    = REQUETE_SQL_ERREUR;
                            message.obj     = "";
                            if(handler != null)
                                handler.sendMessage(message);
                        }
                    }
                    catch(Exception e)
                    {
                        // e.printStackTrace();
                        Log.e(TAG, "executerRequete() Exception = " + e.toString());
                    }
                    finally
                    {
                        mutex.unlock();
                    }
                }
            });

            // Démarrage de l'exécution de la requête
            requeteBDD.start();
        }
        else
        {
            Log.w(TAG, "executerRequete() Pas de connexion MySQL !");
        }
    }

    /**
     * @brief Sélectionne des enregistrements dans la base de données en arrière-plan
     * @param requeteSELECT String la requête SQL
     */
    public void selectionner(final String requeteSELECT)
    {
        Log.d(TAG, "selectionner()");
        if(!BaseDeDonnees.active)
            return;

        // Seulement pour les requêtes SELECT
        if(!requeteSELECT.contains("SELECT"))
            return;

        if(bdd.estConnecte())
        {
            Thread requeteBDD = new Thread(new Runnable() {
                public void run()
                {
                    bdd.mutex.lock();
                    try
                    {
                        Log.d(TAG, "Requête : " + requeteSELECT);
                        Statement statement       = bdd.connexion.createStatement();
                        ResultSet resultatRequete = statement.executeQuery(requeteSELECT);
                        Message   message         = new Message();
                        message.what              = REQUETE_SQL_SELECT;
                        message.obj               = resultatRequete;
                        if(handler != null)
                            handler.sendMessage(message);
                    }
                    catch(Exception e)
                    {
                        e.printStackTrace();
                        Log.e(TAG, "BDD -> exception : " + e.toString());
                    }
                    finally
                    {
                        bdd.mutex.unlock();
                    }
                }
            });

            // Démarrage
            requeteBDD.start();
        }
        else
        {
            Log.w(TAG, "Pas de connexion MySQL !");
        }
    }

    /**
     * @brief Méthode qui retourne une liste de distributeurs de la BDD.
     * @return listeDistributeurs
     */
    public void recupererDistributeurs()
    {
        if(BaseDeDonnees.active)
        {
            if(estConnecte())
            {
                Thread requeteBDD = new Thread(new Runnable() {
                    public void run()
                    {
                        mutex.lock();
                        try
                        {
                            String requeteSQLDistributeurs = "SELECT * FROM Distributeur";
                            Log.d(TAG, "Requete : " + requeteSQLDistributeurs);
                            Statement statement =
                              connexion.createStatement(ResultSet.TYPE_FORWARD_ONLY,
                                                        ResultSet.CONCUR_READ_ONLY);
                            ResultSet resultatRequeteDistributeurs =
                              statement.executeQuery(requeteSQLDistributeurs);
                            Map<Integer, Distributeur> distributeurs =
                              new HashMap<Integer, Distributeur>();
                            while(resultatRequeteDistributeurs.next())
                            {
                                Log.d(TAG,
                                      "recupererDistributeurs() idDistributeur : " +
                                        resultatRequeteDistributeurs.getInt("idDistributeur"));
                                Location coordGeographiques = new Location("Non défini");
                                coordGeographiques.setLatitude(resultatRequeteDistributeurs.getDouble("latitude"));
                                coordGeographiques.setLongitude(resultatRequeteDistributeurs.getDouble("longitude"));
                                distributeurs.put(
                                  resultatRequeteDistributeurs.getInt("idDistributeur"),
                                  new Distributeur(
                                    resultatRequeteDistributeurs.getInt("idDistributeur"),
                                    resultatRequeteDistributeurs.getString("codepostal"),
                                    resultatRequeteDistributeurs.getString("adresse"),
                                    resultatRequeteDistributeurs.getString("ville"),
                                    resultatRequeteDistributeurs.getString("nomDistributeur"),
                                    coordGeographiques,
                                    new ArrayList<Bac>()));
                            }
                            String requeteSQLBacs =
                              "SELECT Distributeur.*,Produit.*,Bac.* FROM Bac\n"
                              +
                              "INNER JOIN Distributeur ON Distributeur.idDistributeur=Bac.idDistributeur\n"
                              + "INNER JOIN Produit ON Produit.idProduit=Bac.idProduit\n"
                              +
                              "INNER JOIN ServeurTTN ON ServeurTTN.idServeurTTN=Distributeur.idServeurTTN;";
                            Log.d(TAG, "Requete : " + requeteSQLBacs);
                            ResultSet resultatRequeteBacs = statement.executeQuery(requeteSQLBacs);
                            while(resultatRequeteBacs.next())
                            {
                                Log.d(TAG,
                                      "recupererDistributeurs() idDistributeur = " +
                                        resultatRequeteBacs.getInt("idDistributeur"));
                                if(distributeurs.containsKey(
                                     resultatRequeteBacs.getInt("idDistributeur")))
                                {
                                    distributeurs.get(resultatRequeteBacs.getInt("idDistributeur"))
                                      .ajouterBac(
                                        new Bac(new Produit(
                                                  resultatRequeteBacs.getString("nomProduit"),
                                                  resultatRequeteBacs.getDouble("prix"),
                                                  resultatRequeteBacs.getDouble("poidsUnitaire"),
                                                  resultatRequeteBacs.getDouble("volumeUnitaire")),
                                                resultatRequeteBacs.getDouble("poidsActuel"),
                                                resultatRequeteBacs.getDouble("poidsTotal"),
                                                resultatRequeteBacs.getInt("hygrometrie")));
                                }
                                Log.d(
                                  TAG,
                                  "recupererDistributeurs() idDistributeur = " +
                                    resultatRequeteBacs.getInt("idDistributeur") + " nbBacs = " +
                                    distributeurs.get(resultatRequeteBacs.getInt("idDistributeur"))
                                      .getNbBacs());
                            }
                            listeDistributeurs =
                              new ArrayList<Distributeur>(distributeurs.values());
                            Message message = new Message();
                            message.what    = REQUETE_SQL_SELECT_DISTRIBUTEURS;
                            message.obj     = listeDistributeurs;
                            if(handler != null)
                                handler.sendMessage(message);
                        }
                        catch(Exception e)
                        {
                            // e.printStackTrace();
                            Log.e(TAG, "recupererDistributeurs() Exception = " + e.toString());
                        }
                        finally
                        {
                            mutex.unlock();
                        }
                    }
                });

                // Démarrage
                requeteBDD.start();
            }
            else
            {
                Log.w(TAG, "Pas de connexion MySQL !");
            }
        }
        else
        {
            // Pour les tests
            // simule une base de données
            List<Bac> bacsDistributeur1 = Arrays.asList(
              new Bac(new Produit("Cacahuète", 0.49, 0.001, 0.004), 1.5, 2, 0),
              new Bac(new Produit("Riz Basmati Blanc", 0.35, 0.00005, 0.0003), 0.8, 1.3, 0),
              new Bac(new Produit("Fèves entières", 0.3, 0.002, 0.003), 1.5, 8, 0));

            List<Bac> bacsDistributeur2 =
              Arrays.asList(new Bac(new Produit("Banane CHIPS", 0.76, 0.003, 0.002), 5.0, 12, 0),
                            new Bac(new Produit("Abricots secs", 1.13, 0.008, 0.004), 14.0, 16, 0),
                            new Bac(new Produit("Raisin sec", 0.39, 0.002, 0.001), 10.5, 16, 0));

            List<Bac> bacsDistributeur3 =
              Arrays.asList(new Bac(new Produit("Cranberries", 2.1, 0.0006, 0.0005), 9.6, 9.6, 1),
                            new Bac(new Produit("Pruneaux", 1.15, 0.008, 0.004), 7.5, 16, 0),
                            new Bac(new Produit("Fruits sec", 1.06, 0.00035, 0.0004), 6.2, 7, 0));

            listeDistributeurs = new ArrayList<Distributeur>();
            Location coordGeographiques1 = new Location("Non défini");
            coordGeographiques1.setLatitude(44.137327);
            coordGeographiques1.setLongitude(4.81958);
            Location coordGeographiques2 = new Location("Non défini");
            coordGeographiques2.setLatitude(43.9416435);
            coordGeographiques2.setLongitude(4.8008485);
            Location coordGeographiques3 = new Location("Non défini");
            coordGeographiques3.setLatitude(44.048701);
            coordGeographiques3.setLongitude(5.0424848);
            listeDistributeurs.add(new Distributeur(1,
                                                    "84100",
                                                    "Avenue Frédéric Mistral",
                                                    "Orange",
                                                    "Gare Orange",
                                                    coordGeographiques1,
                                                    bacsDistributeur1));
            listeDistributeurs.add(new Distributeur(2,
                                                    "84000",
                                                    "Boulevard Saint-Roch",
                                                    "Avignon",
                                                    "Gare Avignon Centre",
                                                    coordGeographiques2,
                                                    bacsDistributeur2));
            listeDistributeurs.add(new Distributeur(3,
                                                    "84200",
                                                    "Avenue De La Gare",
                                                    "Carpentras",
                                                    "Gare de Carpentras",
                                                    coordGeographiques3,
                                                    bacsDistributeur3));
            Message message = new Message();
            message.what    = REQUETE_SQL_SELECT_DISTRIBUTEURS;
            message.obj     = listeDistributeurs;
            if(handler != null)
                handler.sendMessage(message);
        }
    }

    /**
     * @brief Méthode qui retourne une liste d'interventions de la BDD.
     * @return listeInterventions
     */
    public void recupererInterventions()
    {
        if(BaseDeDonnees.active)
        {
            if(estConnecte())
            {
                Thread requeteBDD = new Thread(new Runnable() {
                    public void run()
                    {
                        mutex.lock();
                        try
                        {
                            String requeteSQL =
                              "SELECT * FROM Intervention, Distributeur WHERE Intervention.idDistributeur = Distributeur.idDistributeur";
                            Log.d(TAG, "Requete : " + requeteSQL);
                            Statement statement =
                              connexion.createStatement(ResultSet.TYPE_FORWARD_ONLY,
                                                        ResultSet.CONCUR_READ_ONLY);
                            ResultSet resultatRequete = statement.executeQuery(requeteSQL);
                            listeInterventions        = new ArrayList<Intervention>();
                            while(resultatRequete.next())
                            {
                                for(Distributeur distributeur: listeDistributeurs)
                                {
                                    Log.d(TAG,
                                          "recupererInterventions() idDistributeur = " +
                                            resultatRequete.getInt("idDistributeur"));
                                    if(distributeur.getIdentifiant() ==
                                       resultatRequete.getInt("idDistributeur"))
                                    {
                                        Log.d(TAG,
                                              "recupererInterventions() dateIntervention = " +
                                                resultatRequete.getString("dateIntervention"));
                                        listeInterventions.add(new Intervention(
                                          resultatRequete.getString("dateIntervention"),
                                          distributeur,
                                          (resultatRequete.getInt("effectuee") == 0)));
                                    }
                                    else
                                    {
                                        Log.d(TAG,
                                              "recupererInterventions() pas d'intervention prévue");
                                    }
                                }
                            }
                            Message message = new Message();
                            message.what    = REQUETE_SQL_SELECT_INTERVENTIONS;
                            message.obj     = listeInterventions;
                            if(handler != null)
                                handler.sendMessage(message);
                        }
                        catch(Exception e)
                        {
                            // e.printStackTrace();
                            Log.e(TAG, "recupererInterventions() Exception = " + e.toString());
                        }
                        finally
                        {
                            mutex.unlock();
                        }
                    }
                });

                // Démarrage
                requeteBDD.start();
            }
            else
            {
                Log.w(TAG, "Pas de connexion MySQL !");
            }
        }
        else
        {
            listeInterventions.clear();
            listeInterventions.add(new Intervention(
                    "2023-06-01", listeDistributeurs.get(0), true));
            Message message = new Message();
            message.what    = REQUETE_SQL_SELECT_INTERVENTIONS;
            message.obj     = listeInterventions;
            if(handler != null)
                handler.sendMessage(message);
        }
    }
}