/**
 * @file        communication.cpp
 * @brief       Déclaration de la classe Communication.
 * @details      La classe Communication \c Cette classe permet de définir la communication
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     1.1
 * @date        2023
 */
#include "communication.h"

/**
 * @fn CommunicationMQTT::CommunicationMQTT
 * @brief Constructeur par défaut de la classe CommunicationMQTT
 */
Communication::Communication(int      idServeurTTN,
                             QString  hostname,
                             int      port,
                             QString  username,
                             QString  password,
                             QString  applicationID,
                             bool     estActif,
                             QObject* parent) :
    QObject(parent),
    idServeurTTN(idServeurTTN), hostname(hostname), port(port), username(username),
    password(password), applicationID(applicationID), estActif(estActif), client(nullptr),
    abonnement(nullptr)

{
    qDebug() << Q_FUNC_INFO << "idServeurTTN" << this->idServeurTTN << "hostname" << this->hostname
             << "port" << this->port << "username" << this->username << "password" << this->password
             << "applicationID" << this->applicationID << "estActif" << this->estActif;
    client = new QMqttClient(this);
    client->setHostname(this->hostname);
    client->setPort(this->port);
    client->setUsername(this->username);
    client->setPassword(this->password);
    connect(client, SIGNAL(connected()), this, SLOT(connecter()));
    connect(client, SIGNAL(disconnected()), this, SLOT(deconnecter()));
    connect(client,
            SIGNAL(messageReceived(QByteArray, QMqttTopicName)),
            this,
            SLOT(recevoirDonnees(QByteArray, QMqttTopicName)));
    seConnecter();
}

/**
 * @fn CommunicationMQTT::CommunicationMQTT
 * @brief Destructeur de la classe CommunicationMQTT
 */
Communication::~Communication()
{
    qDebug() << Q_FUNC_INFO;
    seDeconnecter();
}

/**
 * @fn CommunicationMQTT::sAbonner
 * @param topic
 */
void Communication::sAbonner(QString topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic;
    QMqttSubscription* abonnement;
    abonnement = client->subscribe(topic);
    if(!abonnement)
    {
        qDebug() << Q_FUNC_INFO << "erreur abonnement";
        return;
    }
}

/**
 * @fn CommunicationMQTT::demarrer
 */
void Communication::demarrer()
{
    QString topic = QString("v3/") + username + QString("/devices/#");
    qDebug() << Q_FUNC_INFO << "topic" << topic;
    sAbonner(topic);
}

/**
 * @fn CommunicationMQTT::seConnecter
 */
void Communication::seConnecter()
{
    if(client == nullptr || client->state() == QMqttClient::Connected)
        return;
    qDebug() << Q_FUNC_INFO;
    client->connectToHost();
}

/**
 * @fn CommunicationMQTT::seDeconnecter
 */
void Communication::seDeconnecter()
{
    if(client == nullptr || client->state() == QMqttClient::Connected)
    {
        qDebug() << Q_FUNC_INFO;
        client->disconnectFromHost();
    }
}

/**
 * @fn slots pour se connecter
 */
void Communication::connecter()
{
    qDebug() << Q_FUNC_INFO;
    emit clientConnecte();
    demarrer();
}

/**
 * @fn slots pour se déconnecter
 */
void Communication::deconnecter()
{
    qDebug() << Q_FUNC_INFO;
    emit clientDeconnecte();
}

/**
 * @fn slots pour se déconnecter
 */
void Communication::recevoirDonnees(QByteArray message, QMqttTopicName topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic.name() << "message" << message;
    emit donneesRecues(message, topic);
}
