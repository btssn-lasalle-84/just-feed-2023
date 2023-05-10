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
#include <QTime>

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
    QVector<QTime>         heuresIntervention; //!< l'heure de l'intervention
    QVector<Distributeur*> distributeurs;     //!< les distributeurs sur lesquels il faut intervenir
    bool                   effectuee;         //!< si l'intervention a été effectuée
    bool                   remplir;           //!<
    bool                   depanner;          //!<
    int                    numeroIntervention; //!<

  public:
    explicit Intervention(QVector<Distributeur*> listeDistributeursAIntervenir, QVector<QTime> listeHeureIntervention);
    ~Intervention();

    QDate                  getDateIntervention() const;
    QTime                  getHeuresIntervention(int idDistributeur) const;
    QVector<Distributeur*> getDistributeurs() const;
    bool                   getARemplir() const;
    bool                   getADepanner() const;
    int                    getNumeroIntervention() const;
    bool                   estEffectuee() const;
    bool                   estAIntervenir() const;
    void                   setDateIntervention(const QDate& dateIntervention);
    void                   setARemplir(const bool& aRemplir);
    void                   setADepanner(const bool& aDepanner);
    void                   ajouterDistributeur(Distributeur* distributeur);
    void                   effectuer(bool effectuee);
    void                   intervenir(bool aIntervenir);
    void                   creer();
    void                   setNumeroIntervention(const int numeroIntervention);
    void                   affecterEtatIntervention(int const idDistributeur);
    void                   ajouterIntervention(const int idDistributeur);
    void                   ajouterApprovisionnement(int const idDistributeur);
    bool                   interventionEstPlanifie(const int idDistributeur);
};

#endif // INTERVENTION_H
