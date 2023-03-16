#ifndef SERVEUR_H
#define SERVEUR_H

#include <QString>
class Serveur
{
private :
    int port;
    QString hostName;
    QString utilisateur;
    int motDePasse;
public:
    Serveur();
};

#endif // SERVEUR_H
