/**
 * @file        distributeur.cpp
 * @brief       Définition de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet définir un
 * distributeur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#include "bac.h"
#include "distributeur.h"
#include "produit.h"
#include <QDebug>

/**
 * @brief Constructeur par défaut de la classe Distributeur
 */
Distributeur::Distributeur() :
    identifiant(0), position(), hydrometrie(0), aIntervenir(false), bacs()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur d'initialisation de la classe Distributeur
 */
Distributeur::Distributeur(int identifiant, Localisation position) :
    identifiant(identifiant), position(position), hydrometrie(0), aIntervenir(false), bacs()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Destructeur de la classe Distributeur
 */
Distributeur::~Distributeur()
{
    for(int i = 0; i < bacs.size(); ++i)
    {
        delete bacs[i];
    }
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Accesseur de l'attribut identifiant
 * @return un entier qui represente l'identifiant du distributeur
 */
int Distributeur::getIdentifiant() const
{
    return this->identifiant;
}

/**
 * @brief Accesseur de l'attribut hydrometrie
 * @return un entier qui represente le degré d'humidité dans le
 * distributeur
 */
int Distributeur::getHydrometrie() const
{
    return this->hydrometrie;
}

/**
 * @brief Accesseur de l'attribut position
 * @return une Localisaton qui represente la géolocalisation du distributeur
 */
Localisation Distributeur::getPosition() const
{
    return this->position;
}

/**
 * @brief Accesseur de l'attribut AIntervenir
 * @return un bool qui permet de savoir s'il faut intervenir sur le
 * distributeur
 */
int Distributeur::getAIntervenir() const
{
    return this->aIntervenir;
}

/**
 * @brief Mutateur de l'attribut identifiant
 * @param identifiant du distributeur
 */
void Distributeur::setIdentifiant(const int identifiant)
{
    this->identifiant = identifiant;
}

/**
 * @brief Mutateur de l'attribut hydrométrie
 * @param hydrometrie l'hydrometrie du distributeur
 */
void Distributeur::setHydrometrie(int hydrometrie)
{
    this->hydrometrie = hydrometrie;
}

/**
 * @brief Mutateur de l'attribut localisation
 * @param localisation la localisation du distributeur
 */
void Distributeur::setPosition(const Localisation& localisation)
{
    this->position = localisation;
}

/**
 * @brief Mutateur de l'attribut aIntervenir
 * @param aIntervenir un booleen qui détérmine l'état du
 * distributeur
 */
void Distributeur::setAIntervenir(bool aIntervenir)
{
    this->aIntervenir = aIntervenir;
}

/**
 * @brief Ajoute un bac dans le distributeur
 * @param bac
 */
void Distributeur::ajouterBac(const Bac& bac)
{
    bacs.push_back(new Bac(bac));
}
