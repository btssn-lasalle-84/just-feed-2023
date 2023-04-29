/**
 * @file        Bac.cpp
 * @brief       Définition de la classe Bac.
 * @details     La classe Bac \c Cette classe permet de définir un bac
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#include "bac.h"
#include "produit.h"
#include <QDebug>

/**
 * @brief Constructeur par défaut de la classe Bac
 */
Bac::Bac() : produit(nullptr), poidsActuel(0.), pourcentageRemplissage(0.), aIntervenir(false), poidsTotal(0.)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur d'initialisation du bac
 */
Bac::Bac(Produit* produit, double poidsActuel, double poidsTotal, double pourcentageRemplissage) :
    produit(produit), poidsActuel(poidsActuel), poidsTotal(poidsTotal), pourcentageRemplissage(pourcentageRemplissage), aIntervenir(false)
{
    qDebug() << Q_FUNC_INFO << "nom" << produit->getNom() << "marque" << produit->getMarque()
             << "description" << produit->getDescription() << "codeProduit"
             << produit->getCodeProduit() << "prix" << produit->getPrix() << "poidsActuel"
             << poidsActuel << "pourcentageRemplissage" << pourcentageRemplissage;
}

/**
 * @brief Constructeur de copie
 */
Bac::Bac(const Bac& bac) :
    produit(bac.produit), poidsActuel(bac.poidsActuel),
    pourcentageRemplissage(bac.pourcentageRemplissage)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Destructeur de la classe Bac
 */
Bac::~Bac()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Accesseur de l'attribut produit
 * @return un Produits qui represente le produit que contient le
 * bac
 */
Produit* Bac::getProduit() const
{
    return produit;
}

/**
 * @brief Retourne le nom du produit
 * @return le nom du Produit que contient le bac
 */
QString Bac::getNomProduit() const
{
    if(produit != nullptr)
        return produit->getNom();
    return QString();
}

/**
 * @brief Retourne le prix du produit
 * @return le prix du produit que contient le bac
 */
double Bac::getPrixProduit() const
{
    if(produit != nullptr)
        return produit->getPrix();
    return 0.;
}

/**
 * @brief Accesseur de l'attribut poidsActuel
 * @return un entier qui represente le poids actuel dans le bac
 */
double Bac::getPoidsActuel() const
{
    return this->poidsActuel;
}

/**
 * @brief Accesseur de l'attribut AIntervenir
 * @return bool
 */
bool Bac::getAIntervenir() const
{
    return this->aIntervenir;
}

/**
 * @brief Accesseur de l'attribut pourcentageRemplissage
 * @return double
 */
double Bac::getPourcentageRemplissage() const
{
    return this->pourcentageRemplissage;
}

/**
 * @brief Accesseur de l'attribut poidsTotal
 * @return double
 */
double Bac::getPoidsTotal() const
{
    return this->poidsTotal;
}

/**
 * @brief Mutateur de l'attribut Produit
 * @param produit le poduit que contient le bac
 */
void Bac::setProduit(Produit* produit)
{
    this->produit = produit;
}

/**
 * @brief Modifie le nom du produit
 * @param nomProduit le nom de produit que contient le bac
 */
void Bac::setNomProduit(const QString& nomProduit)
{
    if(produit != nullptr)
        this->produit->setNom(nomProduit);
}

/**
 * @brief Modifie le prix du produit
 * @param prixProduit le prix du produit que contient le bac
 */
void Bac::setPrixProduit(const double& prixProduit)
{
    if(produit != nullptr)
        this->produit->setPrix(prixProduit);
}

/**
 * @brief Mutateur de l'attribut poidsActuel
 * @param poidsActuel le poids actuel du bac
 */
void Bac::setPoidsActuel(const double poidsActuel)
{
    this->poidsActuel = poidsActuel;
}

/**
 * @brief Mutateur de l'attribut poidsTotal
 * @param poidsActuel le poids max du bac
 */
void Bac::setPoidsTotal(const double poidsTotal)
{
    this->poidsTotal = poidsTotal;
}
/**
 * @brief Mutateur de l'attribut AIntervenir
 * @param aIntervenir
 */
void Bac::setAIntervenir()
{
    if(pourcentageRemplissage <= 30)
    {
        this->aIntervenir = true;
    }
    else
    {
        this->aIntervenir = false;
    }
}
