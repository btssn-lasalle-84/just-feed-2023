/**
 * @file        Statistiques.h
 * @brief       Déclaration de la classe Statistiques.
 * @detail      La classe Statistiques \c Cette classe permet ...
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef STATISTIQUES_H
#define STATISTIQUES_H

class Statistiques
{
  private:
    int frequenceIntervetion;
    int poidsMoyenProduits;
    int moyenneKilometres;

  public:
    Statistiques();
    ~Statistiques();

    // Accesseurs
    int getFrequenceIntervetion();
    int getPoidsMoyenProduits();
    int getMoyenneKilometres();

    // Mutateurs
    void setFrequenceIntervetion(int frequenceIntervetion);
    void setPoidsMoyenProduits(int poidsMoyenProduits);
    void setMoyenneKilometres(int moyenneKilometres);
};

#endif // STATISTIQUES_H
