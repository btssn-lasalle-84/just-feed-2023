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

  public:
    Produit();
    Produit(double prix, QString nom);
    ~Produit();

    // Accesseurs
    double  getPrix() const;
    QString getNom() const;

    // Mutateurs
    void setPrix(const double prix);
    void setNom(const QString& nom);
};

#endif // PRODUIT_H
