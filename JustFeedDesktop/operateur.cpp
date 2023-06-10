/**
 * @file        operateur.cpp
 * @brief       Définition de la classe Operateur.
 * @details     La classe Operateur \c Cette classe permet de définir un opérateur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     1.1
 * @date        2023
 */
#include "operateur.h"
#include <QDebug>

Operateur::Operateur(int     idOperateur,
                     QString nom,
                     QString prenom,
                     QString identifiant,
                     QString email) :
    id(idOperateur),
    nom(nom), prenom(prenom), identifiant(identifiant), email(email)
{
    qDebug() << Q_FUNC_INFO << "id" << id << "nom" << nom << "prenom" << prenom << "identifiant"
             << identifiant << "email" << email;
}

Operateur::Operateur(const QStringList operateur) :
    id(operateur.at(TableOperateur::ID).toInt()), nom(operateur.at(TableOperateur::NOM)),
    prenom(operateur.at(TableOperateur::PRENOM)),
    identifiant(operateur.at(TableOperateur::IDENTIFIANT)),
    email(operateur.at(TableOperateur::EMAIL))
{
    qDebug() << Q_FUNC_INFO << "id" << id << "nom" << nom << "prenom" << prenom << "identifiant"
             << identifiant << "email" << email;
}

int Operateur::getId() const
{
    return this->id;
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

void Operateur::setId(const int idOperateur)
{
    this->id = idOperateur;
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
