/**
 * @file        Intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @details      La classe Intervention \c Cette classe permet ...
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
    ~Intervention();

    // Accesseurs
    /**
     * @todo Il faut penser const !
     */
    QTime  getHeureIntervention();
    int    getNumeroIntervention();
    QTime  getTempsTrajet();
    double getPoidsARemplir();

    // Mutateurs
    /**
     * @todo Il faut penser référence et const ou pas const !
     */
    void setHeureIntervention(QTime heureIntervention);
    void setNumeroIntervention(int numeroIntervention);
    void setTempsTrajet(QTime tempsTrajet);
    void setPoidsARemplir(double poidsARemplir);
};

#endif // INTERVENTION_H
