/**
 * @file        produit.cpp
 * @brief       Définition de la classe produit.
 * @details     La classe intervention \c Cette classe permet de définir un
 * produit
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "produit.h"
#include <QDebug>

/**
 * @brief Constructeur par défaut de la classe produit
 */
Produit::Produit() : id(0), nom(""), marque(""), description(""), codeProduit(""), prix(0.)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur d'initialisation de la classe Produit
 */
Produit::Produit(QString nom,
                 QString marque,
                 QString description,
                 QString codeProduit,
                 double  prix) :
    id(0),
    nom(nom), marque(marque), description(description), codeProduit(codeProduit), prix(prix)
{
    qDebug() << Q_FUNC_INFO << "nom" << nom << "marque" << marque << "description" << description
             << "codeProduit" << codeProduit << "prix" << prix;
}

/**
 * @brief Constructeur d'initialisation de la classe Produit
 */
Produit::Produit(QStringList produit) :
    id(produit.at(TableProduit::CHAMP_ID_PRODUIT).toInt()),
    nom(produit.at(TableProduit::CHAMP_NOM_PRODUIT)),
    marque(produit.at(TableProduit::CHAMP_MARQUE)),
    description(produit.at(TableProduit::CHAMP_DESCRITION)),
    codeProduit(produit.at(TableProduit::CHAMP_CODE_EAN)),
    prix(produit.at(TableProduit::CHAMP_PRIX).toDouble())
{
    qDebug() << Q_FUNC_INFO << "id" << id << "nom" << nom << "marque" << marque << "description"
             << description << "codeProduit" << codeProduit << "prix" << prix;
}

/**
 * @brief Destructeur de la classe Produit
 */
Produit::~Produit()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Accesseur de l'attribut id
 * @return un int qui permet de connaitre l'id du produit dans la base de données
 */
int Produit::getId() const
{
    return this->id;
}

/**
 * @brief Accesseur de l'attribut nom
 * @return un QString qui permet de connaitre le nom du produit
 */
QString Produit::getNom() const
{
    return this->nom;
}

/**
 * @brief Accesseur de l'attribut marque
 * @return un QString qui permet de connaitre la marque du produit
 */
QString Produit::getMarque() const
{
    return this->marque;
}

/**
 * @brief Accesseur de l'attribut descriptio,
 * @return un QString qui permet de connaitre la description du produit
 */
QString Produit::getDescription() const
{
    return this->description;
}

/**
 * @brief Accesseur de l'attribut codeProduit
 * @return QString le code du produit
 */
QString Produit::getCodeProduit() const
{
    return this->codeProduit;
}

/**
 * @brief Accesseur de l'attribut prix
 * @return un double qui permet de connaitre le prix du produit
 */
double Produit::getPrix() const
{
    return this->prix;
}

/**
 * @brief Mutateur de l'attribut id
 * @param id un int qui affecte l'id du produit
 */
void Produit::setId(int id)
{
    this->id = id;
}

/**
 * @brief Mutateur de l'attribut nom
 * @param nom un QString qui affecte le nom du
 * produit
 */
void Produit::setNom(const QString& nom)
{
    this->nom = nom;
}

/**
 * @brief Mutateur de l'attribut la marque
 * @param marque un QString qui affecte la marque du
 * produit
 */
void Produit::setMarque(const QString& marque)
{
    this->marque = marque;
}

/**
 * @brief Mutateur de l'attribut description
 * @param description un doucle qui affecte la description du
 * produit
 */
void Produit::setDescription(const QString& description)
{
    this->description = description;
}

/**
 * @brief Mutateur de l'attribut code produit
 * @param codeProduit QString le code produit du produit
 */
void Produit::setCodeProduit(const QString& codeProduit)
{
    this->codeProduit = codeProduit;
}

/**
 * @brief Mutateur de l'attribut prix
 * @param prix un doucle qui affecte le prix du
 * produit
 */
void Produit::setPrix(const double prix)
{
    this->prix = prix;
}
