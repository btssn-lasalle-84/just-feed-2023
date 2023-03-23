#include "distributeur.h"

Distributeur::Distributeur()
{

}

Distributeur::~Distributeur()
{

}

int Distributeur::getIdentifiant()
{
    return this->identifiant;
}

Produits Distributeur::getProduit()
{
    return this->produit;
}

int Distributeur::getHydrometrie()
{
    return this->hydroetrie;
}

Localisation Distributeur::getPosition()
{
    return this->position;
}

int Distributeur::getPoidsTotal()
{
    return this->poidsTotal;
}

int Distributeur::getPoidsActuel()
{
    return this->poidsActuel;
}

int Distributeur::getAIntervenir()
{
    return this->aIntervenir;
}

void Distributeur::setProduit(Produits produit)
{
    this->produit = produit;
}

void Distributeur::setHydrometrie(int hydrometrie)
{
    this->hydroetrie = hydrometrie;
}

void Distributeur::setPosition(Localisation localisation)
{
    this->position = localisation;
}

void Distributeur::setPoidsTotal(int poidsTotal)
{
    this->poidsTotal = poidsTotal;
}

void Distributeur::setPoidsActuel(int poidsActuel)
{
    this->poidsActuel = poidsActuel;
}

void Distributeur::setAIntervenir(bool aIntervenir)
{
    this->aIntervenir = aIntervenir;
}
