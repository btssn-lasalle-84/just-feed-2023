/**
 * @file Distributeur.java
 * @brief Déclaration de la classe Distributeur
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import java.util.List;
import java.util.Map;

/**
 * @brief Définition de la classe Distributeur
 * @details La classe distributeur \c Distributeur permet de décrire un
 * distributeur pour l'opérateur. , un distributeur à un identifiant, contient
 * le prix du produit qu'il distribue, des indications sur son poids ainsi que
 * l'hydrométrie.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Distributeur
{
    /**
     * Attributs
     */
    private int       id; //!< l'identifiant d'un ditributeur.
    private int       codePostal; //!< Code postal de la ville où se trouve le distributeur.
    private String    adresse; //!< Adresse du distributeur.
    private String    ville; //!< Ville où se situe le distributeur.
    private String    lieu; //!< Lieu où se trouve le distributeur.
    private List<Bac> listeBacs; //!< les bacs du distributeur avec leurs produits et leurs poids actuel.

    /**
     * @brief Constructeur par défaut de la classe Distributeur.
     * @see Distributeur()
     */
    public Distributeur()
    {
        this.id        = 0;
        this.listeBacs = null;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Distributeur.
     * @see Distributeur(int id, int codePostal, String adresse, String Ville, String lieu, List<Bac> listeBacs)
     * @param id L'identifiant du distributeur.
     * @param codePostal Code postal de la ville.
     * @param adresse Adresse du distributeur.
     * @param ville Ville du distributeur.
     * @param lieu Lieu du distributeur.
     * @param listeBacs Les bacs du distributeur.
     */
    public Distributeur(int id, int codePostal, String adresse, String ville, String lieu, List<Bac> listeBacs)
    {
        this.id         = id;
        this.codePostal = codePostal;
        this.adresse    = adresse;
        this.ville      = ville;
        this.lieu       = lieu;
        this.listeBacs  = listeBacs;
    }

    // Accesseurs
    /**
     * @brief Accesseur de la localisation du distributeur.
     */
    public String getLocalisation()
    {
        String localisation = "";
        localisation = localisation.concat(Integer.toString(this.codePostal)+", ");
        localisation = localisation.concat(this.ville+" "+this.adresse+" "+this.lieu);

        return adresse;
    }
    /**
     * @brief Accesseur de l'identifiant du distributeur.
     * @return id du distributeur.
     */
    public int getIdentifiant()
    {
        return this.id;
    }

    /**
     * @brief Accesseur des bacs du distributeur
     * @return listeBacs , la liste des bacs du distributeur
     */
    public List<Bac> getListeBacs()
    {
        return this.listeBacs;
    }

    /**
     * @brief Mutateur du type de produit contenu dans un bac.
     * @param numeroBac le numéro du bac à changer.
     * @param nouveauProduit le nouveau produit.
     */
    public void changerProduit(int numeroBac, Produit nouveauProduit)
    {
        this.listeBacs.get(numeroBac).changerTypeProduit(nouveauProduit);
    }
}