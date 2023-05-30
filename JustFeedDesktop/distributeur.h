/**
 * @file        distributeur.h
 * @brief       Déclaration de la classe Distributeur.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @author      Rouanet Nicolas
 * @version     0.2
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
  public:
    /**
     * @enum TableDistributeur
     * @brief Définit les champs de la table Distributeur
     *
     */
    enum TableDistributeur
    {
        ID                   = 0,
        ID_SERVEUR_TTN       = 1,
        NOM                  = 2,
        DESCRIPTION          = 3,
        ADRESSE              = 4,
        VILLE                = 5,
        CODE_POSTAL          = 6,
        DATE_MISE_EN_SERVICE = 7,
        LONGITUDE            = 8,
        LATITUDE             = 9,
        DEVICE_ID            = 10,
        NB_BACS              = 11,
    };

  private:
    int           id;                //!< identifiant du distributeur
    QString       deviceID;          //!< identifiant TTN du distributeur
    QVector<Bac*> bacs;              //!< les bacs du distributeur
    QString       nom;               //!< nom du distributeur
    QString       adresse;           //!< adresse du distributeur
    QString       codePostal;        //!< code postal du distributeur
    QString       ville;             //!< ville du distributeur
    QString       description;       //!< description du distributeur
    QDate         dateMiseEnService; //!< date de mise en service du distributeur
    Localisation  position;          //!< géolocalisation du distributeur
    int           hygrometrie;       //!< hygrometrie de l'interieur du distributeur
    bool          aIntervenir;       //!< pour savoir s'il faut intervenir sur le
                                     //!< distributeur

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
    Distributeur(const QStringList& distributeur);
    ~Distributeur();

    // Accesseurs
    int          getId() const;
    QString      getDeviceID() const;
    QString      getNom() const;
    QString      getAdresse() const;
    QString      getCodePostal() const;
    QString      getVille() const;
    QString      getDescription() const;
    QDate        getDateMiseService() const;
    Localisation getPosition() const;
    int          getHygrometrie() const;
    bool         getAIntervenir() const;
    Bac*         getBac(int numeroBac) const;
    int          getNbBacs() const;
    double       getPourcentageBac(int numeroBac) const;
    double       getPoidsBac(int numeroBac) const;
    double       getPoidsTotalBac(int numeroBac) const;
    int          getHygrometrieBac(int numeroBac) const;

    // mutateurs
    void setId(int id);
    void setDeviceID(const QString deviceID);
    void setNom(const QString& nom);
    void setAdresse(const QString& adresse);
    void setCodePostal(const QString& codePostal);
    void setVille(const QString& ville);
    void setDescription(const QString& description);
    void setDateMiseEnService(const QDate& dateMiseEnService);
    void setPosition(const Localisation& localisation);
    void setHygrometrie(int hygrometrie);
    void setAIntervenir(bool aIntervenir);
    void setPrixProduit(const int& numeroBac, const double& prix);
    void ajouterBac(const Bac& bac);
    void supprimerBac(const int indiceBacASupprimer);
};

#endif // DISTRIBUTEUR_H
