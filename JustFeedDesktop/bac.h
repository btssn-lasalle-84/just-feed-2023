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
    Produit* produit;                //!< produit que contient le bac
    double   poidsActuel;            //!< à définir
    double   poidsTotal;             //!< à définir
    double   pourcentageRemplissage; //!< pourcentage de remplissage du bac
    bool     aIntervenir;

  public:
    Bac();
    Bac(Produit* produit, double poidsActuel, double poidsTotal);
    Bac(Produit* produit, double poidsTotal);
    Bac(const Bac& bac);
    ~Bac();

    // Accesseurs
    Produit* getProduit() const;
    QString  getNomProduit() const;
    double   getPrixProduit() const;
    double   getPoidsActuel() const;
    double   getPoidsTotal() const;
    double   getPourcentageRemplissage() const;
    bool     getAIntervenir() const;
    double   getQuantiteARemplir() const;

    // Mutateurs
    void setProduit(Produit* produit);
    void setNomProduit(const QString& nomProduit);
    void setPrixProduit(const double& prixProduit);
    void setPoidsActuel(const double& poidsActuel);
    void setPoidsTotal(const double& poidsTotal);
    void setPourcentageRemplissage(const double& pourcentageRemplissage);
    void setAIntervenir(bool aIntervenir);
};

#endif // BAC_H
