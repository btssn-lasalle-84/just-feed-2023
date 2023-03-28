/**
 * @file        distributeur.cpp
 * @brief       Définition de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet définir un
 * distributeur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "distributeur.h"

/**
 * @brief Constructeur par défaut de la classe Distributeur
 */
Distributeur::Distributeur() :
    identifiant(0), produit(), poidsTotal(0), poidsActuel(0), hydrometrie(0),
    position(), aIntervenir(false)
{
}

/**
 * @brief Constructeur d'initialisation de la classe Distributeur
 */
Distributeur::Distributeur(int          identifiant,
                           Produit      produit,
                           int          poidsTotal,
                           int          poidsActuel,
                           int          hydrometrie,
                           Localisation position,
                           bool         aIntervenir) :
    identifiant(identifiant),
    produit(produit), poidsTotal(poidsTotal), poidsActuel(poidsActuel),
    hydrometrie(hydrometrie), position(position), aIntervenir(aIntervenir)
{
}

/**
 * @brief Destructeur de la classe Distributeur
 */
Distributeur::~Distributeur()
{
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
 * @brief Accesseur de l'attribut produit
 * @return un Produits qui represente le produit que contient le
 * distributeur
 */
Produit Distributeur::getProduit() const
{
    return this->produit;
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
 * @brief Accesseur de l'attribut poidsTotal
 * @return un entier qui represente le poids total que peut contenir le
 * distributeur
 */
int Distributeur::getPoidsTotal() const
{
    return this->poidsTotal;
}

/**
 * @brief Accesseur de l'attribut poidsActuel
 * @return un entier qui represente le poids actuel dans le distributeur
 */
int Distributeur::getPoidsActuel() const
{
    return this->poidsActuel;
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
 * @brief Mutateur de l'attribut Produit
 * @param produit le type de produit que contient le distributeur
 */
void Distributeur::setProduit(const Produit& produit)
{
    this->produit = produit;
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
 * @brief Mutateur de l'attribut poidsTotal
 * @param poidsTotal le poids total du distributeur
 */
void Distributeur::setPoidsTotal(int poidsTotal)
{
    this->poidsTotal = poidsTotal;
}

/**
 * @briefmutateur de l'attribut poidsActuel
 * @param poidsActuel le poids actuel du distributeur
 */
void Distributeur::setPoidsActuel(int poidsActuel)
{
    this->poidsActuel = poidsActuel;
}

/**
 * @briefmutateur de l'attribut aIntervenir
 * @param aIntervenir un booleen qui détérmine l'état du
 * distributeur
 */
void Distributeur::setAIntervenir(bool aIntervenir)
{
    this->aIntervenir = aIntervenir;
}
