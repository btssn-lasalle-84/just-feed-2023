/**
 * @file        Serveur.h
 * @brief       Définition de la classe Serveur.
 * @detail      La classe Serveur \c Cette classe permet de définir les attributs et les méthodes de la classe.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
*/

#ifndef SERVEUR_H
#define SERVEUR_H

#include <QString>
class Serveur
{
private :
    int port; //!< port du serveur
    QString hostName; //!<name du serveur
    QString utilisateur; //!< ulisateur du serveur
    int motDePasse; //!< mot de passe du serveur
public:
    Serveur();
    /**
     * @brief Constructeur par défault de la classe Serveur
     * @see Intervention
     */
    ~Serveur();
    /**
     * @brief Destructeur de la classe Serveur
     * ^@see Intervention
     */
    //accesseur
    int getPort();
    /**
     * @brief Accesseur de l'attribut port.
     * @return un entier qui represente le port du serveur
     */
    QString getHostName();
    /**
     * @brief Accesseur de l'attribut hostName.
     * @return un QString
     */
    QString getUtilisateur();
    /**
     * @brief Accesseur de l'attribut utilisateur.
     * @return un QString
     */
    int getMotDePasse();
    /**
     * @brief Accesseur de l'attribut motDePasse.
     * @return un entier
     */
    //mutateur
    void setPort(int port);
    /**
     * @brief Mutateur de l'attribut port.
     * @param il prend en argument le port du serveur.
     */
    void setHostName(QString hostName);
    /**
     * @brief Mutateur de l'attribut hostName.
     * @param il prend en argument .  //TODO
     */
    void setUtilisateur(QString utilisateur);
    /**
     * @brief Mutateur de l'attribut utilisateur.
     * @param il prend en argument le nom de l'utilisateur.
     */
    void setMotDePasse(int motDePasse);
    /**
     * @brief Mutateur de l'attribut motDePasse.
     * @param il prend en argument le mot de passe.
     */
};

#endif // SERVEUR_H
