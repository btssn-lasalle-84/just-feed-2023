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
#include <QDate>

class Bac;
class Produit;

/**
 * @struct Localisation
 * @brief Pour localiser un distributeur
 */
struct Localisation
{
    QString latitude;
    QString longitude;
    QString atitude;
};

/**
 * @class       Distributeur
 * @brief       Déclaration de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet ...
 */
class Distributeur
{
  private:
    QString       deviceID;          //!< identifiant du distributeur
    Localisation  position;          //!< géolocalisation du distributeur
    QVector<Bac*> bacs;              //!< les bacs du distributeur
    QString       nom;               //!< nom du distributeur
    QString       adresse;           //!< adresse du distributeur
    QString       codePostal;        //!< code postal du distributeur
    QString       ville;             //!< ville du distributeur
    QDate         dateMiseEnService; //!< date de mise en service du distributeur
    QString       description;       //!< description du distributeur
    float         hygrometrie;       //!< hygrometrie de l'interieur du distributeur
    bool          aIntervenir;       //!< permet de savoir s'il faut intervenir sur le
                                     //!< distributeur

  public:
    Distributeur();
    Distributeur(QString      deviceID,
                 Localisation position,
                 QString      nom,
                 QString      adresse,
                 QString      codePostal,
                 QString      ville,
                 QString      description,
                 QDate        dateMiseEnService);
    ~Distributeur();

    // Accesseurs
    QString      getdeviceID() const;
    Localisation getPosition() const;
    int          getAIntervenir() const;
    float        getHygrometrie() const;
    QString      getNom() const;
    QString      getAdresse() const;
    QString      getCodePostal() const;
    QString      getVille() const;
    QDate        getDateMiseService() const;
    QString      getDescription() const;
    QString      getNomProduitBac(int numeroBac) const;
    double       getProduitPrix(int numeroBac) const;
    Produit*     getProduitBac(int numeroBac) const;
    int          getNbBacs() const;

    // mutateurs
    void setdeviceID(const QString deviceID);
    void setHygrometrie(float hydrometrie);
    void setPosition(const Localisation& localisation);
    void setAIntervenir(bool aIntervenir);
    void setNom(const QString& nom);
    void setAdresse(const QString& adresse);
    void setCodePostal(const QString& codePostal);
    void setVille(const QString& ville);
    void setDateMiseEnService(const QDate& dateMiseEnService);
    void setDescription(const QString& description);
    void setPrixProduit(const int& numeroBac, const double& prix);
    void ajouterBac(const Bac& bac);
};

#endif // DISTRIBUTEUR_H
