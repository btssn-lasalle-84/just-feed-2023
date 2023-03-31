/**
 * @file        distributeur.cpp
 * @brief       Définition de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet définir un
 * distributeur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#include "bac.h"
#include "distributeur.h"
#include "produit.h"
#include <QDebug>

/**
 * @brief Constructeur par défaut de la classe Distributeur
 */
Distributeur::Distributeur() :
    deviceID(""), position(), hydrometrie(0), aIntervenir(false), bacs(), nom(""), adresse(""), codePostal(0),
    ville(""), dateMiseEnService(), description("")
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur d'initialisation de la classe Distributeur
 */
Distributeur::Distributeur(QString deviceID, Localisation position, QString nom, QString adresse, unsigned int codePostal, QString ville, QString description) :
    deviceID(deviceID), position(position), nom(nom), adresse(adresse), codePostal(codePostal), ville(ville), description(description), hydrometrie(0),
    aIntervenir(false), bacs(), dateMiseEnService(QDate::currentDate())
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Destructeur de la classe Distributeur
 */
Distributeur::~Distributeur()
{
    for(int i = 0; i < bacs.size(); ++i)
    {
        delete bacs[i];
    }
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Accesseur de l'attribut identifiant
 * @return un QString qui represente l'identifiant du distributeur
 */
QString Distributeur::getdeviceID() const
{
    return this->deviceID;
}

/**
 * @brief Accesseur de l'attribut hydrometrie
 * @return un entier qui represente le degré d'humidité dans le
 * distributeur
 */
int Distributeur::getHydrometrie() const
{
    return this->hydrometrie;
}

/**
 * @brief Accesseur de l'attribut position
 * @return une Localisaton qui represente la géolocalisation du distributeur
 */
Localisation Distributeur::getPosition() const
{
    return this->position;
}

/**
 * @brief Accesseur de l'attribut AIntervenir
 * @return un bool qui permet de savoir s'il faut intervenir sur le
 */
int Distributeur::getAIntervenir() const
{
    return this->aIntervenir;
}

/**
 * @brief Accesseur de l'attribut nom
 * @return un QString qui permet de connaitre le nom du distributeur
 */
QString Distributeur::getNom() const
{
    return this->nom;
}

/**
 * @brief Accesseur de l'attribut adresse
 * @return un QString qui permet de connaitre l'adresse du distributeur
 */
QString Distributeur::getAdresse() const
{
    return this->adresse;
}

/**
 * @brief Accesseur de l'attribut codePostal
 * @return un unsigned int qui permet de connaitre le code postal du distributeur
 */
unsigned int Distributeur::getCodePostal() const
{
    return this->codePostal;
}

/**
 * @brief Accesseur de l'attribut ville
 * @return un QString qui permet de connaitre la ville du distributeur
 */
QString Distributeur::getVille() const
{
    return this->ville;
}

/**
 * @brief Accesseur de l'attribut dateMiseEnService
 * @return QDate int qui permet de connaitre la date de mise en service du distributeur
 */
QDate Distributeur::getDateMiseService() const
{
    return this->dateMiseEnService;
}

/**
 * @brief Accesseur de l'attribut description
 * @return QString  qui permet de connaitre la description du distributeur
 */
QString Distributeur::getDescription() const
{
    return this->description;
}


/**
 * @brief Mutateur de l'attribut identifiant
 * @param identifiant du distributeur
 */
void Distributeur::setdeviceID(const QString deviceID)
{
    this->deviceID = deviceID;
}

/**
 * @brief Mutateur de l'attribut hydrométrie
 * @param hydrometrie l'hydrometrie du distributeur
 */
void Distributeur::setHydrometrie(int hydrometrie)
{
    this->hydrometrie = hydrometrie;
}

/**
 * @brief Mutateur de l'attribut localisation
 * @param localisation la localisation du distributeur
 */
void Distributeur::setPosition(const Localisation& localisation)
{
    this->position = localisation;
}

/**
 * @brief Mutateur de l'attribut aIntervenir
 * @param aIntervenir un booleen qui détérmine l'état du
 * distributeur
 */
void Distributeur::setAIntervenir(bool aIntervenir)
{
    this->aIntervenir = aIntervenir;
}

/**
 * @brief Mutateur de l'attribut nom
 * @param nom un QString qui détérmine le nom du
 * distributeur
 */
void Distributeur::setNom(const QString& nom)
{
    this->nom = nom;
}

/**
 * @brief Mutateur de l'attribut adresse
 * @param adresse un QString qui détérmine l'e nom'adresse du
 * distributeur
 */
void Distributeur::setAdresse(const QString& adresse)
{
    this->adresse = adresse;
}

/**
 * @brief Mutateur de l'attribut codePostal
 * @param codePostal un unsigned int qui détérmine l'edresse du
 * distributeur
 */
void Distributeur::setCodePostal(const unsigned int& codePostal)
{
    this->codePostal = codePostal;
}

/**
 * @brief Mutateur de l'attribut ville
 * @param ville un QString qui détérmine la ville du
 * distributeur
 */
void Distributeur::setVille(const QString& ville)
{
    this->ville = ville;
}

/**
 * @brief Mutateur de l'attribut dateMiseEnService
 * @param dateMiseEnService un QTime qui détérmine la date de mise en place du
 * distributeur
 */
void Distributeur::setDateMiseEnService(const QDate& dateMiseEnService)
{
    this->dateMiseEnService = dateMiseEnService;
}

/**
 * @brief Mutateur de l'attribut description
 * @param description un QString qui détérmine la description du
 * distributeur
 */
void Distributeur::setDescription(const QString& description)
{
    this->description = description;
}

/**
 * @brief Ajoute un bac dans le distributeur
 * @param bac
 */
void Distributeur::ajouterBac(const Bac& bac)
{
    bacs.push_back(new Bac(bac));
}
