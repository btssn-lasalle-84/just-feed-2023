/**
 * @file        Serveur.h
 * @brief       Déclaration de la classe Serveur.
 * @detail      La classe Serveur \c Cette classe permet ...
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef SERVEUR_H
#define SERVEUR_H

#include <QString>

class Serveur
{
  private:
    int     port;        //!< port du serveur
    QString hostName;    //!< name du serveur
    QString utilisateur; //!< ulisateur du serveur
    int     motDePasse;  //!< mot de passe du serveur

  public:
    Serveur();
    ~Serveur();

    // Accesseurs
    int     getPort();
    QString getHostName();
    QString getUtilisateur();
    int     getMotDePasse();

    // Mutateurs
    void setPort(int port);
    void setHostName(QString hostName);
    void setUtilisateur(QString utilisateur);
    void setMotDePasse(int motDePasse);
};

#endif // SERVEUR_H
