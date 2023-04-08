package com.justfeed.justfeedandroid;

/**
 * @brief Définition de la Classe Produit.
 * @details La classe Produit décrit un type de produit, avec ses propriétés : nom, poids, prix.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Produit
{
    private double prix;           //!< prix du produit pour 100g
    private double poidsDuProduit; //!< poids en kg à l'unité du produit

    private double       volumeProduit; //!< Volume du produit en dm3
    private final String nom;           //!< nom du produit

    /**
     * @brief Constructeur d'initialisation de la classe Produit.
     * @see Produit(double prix, double poidsDuProduit, double volumeProduit, String nom)
     * @param prix le prix du produit.
     * @param poidsDuProduit le poid du produit à l'unité.
     * @param volumeProduit le volume du produit.
     * @param nom le nom du produit.
     */
    public Produit(double prix, double poidsDuProduit, double volumeProduit, String nom)
    {
        this.prix           = prix;
        this.poidsDuProduit = poidsDuProduit;
        this.volumeProduit  = volumeProduit;
        this.nom            = nom;
    }

    // Accesseurs
    /**
     * @brief Accesseur du prix du produit.
     * @return prix le prix du produit
     */
    public double getPrix()
    {
        return this.prix;
    }

    /**
     * @brief Accesseur du poids du produit.
     * @return poidsDuProduit le poids du produit à l'unité
     */
    public double getPoidsDuProduit()
    {
        return this.poidsDuProduit;
    }

    /**
     * @brief Accesseur du volume du produit.
     * @return volumeProduit le volume du produit à l'unité
     */
    public double getVolume()
    {
        return this.volumeProduit;
    }

    /**
     * @brief Accesseur du nom du produit.
     * @return nom le nom du produit
     */
    public String getNom()
    {
        return this.nom;
    }

    // Mutateur
    /**
     * @brief Mutateur du prix du produit.
     * @param nouveauPrix le nouveau prix du produit
     */
    public void modifierPrix(int nouveauPrix)
    {
        this.prix = nouveauPrix;
    }
}
