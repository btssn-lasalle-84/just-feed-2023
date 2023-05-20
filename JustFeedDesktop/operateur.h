#ifndef OPERATEUR_H
#define OPERATEUR_H

#include <QVector>
#include <QString>
class Operateur
{
private :
    unsigned int idOperateur; //!< id de l'operateur
    QString nom; //!< nom de l'operateur
    QString prenom; //!< prenom de l'operateur
    QString identifiant; //!< identifiant de l'operateur
    QString email; //!< email de l'operateur

public:
    Operateur(int idOperateur, QString nom, QString prenom, QString identifiant, QString email);
    int getIdOperateur() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getIdentifiant() const;
    QString getEmail() const;

    void setIdOerateur(const int idOperateur);
    void setNom(const QString nom);
    void setPrenom(const QString prenom);
    void setIdentifiant(const QString identifiant);
    void setEmail(const QString email);
};

#endif // OPERATEUR_H
