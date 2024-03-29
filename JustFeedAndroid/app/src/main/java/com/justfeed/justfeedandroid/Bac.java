/**
 * @file Bac.java
 * @brief Déclaration de la classe Bac qui permet de décrire un bac d'un distributeur
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import android.util.Log;

/**
 * @brief Définition de la classe Bac
 * @details La classe Bac \c Bac permet de décrire un
 * bac, qui est une partie d'un distributeur qui contient un produit. Un Bac à un type de Produit et
 * un poids actuel.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Bac
{
    /**
     * Constantes
     */
    private static final String TAG = "_Bac"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private String idSimulateur; //!< Simulateur auquel appartient le bac
    private Produit typeProduit; //!< Type de produit dans le bac
    private int position; //!< position du bac dans le distributeur
    private double  poidsActuel; //!< Poids actuel du bac en Kg
    private double  poidsTotal;  //!< Poids total du bac en kg
    private int     hygrometrie; //!< Taux d'humidité dans un bac
    private double  quantiteARemplir; //!< Quantité à remplir en kg
    private double  remplissage; //!< Remplissage d'un bac en pourcentage

    /**
     * @brief Constructeur par défaut de la classe Bac
     * @see Bac()
     */
    public Bac()
    {
        Log.d(TAG, "Bac()");
        this.typeProduit = null;
        this.poidsActuel = 0.0;
        this.poidsTotal  = 0.0;
        this.hygrometrie = 0;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Bac
     * @paramm distributeur distributeur auquel appartient le bac
     * @param idSimulateur simulateur du distributeur
     * @param typeProduit type de produit dans le bac
     * @param position position du bac
     * @param poidsActuel poids actuel d'un bac
     * @param poidsTotal  poids total d'un bac
     * @param hygrometrie
     * @param quantiteARemplir
     * @param remplissage
     */
    public Bac(String idSimulateur, Produit typeProduit, int position, double poidsActuel, double poidsTotal, int hygrometrie, double quantiteARemplir, double remplissage)
    {
        Log.d(TAG,
              "Bac() nomProduit = " + typeProduit.getNom() + " - poidsActuel = " + poidsActuel +
                " - poidsTotal = " + poidsTotal + " - hygrometrie = " + hygrometrie);
        this.idSimulateur     = idSimulateur;
        this.typeProduit      = typeProduit;
        this.position         = position;
        this.poidsActuel      = poidsActuel;
        this.poidsTotal       = poidsTotal;
        this.hygrometrie      = hygrometrie;
        this.quantiteARemplir = quantiteARemplir;
        this.remplissage      = remplissage;
    }

    /**
     * Accesseurs
     */

    /**
     * @brief Accesseur du distributeur du bac
     * @return identifiant du simulateur du distributeur
     */
    public String getIdSimulateur(){ return this.idSimulateur; }

    /**
     * @brief Accesseur du produit contenu dans le bac.
     * @return Produit , produit contenu dans le bac.
     */
    public Produit getTypeProduit()
    {
        return this.typeProduit;
    }

    /**
     * @brief Accesseur de la position du bac
     * @return position
     */
    public int getPosition() { return this.position; }

    /**
     * @brief Accesseur du poids actuel du bac.
     * @return poidsActuel , poids actuel en kg du bac.
     */
    public double getPoidsActuel()
    {
        return this.poidsActuel;
    }

    /**
     * @brief Accesseur du poids total d'un bac du distributeur en kg.
     * @return Le poids total d'un bac du distributeur quant-il est plein.
     */
    public double getPoidsTotalBac()
    {
        return this.poidsTotal;
    }

    /**
     * @brief Accesseur de l'hydrométrie d'un bac.
     * @return hydrometrie le taux d'humidité d'un bac.
     */
    public int getHygrometrie()
    {
        return this.hygrometrie;
    }

    /**
     * @brief Accesseur de la quantité à remplir.
     * @return quantiteARemplir , la quantité en kg à remplir
     */
    public double getQuantiteARemplir() { return this.quantiteARemplir; }

    /**
     * @brief Accesseur du taux de remplissage d'un bac
     * @return remplissage
     */
    public double getRemplissage() { return this.remplissage; }

    /**
     * Services
     */

    /**
     * @brief Change de produit.
     * @param nouveauProduit le nouveau produit.
     */
    public void changerTypeProduit(Produit nouveauProduit)
    {
        this.typeProduit = nouveauProduit;
    }

    /**
     * @brief Change le poids actuel.
     * @param nouveauPoids le nouveau poids.
     */
    public void changerPoidsActuel(double nouveauPoids)
    {
        this.poidsActuel = nouveauPoids;
    }

    /**
     * @brief Change la quantité à remplir.
     * @param nouvelleQuantite la nouvelle quantité.
     */
    public void changerQuantiteARemplir(double nouvelleQuantite) { this.quantiteARemplir = nouvelleQuantite; }
}