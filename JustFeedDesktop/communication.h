/**
 * @file        communication.h
 * @brief       Déclaration de la classe Communication.
 * @details     La classe Communication \c Cette classe permet ...
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     1.1
 * @date        2023
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>
#include <QtMqtt/QtMqtt>

/**
 * @class       Communication
 * @brief       Définition de la classe Communication.
 * @details      La classe Communication \c Cette classe permet ...
 */
class Communication : public QObject
{
    Q_OBJECT
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

  private:
    int                idServeurTTN;  //!< idServeurTTN
    QString            hostname;      //!< hostname
    int                port;          //!< port
    QString            username;      //!< username
    QString            password;      //!< password
    QString            applicationID; //!< applicationID
    bool               estActif;      //!< estActif
    QMqttClient*       client;        //!< client
    QMqttSubscription* abonnement;    //!< abonnement

  public:
    Communication(int      idServeurTTN,
                  QString  hostname,
                  int      port,
                  QString  username,
                  QString  password,
                  QString  applicationID,
                  bool     estActif,
                  QObject* parent = nullptr);
    ~Communication();

  public slots:
    void sAbonner(QString topic);
    void demarrer();
    void seConnecter();
    void seDeconnecter();
    void connecter();
    void deconnecter();
    void recevoirDonnees(QByteArray message, QMqttTopicName topic);

  signals:
    void clientConnecte();
    void clientDeconnecte();
    void donneesRecues(QByteArray message, QMqttTopicName topic);
};

#endif // COMMUNICATION_H
