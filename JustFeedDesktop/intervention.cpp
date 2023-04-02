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
Intervention::Intervention() :
    heureIntervention(), tempsTrajet(), distributeurAIntervenir(), poidsARemplir()
{

}

/**
 * @brief Constructeur d'initialisation de la classe Intervention
 */
Intervention::Intervention(QTime  heureIntervention,
                           QTime  tempsTrajet,
                           QVector<double> poidsARemplir,
                           Distributeur *distributeurAIntervenir) :
    heureIntervention(heureIntervention),
    tempsTrajet(tempsTrajet),
    distributeurAIntervenir(distributeurAIntervenir)
{
    for(int i = 0; i < this->distributeurAIntervenir->getNbBacs(); i++)
    {
        this->poidsARemplir[i] = poidsARemplir[i];
    }
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
double Intervention::getPoidsARemplir(int numeroBac) const
{
    if(numeroBac >= 0 && numeroBac < distributeurAIntervenir->getNbBacs())
    {
        return this->poidsARemplir[numeroBac];
    }
    return 0.;
}

/**
 * @brief Accesseur de l'attribut distributeurAIntervenir
 * @return Distributeur qui represente le distributeur sur lequel il faut intervenir
 */
Distributeur* Intervention::getDistributeurAIntervenir() const
{
    return this->distributeurAIntervenir;
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
 * distributeur et numeroBac pour savoir pour quel bac
 */
void Intervention::setPoidsARemplir(const double poidsARemplir, const int numeroBac)
{
    if(numeroBac >= 0 && numeroBac < distributeurAIntervenir->getNbBacs())
    {
        this->poidsARemplir[numeroBac] = poidsARemplir;
    }
}

/**
 * @brief Mutateur de l'attribut distributeurAIntervenir
 * @param distributeur, distributeur sur lequel il faut intervenir
 */
void Intervention::setDistributeurAIntervenir(Distributeur* distributeur)
{
    this->distributeurAIntervenir = distributeur;
}
