/**
 * @file Produit.java
 * @brief Déclaration de la classe Produit
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import android.util.Log;

/**
 * @brief Définition de la Classe Produit.
 * @details La classe Produit décrit un type de produit, avec ses propriétés : nom, poids, prix.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Produit
{
    /**
     * Constantes
     */
    private static final String TAG = "_Produit"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private final String nom;            //!< nom du produit
    private double       prix;           //!< prix du produit pour 100g
    private double       poidsDuProduit; //!< poids en kg à l'unité du produit
    private double       volumeProduit;  //!< Volume du produit en dm3

    /**
     * @brief Constructeur d'initialisation de la classe Produit.
     * @see Produit(String nom, double prix, double poidsDuProduit, double volumeProduit)
     * @param prix le prix du produit.
     * @param poidsDuProduit le poid du produit à l'unité.
     * @param volumeProduit le volume du produit.
     * @param nom le nom du produit.
     */
    public Produit(String nom, double prix, double poidsDuProduit, double volumeProduit)
    {
        Log.d(TAG, "Produit() nom = " + nom + " - prix = " + prix + " - poidsDuProduit = " + poidsDuProduit + " - volumeProduit = " + volumeProduit);
        this.nom            = nom;
        this.prix           = prix;
        this.poidsDuProduit = poidsDuProduit;
        this.volumeProduit  = volumeProduit;
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
    public void modifierPrix(double nouveauPrix)
    {
        BaseDeDonnees baseDeDonnees = BaseDeDonnees.getInstance();
        this.prix = nouveauPrix;

        baseDeDonnees.executerRequete(
                "UPDATE `Produit` SET `prix` = "+prix+" WHERE nomProduit = "+"\""+this.nom+"\""
        );
    }
}
