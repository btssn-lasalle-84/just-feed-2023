/**
 * @file        distributeur.h
 * @brief       Déclaration de la classe Distributeur.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <QVector>

class Bac;

/**
 * @struct Localisation
 * @brief Pour localiser un distributeur
 */
struct Localisation
{
    QString latitude;
    QString longitude;
};

/**
 * @class       Distributeur
 * @brief       Déclaration de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet ...
 */
class Distributeur
{
  private:
    int          identifiant; //!< identifiant du distributeur
    Localisation position;    //!< géolocalisation du distributeur
    int          hydrometrie; //!< hydrométrie de l'interieur du distributeur
    bool         aIntervenir; //!< permet de savoir s'il faut intervenir sur le
                              //!< distributeur
    QVector<Bac*> bacs;       //!< les bacs du distributeur

  public:
    Distributeur();
    Distributeur(int identifiant, Localisation position);
    ~Distributeur();

    // Accesseurs
    int          getIdentifiant() const;
    Localisation getPosition() const;
    int          getAIntervenir() const;
    int          getHydrometrie() const;

    // mutateurs
    void setIdentifiant(const int identifiant);
    void setHydrometrie(int hydrometrie);
    void setPosition(const Localisation& localisation);
    void setAIntervenir(bool aIntervenir);
    void ajouterBac(const Bac& bac);
};

#endif // DISTRIBUTEUR_H
