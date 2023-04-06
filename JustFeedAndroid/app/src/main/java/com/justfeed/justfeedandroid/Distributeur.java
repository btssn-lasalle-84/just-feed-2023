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
    private int id; //!< identifie le ditributeur.
    private List<Bac>
      listeBacs; //!< Identifie les bacs du distributeur avec leurs produits et leurs poids actuel.

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
     * @see Distributeur(int id, List<Bac> listeBacs)
     * @param id L'identifiant du distributeur.
     * @param listeBacs Les bacs du distributeur.
     */
    public Distributeur(int id, List<Bac> listeBacs)
    {
        this.id        = id;
        this.listeBacs = listeBacs;
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
    public List<Bac> getListeBacs()
    {
        return this.listeBacs;
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