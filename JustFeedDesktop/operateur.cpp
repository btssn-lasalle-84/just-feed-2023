#include "operateur.h"

Operateur::Operateur(int idOperateur, QString nom, QString prenom, QString identifiant, QString email)
                    : idOperateur(idOperateur), nom(nom), prenom(prenom), identifiant(identifiant), email(email)
{

}

int Operateur::getIdOperateur() const
{
    return this->idOperateur;
}


QString Operateur::getNom() const
{
    return this->nom;
}


QString Operateur::getPrenom() const
{
    return this->prenom;
}

QString Operateur::getIdentifiant() const
{
    return this->identifiant;
}


QString Operateur::getEmail() const
{
    return this->email;
}

void Operateur::setIdOerateur(const int idOperateur)
{
    this->idOperateur = idOperateur;
}


void Operateur::setNom(const QString nom)
{
    this->nom = nom;
}


void Operateur::setPrenom(const QString prenom)
{
    this->prenom = prenom;
}


void Operateur::setIdentifiant(const QString identifiant)
{
    this->identifiant = identifiant;
}


void Operateur::setEmail(const QString email)
{
    this->email = email;
}
