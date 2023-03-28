/**
 * @file        serveur.cpp
 * @brief       Définition de la classe serveur.
 * @details     La classe serveur \c Cette classe permet de définir le serveur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "serveur.h"

/**
 * @brief Constructeur par défaut de la classe Serveur
 * @see Intervention
 */
Serveur::Serveur() : port(0), hostName(""), utilisateur(""), motDePasse("")
{
}

/**
 * @brief Constructeur d'initialisation de la classe Serveur
 * @see Intervention
 */
Serveur::Serveur(int     port,
                 QString hostName,
                 QString utilisateur,
                 QString motDePasse) :
    port(port),
    hostName(hostName), utilisateur(utilisateur), motDePasse(motDePasse)
{
}

/**
 * @brief Destructeur de la classe Serveur
 * @see Intervention
 */
Serveur::~Serveur()
{
}

/**
 * @brief Accesseur de l'attribut port
 * @return un entier qui represente le port du serveur
 */
int Serveur::getPort() const
{
    return this->port;
}

/**
 * @brief Accesseur de l'attribut hostName
 * @return un QString
 */
QString Serveur::getHostName() const
{
    return this->hostName;
}

/**
 * @brief Accesseur de l'attribut utilisateur
 * @return un QString
 */
QString Serveur::getUtilisateur() const
{
    return this->utilisateur;
}

/**
 * @brief Accesseur de l'attribut motDePasse
 * @return un QString
 */
QString Serveur::getMotDePasse() const
{
    return this->motDePasse;
}

/**
 * @brief Mutateur de l'attribut port
 * @param port le port du serveur
 */
void Serveur::setPort(const int port)
{
    this->port = port;
}

/**
 * @brief Mutateur de l'attribut hostName
 * @param hostname
 */
void Serveur::setHostName(const QString& hostName)
{
    this->hostName = hostName;
}

/**
 * @brief Mutateur de l'attribut utilisateur
 * @param utilisateur le nom de l'utilisateur
 */
void Serveur::setUtilisateur(const QString& utilisateur)
{
    this->utilisateur = utilisateur;
}

/**
 * @brief Mutateur de l'attribut motDePasse
 * @param motDePasse le mot de passe
 */
void Serveur::setMotDePasse(const QString& motDePasse)
{
    this->motDePasse = motDePasse;
}
