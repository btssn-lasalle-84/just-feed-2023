package com.justfeed.justfeedandroid;

/**
 * @brief Définition de la classe Intervention.
 * @details La classe Intervention \c Intervention permet de décrire une Intervention pour l'opérateur.
 * elle contient toutes les informations liées à une intervention : heure, trajet, type d'intervention, poids à remplir...
 * @author Fargier Mayeul
 * @version 0.1
 */
public class Intervention {
    private String heureIntervention;
    private String tempsTrajet;

    private float poidsARemplir;

    private final int numeroIntervention;

    private boolean estIntervenu;

    public Intervention(){
        this.poidsARemplir = 0;
        this.numeroIntervention = 0;
        this.estIntervenu = false;
    }

    public Intervention(String heureIntervention, String tempsTrajet, float poidsARemplir, int numeroIntervention){
        this.heureIntervention = heureIntervention;
        this.tempsTrajet = tempsTrajet;
        this.poidsARemplir = poidsARemplir;
        this.numeroIntervention = numeroIntervention;
        this.estIntervenu = false;
    }

    //Accesseurs
    public String getHeureIntervention(){
        return this.heureIntervention;
    }
    public String getTempsTrajet(){
        return this.tempsTrajet;
    }
    public float getPoidsARemplir(){
        return this.poidsARemplir;
    }
    public boolean interventionTerminee(){
        return this.estIntervenu;
    }

    //Mutateurs
    public void modifierHeureIntervention(String nouvelleHeureIntervention){
        this.heureIntervention = nouvelleHeureIntervention;
    }
    public void modifierEtatIntervention(boolean estIntervenu){
        this.estIntervenu = estIntervenu;
    }
}
