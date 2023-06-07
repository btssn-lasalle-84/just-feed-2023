/**
 * @file        operateur.h
 * @brief       Déclaration de la classe Operateur.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     1.1
 * @date        2023
 */

#ifndef OPERATEUR_H
#define OPERATEUR_H

#include <QVector>
#include <QString>
#include <QStringList>

/**
 * @def ID_OPERATEUR_NON_DEFINI
 * @brief Définit la valeur d'un id non défini
 */
#define ID_OPERATEUR_NON_DEFINI -1

class Operateur
{
  public:
    /**
     * @enum TableOperateur
     * @brief Définit les champs de la table Operateur
     *
     */
    enum TableOperateur
    {
        ID          = 0,
        NOM         = 1,
        PRENOM      = 2,
        IDENTIFIANT = 3,
        EMAIL       = 4
    };

  private:
    int     id;          //!< id de l'operateur
    QString nom;         //!< nom de l'operateur
    QString prenom;      //!< prenom de l'operateur
    QString identifiant; //!< identifiant de l'operateur
    QString email;       //!< email de l'operateur

  public:
    Operateur(int idOperateur, QString nom, QString prenom, QString identifiant, QString email);
    Operateur(const QStringList operateur);
    int     getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getIdentifiant() const;
    QString getEmail() const;

    void setId(const int idOperateur);
    void setNom(const QString nom);
    void setPrenom(const QString prenom);
    void setIdentifiant(const QString identifiant);
    void setEmail(const QString email);
};

#endif // OPERATEUR_H
