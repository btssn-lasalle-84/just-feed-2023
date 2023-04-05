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
    private double  poidsTotal; //!< Poids total du bac en kg
    private int     hydrometrie; //!< Taux d'humidité dans un bac

    /**
     * @brief Constructeur par défaut de la classe Bac
     * @see Bac()
     */
    public Bac()
    {
        this.typeProduit  = null;
        this.poidsActuel  = 0.0;
        this.poidsTotal   = 0.0;
        this.hydrometrie  = 0;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Bac
     * @see Bac(Produit typeProduit, double poidsActuel, double poidsTotal, int hydrometrie)
     * @param typeProduit , type de produit dans le bac
     * @param poidsActuel , poids actuel d'un bac
     * @param poidsTotal  , poids total d'un bac
     */
    public Bac(Produit typeProduit, double poidsActuel, double poidsTotal, int hydrometrie)
    {
        this.typeProduit  = typeProduit;
        this.poidsActuel  = poidsActuel;
        this.poidsTotal   = poidsTotal;
        this.hydrometrie  = hydrometrie;
    }

    /**
     * Accesseurs
     */
    /**
     * @brief Accesseur du produit contenu dans le bac.
     * @return Produit , produit contenu dans le bac.
     */
    public Produit getTypeProduit(){ return this.typeProduit; }
    /**
     * @brief Accesseur du poids actuel du bac.
     * @return poidsActuel , poids actuel en kg du bac.
     */
    public double getPoidsActuel(){ return this.poidsActuel; }
    /**
     * @brief Accesseur du poids total d'un bac du distributeur en kg.
     * @return Le poids total d'un bac du distributeur quant-il est plein.
     */
    public double getPoidsTotalBac() { return this.poidsTotal; }
    /**
     * @brief Accesseur de l'hydrométrie d'un bac.
     * @return hydrometrie le taux d'humidité d'un bac.
     */
    public int getHydrometrie()
    {
        return this.hydrometrie;
    }
    /**
     * Mutateurs
     */
    public void changerTypeProduit(Produit nouveauProduit){ this.typeProduit = nouveauProduit; }
    public void changerPoidsActuel(double nouveauPoids){ this.poidsActuel = nouveauPoids; }
}