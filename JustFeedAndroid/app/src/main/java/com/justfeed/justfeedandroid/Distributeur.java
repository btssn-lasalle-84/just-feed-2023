/**
 * @file Distributeur.java
 * @brief Déclaration de la classe Distributeur
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import android.util.Log;

import java.util.List;
import java.util.Map;

/**
 * @brief Définition de la classe Distributeur
 * @details La classe distributeur \c Distributeur permet de décrire un
 * distributeur pour l'opérateur. , un distributeur à un identifiant, contient
 * le prix du produit qu'il distribue, des indications sur son poids ainsi que
 * l'hydrométrie.
 * @author Fargier Mayeul
 * @version 0.2
 */
public class Distributeur
{
    /**
     * Constantes
     */
    private static final String TAG = "_Distributeur"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    private int    id;              //!< l'identifiant d'un ditributeur.
    private String codePostal;      //!< Code postal de la ville où se trouve le distributeur.
    private String adresse;         //!< Adresse du distributeur.
    private String ville;           //!< Ville où se situe le distributeur.
    private String nomDistributeur; //!< Lieu où se trouve le distributeur.
    private String coordGeographiques; //!< Coordonnées Géographiques des distributeurs.
    private List<Bac>
      listeBacs; //!< les bacs du distributeur avec leurs produits et leurs poids actuel.

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
     * @see Distributeur(int id, String codePostal, String adresse, String Ville, String
     *   nomDistributeur, String coordGeographiques,List<Bac> listeBacs)
     * @param id L'identifiant du distributeur.
     * @param codePostal Code postal de la ville.
     * @param adresse Adresse du distributeur.
     * @param ville Ville du distributeur.
     * @param nomDistributeur Nom du distributeur.
     * @param coordGeographiques Géo-localisation du distributeur.
     * @param listeBacs Les bacs du distributeur.
     */
    public Distributeur(int       id,
                        String    codePostal,
                        String    adresse,
                        String    ville,
                        String    nomDistributeur,
                        String    coordGeographiques,
                        List<Bac> listeBacs)
    {
        Log.d(TAG, "Distributeur() id = " + id + " - nomDistributeur = " + nomDistributeur + " - nb bacs = " + listeBacs.size() );
        this.id                 = id;
        this.codePostal         = codePostal;
        this.adresse            = adresse;
        this.ville              = ville;
        this.nomDistributeur    = nomDistributeur;
        this.coordGeographiques = coordGeographiques;
        this.listeBacs          = listeBacs;
    }

    // Accesseurs
    /**
     * @brief Accesseur de la localisation du nomDistributeur.
     */
    public String getNom()
    {
        return nomDistributeur;
    }

    /**
     * @brief Accesseur de la localisation du distributeur.
     */
    public String getLocalisation()
    {
        String localisation = "";
        localisation        = localisation.concat(this.codePostal + ", ");
        localisation =
          localisation.concat(this.ville + " " + this.adresse + " " + this.nomDistributeur);

        return localisation;
    }

    public String getCoordGeographiques() { return this.coordGeographiques; }

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
     * @brief Accesseur du nombre de bacs du distributeur
     * @return int le nombre de bacs
     */
    public int getNbBacs()
    {
        return this.listeBacs.size();
    }

    /**
     * @brief Mutateur du type de produit contenu dans un bac.
     * @param numeroBac le numéro du bac à changer.
     * @param nouveauProduit le nouveau produit.
     */
    public void changerProduit(int numeroBac, Produit nouveauProduit)
    {
        this.listeBacs.get(numeroBac).changerTypeProduit(nouveauProduit);
    }

    /**
     * @brief Mutateur de la liste des bacs.
     * @param nouveauBac le bac à ajouter.
     */
    public void ajouterBac(Bac nouveauBac)
    {
        this.listeBacs.add(nouveauBac);
    }
}