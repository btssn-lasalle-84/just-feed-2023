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

class Bac {
private:
  Produit *produit;              //!< produit que contient le bac
  double poidsActuel;            //!< à définir
  double poidsTotal;             //!< à définir
  double pourcentageRemplissage; //!< pourcentage de remplissage du bac
  bool aRemplir;   //!< permet de savoir s'il faut remplir ce distributeur
  bool aDepanner;  //!< permet de savoir s'il faut intervenir sur le
                   //!< distributeur
  int hygrometrie; //!< hygrometrie de l'interieur du distributeur

public:
  Bac();
  Bac(Produit *produit, double poidsActuel, double poidsTotal, int hygrometrie);
  Bac(Produit *produit, double poidsTotal);
  Bac(const Bac &bac);
  ~Bac();

  // Accesseurs
  Produit *getProduit() const;
  QString getNomProduit() const;
  double getPrixProduit() const;
  double getPoidsActuel() const;
  double getPoidsTotal() const;
  double getPourcentageRemplissage() const;
  double getQuantiteARemplir() const;
  int getHygrometrie() const;
  bool getARemplir() const;
  bool getADepanner() const;

  // Mutateurs
  void setProduit(Produit *produit);
  void setNomProduit(const QString &nomProduit);
  void setPrixProduit(const double &prixProduit);
  void setPoidsActuel(const double &poidsActuel);
  void setPoidsTotal(const double &poidsTotal);
  void setPourcentageRemplissage(const double &pourcentageRemplissage);
  void setHygrometrie(int hydrometrie);
  void setARemplir(bool aRemplir);
  void setADepanner(bool aDepanner);
};

#endif // BAC_H
