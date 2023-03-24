package com.justfeed.justfeedandroid;

/**
 * @brief Définition de la classe Intervention.
 * @details La classe Intervention \c Intervention permet de décrire une Intervention pour l'opérateur.
 * elle contient toutes les informations liées à une intervention : heure, trajet, type d'intervention, poids à remplir...
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Intervention
{
    private int numeroIntervention;
    private String heureIntervention;
    private String tempsTrajet;
    private double poidsARemplir;
    private boolean estIntervenu;

    public Intervention()
    {
        this.numeroIntervention = 0;
        this.poidsARemplir = 0.0;
        this.estIntervenu = false;
    }

    public Intervention(int numeroIntervention, String heureIntervention, String tempsTrajet, double poidsARemplir)
    {
        this.numeroIntervention = numeroIntervention;
        this.heureIntervention = heureIntervention;
        this.tempsTrajet = tempsTrajet;
        this.poidsARemplir = poidsARemplir;
        this.estIntervenu = false;
    }

    //Accesseurs
    public String getHeureIntervention(){
        return this.heureIntervention;
    }
    public String getTempsTrajet(){
        return this.tempsTrajet;
    }
    public double getPoidsARemplir(){
        return this.poidsARemplir;
    }
    public boolean interventionTerminee(){
        return this.estIntervenu;
    }

    //Mutateurs
    public void modifierHeureIntervention(String nouvelleHeureIntervention)
    {
        this.heureIntervention = nouvelleHeureIntervention;
    }
    public void modifierEtatIntervention(boolean estIntervenu){
        this.estIntervenu = estIntervenu;
    }
}
