/**
 * @file        communication.h
 * @brief       Déclaration de la classe Communication.
 * @details     La classe Communication \c Cette classe permet ...
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>
/**
 * @class       Communication
 * @brief       Définition de la classe Communication.
 * @details      La classe Communication \c Cette classe permet ...
 */
class Communication
{
  private:
    int     idServeurTTN;
    QString hostname;
    int     port;
    QString username;
    QString password;
    QString applicationID;
    bool    estActif;

  public:
    enum TableCommunication
    {
        ID_SERVEUR_TTN,
        HOSTNAME_COMMUNICATION,
        PORT,
        USERANME,
        PASSWORD_COMMUNICATION,
        APPLICATION_ID,
        EST_ACTIF
    };

    Communication(int     idServeurTTN,
                  QString hostname,
                  int     port,
                  QString username,
                  QString password,
                  QString applicationID,
                  bool    estActif);
    ~Communication();
    void connecter();
};

#endif // COMMUNICATION_H
