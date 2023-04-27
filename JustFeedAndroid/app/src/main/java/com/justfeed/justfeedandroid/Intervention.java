/**
 * @file Intervention.java
 * @brief Déclaration de la classe Intervention
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import android.util.Log;

/**
 * @brief Définition de la classe Intervention.
 * @details La classe Intervention \c Intervention permet de décrire une Intervention pour
 * l'opérateur. elle contient toutes les informations liées à une intervention : heure, trajet, type
 * d'intervention, poids à remplir...
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Intervention
{
    /**
     * Constantes
     */
    private static final String TAG = "_Intervention"; //!< TAG pour les logs (cf. Logcat)
    private final int SEUIL_HUMIDITE = 12; //!< Seuil du taux d'humidité d'un distributeur.

    /**
     * Attributs
     */
    private String       dateIntervention; //!< Heure de l'intervention.
    private Distributeur distributeur;     //!< Distributeur où intervenir.
    private boolean      aIntervenir;      //!< Si l'intervention a été ménée ou non.
    private boolean      aRemplir;         //!< Si l'intervention consiste à remplir.
    private boolean      aDepanner;        //!< Si l'intervention consiste à dépanner.

    /**
     * @brief Constructeur par défaut de classe Intervention.
     */
    public Intervention()
    {
        this.distributeur = null;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Intervention.
     * @param dateIntervention
     * @param distributeur
     * @param aIntervenir
     * @param aRemplir
     * @param aDepanner
     */
    public Intervention(String dateIntervention, Distributeur distributeur, boolean aIntervenir, boolean aRemplir, boolean aDepanner)
    {
        Log.d(TAG,
                "Intervention() dateIntervention = " + dateIntervention + " - nomdistributeur = " + distributeur.getNom() +
                        " - aIntervenir = " + aIntervenir);
        this.dateIntervention = dateIntervention;
        this.distributeur     = distributeur;
        this.aIntervenir      = true;
        this.aRemplir         = aRemplir;
        this.aDepanner        = aDepanner;
    }

    // Accesseurs

    /**
     * @brief Méthode d'accés à l'heure d'intervention.
     * @return l'heure de l'intervention.
     */
    public String getDateIntervention()
    {
        return this.dateIntervention;
    }

    /**
     * @brief Méthode d'accés à l'identifiant du distributeur.
     * @return l'identifiant du distributeur.
     */
    public int getIdentifiantDistribteur()
    {
        return this.distributeur.getIdentifiant();
    }

    /**
     * @brief Méthode d'accés au nom du distributeur.
     * @return le nom du distributeur.
     */
    public String getNomDistribteur()
    {
        return this.distributeur.getNom();
    }

    /**
     * @brief Méthode d'accés à aIntervenir.
     * @return aIntervenir.
     */
    public boolean estAIntervenir()
    {
        return this.aIntervenir;
    }

    /**
     * @brief Méthode d'accés à aRemplir.
     * @return aRemplir
     */
    public boolean estARemplir() { return this.aRemplir; }

    /**
     * @brief Méthode d'accés à aDepanner.
     * @return aDepanner
     */
    public boolean estADepanner() { return this.aDepanner; }

    /**
     * Services
     */

    /**
     * @brief Méthode qui renvoie la liste des bacs à remplir.
     * @return la liste des bacs à remplir.
     */
    public String bacsARemplir()
    {
        String listeBacsARemplir = "";
        String typeProduit;

        for(Bac bac: distributeur.getListeBacs())
        {
            if(bac.getQuantiteARemplir() != 0.)
            {
                typeProduit       = bac.getTypeProduit().getNom();
                listeBacsARemplir = listeBacsARemplir.concat(
                  typeProduit + " : " + String.format("%.2f kg", bac.getQuantiteARemplir()) + "\n");
            }
        }

        return listeBacsARemplir;
    }

    /**
     * @brief Méthode qui renvoie la liste des bacs à dépanner.
     * @return la liste des bacs à dépanner.
     */
    public String bacsADepanner()
    {
        String listeBacsADepanner = "";

        for(Bac bac: distributeur.getListeBacs())
        {
            if(bac.getHygrometrie() > SEUIL_HUMIDITE)
            {
                listeBacsADepanner =
                  listeBacsADepanner.concat(bac.getTypeProduit().getNom() + "\n");
            }
        }

        return listeBacsADepanner;
    }

    // Mutateurs

    /**
     * @brief Méthode pour modifier la date d'intervention.
     * @param nouvelleDateIntervention
     */
    public void modifierdateIntervention(String nouvelleDateIntervention)
    {
        this.dateIntervention = nouvelleDateIntervention;
    }

    /**
     * @brief Méthode pour modifier l'état de l'intervention.
     * @param estIntervenu
     */
    public void modifierEtatIntervention(boolean estIntervenu)
    {
        this.aIntervenir = estIntervenu;
    }
}