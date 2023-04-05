package com.justfeed.justfeedandroid;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Dictionary;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;

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
    private String       heureIntervention;
    private Distributeur distributeur;
    private boolean      aIntervenir;

    public Intervention()
    {
        this.distributeur = null;
    }

    public Intervention(String heureIntervention,
                        Distributeur distributeur,
                        boolean aIntervenir)
    {
        this.heureIntervention  = heureIntervention;
        this.distributeur       = distributeur;
        this.aIntervenir        = true;
    }

    // Accesseurs
    public String getHeureIntervention() { return this.heureIntervention; }
    public int getIdentifiantDistribteur() { return this.distributeur.getIdentifiant(); }
    public boolean estAIntervenir() { return this.aIntervenir; }
    public String bacsARemplir() {
        String listeBacsARemplir = "";
        String typeProduit;
        Double quantiteARemplir;

        for(Bac bac: distributeur.getListeBacs())
        {
            if (bac.getPoidsActuel() < (bac.getPoidsTotalBac() / MOITIE) )
            {
                quantiteARemplir  = bac.getPoidsTotalBac() - bac.getPoidsActuel();
                typeProduit       = bac.getTypeProduit().getNom();
                listeBacsARemplir = listeBacsARemplir.concat(typeProduit+" : "+String.format("%.2f kg",quantiteARemplir)+"\n");
            }
        }

        return listeBacsARemplir;
    }
    public String bacsADepanner()
    {
        String listeBacsADepanner = "";

        for(Bac bac: distributeur.getListeBacs())
        {
            if(bac.getHydrometrie() > SEUIL_HUMIDITE)
            {
                listeBacsADepanner = listeBacsADepanner.concat(bac.getTypeProduit().getNom()+"\n");
            }
        }

        return listeBacsADepanner;
    }

    // Mutateurs
    public void modifierHeureIntervention(String nouvelleHeureIntervention) { this.heureIntervention = nouvelleHeureIntervention; }
    public void modifierEtatIntervention(boolean estIntervenu) { this.aIntervenir = estIntervenu; }
}