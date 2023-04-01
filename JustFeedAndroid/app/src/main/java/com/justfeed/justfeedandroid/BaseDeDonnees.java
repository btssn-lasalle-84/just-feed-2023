package com.justfeed.justfeedandroid;

import android.util.Log;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @brief Classe BaseDeDonnees.
 * @details La classe BaseDeDonnees permet de créer une interface entre
 * l'application Android et une bose de données distante.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class BaseDeDonnees
{
    /**
     * Constantes
     */
    private static final String TAG = "_BaseDeDonnees"; //!< TAG pour les logs
    private static final int PORT_DEFAUT = 3306; //!< Le numéro de port par défaut pour MySQL
    /**
     * Attributs
     */
    private String identifiant; //!< Identifiant de l'utilisateur de la base de donées.
    private String motDePasse;  //!< Mot de passe de l'identifiant.
    private String hostName;    //!< Nom de la machine distante.
    private int    port;        //!< Port sur lequel le processus de la base de données écoute.

    /**
     * @brief Constructeur par défaut de la classe BaseDeDonnees.
     * @see BaseDeDonnees()
     */
    public BaseDeDonnees()
    {
        this.identifiant = "";
        this.motDePasse  = "";
        this.hostName    = "";
        this.port = PORT_DEFAUT;
    }

    /**
     * @brief Constructeur d'initialisation de la classe BaseDeDonnees.
     * @see BaseDeDonnees(String identifiant, String motDePasse, String
     *   hostName, int port)
     * @param identifiant le nom d'un utilisateur autorisé sur la base de
     *   données.
     * @param motDePasse le mot de passe de l'utilisateur.
     * @param hostName le nom de la machine distante.
     * @param port le numéro de port sur lequel le processus de la base de
     *   données écoute.
     */
    public BaseDeDonnees(String identifiant, String motDePasse, String hostName, int port)
    {
        this.identifiant = identifiant;
        this.motDePasse  = motDePasse;
        this.hostName    = hostName;
        this.port = port;
    }

    public List<Distributeur> recupererDistributeurs()
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

        List<Distributeur> listeDistributeurs = Arrays.asList(
                new Distributeur(8456, bacsDistributeur1, 2, listeProduits1),
                new Distributeur(8457, bacsDistributeur2, 4, listeProduits2),
                new Distributeur(8458, bacsDistributeur3, 2, listeProduits3)
        );

        return listeDistributeurs;
    }

    public List<Intervention> recupererInterventions()
    {
        /**
         * @todo récupérer les informations des interventions sur la base de données
         */
        List<Intervention> listeInterventions = null;
        return listeInterventions;
    }

    /**
     * @todo méthodes pour executer des requêtes SQL, se connecter, fermer la
     * connexion.
     */
}
