#include "serveur.h"

Serveur::Serveur()
{

}

Serveur::~Serveur()
{

}

int Serveur::getPort()
{
    return this->port;
}

QString Serveur::getHostName()
{
    return this->hostName;
}

QString Serveur::getUtilisateur()
{
    return this->utilisateur;
}

int Serveur::getMotDePasse()
{
    return this->motDePasse;
}

void Serveur::setPort(int port)
{
    this->port = port;
}

void Serveur::setHostName(QString hostName)
{
    this->hostName = hostName;
}

void Serveur::setUtilisateur(QString utilisateur)
{
    this->utilisateur = utilisateur;
}

void Serveur::setMotDePasse(int motDePasse)
{
    this->motDePasse = motDePasse;
}
