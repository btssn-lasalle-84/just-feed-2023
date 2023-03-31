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

/**
 * @brief Constructeur par défaut de la classe Distributeur
 */
Distributeur::Distributeur() :
    identifiant(0), bacs(nullptr)
{
}

/**
 * @brief Constructeur d'initialisation de la classe Distributeur
 */
Distributeur::Distributeur(int identifiant, std::vector<Bac*>  bacs) : identifiant(identifiant), bacs(bacs)
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
 * @brief Mutateur de l'attribut identifiant
 * @param identifiant du distributeur
 */
void Distributeur::setIdentifiant(const int identifiant)
{
    this->identifiant = identifiant;
}

/**
 * @brief Mutateur pour changer le produit d'un bac
 * @param identifiant du bac et le produit
 */
void Distributeur::setBacsProduit(const int identifiantBac, const Produit produit)
{
        bacs[identifiantBac] = new produit();
}
