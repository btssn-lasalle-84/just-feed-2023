/**
 * @file        serveur.h
 * @brief       Déclaration de la classe Serveur.
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
    QString motDePasse;  //!< mot de passe du serveur

  public:
    Serveur();
    Serveur(int port, QString hostName, QString utilisateur, QString motDePasse);
    ~Serveur();

    // Accesseurs
    int     getPort() const;
    QString getHostName() const;
    QString getUtilisateur() const;
    QString getMotDePasse() const;

    // Mutateurs
    void setPort(const int port);
    void setHostName(const QString& hostName);
    void setUtilisateur(const QString& utilisateur);
    void setMotDePasse(const QString& motDePasse);
};

#endif // SERVEUR_H
