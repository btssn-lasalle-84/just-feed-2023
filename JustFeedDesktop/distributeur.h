/**
 * @file        distributeur.h
 * @brief       Déclaration de la classe Distributeur.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <vector>
class Bac;

/**
 * @class       Distributeur
 * @brief       Déclaration de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet ...
 */
class Distributeur
{
  private:
    int          identifiant; //!< identifiant du distributeur
    std::vector<Bac*>  bacs; //!< conteneur de bac

  public:
    Distributeur();
    Distributeur(int identifiant, std::vector<Bac*>  bacs);
    ~Distributeur();

    // Accesseurs
    int          getIdentifiant() const;

    //mutateurs
    void        setIdentifiant(const int identifiant);
    void        setBacsProduit(const int identifiantBac, const Produit produit);

};

#endif // DISTRIBUTEUR_H
