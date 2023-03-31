/**
 * @file        Bac.h
 * @brief       Déclaration de la classe Bac.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef BAC_H
#define BAC_H

#include <QString>

class Produit;

class Bac
{
  private:
    Produit*     produit;     //!< produit que contient le bac
    unsigned int poidsActuel; //!< à définir
    double       pourcentageRemplissage;

  public:
    Bac();
    Bac(Produit* produit, unsigned int poidsActuel, double pourcentageRemplissage = 100.);
    Bac(const Bac& bac);
    ~Bac();

    // Accesseurs
    Produit*     getProduit() const;
    QString      getNomProduit() const;
    double       getPrixProduit() const;
    unsigned int getPoidsActuel() const;

    // Mutateurs
    void setProduit(Produit* produit);
    void setNomProduit(const QString& nomProduit);
    void setPrixProduit(const int& prixProduit);
    void setPoidsActuel(int poidsActuel);
};

#endif // BAC_H
