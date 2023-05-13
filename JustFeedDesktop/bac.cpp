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
Bac::Bac() :
    produit(nullptr), idBac(ID_BAC_NON_DEFINI), poidsActuel(0.), poidsTotal(0.),
    pourcentageRemplissage(0.), aRemplir(false), aDepanner(false), hygrometrie(0)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur d'initialisation du bac
 */
Bac::Bac(int idBac, Produit* produit, double poidsActuel, double poidsTotal, int hygrometrie) :
    produit(produit), idBac(idBac), poidsActuel(poidsActuel), poidsTotal(poidsTotal),
    pourcentageRemplissage((poidsActuel * 100.) / poidsTotal), aRemplir(false), aDepanner(false),
    hygrometrie(hygrometrie)
{
    qDebug() << Q_FUNC_INFO << "nom" << produit->getNom() << "marque" << produit->getMarque()
             << "description" << produit->getDescription() << "codeProduit"
             << produit->getCodeProduit() << "prix" << produit->getPrix() << "poidsActuel"
             << poidsActuel << "poidsTotal" << poidsTotal << "pourcentageRemplissage"
             << pourcentageRemplissage;
}

/**
 * @brief Constructeur d'initialisation du bac
 */
Bac::Bac(int idBac, Produit* produit, double poidsTotal) :
    produit(produit), idBac(idBac), poidsActuel(poidsTotal), poidsTotal(poidsTotal),
    pourcentageRemplissage(100.), aRemplir(false), aDepanner(false), hygrometrie(0)
{
    qDebug() << Q_FUNC_INFO << "nom" << produit->getNom() << "marque" << produit->getMarque()
             << "description" << produit->getDescription() << "codeProduit"
             << produit->getCodeProduit() << "prix" << produit->getPrix() << "poidsActuel"
             << poidsActuel << "poidsTotal" << poidsTotal << "pourcentageRemplissage"
             << pourcentageRemplissage;
}

/**
 * @brief Constructeur de copie
 */
Bac::Bac(const Bac& bac) :
    produit(bac.produit), idBac(bac.idBac), poidsActuel(bac.poidsActuel),
    poidsTotal(bac.poidsTotal), pourcentageRemplissage(bac.pourcentageRemplissage),
    aRemplir(bac.aRemplir), aDepanner(bac.aDepanner), hygrometrie(bac.hygrometrie)
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
 * @brief Accesseur de l'attribut aDepanner
 * @return un bool qui permet de savoir s'il faut dépanner le distributeur
 */
int Bac::getIdBac() const
{
    return this->idBac;
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
 * @brief Accesseur de l'attribut aRemplir
 * @return un bool qui permet de savoir s'il faut remplir le distributeur
 */
bool Bac::getARemplir() const
{
    return this->aRemplir;
}

/**
 * @brief Accesseur de l'attribut aDepanner
 * @return un bool qui permet de savoir s'il faut dépanner le distributeur
 */
bool Bac::getADepanner() const
{
    return this->aDepanner;
}

/**
 * @brief Méthode qui détermine la quantité à remplir
 * @return double la quantité à remplir
 */
double Bac::getQuantiteARemplir() const
{
    return (getPoidsTotal() * (100. - getPourcentageRemplissage()) / 100.);
}

/**
 * @brief Accesseur de l'attribut pourcentageRemplissage
 * @return un double qui represente le pourcentage de remplissage dans le bac
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
 * @brief Accesseur de l'attribut hygrometrie
 * @return int
 */
int Bac::getHygrometrie() const
{
    return this->hygrometrie;
}

/**
 * @brief Accesseur de l'attribut aIntervenir
 * @return bool
 */
bool Bac::getAIntervenir() const
{
    return this->aIntervenir;
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
void Bac::setPoidsActuel(const double& poidsActuel)
{
    if(this->poidsActuel != poidsActuel)
    {
        this->poidsActuel            = poidsActuel;
        this->pourcentageRemplissage = (poidsActuel * 100.) / poidsTotal;
    }
}

/**
 * @brief Mutateur de l'attribut poidsTotal
 * @param poidsActuel le poids max du bac
 */
void Bac::setPoidsTotal(const double& poidsTotal)
{
    if(this->poidsTotal != poidsTotal)
    {
        this->poidsTotal             = poidsTotal;
        this->pourcentageRemplissage = (poidsActuel * 100.) / poidsTotal;
    }
}

/**
 * @brief Mutateur de l'attribut pourcentageRemplissage
 * @param pourcentageRemplissage le % de remplissage du bac
 */
void Bac::setPourcentageRemplissage(const double& pourcentageRemplissage)
{
    if(this->pourcentageRemplissage != pourcentageRemplissage)
    {
        this->pourcentageRemplissage = pourcentageRemplissage;
        this->poidsActuel            = (poidsTotal * pourcentageRemplissage) / 100.;
    }
}

/**
 * @brief Mutateur de l'attribut hygrometrie
 * @param hygrometrie l'hygrometrie, mesure de la quantité de vapeur d'eau
 * contenue de l'air du distributeur
 */
void Bac::setHygrometrie(int hygrometrie)
{
    this->hygrometrie = hygrometrie;
}

/**
 * @brief Mutateur de l'attribut aRemplir
 * @param aRemplir un booleen qui détermine l'état du
 * bac
 */
void Bac::setARemplir(bool aRemplir)
{
    this->aRemplir = aRemplir;
}

/**
 * @brief Mutateur de l'attribut aDepanner
 * @param aDepanner un booleen qui détermine l'état du
 * bac
 */
void Bac::setADepanner(bool aDepanner)
{
    this->aDepanner = aDepanner;
}

/**
 * @brief Mutateur de l'attribut aIntervenir
 * @param attribue
 */
void Bac::setAIntervenir(bool attribue)
{
    this->aIntervenir = attribue;
}
