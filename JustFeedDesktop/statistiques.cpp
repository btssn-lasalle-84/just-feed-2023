/**
 * @file        statistiques.cpp
 * @brief       Définition de la classe statistiques.
 * @details     La classe statistiques \c Cette classe permet de définir les statistiques
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "statistiques.h"

/**
 * @brief Constructeur par défault de la classe Serveur
 * @see Intervention
 */
Statistiques::Statistiques() :  frequenceIntervetion(0),  poidsMoyenProduits(0),  moyenneKilometres(0)
{
}

/**
 * @brief Constructeur d'initialisation de la classe Serveur
 * @see Intervention
 */
Statistiques::Statistiques(int frequenceIntervetion, int poidsMoyenProduits, int moyenneKilometres) :
    frequenceIntervetion(frequenceIntervetion), poidsMoyenProduits(poidsMoyenProduits), moyenneKilometres(moyenneKilometres)
{

}

/**
 * @brief Destructeur de la classe Serveur
 * @see Intervention
 */
Statistiques::~Statistiques()
{
}

/**
 * @brief Accesseur de l'attribut frequenceIntervetion.
 * @return un entier
 */
int Statistiques::getFrequenceIntervetion() const
{
    return this->frequenceIntervetion;
}

/**
 * @brief Accesseur de l'attribut poidsMoyenProduits.
 * @return un entier
 */
int Statistiques::getPoidsMoyenProduits() const
{
    return this->poidsMoyenProduits;
}

/**
 * @brief Accesseur de l'attribut poidsMoyenProduits.
 * @return un entier
 */
int Statistiques::getMoyenneKilometres() const
{
    return this->moyenneKilometres;
}

/**
 * @brief Mutateur de l'attribut frequenceIntervetion.
 * @param il prend en argument la frequence d'intervention.
 */
void Statistiques::setFrequenceIntervetion(const int frequenceIntervetion)
{
    this->frequenceIntervetion = frequenceIntervetion;
}

/**
 * @brief Mutateur de l'attribut poidsMoyenProduits.
 * @param il prend en argument le poids moyen du produits concerné.
 */
void Statistiques::setPoidsMoyenProduits(const int poidsMoyenProduits)
{
    this->poidsMoyenProduits = poidsMoyenProduits;
}

/**
 * @brief Mutateur de l'attribut moyenneKilometres.
 * @param il prend en argument la moyenne des kilometres fait par le/les techniciens.
 */
void Statistiques::setMoyenneKilometres(const int moyenneKilometres)
{
    this->moyenneKilometres = moyenneKilometres;
}
