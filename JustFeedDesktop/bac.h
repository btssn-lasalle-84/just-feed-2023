/**
 * @file        Bac.h
 * @brief       Déclaration de la classe Bac.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef BAC_H
#define BAC_H

#include <QString>

class Produit;
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

class Bac
{
private:
    Produit      *produit;     //!< type de produit que contient le distributeur
    unsigned int poidsActuel; //!< à définir
    float        pourcentageRemplissage;
    int          hydrometrie; //!< hydrométrie de l'interieur du distributeur
    Localisation position;    //!< géolocalisation du distributeur
    bool         aIntervenir; //!< permet de savoir s'il faut intervenir sur le
                              //!< distributeur
public:
    Bac();
    Bac(Produit      produit,
        unsigned int          poidsActuel,
        float        pourcentageRemplissage,
        int          hydrometrie,
        Localisation position,
        bool         aIntervenir);
    ~Bac();

    // Accesseurs
    QString      getNomProduit() const;
    double       getPrixProduit() const;
    int          getHydrometrie() const;
    Localisation getPosition() const;
    unsigned int          getPoidsActuel() const;
    int          getAIntervenir() const;

    // Mutateurs
    void setNomProduit(const QString& NomProduit);
    void setPrixProduit(const int& prixProduit);
    void setHydrometrie(int hydrometrie);
    void setPosition(const Localisation& localisation);
    void setPoidsActuel(int poidsActuel);
    void setAIntervenir(bool aIntervenir);
};

#endif // BAC_H
