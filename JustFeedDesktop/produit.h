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
    double  prix; //!< prix au 100 grammes du produit
    QString nom;  //!< nom du produit
    QString marque; //!< marque du produit
    QString description; //!< description du produit
    unsigned long long codeProduit; //!< code EAN 13 du produit

  public:
    Produit();
    Produit(double prix, QString nom, QString marque, QString description, unsigned long long codeProduit);
    ~Produit();

    // Accesseurs
    double  getPrix() const;
    QString getNom() const;
    QString getMarque() const;
    QString getDescription() const;
    unsigned long long getCodeProduit() const;

    // Mutateurs
    void setPrix(const double prix);
    void setNom(const QString& nom);
    void setMarque(const QString& marque);
    void setDescription(const QString& description);
    void setCodeProduit(const unsigned long long& codeProduit);
};

#endif // PRODUIT_H
