/**
 * @file        distributeur.h
 * @brief       Définition de la classe distributeur.
 * @detail      La classe distrubuteur \c Cette classe permet de définir les attributs et les méthodes de la classe.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
*/

#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

struct Produits //!< Structure des differents produits.
{
//Todo
};

struct Localisation //!< Structure pour localiser le distributeur.
{
//Todo
};

class Distributeur
{
private:
    int identifiant; //!< identifiant du distributeur.
    Produits produit; //!< type de produit que contient le distributeur.
    int poidsTotal; //!< à définir.
    int poidsActuel; //!< à définir.
    int hydroetrie; //!< hydrométrie de l'interieur du distributeur.
    Localisation position; //!< géolocalisation du distributeur.
    bool aIntervenir; //!< permet de savoir si il faut intervenir sur le distributeur.

public:

    Distributeur(); //TODO
    /**
     * @brief Constructeur par défault de la classe Distributeur
     * @see Distributeur
     */
    ~Distributeur(); //TODO
    /**
     * @brief Destructeur de la classe Distributeur
     * @see Distributeur
     */
    //Accesseur
    int getIdentifiant();
    /**
     * @brief Accesseur de l'attribut identifiant.
     * @return un entier qui represente l'identifiant du distributeur
     */
    Produits getProduit();
    /**
     * @brief Accesseur de l'attribut produit.
     * @return un Produits qui represente le produit que contient le distributeur
     */
    int getHydrometrie();
    /**
     * @brief Accesseur de l'attribut hydrometrie.
     * @return un entier qui represente le degres d'humidité dans le distributeur
     */
    Localisation getPosition();
    /**
     * @brief Accesseur de l'attribut position.
     * @return une Localisaton qui represente la géolocalisation du distributeur
     */
    int getPoidsTotal();
    /**
     * @brief Accesseur de l'attribut poidsTotal.
     * @return un entier qui represente le poids total que peut contenir le distributeur
     */
    int getPoidsActuel();
    /**
     * @brief Accesseur de l'attribut poidsActuel.
     * @return un entier qui represente le poids actuel dans le distributeur.
     */
    int getAIntervenir();
    /**
     * @brief Accesseur de l'attribut AIntervenir.
     * @return un bool qui permet de savoir si il faut intervenir sur le distributeur.
     */
    //Mutateurs
    void setProduit(Produits produit);
    /**
     * @brief Mutateur de l'attribut Produit.
     * @param il prend en argument le produit du distributeur.
     */
    void setHydrometrie(int hydrometrie);
    /**
     * @brief Mutateur de l'attribut hydrométrie.
     * @param il prend en argument l'hydrometrie du distributeur.
     */
    void setPosition(Localisation localisation);
    /**
     * @brief Mutateur de l'attribut localisation.
     * @param il prend en argument la localisation du distributeur.
     */
    void setPoidsTotal(int poidsTotal);
    /**
     * @brief Mutateur de l'attribut poidsTotal.
     * @param il prend en argument le poids total du distributeur.
     */
    void setPoidsActuel(int poidsActuel);
    /**
     * @briefmutateur de l'attribut poidsActuel
     * @param il prend en argument le poids actuel du distributeur.
     */
    void setAIntervenir(bool aIntervenir);
    /**
     * @briefmutateur de l'attribut aIntervenir.
     * @param il prend en argument un booleen qui détérmine l'état du distributeur.
     */
};

#endif // DISTRIBUTEUR_H
