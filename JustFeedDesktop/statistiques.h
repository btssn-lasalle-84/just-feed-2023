/**
 * @file        Statistiques.h
 * @brief       Définition de la classe Statistiques.
 * @detail      La classe Statistiques \c Cette classe permet de définir les attributs et les méthodes de la classe.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
*/


#ifndef STATISTIQUES_H
#define STATISTIQUES_H


class Statistiques
{
private :
    int frequenceIntervetion;
    int poidsMoyenProduits;
    int moyenneKilometres;

public:        
    Statistiques();
    /**
     * @brief Constructeur par défault de la classe Serveur
     * @see Intervention
     */
    ~Statistiques();
    /**
     * @brief Destructeur de la classe Serveur
     * @see Intervention
     */
    //accesseur
    int getFrequenceIntervetion();
    /**
     * @brief Accesseur de l'attribut frequenceIntervetion.
     * @return un entier
     */
    int getPoidsMoyenProduits();
    /**
     * @brief Accesseur de l'attribut poidsMoyenProduits.
     * @return un entier
     */
    int getMoyenneKilometres();
    /**
     * @brief Accesseur de l'attribut moyenneKilometres.
     * @return un entier
     */
    //mutateur
    void setFrequenceIntervetion(int frequenceIntervetion);
    /**
     * @brief Mutateur de l'attribut frequenceIntervetion.
     * @param il prend en argument la frequence d'intervention.
     */
    void setPoidsMoyenProduits(int poidsMoyenProduits);
    /**
     * @brief Mutateur de l'attribut poidsMoyenProduits.
     * @param il prend en argument le poids moyen du produits concerné.
     */
    void setMoyenneKilometres(int moyenneKilometres);
    /**
     * @brief Mutateur de l'attribut moyenneKilometres.
     * @param il prend en argument la moyenne des kilometres fait par le/les techniciens.
     */
};

#endif // STATISTIQUES_H
