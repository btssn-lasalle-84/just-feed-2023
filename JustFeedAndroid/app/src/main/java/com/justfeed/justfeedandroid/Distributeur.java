package com.justfeed.justfeedandroid;

/**
 * @brief Définition de la classe Distributeur
 * @details La classe distributeur \c Distributeur permet de décrire un distributeur pour l'opérateur.
 * , un distributeur à un identifiant, contient le prix du produit qu'il distribue, des indications
 * sur son poids ainsi que l'hydrométrie.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Distributeur {
    private int id; //!< Nombre pour identifier le ditributeur.
    private float poidsTotal; //!< Nombre pour indiquer le poids total du distributeur.
    private float poidsActuel; //!< Nombre pour indiquer le poids actuel du distributeur.
    private int hydrometrie; //!< Mesure du degré d'humidité présent dans le distributeur.

    private Produit produit; //!< Type de produit présent dans le distributeur.

    private boolean aRemplir; //<! Le distributeur a besoin d'être remplie ou non.

    /**
     * @brief Constructeur par défaut de la classe Distributeur.
     * @see Distributeur()
     */
    public Distributeur(){
        this.id = 0;
        this.poidsTotal = 0;
        this.poidsActuel = 0;
        this.hydrometrie = 0;

        this.produit = null;

        this.aRemplir = false;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Distributeur.
     * @see Distributeur(int id, int prix, int poidsTotal, int poidsActuel, int hydrometrie, Produit produit)
     * @param id L'identifiant du distributeur.
     * @param poidsTotal Le poids total du contenue du distributeur.
     * @param poidsActuel Le poids actuel du contenue du distributeur.
     * @param hydrometrie Le degré d'humidité présent dans le distributeur.
     * @param produit Type de produit dans le distributeur.
     */
    public Distributeur(int id, float poidsTotal, float poidsActuel, int hydrometrie, Produit produit){
        this.id = id;
        this.poidsTotal = poidsTotal;
        this.poidsActuel = poidsActuel;
        this.hydrometrie = hydrometrie;

        this.produit = produit;

        this.aRemplir = false;
    }

    //Accesseurs

    /**
     * @brief Accesseur de l'identifiant du distributeur.
     * @return id du distributeur.
     */
    public int getIdentifiant() {
        return this.id;
    }
    /**
     * @brief Accesseur du poids total du distributeur.
     * @return poidsTotal la valeur du poids total du distributeur.
     */
    public float getPoidsTotal(){
        return this.poidsTotal;
    }
    /**
     * @brief Accesseur du poids actuel du distributeur.
     * @return poidsActuel la valeur du poids actuel du distributeur.
     */
    public float getPoidsActuel(){
        return this.poidsActuel;
    }
    /**
     * @brief Accesseur de l'hydrométrie du distributeur.
     * @return hydrometrie la valeur de l'hydrométrie du distributeur.
     */
    public int getHydrometrie(){
        return this.hydrometrie;
    }
    /**
     * @brief Accesseur du type de produit du distributeur.
     * @return produit le type du produit.
     */
    public Produit getProduit(){
        return this.produit;
    }
    /**
     * @brief Accesseur de l'état du distributeur.
     * @return aRemplir le booléen qui indique si la machine est à remplir.
     */
    public boolean estRemplie(){
        return this.aRemplir;
    }

    //Mutateurs
    /**
     * @brief Mutateur du poids total du distributeur.
     * @param nouveauPoids.
     */
    public void changerPoidsTotal(float nouveauPoids){
        this.poidsTotal = nouveauPoids;
    }
    /**
     * @brief Mutateur du type de produit.
     * @param nouveauProduit.
     */
    public void changerProduit(Produit nouveauProduit){
        this.produit = nouveauProduit;
    }
    /**
     * @brief Mutateur de l'état du distributeur.
     * @param nouvelEtat.
     */
    public void changerEtat(boolean nouvelEtat){
        this.aRemplir = nouvelEtat;
    }
}
