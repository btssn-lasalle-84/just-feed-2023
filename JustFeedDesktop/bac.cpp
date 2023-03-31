/**
 * @file        Bac.cpp
 * @brief       Déclaration de la classe Bac.
 * @details     La classe Bac \c Cette classe permet de définir un bac
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#include "bac.h"
#include "produit.h"

/**
 * @brief Constructeur par défaut de la classe bac
 */
Bac::Bac(): produit(NULL), poidsTotal(0), poidsActuel(0), hydrometrie(0),
    position(), aIntervenir(false)
{

}

/**
 * @brief Constructeur d'initialisation du bac
 */
Bac::Bac(Produit produit,int poidsTotal, int poidsActuel, int hydrometrie, Localisation position, bool aIntervenir) :
    produit(new Produit(produit)),poidsTotal(poidsTotal), poidsActuel(poidsActuel),
    hydrometrie(hydrometrie), position(position), aIntervenir(aIntervenir)
{

}

/**
 * @brief Destructeur de la classe Bac
 */
Bac::~Bac()
{

}

/**
 * @brief Accesseur de l'attribut produit
 * @return un Produits qui represente le produit que contient le
 * distributeur
 */
QString Bac::getNomProduit() const
{
    return produit->getNom();
}

/**
 * @brief Accesseur de l'attribut hydrometrie
 * @return un entier qui represente le degré d'humidité dans le
 * distributeur
 */
int Bac::getHydrometrie() const
{
    return this->hydrometrie;
}

/**
 * @brief Accesseur de l'attribut position
 * @return une Localisaton qui represente la géolocalisation du distributeur
 */
Localisation Bac::getPosition() const
{
    return this->position;
}

/**
 * @brief Accesseur de l'attribut poidsTotal
 * @return un entier qui represente le poids total que peut contenir le
 * distributeur
 */
int Bac::getPoidsTotal() const
{
    return this->poidsTotal;
}

/**
 * @brief Accesseur de l'attribut poidsActuel
 * @return un entier qui represente le poids actuel dans le distributeur
 */
int Bac::getPoidsActuel() const
{
    return this->poidsActuel;
}

/**
 * @brief Accesseur de l'attribut AIntervenir
 * @return un bool qui permet de savoir s'il faut intervenir sur le
 * distributeur
 */
int Bac::getAIntervenir() const
{
    return this->aIntervenir;
}

/**
 * @brief Mutateur de l'attribut Produit
 * @param nomProduit le type de produit que contient le distributeur
 */
void Bac::setNomProduit(const QString& NomProduit)
{
    this->produit->setNom(NomProduit);
}

/**
 * @brief Mutateur de l'attribut Produit
 * @param prixProduit le prix du produit que contient le distributeur
 */
void Bac::setPrixProduit(const int& prixProduit)
{
    this->produit->setPrix(prixProduit);
}

/**
 * @brief Mutateur de l'attribut hydrométrie
 * @param hydrometrie l'hydrometrie du distributeur
 */
void Bac::setHydrometrie(int hydrometrie)
{
    this->hydrometrie = hydrometrie;
}

/**
 * @brief Mutateur de l'attribut localisation
 * @param localisation la localisation du distributeur
 */
void Bac::setPosition(const Localisation& localisation)
{
    this->position = localisation;
}

/**
 * @brief Mutateur de l'attribut poidsTotal
 * @param poidsTotal le poids total du distributeur
 */
void Bac::setPoidsTotal(int poidsTotal)
{
    this->poidsTotal = poidsTotal;
}

/**
 * @briefmutateur de l'attribut poidsActuel
 * @param poidsActuel le poids actuel du distributeur
 */
void Bac::setPoidsActuel(int poidsActuel)
{
    this->poidsActuel = poidsActuel;
}

/**
 * @briefmutateur de l'attribut aIntervenir
 * @param aIntervenir un booleen qui détérmine l'état du
 * distributeur
 */
void Bac::setAIntervenir(bool aIntervenir)
{
    this->aIntervenir = aIntervenir;
}
