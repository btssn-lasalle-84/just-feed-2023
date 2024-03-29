/**
 * @file        bac.h
 * @brief       Déclaration de la classe Bac.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     1.1
 * @date        2023
 */

#ifndef BAC_H
#define BAC_H

/**
 * @def ID_BAC_NON_DEFINI
 * @brief Définit la valeur d'un id non défini
 */
#define ID_BAC_NON_DEFINI -1

#include <QString>

class Produit;

class Bac
{
  public:
    /**
     * @enum TableBac
     * @brief Définit les champs de la table Bac
     *
     */
    enum TableBac
    {
        ID_BAC          = 0,
        ID_DISTRIBUTEUR = 1,
        ID_PRODUIT      = 2,
        POIDS_ACTUEL    = 3,
        POID_TOTAL      = 4,
        HYGROMETRIE     = 5,
        REMPLISSAGE     = 6,
    };

  private:
    int      idBac;                  //!< identifiant du bac
    Produit* produit;                //!< produit que contient le bac
    double   poidsActuel;            //!< à définir
    double   poidsTotal;             //!< à définir
    double   pourcentageRemplissage; //!< pourcentage de remplissage du bac
    bool     aRemplir;               //!< permet de savoir s'il faut remplir ce distributeur
    bool     aDepanner;              //!< permet de savoir s'il faut intervenir sur le
                                     //!< distributeur
    int  hygrometrie;                //!< hygrometrie de l'interieur du distributeur
    bool aIntervenir;                //!< bac attribué à une intervention

  public:
    Bac();
    Bac(int idBac, Produit* produit, double poidsActuel, double poidsTotal, int hygrometrie);
    Bac(int idBac, Produit* produit, double poidsTotal);
    Bac(const QStringList& bac, Produit* produit);
    Bac(const Bac& bac);
    ~Bac();

    // Accesseurs
    int      getIdBac() const;
    Produit* getProduit() const;
    QString  getNomProduit() const;
    double   getPrixProduit() const;
    double   getPoidsActuel() const;
    double   getPoidsTotal() const;
    double   getPourcentageRemplissage() const;
    double   getQuantiteARemplir() const;
    int      getHygrometrie() const;
    bool     getARemplir() const;
    bool     getADepanner() const;
    bool     getAIntervenir() const;

    // Mutateurs
    void setProduit(Produit* produit);
    void setNomProduit(const QString& nomProduit);
    void setPrixProduit(const double& prixProduit);
    void setPoidsActuel(const double& poidsActuel);
    void setPoidsTotal(const double& poidsTotal);
    void setPourcentageRemplissage(const double& pourcentageRemplissage);
    void setHygrometrie(int hydrometrie);
    void setARemplir(bool aRemplir);
    void setADepanner(bool aDepanner);
    void setAIntervenir(bool attribue);
};

#endif // BAC_H
