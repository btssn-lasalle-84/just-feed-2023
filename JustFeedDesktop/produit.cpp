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

/**
 * @brief Constructeur par défaut de la classe produit
 */
Produit::Produit() : nom(""), marque(""), description(""), codeProduit(""), prix(0.)
{
}

/**
 * @brief destructeur par défaut de la classe produit
 */
Produit::Produit(QString nom,
                 QString marque,
                 QString description,
                 QString codeProduit,
                 double  prix) :
    nom(nom),
    marque(marque), description(description), codeProduit(codeProduit), prix(prix)
{
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
