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
     * Constantes
     */
    private final int VOLUME_BACS = 8; //!< Volume en dm3 d'un bac de 8 litres.
    private final int MOITIE      = 2;

    /**
     * Attributs
     */
    private int                  id; //!< identifie le ditributeur.

    private Map<Produit, String> bacs; //!< Identifie les bacs du distributeur avec leurs produits et leurs poids actuel.
    private int                  hydrometrie; //!< pourcentage d'humidité présent dans le distributeur.
    private List<Produit>        produits; //!< produits présents dans le distributeur.

    /**
     * @brief Constructeur par défaut de la classe Distributeur.
     * @see Distributeur()
     */
    public Distributeur()
    {
        this.id          = 0;
        this.bacs        = null;
        this.hydrometrie = 0;
        this.produits    = null;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Distributeur.
     * @see Distributeur(int id, Map<Produit, String> bacs, int hydrometrie, List<Produit> produits)
     * @param id L'identifiant du distributeur.
     * @param bacs Les bacs du distributeur.
     * @param hydrometrie Le degré d'humidité présent dans le distributeur.
     * @param produits Produits disponibles dans le distributeur.
     */
    public Distributeur(int     id,
                        Map<Produit, String> bacs,
                        int     hydrometrie,
                        List<Produit> produits)
    {
        this.id          = id;
        this.bacs        = bacs;
        this.hydrometrie = hydrometrie;
        this.produits    = produits;
    }

    // Accesseurs
    /**
     * @brief Accesseur de l'identifiant du distributeur.
     * @return id du distributeur.
     */
    public int getIdentifiant()
    {
        return this.id;
    }
    /**
     * @brief Accesseur du poids total d'un bac du distributeur en kg.
     * @return Le poids total d'un bac du distributeur quant-il est plein.
     */
    public double getPoidsTotalBac(Produit produit)
    {
        return ( VOLUME_BACS / produit.getVolume() ) * produit.getPoidsDuProduit();
    }
    /**
     * @brief Accesseur du poids actuel d'un bac en kg.
     * @return le poids actuel d'un bac.
     */
    public String getPoidsActuel(Produit produit)

    {
        return this.bacs.get(produit);
    }
    /**
     * @brief Accesseur de l'hydrométrie du distributeur.
     * @return hydrometrie la valeur de l'hydrométrie du distributeur.
     */
    public int getHydrometrie()
    {
        return this.hydrometrie;
    }
    /**
     * @brief Accesseur da la liste de produits du distributeur.
     * @return produits la liste des produits disponibles.
     */
    public List<Produit> getProduits()
    {
        return this.produits;
    }
    /**
     * @brief Accesseur de l'état du distributeur.
     * @return aRemplir le booléen qui indique si la machine est à remplir.
     */
    public boolean estRemplie(Produit produit)
    {
        boolean aRemplir = false;
        if (Integer.parseInt(this.bacs.get(produit)) <= (getPoidsTotalBac(produit)/MOITIE))
        {
            aRemplir = true;
        }
        return aRemplir;
    }

    /**
     * @brief Mutateur du type de produit.
     * @param nouveauxProduits.
     */
    public void changerProduit(Produit ancienProduit, Produit nouveauProduit)
    {
        this.produits.set(produits.indexOf(ancienProduit), nouveauProduit);
    }
}