/**
 * @file        Intervention.h
 * @brief       Définition de la classe Intervention.
 * @detail      La classe Intervention \c Cette classe permet de définir les attributs et les méthodes de la classe.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
*/
#ifndef INTERVENTION_H
#define INTERVENTION_H
#include <ctime>

class Intervention
{
private:
    time_t heureIntervention; //!< heure de l'intervention
    int numeroIntervention; //!< numéro qui identifie l'intervention
    time_t tempsTrajet; //!< temps de trajet vers le distributeur
    float poidsARemplir; //!< poids à prévoir pour remplir le distributeur
    //float localisation; //!< localisation de l'intervetion //à déterminer
public:
    Intervention();
    /**
     * @brief Constructeur par défault de la classe Intervention
     * @see Intervention
     */
    ~Intervention();
    /**
     * @brief Destructeur de la classe Intervention
     * @see Intervention
     */
    //Accesseur
    time_t getHeureIntervention();
    /**
     * @brief Accesseur de l'attribut heureIntervention.
     * @return un time_t qui represente l'heure de l'intervention sur le distributeur
     */
    int getNumeroIntervention();
    /**
     * @brief Accesseur de l'attribut numeroIntervention.
     * @return un entier qui represente le numéro de l'intervention sur le distributeur
     */
    float getTempsTrajet();
    /**
     * @brief Accesseur de l'attribut tempsTrajet.
     * @return un time_t qui represente le temps de trajet entre lui et le distributeur
     */
    int getPoidsARemplir();
    /**
     * @brief Accesseur de l'attribut poidsARemplir.
     * @return un float qui represente le poids que doit prendre le technicien pour remplir le distributeur.
     */
    //float getLocalisation(); //à déterminer

    //Mutateur
    void setHeureIntervention(time_t heureIntervention);
    /**
     * @brief Mutateur de l'attribut heureIntervention.
     * @param il prend en argument l'heure à laquel le technicien doit intervenir.
     */
    void setNumeroIntervention(int numeroIntervention);
    /**
     * @brief Mutateur de l'attribut numeroIntervention.
     * @param il prend en argument le numero d'intervention.
     */
    void setTempsTrajet(time_t tempsTrajet);
    /**
     * @brief Mutateur de l'attribut tempsTrajet.
     * @param il prend en argument le temps de trajet.
     */
    void setPoidsARemplir(float poidsARemplir);
    /**
     * @brief Mutateur de l'attribut poidsARemplir.
     * @param il prend en argument le poids que le technicien doit prendre pour remplir le distributeur.
     */
    //void setLocalisation();//à déterminer

};

#endif // INTERVENTION_H
