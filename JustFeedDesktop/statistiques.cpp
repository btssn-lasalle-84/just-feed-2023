#include "statistiques.h"

/**
 * @todo Il faut initialiser les attributs !
 */
Statistiques::Statistiques()
{
}

Statistiques::~Statistiques()
{
}
int Statistiques::getFrequenceIntervetion()
{
    return this->frequenceIntervetion;
}

int Statistiques::getPoidsMoyenProduits()
{
    return this->poidsMoyenProduits;
}

int Statistiques::getMoyenneKilometres()
{
    return this->moyenneKilometres;
}

void Statistiques::setFrequenceIntervetion(int frequenceIntervetion)
{
    this->frequenceIntervetion = frequenceIntervetion;
}

void Statistiques::setPoidsMoyenProduits(int poidsMoyenProduits)
{
    this->poidsMoyenProduits = poidsMoyenProduits;
}

void Statistiques::setMoyenneKilometres(int moyenneKilometres)
{
    this->moyenneKilometres = moyenneKilometres;
}
