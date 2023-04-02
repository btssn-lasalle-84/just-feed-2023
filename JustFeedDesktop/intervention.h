/**
 * @file        Intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QVector>
#include <QTime>
class Distributeur;
class Produit;

class Intervention
{
  private:
    QTime  heureIntervention;  //!< heure de l'intervention
    QTime  tempsTrajet;        //!< temps de trajet vers le distributeur
    QVector<double> poidsARemplir; //!< poids à prévoir pour remplir les differents bac du distributeur
    Distributeur *distributeurAIntervenir; //!< les distributeurs sur les quels il faut intervenir

  public:
    Intervention();
    Intervention(QTime  heureIntervention,
                 QTime  tempsTrajet,
                 QVector<double> poidsARemplir,
                 Distributeur *distributeurAIntervenir);
    ~Intervention();

    // Accesseurs
    QTime  getHeureIntervention() const;
    QTime  getTempsTrajet() const;
    double getPoidsARemplir(int numeroBac) const;
    Distributeur* getDistributeurAIntervenir() const;

    // Mutateurs
    void setHeureIntervention(const QTime& heureIntervention);
    void setTempsTrajet(const QTime& tempsTrajet);
    void setPoidsARemplir(const double poidsARemplir, const int numeroBac);
    void setDistributeurAIntervenir(Distributeur* distributeur);
};

#endif // INTERVENTION_H
