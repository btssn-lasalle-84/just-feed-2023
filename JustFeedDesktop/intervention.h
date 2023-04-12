/**
 * @file        Intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QDateTime>
#include <QTime>
#include <QVector>
#include <QtWidgets>

class Distributeur;
class Produit;
class IHMJustFeed;

class Intervention : public QDialog {
private:
  IHMJustFeed *ihmJustFeed; //!< l'ihm principale
  QDateTime horodatage;     //!< date et heure de l'intervention
  QVector<Distributeur *>
      distributeurs; //!< les distributeurs sur lesquels il faut intervenir
  bool effectuee;    //!< si l'intervention a été effectuée

public:
  Intervention();
  ~Intervention();

  // Accesseurs
  QDateTime getHorodatage() const;
  QVector<Distributeur *> getDistributeurs() const;
  double getEffectuee() const;

  // Mutateurs
  void setHorodatage(const QDateTime &horodatage);
  void ajouterDistributeur(Distributeur *distributeur);
  void setEffectuee(const bool effectuee);
};

#endif // INTERVENTION_H
