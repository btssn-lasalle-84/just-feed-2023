#include "intervention.h"

Intervention::Intervention()
{

}

Intervention::~Intervention()
{

}

time_t Intervention::getHeureIntervention()
{
    return this->heureIntervention;
}
int Intervention::getNumeroIntervention()
{
    return this->numeroIntervention;
}

float Intervention::getTempsTrajet()
{
    return this->tempsTrajet;
}

int Intervention::getPoidsARemplir()
{
    return this->poidsARemplir;
}

//loat getLocalisation(); //à déterminer

void Intervention::setHeureIntervention(time_t heureIntervention)
{
    this->heureIntervention = heureIntervention;
}

void Intervention::setNumeroIntervention(int numeroIntervention)
{
    this->numeroIntervention = numeroIntervention;
}

void Intervention::setTempsTrajet(time_t tempsTrajet)
{
    this->tempsTrajet = tempsTrajet;
}

void Intervention::setPoidsARemplir(float poidsARemplir)
{
    this->poidsARemplir = poidsARemplir;
}

//void setLocalisation();//à déterminer

