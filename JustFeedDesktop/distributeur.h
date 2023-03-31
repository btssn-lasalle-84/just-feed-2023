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

/**
 * @struct Localisation
 * @brief Pour localiser un distributeur
 */
struct Localisation
{
    QString latitude;
    QString longitude;
};

/**
 * @class       Distributeur
 * @brief       Déclaration de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet ...
 */
class Distributeur
{
  private:
    QString      deviceID; //!< identifiant du distributeur
    Localisation position;    //!< géolocalisation du distributeur
    QVector<Bac*> bacs;       //!< les bacs du distributeur
    QString nom; //!< nom du distributeur
    QString adresse; //!< adresse du distributeur
    unsigned int codePostal; //!< code postal du distributeur
    QString ville; //!< ville du distributeur
    QDate dateMiseEnService; //!< date de mise en service du distributeur
    QString description; //!< description du distributeur
    int          hydrometrie; //!< hydrométrie de l'interieur du distributeur
    bool         aIntervenir; //!< permet de savoir s'il faut intervenir sur le
                              //!< distributeur

  public:
    Distributeur();
    Distributeur(QString deviceID, Localisation position, QString nom, QString adresse, unsigned int codePostal, QString ville, QString description);
    ~Distributeur();

    // Accesseurs
    QString      getdeviceID() const;
    Localisation getPosition() const;
    int          getAIntervenir() const;
    int          getHydrometrie() const;
    QString getNom() const;
    QString getAdresse() const;
    unsigned int getCodePostal() const;
    QString getVille() const;
    QDate getDateMiseService() const;
    QString getDescription() const;

    // mutateurs
    void setdeviceID(const QString deviceID);
    void setHydrometrie(int hydrometrie);
    void setPosition(const Localisation& localisation);
    void setAIntervenir(bool aIntervenir);
    void ajouterBac(const Bac& bac);
    void setNom(const QString& nom);
    void setAdresse(const QString& adresse);
    void setCodePostal(const unsigned int& codePostal) ;
    void setVille(const QString& ville);
    void setDateMiseEnService(const QDate& dateMiseEnService);
    void setDescription(const QString& description);
};

#endif // DISTRIBUTEUR_H