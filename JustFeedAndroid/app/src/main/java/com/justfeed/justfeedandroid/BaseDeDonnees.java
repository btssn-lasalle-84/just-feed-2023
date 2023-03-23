package com.justfeed.justfeedandroid;

/**
 * @brief Classe BaseDeDonnees.
 * @details La classe BaseDeDonnees permet de créer une interface entre l'application Android
 * et une bose de données distante.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class BaseDeDonnees {
    private String identifiant; //!< Identifiant de l'utilisateur de la base de donées.
    private String motDePasse; //!< Mot de passe de l'identifiant.
    private String hostName; //!< Nom de la machine distante.

    private int port; //!< Port sur lequel le processus de la base de données écoute.

    /**
     * @brief Constructeur par défaut de la classe BaseDeDonnees.
     * @see BaseDeDonnees()
     */
    public BaseDeDonnees(){
        /**
         * @todo créer un utilisateur par défaut.
         */
    }

    /**
     * @brief Constructeur d'initialisation de la classe BaseDeDonnees.
     * @see BaseDeDonnees(String identifiant, String motDePasse, String hostName, int port)
     * @param identifiant le nom d'un utilisateur autorisé sur la base de données.
     * @param motDePasse le mot de passe de l'utilisateur.
     * @param hostName le nom de la machine distante.
     * @param port le numéro de port sur lequel le processus de la base de données écoute.
     */
    public BaseDeDonnees(String identifiant, String motDePasse, String hostName, int port){
        this.identifiant = identifiant;
        this.motDePasse = motDePasse;
        this.hostName = hostName;

        this.port = port;
    }

    /**
     * @todo méthodes pour executer des requêtes SQL, se connecter, fermer la connexion.
     */
}
