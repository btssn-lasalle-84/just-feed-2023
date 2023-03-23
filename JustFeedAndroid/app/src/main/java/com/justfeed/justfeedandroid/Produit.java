package com.justfeed.justfeedandroid;

/**
 * @brief Définition de la Classe Produit.
 * @details La classe Produit décrit un type de produit, avec ses propriétés : nom, poids, prix.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Produit {
    private int prix; //!< prix du produit
    private final int poidsDuProduit; //!< poids à l'unité du produit
    private final String nom; //!< nom du produit

    /**
     * @brief Constructeur d'initialisation de la classe Produit.
     * @see Produit(int prix, int poidsDuProduit, String nom)
     * @param prix le prix du produit.
     * @param poidsDuProduit le poid du produit à l'unité.
     * @param nom le nom du produit.
     */
    public Produit(int prix, int poidsDuProduit, String nom){
        this.prix = prix;
        this.poidsDuProduit = poidsDuProduit;

        this.nom = nom;
    }

    //Accesseurs
    /**
     * @brief Accesseur du prix du produit.
     * @return prix le prix du produit
     */
    public int getPrix(){
        return this.prix;
    }

    /**
     * @brief Accesseur du poids du produit.
     * @return poidsDuProduit le poids du produit à l'unité
     */
    public int getPoidsDuProduit(){
        return this.poidsDuProduit;
    }

    /**
     * @brief Accesseur du nom du produit.
     * @return nom le nom du produit
     */
    public String getNom(){
        return this.nom;
    }

    //Mutateur
    /**
     * @brief Mutateur du prix du produit.
     * @param nouveauPrix le nouveau prix du produit
     */
    public void modifierPrix(int nouveauPrix){
        this.prix = nouveauPrix;
    }
}
