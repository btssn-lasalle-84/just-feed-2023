#include "produit.h"

/**
 * @brief Constructeur par défaut de la classe produit
 */
Produit::Produit() : prix(0), nom("")
{

}

/**
 * @brief destructeur par défaut de la classe produit
 */
Produit::Produit(double prix, QString nom) : prix(prix), nom(nom)
{

}

double Produit::getPrix() const
{
    return this->prix;
}

QString Produit::getNom() const
{
    return this->nom;
}

void Produit::setPrix(const double prix)
{
    this->prix = prix;
}

void Produit::setNom(const QString nom)
{
    this->nom = nom;
}
