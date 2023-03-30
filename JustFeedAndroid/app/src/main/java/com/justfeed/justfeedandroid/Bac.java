package com.justfeed.justfeedandroid;

/**
 * @brief Définition de la classe Bac
 * @details La classe Bac \c Bac permet de décrire un
 * bac, qui est une partie d'un distributeur qui contient un produit. Un Bac à un type de Produit et un poids actuel.
 * @author Fargier Mayeul
 * @version 0.1
 */

public class Bac
{
    /**
     * Attributs
     */
    private Produit typeProduit; //!< Type de produit dans le bac
    private double  poidsActuel; //!< Poids actuel du bac en Kg

    /**
     * @brief Constructeur par défaut de la classe Bac
     * @see Bac()
     */
    public Bac()
    {
        this.typeProduit = null;
        this.poidsActuel = 0.0;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Bac
     * @see Bac(Produit typeProduit, double poidsActuel)
     * @param typeProduit typroduit, type de produit dans le bac
     * @param poidsActuel poidsActuel, poids actuel d'un bac
     */
    public Bac(Produit typeProduit, double poidsActuel)
    {
        this.typeProduit = typeProduit;
        this.poidsActuel = poidsActuel;
    }

    /**
     * Accesseurs
     */
    public Produit getTypeProduit(){ return this.typeProduit; }
    public double getPoidsActuel(){ return this.poidsActuel; }

    /**
     * Mutateurs
     */
    public void changerTypeProduit(Produit nouveauProduit){ this.typeProduit = nouveauProduit; }
    public void changerPoidsActuel(double nouveauPoids){ this.poidsActuel = nouveauPoids; }
}
