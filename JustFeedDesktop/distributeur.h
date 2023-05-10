/**
 * @file        distributeur.h
 * @brief       Déclaration de la classe Distributeur.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

#include <QDate>
#include <QVector>

/**
 * @def ID_DISTRIBUTEUR_NON_DEFINI
 * @brief Définit la valeur d'un id non défini
 */
#define ID_DISTRIBUTEUR_NON_DEFINI -1

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
    QString altitude;
};

/**
 * @class       Distributeur
 * @brief       Déclaration de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet ...
 */
class Distributeur
{
  private:
    int           id;
    QString       deviceID;          //!< identifiant du distributeur
    QVector<Bac*> bacs;              //!< les bacs du distributeur
    QString       nom;               //!< nom du distributeur
    QString       adresse;           //!< adresse du distributeur
    QString       codePostal;        //!< code postal du distributeur
    QString       ville;             //!< ville du distributeur
    QString       description;       //!< description du distributeur
    QDate         dateMiseEnService; //!< date de mise en service du distributeur
    Localisation  position;          //!< géolocalisation du distributeur
    bool          aIntervenir;

  public:
    Distributeur();
    Distributeur(int          id,
                 QString      deviceID,
                 QString      nom,
                 QString      adresse,
                 QString      codePostal,
                 QString      ville,
                 QString      description,
                 QDate        dateMiseEnService,
                 Localisation position);
    ~Distributeur();

    // Accesseurs
    int          getIdDistributeur() const;
    QString      getDeviceID() const;
    Localisation getPosition() const;
    bool         getAIntervenir() const;
    int          getHygrometrieBac(int numeroBac) const;
    QString      getNom() const;
    QString      getAdresse() const;
    QString      getCodePostal() const;
    QString      getVille() const;
    QDate        getDateMiseService() const;
    QString      getDescription() const;
    Bac*         getBac(int numeroBac) const;
    int          getNbBacs() const;


    // mutateurs
    void setIdDistributeur(int id);
    void setAIntervenir(bool aIntervenir);
    void setDeviceID(const QString deviceID);
    void setPosition(const Localisation& localisation);
    void setNom(const QString& nom);
    void setAdresse(const QString& adresse);
    void setCodePostal(const QString& codePostal);
    void setVille(const QString& ville);
    void setDateMiseEnService(const QDate& dateMiseEnService);
    void setDescription(const QString& description);
    void setPrixProduit(const int& numeroBac, const double& prix);
    void ajouterBac(const Bac& bac);
    void supprimerBac(const int numeroBacASupprimer);
};

#endif // DISTRIBUTEUR_H
