/**
 * @file        distributeur.h
 * @brief       Déclaration de la classe Distributeur.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <QDate>
#include <QVector>

class Bac;
class Produit;

/**
 * @struct Localisation
 * @brief Pour localiser un distributeur
 */
struct Localisation {
  QString latitude;
  QString longitude;
  QString altitude;
};

/**
 * @class       Distributeur
 * @brief       Déclaration de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet ...
 */
class Distributeur {
private:
  QString deviceID;        //!< identifiant du distributeur
  QVector<Bac *> bacs;     //!< les bacs du distributeur
  QString nom;             //!< nom du distributeur
  QString adresse;         //!< adresse du distributeur
  QString codePostal;      //!< code postal du distributeur
  QString ville;           //!< ville du distributeur
  QString description;     //!< description du distributeur
  QDate dateMiseEnService; //!< date de mise en service du distributeur
  Localisation position;   //!< géolocalisation du distributeur
  bool aRemplir;  //!< permet de savoir s'il faut remplir ce distributeur
  bool aDepanner; //!< permet de savoir s'il faut intervenir sur le
                  //!< distributeur

public:
  Distributeur();
  Distributeur(QString deviceID, QString nom, QString adresse,
               QString codePostal, QString ville, QString description,
               QDate dateMiseEnService, Localisation position);
  ~Distributeur();

  // Accesseurs
  QString getDeviceID() const;
  Localisation getPosition() const;
  bool getARemplir() const;
  bool getADepanner() const;
  bool getAIntervenir() const;
  int getHygrometrieBac(int numeroBac) const;
  QString getNom() const;
  QString getAdresse() const;
  QString getCodePostal() const;
  QString getVille() const;
  QDate getDateMiseService() const;
  QString getDescription() const;
  QString getNomProduitBac(int numeroBac) const;
  double getProduitPrix(int numeroBac) const;
  Produit *getProduitBac(int numeroBac) const;
  Bac *getBac(int numeroBac) const;
  int getNbBacs() const;
  bool getAIntervenirBac(int numeroBac) const;
  double getPourcentageBac(int numeroBac) const;
  double getPoidsBac(int numeroBac) const;
  double getPoidsTotalBac(int numeroBac) const;

  // mutateurs
  void setDeviceID(const QString deviceID);
  void setPosition(const Localisation &localisation);
  void setARemplir(bool aRemplir);
  void setADepanner(bool aDepanner);
  void setNom(const QString &nom);
  void setAdresse(const QString &adresse);
  void setCodePostal(const QString &codePostal);
  void setVille(const QString &ville);
  void setDateMiseEnService(const QDate &dateMiseEnService);
  void setDescription(const QString &description);
  void setPrixProduit(const int &numeroBac, const double &prix);
  void ajouterBac(const Bac &bac);
  void supprimerBac(const int numeroBacASupprimer);
};

#endif // DISTRIBUTEUR_H
