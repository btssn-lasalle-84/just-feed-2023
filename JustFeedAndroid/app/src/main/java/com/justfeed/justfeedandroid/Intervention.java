/**
 * @file Intervention.java
 * @brief Déclaration de la classe Intervention
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

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
    private final int SEUIL_HUMIDITE = 0; //!< Seuil du taux d'humidité d'un distributeur.
    private final int MOITIE         = 2; //!< Moitie d'un bac.

    /**
     * Attributs
     */
    private String       heureIntervention; //!< Heure de l'intervention.
    private Distributeur distributeur;      //!< Distributeur où intervenir.
    private boolean      aIntervenir;       //!< Si l'intervention a été ménée ou non.

    /**
     * @brief Constructeur par défaut de classe Intervention.
     */
    public Intervention()
    {
        this.distributeur = null;
    }

    /**
     * @brief Constructeur d'initialisation de la classe Intervention.
     * @param heureIntervention
     * @param distributeur
     * @param aIntervenir
     */
    public Intervention(String heureIntervention, Distributeur distributeur, boolean aIntervenir)
    {
        this.heureIntervention = heureIntervention;
        this.distributeur      = distributeur;
        this.aIntervenir       = true;
    }

    // Accesseurs

    /**
     * @brief Méthode d'accés à l'heure d'intervention.
     * @return l'heure de l'intervention.
     */
    public String getHeureIntervention()
    {
        return this.heureIntervention;
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
     * @brief Méthode d'accés à aIntervenir.
     * @return aIntervenir.
     */
    public boolean estAIntervenir()
    {
        return this.aIntervenir;
    }

    /**
     * @brief Méthode qui renvoie la liste des bacs à remplir.
     * @return la liste des bacs à remplir.
     */
    public String bacsARemplir()
    {
        String listeBacsARemplir = "";
        String typeProduit;
        Double quantiteARemplir;

        for(Bac bac: distributeur.getListeBacs())
        {
            if(bac.getPoidsActuel() < (bac.getPoidsTotalBac() / MOITIE))
            {
                quantiteARemplir  = bac.getPoidsTotalBac() - bac.getPoidsActuel();
                typeProduit       = bac.getTypeProduit().getNom();
                listeBacsARemplir = listeBacsARemplir.concat(
                  typeProduit + " : " + String.format("%.2f kg", quantiteARemplir) + "\n");
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
     * @brief Méthode pour modifier l'heure d'intervention.
     * @param nouvelleHeureIntervention
     */
    public void modifierHeureIntervention(String nouvelleHeureIntervention)
    {
        this.heureIntervention = nouvelleHeureIntervention;
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