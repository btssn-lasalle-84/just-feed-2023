package com.justfeed.justfeedandroid;

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
     * Attributs
     */
    private String nom; //!< Nom de l'opérateur
    private String prenom; //!< Prénom de l'opérateur
    private int idOperateur; //!< Identifiant de l'opérateur

    /**
     * @brief Constructeur d'initialisation de la classe Operateur
     * @param nom , nom de l'opérateur
     * @param prenom , prenom de l'opérateur
     * @param idOperateur , identifiant de l'opérateur
     */
    public Operateur(String nom, String prenom, int idOperateur)
    {
        this.nom         = nom;
        this.prenom      = prenom;
        this.idOperateur = idOperateur;
    }

    /**
     * Accesseurs
     */

    /**
     * @brief Accesseur du nom de l'opérateur
     * @return nom
     */
    public String getNom() { return this.nom; }

    /**
     * @brief Accesseur du prénom de l'opérateur
     * @return prenom
     */
    public String getPrenom() { return this.prenom; }

    /**
     * @brief Accesseur de l'identifiant numérique de l'opérateur
     * @return idOperateur
     */
    public int getIdOperateur() { return this.idOperateur; }
}
