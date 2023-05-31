/**
 * @file        communication.cpp
 * @brief       Déclaration de la classe Communication.
 * @details      La classe Communication \c Cette classe permet de définir la communication
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#include "communication.h"

/**
 * @brief Constructeur par défaut de la classe bac
 */
Communication::Communication(int     idServeurTTN,
                             QString hostname,
                             int     port,
                             QString username,
                             QString password,
                             QString applicationID,
                             bool    estActif) :
    idServeurTTN(idServeurTTN),
    hostname(hostname), port(port), username(username), password(password),
    applicationID(applicationID), estActif(estActif)
{
    qDebug() << Q_FUNC_INFO << "idServeurTTN" << this->idServeurTTN << "hostname" << this->hostname
             << "port" << this->port << "username" << this->username << "password" << this->password
             << "applicationID" << this->applicationID << "estActif" << this->estActif;
}

/**
 * @brief Destructeur de la classe bac
 */
Communication::~Communication()
{
}

void Communication::connecter()
{
    QMqttClient client;
    client.setHostname(this->hostname);
    client.setPort(this->port);
}
