/**
 * @file        Serveur.h
 * @brief       Déclaration de la classe Serveur.
 * @details      La classe Serveur \c Cette classe permet déclarer un objet Serveur
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
    Serveur(int port, QString hostName, QString utilisateur, int motDePasse);
    ~Serveur();

    // Accesseurs
    int     getPort() const;
    QString getHostName() const;
    QString getUtilisateur() const;
    int     getMotDePasse() const;

    // Mutateurs
    void setPort(const int port);
    void setHostName(const QString hostName);
    void setUtilisateur(const QString utilisateur);
    void setMotDePasse(const int motDePasse);
};

#endif // SERVEUR_H
