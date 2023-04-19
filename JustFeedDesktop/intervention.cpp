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
 * @brief Constructeur de la classe Intervention
 */
Intervention::Intervention(IHMJustFeed* parent) : ihmJustFeed(parent), horodatage(), effectuee(false), dateIntervention(){
    initialiserBoiteDeDialogue();
}

/**
 * @brief Destructeur de la classe Intervention
 */
Intervention::~Intervention() {}



void Intervention::initialiserBoiteDeDialogue()
{
    instancierWidgets();
    initialiserWidgets();
    positionnerWidgets();
    initialiserEvenements();
    setWindowTitle(TITRE_INTERVENTION);
}

void Intervention::instancierWidgets()
{

}

void Intervention::initialiserWidgets()
{

}

void Intervention::positionnerWidgets()
{

}

void Intervention::initialiserEvenements()
{

}


/**
 * @brief Accesseur de l'attribut horodatage
 * @return QDateTime représente la date et l'heure de l'intervention sur le
 * distributeur
 */
QDateTime Intervention::getHorodatage() const { return this->horodatage; }

/**
 * @brief Accesseur de l'attribut distributeurAIntervenir
 * @return QVector<Distributeur*> represente les distributeurs surlequels il
 * faut intervenir
 */
QVector<Distributeur *> Intervention::getDistributeurs() const {
  return this->distributeurs;
}

/**
 * @brief Accesseur de l'attribut effectuee
 * @return effectuee
 */
double Intervention::getEffectuee() const { return this->effectuee; }

/**
 * @brief Mutateur de l'attribut distributeurAIntervenir
 * @param distributeur distributeur sur lequel il faut intervenir
 */
void Intervention::ajouterDistributeur(Distributeur *distributeur) {
  this->distributeurs.push_back(distributeur);
}

/**
 * @brief Mutateur de l'attribut horodatage
 * @param horodatage
 */
void Intervention::setHorodatage(const QDateTime &horodatage) {
  this->horodatage = horodatage;
}

/**
 * @brief Mutateur de l'attribut effectuee
 * @param effectuee
 */
void Intervention::setEffectuee(const bool effectuee) {
  this->effectuee = effectuee;
}
