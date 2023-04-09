/**
 * @file        produit.h
 * @brief       Déclaration de la classe Produit.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>

class Produit
{
  private:
    QString nom;         //!< nom du produit
    QString marque;      //!< marque du produit
    QString description; //!< description du produit
    QString codeProduit; //!< code EAN 13 du produit
    double  prix;        //!< prix au 100 grammes du produit

  public:
    Produit();
    Produit(QString nom, QString marque, QString description, QString codeProduit, double prix);
    ~Produit();

    // Accesseurs
    QString getNom() const;
    QString getMarque() const;
    QString getDescription() const;
    QString getCodeProduit() const;
    double  getPrix() const;

    // Mutateurs
    void setNom(const QString& nom);
    void setMarque(const QString& marque);
    void setDescription(const QString& description);
    void setCodeProduit(const QString& codeProduit);
    void setPrix(const double prix);
};

#endif // PRODUIT_H
