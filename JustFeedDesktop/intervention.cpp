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

/**
 * @brief Constructeur par défaut de la classe Intervention
 */
Intervention::Intervention() :
    heureIntervention(), numeroIntervention(0), tempsTrajet(), poidsARemplir(0.)
{
}
/**
 * @brief Constructeur d'initialisation de la classe Intervention
 */
Intervention::Intervention(QTime  heureIntervention,
                           int    numeroIntervention,
                           QTime  tempsTrajet,
                           double poidsARemplir) :
    heureIntervention(heureIntervention),
    numeroIntervention(numeroIntervention), tempsTrajet(tempsTrajet),
    poidsARemplir(poidsARemplir)
{
}
/**
 * @brief Destructeur de la classe Intervention
 */
Intervention::~Intervention()
{
}

/**
 * @brief Accesseur de l'attribut heureIntervention
 * @return QTime représente l'heure de l'intervention sur le distributeur
 */
QTime Intervention::getHeureIntervention() const
{
    return this->heureIntervention;
}

/**
 * @brief Accesseur de l'attribut numeroIntervention
 * @return un entier qui représente le numéro de l'intervention sur le
 * distributeur
 */
int Intervention::getNumeroIntervention() const
{
    return this->numeroIntervention;
}

/**
 * @brief Accesseur de l'attribut tempsTrajet
 * @return QTime représente le temps de trajet entre lui et le distributeur
 */
QTime Intervention::getTempsTrajet() const
{
    return this->tempsTrajet;
}

/**
 * @brief Accesseur de l'attribut poidsARemplir
 * @return un float qui represente le poids que doit prendre le technicien pour
 * remplir le distributeur
 */
double Intervention::getPoidsARemplir() const
{
    return this->poidsARemplir;
}

/**
 * @brief Mutateur de l'attribut heureIntervention
 * @param heureIntervention l'heure à laquel le technicien doit intervenir
 */
void Intervention::setHeureIntervention(const QTime& heureIntervention)
{
    this->heureIntervention = heureIntervention;
}

/**
 * @brief Mutateur de l'attribut numeroIntervention
 * @param numeroIntervention le numero d'intervention
 */
void Intervention::setNumeroIntervention(const int numeroIntervention)
{
    this->numeroIntervention = numeroIntervention;
}

/**
 * @brief Mutateur de l'attribut tempsTrajet
 * @param tempsTrajet le temps de trajet
 */
void Intervention::setTempsTrajet(const QTime& tempsTrajet)
{
    this->tempsTrajet = tempsTrajet;
}

/**
 * @brief Mutateur de l'attribut poidsARemplir
 * @param poidsARemplir le poids que le technicien doit prendre pour remplir le
 * distributeur
 */
void Intervention::setPoidsARemplir(const double poidsARemplir)
{
    this->poidsARemplir = poidsARemplir;
}