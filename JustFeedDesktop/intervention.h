/**
 * @file        Intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.2
 * @date        2023
 */
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QDateTime>
#include <QVector>
#include <QString>
#include <QTime>

#define INTERVENTION_PAS_DEFINIE -1
#define OPERATEUR_NON_DEFINI     -1

class Distributeur;
class Produit;
class BaseDeDonnees;

class Intervention
{
  private:
    BaseDeDonnees*         baseDeDonnees;      //!< association avec la base de données
    QDate                  dateIntervention;   //!< la date de l'intervention
    QVector<QTime>         heuresIntervention; //!< l'heure de l'intervention
    QVector<Distributeur*> distributeurs;  //!< les distributeurs sur lesquels il faut intervenir
    bool                   effectuee;      //!< si l'intervention a été effectuée
    bool                   aRemplir;       //!< si on doit remplir au moins un distributeur
    bool                   aDepanner;      //!< si on doit dépanner au moins un distributeur
    int                    idIntervention; //!< id de l'intervention
    int                    idOperateur;    //!< id de l'opérateur

  public:
    explicit Intervention(QVector<Distributeur*> listeDistributeursAIntervenir);
    ~Intervention();

    QDate                  getDateIntervention() const;
    QVector<Distributeur*> getDistributeurs() const;
    bool                   getARemplir() const;
    bool                   getADepanner() const;
    int                    getIdIntervention() const;
    int                    getIdOperateur() const;
    bool                   estEffectuee() const;
    bool                   estAIntervenir() const;
    void                   setDateIntervention(const QDate& dateIntervention);
    void                   setARemplir(const bool& aRemplir);
    void                   setADepanner(const bool& aDepanner);
    void                   setIdOperateur(const int& idOperateur);
    void                   setIdIntervention(const int numeroIntervention);
    void                   ajouterDistributeur(Distributeur* distributeur);
    void                   effectuer(bool effectuee);
    void                   intervenir(bool aIntervenir);
    void                   creer();
    void                   affecterEtatIntervention(int const indexDistributeur);
    int                    ajouterIntervention(const int indexDistributeur);
    void                   ajouterApprovisionnement(int const indexDistributeur);
    int                    estPlanifiee(const int idDistributeur);
};

#endif // INTERVENTION_H
