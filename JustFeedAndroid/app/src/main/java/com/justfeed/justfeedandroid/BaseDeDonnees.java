package com.justfeed.justfeedandroid;

import android.util.Log;

import java.util.ArrayList;
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
    private String             identifiant; //!< Identifiant de l'utilisateur de la base de donées.
    private String             motDePasse;  //!< Mot de passe de l'identifiant.
    private String             hostName;    //!< Nom de la machine distante.
    private List<Distributeur> listeDistributeurs; //Simule la récupération d'une liste de Distributeurs sur une BDD
    private List<Intervention> listeInterventions;
    private int                port;        //!< Port sur lequel le processus de la base de données écoute.

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
     *     hostName, int port)
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

        List<Bac> bacsDistributeur1 = Arrays.asList(
                new Bac(new Produit(0.70, 0.001, 0.004, "cacahuètes"),
                        1.5, 2.0, 0),
                new Bac(new Produit(0.35, 0.00005, 0.0003, "riz"),
                        0.8, 1.3,0),
                new Bac(new Produit(0.50, 0.002, 0.003,"fèves"),
                        1.5, 8.0, 0)
        );

        List<Bac> bacsDistributeur2 = Arrays.asList(
                new Bac(new Produit(3.10, 0.003, 0.002, "Banane séchée"),
                        5.0, 12.0, 0),
                new Bac(new Produit(3.20, 0.008, 0.004, "Abricot sec"),
                        14.0, 16.0, 0),
                new Bac(new Produit(2.15, 0.002, 0.001,"raisin sec"),
                        10.5, 16.0, 0)
        );

        List<Bac> bacsDistributeur3 = Arrays.asList(
                new Bac(new Produit(3.55, 0.0006, 0.0005, "pistache"),
                        9.6, 9.6, 1),
                new Bac(new Produit(1.45, 0.00035, 0.0004, "maïs séché"),
                        4.5, 7.0, 0),
                new Bac(new Produit(4.49, 0.00006, 0.0005,"graine de café"),
                        1.0, 1.0, 0)
        );

        this.listeDistributeurs = Arrays.asList(
                new Distributeur(8456, bacsDistributeur1),
                new Distributeur(8457, bacsDistributeur2),
                new Distributeur(8458, bacsDistributeur3)
        );

        this.listeInterventions = Arrays.asList(
            new Intervention("10h" , new Distributeur(8456, bacsDistributeur1), true),
            new Intervention("11h", new Distributeur(8457, bacsDistributeur2), true),
            new Intervention("12h", new Distributeur(8458, bacsDistributeur3), true)
        );
    }

    public List<Distributeur> recupererDistributeurs()
    {
        /**
         * @todo récupérer les informations des distributeurs sur la base de données
         */

        return this.listeDistributeurs;
    }

    public List<Intervention> recupererInterventions()
    {
        /**
         * @todo récupérer les informations des interventions sur la base de données
         */
        Log.d(TAG, "recupererInterventions()");

        return this.listeInterventions;
    }

    /**
     * @todo méthodes pour executer des requêtes SQL, se connecter, fermer la
     * connexion.
     */
}