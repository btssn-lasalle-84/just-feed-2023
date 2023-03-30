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

    private List<Bac>            listeBacs; //!< Identifie les bacs du distributeur avec leurs produits et leurs poids actuel.
    private int                  hydrometrie; //!< pourcentage d'humidité présent dans le distributeur.

    /**
     * @brief Constructeur par défaut de la classe Distributeur.
     * @see Distributeur()
     */
    public Distributeur()
    {
        this.id          = 0;
        this.listeBacs   = null;
        this.hydrometrie = 0;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Distributeur.
     * @see Distributeur(int id, List<Bac> listeBacs, int hydrometrie)
     * @param id L'identifiant du distributeur.
     * @param listeBacs Les bacs du distributeur.
     * @param hydrometrie Le degré d'humidité présent dans le distributeur.
     */
    public Distributeur(int     id,
                        List<Bac> listeBacs,
                        int     hydrometrie)
    {
        this.id          = id;
        this.listeBacs   = listeBacs;
        this.hydrometrie = hydrometrie;
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
     * @brief Accesseur des bacs du distributeur
     * @return listeBacs , la liste des bacs du distributeur
     */
    public List<Bac> getListeBacs() { return this.listeBacs; }
    /**
     * @brief Accesseur du poids total d'un bac du distributeur en kg.
     * @return Le poids total d'un bac du distributeur quant-il est plein.
     */
    public double getPoidsTotalBac(int numeroBac)
    {
        Produit produit = listeBacs.get(numeroBac).getTypeProduit();
        return ( VOLUME_BACS / produit.getVolume() ) * produit.getPoidsDuProduit();
    }
    /**
     * @brief Accesseur du poids actuel d'un bac en kg.
     * @return le poids actuel d'un bac.
     */
    public double getPoidsActuel(int numeroBac)
    {
        return listeBacs.get(numeroBac).getPoidsActuel();
    }
    /**
     * @brief Accesseur du produits présent dans un bac du distributeur.
     * @return le type de produit contenu dans le bac.
     */
    public Produit getProduits(int numeroBac)
    {
        return listeBacs.get(numeroBac).getTypeProduit();
    }
    /**
     * @brief Accesseur de l'état d'un bac du distributeur.
     * @return aRemplir le booléen qui indique si le bac est à remplir.
     */
    public boolean estRemplie(int numeroBac)
    {
        /**
         * @todo rajouter un booléen estImportant pour définir si le remplissage est vraiment nécessaire
         */
        boolean aRemplir = false;
        if (listeBacs.get(numeroBac).getPoidsActuel() <= (getPoidsTotalBac(numeroBac)/MOITIE))
        {
            aRemplir = true;
        }
        return aRemplir;
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
     * @brief Mutateur du type de produit contenu dans un bac.
     * @param nouveauxProduits.
     */
    public void changerProduit(int numeroBac, Produit nouveauProduit)
    {
        this.listeBacs.get(numeroBac).changerTypeProduit(nouveauProduit);
    }
}