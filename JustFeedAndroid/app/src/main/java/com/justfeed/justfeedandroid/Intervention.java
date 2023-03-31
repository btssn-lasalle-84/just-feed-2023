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
    private final int    SEUIL_HUMIDITE = 0;
    private final int    MOITIE         = 2;
    /**
     * Attributs
     */
    private String  heureIntervention;
    private double  poidsARemplir;
    private boolean aRemplir;
    private boolean aDepanner;
    private boolean estIntervenu;

    public Intervention()
    {
        this.poidsARemplir      = 0.0;
        this.aRemplir           = false;
        this.aDepanner          = false;
        this.estIntervenu       = false;
    }

    public Intervention(String heureIntervention,
                        double poidsARemplir,
                        boolean aRemplir,
                        boolean aDepanner)
    {
        this.heureIntervention  = heureIntervention;
        this.poidsARemplir      = poidsARemplir;
        this.aRemplir           = aRemplir;
        this.aDepanner          = aDepanner;
        this.estIntervenu       = false;
    }

    // Accesseurs
    public String getHeureIntervention() { return this.heureIntervention; }
    public double getPoidsARemplir() { return this.poidsARemplir; }
    public boolean estARemplir() { return this.aRemplir; }
    public boolean estADepanner() { return this.aDepanner; }
    public boolean interventionTerminee() { return this.estIntervenu; }

    // Mutateurs
    public void modifierHeureIntervention(String nouvelleHeureIntervention) { this.heureIntervention = nouvelleHeureIntervention; }
    public void modifierEtatIntervention(boolean estIntervenu) { this.estIntervenu = estIntervenu; }
    public void modifierIntervention(double poidsActuel, double poidsTotal, int hydrometrie)
    {
        if (poidsActuel < (poidsTotal / MOITIE) )
        {
            this.aRemplir = true;
        }
        else
        {
            this.aRemplir = false;
        }

        if (hydrometrie > SEUIL_HUMIDITE)
        {
            this.aDepanner = true;
        }
        else
        {
            this.aDepanner = false;
        }
    }
}
