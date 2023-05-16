package com.justfeed.justfeedandroid;

import android.util.Log;

/**
 * @brief Définition de la classe Operateur.
 * @details La classe Operateur \c Operateur permet choisir l'opérateur
 * qui effectuera l'intervention.
 * @author Fargier Mayeul
 * @version 0.2
 */
public class Operateur
{
    /**
     * Constantes
     */
    private static final String TAG = "_Operateur"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private int    idOperateur; //!< Identifiant de l'opérateur dans la table Operateur
    private String nom;         //!< Nom de l'opérateur
    private String prenom;      //!< Prénom de l'opérateur
    private String identifiant; //!< Identifiant de l'opérateur
    private String email;       //!< Email de l'opérateur

    /**
     * @brief Constructeur d'initialisation de la classe Operateur
     * @param nom nom de l'opérateur
     * @param prenom prenom de l'opérateur
     */
    public Operateur(String nom, String prenom)
    {
        Log.d(TAG, "Operateur(" + nom + ", " + prenom + ")");
        this.idOperateur = -1;
        this.nom         = nom;
        this.prenom      = prenom;
        this.identifiant = prenom.substring(0, 1).toLowerCase() + this.nom.toLowerCase();
        this.email       = "";
    }

    /**
     * @brief Constructeur d'initialisation de la classe Operateur
     * @param nom nom de l'opérateur
     * @param prenom prenom de l'opérateur
     * @param idOperateur identifiant de l'opérateur
     */
    public Operateur(String nom, String prenom, int idOperateur)
    {
        Log.d(TAG, "Operateur(" + nom + ", " + prenom + " ," + idOperateur + ")");
        this.idOperateur = idOperateur;
        this.nom         = nom;
        this.prenom      = prenom;
        this.identifiant = prenom.substring(0, 1).toLowerCase() + this.nom.toLowerCase();
        this.email       = "";
    }

    /**
     * @brief Constructeur d'initialisation de la classe Operateur
     * @param nom , nom de l'opérateur
     * @param prenom , prenom de l'opérateur
     * @param idOperateur , identifiant de l'opérateur
     */
    public Operateur(String nom, String prenom, String identifiant, String email, int idOperateur)
    {
        Log.d(TAG,
              "Operateur(" + nom + ", " + prenom + " ," + identifiant + " ," + email + " ," +
                idOperateur + ")");
        this.idOperateur = idOperateur;
        this.nom         = nom;
        this.prenom      = prenom;
        this.identifiant = identifiant;
        this.email       = email;
    }

    /**
     * Accesseurs
     */

    /**
     * @brief Accesseur de l'identifiant numérique de l'opérateur
     * @return idOperateur
     */
    public int getIdOperateur()
    {
        return this.idOperateur;
    }

    /**
     * @brief Accesseur du nom de l'opérateur
     * @return nom
     */
    public String getNom()
    {
        return this.nom;
    }

    /**
     * @brief Accesseur du prénom de l'opérateur
     * @return prenom
     */
    public String getPrenom()
    {
        return this.prenom;
    }

    /**
     * @brief Accesseur de l'identifiant de l'opérateur
     * @return identifiant
     */
    public String getIdentifiant()
    {
        return this.identifiant;
    }

    /**
     * @brief Accesseur de l'email de l'opérateur
     * @return prenom
     */
    public String getEmail()
    {
        return this.email;
    }

    /**
     * Mutateurs
     */

    /**
     * @brief Mutateur de l'identifiant numérique de l'opérateur
     * @param idOperateur
     */
    public void setIdOperateur(int idOperateur)
    {
        this.idOperateur = idOperateur;
    }
}
