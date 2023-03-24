#include "intervention.h"

/**
 * @todo Il faut initialiser les attributs !
 */
Intervention::Intervention()
{
}

Intervention::~Intervention()
{
}

QTime Intervention::getHeureIntervention()
{
    return this->heureIntervention;
}

int Intervention::getNumeroIntervention()
{
    return this->numeroIntervention;
}

QTime Intervention::getTempsTrajet()
{
    return this->tempsTrajet;
}

double Intervention::getPoidsARemplir()
{
    return this->poidsARemplir;
}

void Intervention::setHeureIntervention(QTime heureIntervention)
{
    this->heureIntervention = heureIntervention;
}

void Intervention::setNumeroIntervention(int numeroIntervention)
{
    this->numeroIntervention = numeroIntervention;
}

void Intervention::setTempsTrajet(QTime tempsTrajet)
{
    this->tempsTrajet = tempsTrajet;
}

void Intervention::setPoidsARemplir(double poidsARemplir)
{
    this->poidsARemplir = poidsARemplir;
}
