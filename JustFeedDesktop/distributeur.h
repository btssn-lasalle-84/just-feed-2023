/**
 * @file        distributeur.h
 * @brief       Déclaration de la classe Distributeur.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

/**
 * @struct Produit
 * @brief Définit les propriétés d'un produit
 */
struct Produit
{
    /**
     * @todo Définir les propriétés d'un Produit
     */
};

/**
 * @struct Localisation
 * @brief Pour localiser un distributeur
 */
struct Localisation
{
    /**
     * @todo Il manque des choses
     */
    float latitude;
    float longitude;
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
    Produit      produit;     //!< type de produit que contient le distributeur
    int          poidsTotal;  //!< à définir
    int          poidsActuel; //!< à définir
    int          hydrometrie; //!< hydrométrie de l'interieur du distributeur
    Localisation position;    //!< géolocalisation du distributeur
    bool         aIntervenir; //!< permet de savoir s'il faut intervenir sur le
                              //!< distributeur

  public:
    Distributeur();
    Distributeur(int          identifiant,
                 Produit      produit,
                 int          poidsTotal,
                 int          poidsActuel,
                 int          hydrometrie,
                 Localisation position,
                 bool         aIntervenir);
    ~Distributeur();

    // Accesseurs
    int          getIdentifiant() const;
    Produit      getProduit() const;
    int          getHydrometrie() const;
    Localisation getPosition() const;
    int          getPoidsTotal() const;
    int          getPoidsActuel() const;
    int          getAIntervenir() const;

    // Mutateurs
    void setProduit(const Produit& produit);
    void setHydrometrie(int hydrometrie);
    void setPosition(const Localisation& localisation);
    void setPoidsTotal(int poidsTotal);
    void setPoidsActuel(int poidsActuel);
    void setAIntervenir(bool aIntervenir);
};

#endif // DISTRIBUTEUR_H