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
#include <QVector>
#include <QString>

#define ZERO      0
#define QUINZE    15
#define TRENTE    30
#define CINQUANTE 50
#define SOIXANTE  60
#define CENT      100
#define OPERATEUR 1

class Distributeur;
class Produit;
class BaseDeDonnees;

class Intervention
{
  private:
    BaseDeDonnees*         baseDeDonnees;
    QDate                  dateIntervention;  //!< la date de l'intervention
    QTime                  heureIntervention; //!< l'heure de l'intervention
    QVector<Distributeur*> distributeurs;     //!< les distributeurs sur lesquels il faut intervenir
    bool                   effectuee;         //!< si l'intervention a été effectuée

  public:
    explicit Intervention(QVector<Distributeur*> listeDistributeursAIntervenir);
    ~Intervention();

    QDate                  getDateIntervention() const;
    QTime                  getHeureIntervention() const;
    QVector<Distributeur*> getDistributeurs() const;
    bool                   estEffectuee() const;
    bool                   estAIntervenir() const;
    void                   setDateIntervention(const QDate& dateIntervention);
    void                   setHeureIntervention(const QTime& heureIntervention);
    void                   ajouterDistributeur(Distributeur* distributeur);
    void                   effectuer(bool effectuee);
    void                   intervenir(bool aIntervenir);
    void                   creer();
};

#endif // INTERVENTION_H
