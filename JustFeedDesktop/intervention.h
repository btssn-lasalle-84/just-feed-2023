/**
 * @file        Intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QTime>

class Intervention
{
  private:
    QTime  heureIntervention;  //!< heure de l'intervention
    int    numeroIntervention; //!< numéro qui identifie l'intervention
    QTime  tempsTrajet;        //!< temps de trajet vers le distributeur
    double poidsARemplir; //!< poids à prévoir pour remplir le distributeur

  public:
    Intervention();
    Intervention(QTime  heureIntervention,
                 int    numeroIntervention,
                 QTime  tempsTrajet,
                 double poidsARemplir);
    ~Intervention();

    // Accesseurs
    QTime  getHeureIntervention() const;
    int    getNumeroIntervention() const;
    QTime  getTempsTrajet() const;
    double getPoidsARemplir() const;

    // Mutateurs
    void setHeureIntervention(const QTime& heureIntervention);
    void setNumeroIntervention(const int numeroIntervention);
    void setTempsTrajet(const QTime& tempsTrajet);
    void setPoidsARemplir(const double poidsARemplir);
};

#endif // INTERVENTION_H
