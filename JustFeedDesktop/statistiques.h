/**
 * @file        Statistiques.h
 * @brief       Déclaration de la classe Statistiques.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef STATISTIQUES_H
#define STATISTIQUES_H

class Statistiques
{
  private:
    int frequenceIntervetion; //!< frequence d'intervention pour chaque bac
    int poidsMoyenProduits; //!< poids moyen à prendre pour remplir un bac
    int moyenneKilometres; //!< kilometres moyen lors d'une intervention

  public:
    Statistiques();
    Statistiques(int frequenceIntervetion,
                 int poidsMoyenProduits,
                 int moyenneKilometres);
    ~Statistiques();

    // Accesseurs
    int getFrequenceIntervetion() const;
    int getPoidsMoyenProduits() const;
    int getMoyenneKilometres() const;

    // Mutateurs
    void setFrequenceIntervetion(const int frequenceIntervetion);
    void setPoidsMoyenProduits(const int poidsMoyenProduits);
    void setMoyenneKilometres(const int moyenneKilometres);
};

#endif // STATISTIQUES_H
