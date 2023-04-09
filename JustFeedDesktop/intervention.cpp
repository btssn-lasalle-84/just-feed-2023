/**
 * @file        intervention.cpp
 * @brief       Définition de la classe intervention.
 * @details     La classe intervention \c Cette classe permet de définir une
 * intervention
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "intervention.h"
#include "distributeur.h"

/**
 * @brief Constructeur par défaut de la classe Intervention
 */
Intervention::Intervention() : horodatage(), effectuee(false)
{
}

/**
 * @brief Destructeur de la classe Intervention
 */
Intervention::~Intervention()
{
}

/**
 * @brief Accesseur de l'attribut horodatage
 * @return QDateTime représente la date et l'heure de l'intervention sur le distributeur
 */
QDateTime Intervention::getHorodatage() const
{
    return this->horodatage;
}

/**
 * @brief Accesseur de l'attribut distributeurAIntervenir
 * @return QVector<Distributeur*> represente les distributeurs surlequels il faut intervenir
 */
QVector<Distributeur*> Intervention::getDistributeurs() const
{
    return this->distributeurs;
}

/**
 * @brief Mutateur de l'attribut distributeurAIntervenir
 * @param distributeur distributeur sur lequel il faut intervenir
 */
void Intervention::ajouterDistributeur(Distributeur* distributeur)
{
    this->distributeurs.push_back(distributeur);
}
