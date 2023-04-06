/**
 * @file        distributeur.cpp
 * @brief       Définition de la classe Distributeur.
 * @details     La classe Distributeur \c Cette classe permet définir un
 * distributeur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#include "distributeur.h"
#include "bac.h"
#include "produit.h"
#include <QDebug>

/**
 * @brief Constructeur par défaut de la classe Distributeur
 */
Distributeur::Distributeur() :
    deviceID(""), position(), bacs(), nom(""), adresse(""), codePostal(""), ville(""),
    dateMiseEnService(QDate::currentDate()), description(""), hygrometrie(0), aIntervenir(false)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur d'initialisation de la classe Distributeur
 */
Distributeur::Distributeur(QString      deviceID,
                           Localisation position,
                           QString      nom,
                           QString      adresse,
                           QString      codePostal,
                           QString      ville,
                           QString      description,
                           QDate        dateMiseEnService) :
    deviceID(deviceID),
    position(position), bacs(), nom(nom), adresse(adresse), codePostal(codePostal), ville(ville),
    dateMiseEnService(dateMiseEnService), description(description), hygrometrie(0),
    aIntervenir(false)
{
    qDebug() << Q_FUNC_INFO << "deviceID" << deviceID << "latitude" << position.latitude
             << "longitude" << position.longitude << "nom" << nom << "adresse"
             << "codePostal" << codePostal << "ville" << ville << "dateMiseEnService"
             << dateMiseEnService << "description" << description << "hydrometrie" << hygrometrie
             << "aIntervenir" << aIntervenir;
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
 * @brief Accesseur de l'attribut hygrometrie
 * @return un entier qui represente la mesure de la quantité de vapeur d'eau contenue de l'air
 * humide du distributeur
 */
float Distributeur::getHygrometrie() const
{
    return this->hygrometrie;
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
 * @return QString le code postal du distributeur
 */
QString Distributeur::getCodePostal() const
{
    return this->codePostal;
}

/**
 * @brief Accesseur de l'attribut ville
 * @return QString la ville où est implanté le distributeur
 */
QString Distributeur::getVille() const
{
    return this->ville;
}

/**
 * @brief Accesseur de l'attribut dateMiseEnService
 * @return QDate la date de mise en service du distributeur
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
 * @brief Accesseur pour récupérer le nom du produit dans le bac voulu
 * @return QString  qui permet de connaitre le nom du produit
 */
QString Distributeur::getNomProduitBac(int numeroBac) const
{
    if(numeroBac >= 0 && numeroBac < bacs.size())
    {
        return bacs[numeroBac]->getNomProduit();
    }
    return QString();
}

/**
 * @brief Accesseur pour récupérer le prix du produit dans le bac voulu
 * @return double qui permet de connaitre le prix du produit
 */
double Distributeur::getProduitPrix(int numeroBac) const
{
    if(numeroBac >= 0 && numeroBac < bacs.size())
    {
        return bacs[numeroBac]->getPrixProduit();
    }
    return 0.;
}

/**
 * @brief Accesseur pour récupérer le produit dans le bac voulu
 * @return Produit qui permet de connaitre le produit
 */
Produit* Distributeur::getProduitBac(int numeroBac) const
{
    if(numeroBac >= 0 && numeroBac < bacs.size())
    {
        return bacs[numeroBac]->getProduit();
    }
    return nullptr;
}

/**
 * @brief Accesseur pour récupérer le produit dans le bac voulu
 * @return Produit qui permet de connaitre le produit
 */
int Distributeur::getNbBacs() const
{
    return bacs.size();
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
 * @brief Mutateur de l'attribut Hygrometrie
 * @param Hygrometrie l'Hygrometrie, mesure de la quantité de vapeur d'eau contenue de l'air du
 * distributeur
 */
void Distributeur::setHygrometrie(float Hygrometrie)
{
    this->hygrometrie = Hygrometrie;
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
 * @param aIntervenir un booleen qui détermine l'état du
 * distributeur
 */
void Distributeur::setAIntervenir(bool aIntervenir)
{
    this->aIntervenir = aIntervenir;
}

/**
 * @brief Mutateur de l'attribut nom
 * @param nom un QString qui détermine le nom du
 * distributeur
 */
void Distributeur::setNom(const QString& nom)
{
    this->nom = nom;
}

/**
 * @brief Mutateur de l'attribut adresse
 * @param adresse un QString qui détermine l'e nom'adresse du
 * distributeur
 */
void Distributeur::setAdresse(const QString& adresse)
{
    this->adresse = adresse;
}

/**
 * @brief Mutateur de l'attribut codePostal
 * @param codePostal QString
 * distributeur
 */
void Distributeur::setCodePostal(const QString& codePostal)
{
    this->codePostal = codePostal;
}

/**
 * @brief Mutateur de l'attribut ville
 * @param ville un QString qui détermine la ville du
 * distributeur
 */
void Distributeur::setVille(const QString& ville)
{
    this->ville = ville;
}

/**
 * @brief Mutateur de l'attribut dateMiseEnService
 * @param dateMiseEnService un QTime qui détermine la date de mise en place du
 * distributeur
 */
void Distributeur::setDateMiseEnService(const QDate& dateMiseEnService)
{
    this->dateMiseEnService = dateMiseEnService;
}

/**
 * @brief Mutateur de l'attribut description
 * @param description un QString qui détermine la description du
 * distributeur
 */
void Distributeur::setDescription(const QString& description)
{
    this->description = description;
}

void Distributeur::setPrixProduit(const int& numeroBac, const double& prix)
{
    if(numeroBac >= 0 && numeroBac < bacs.size())
        this->bacs[numeroBac]->setPrixProduit(prix);
}

/**
 * @brief Ajoute un bac dans le distributeur
 * @param bac
 */
void Distributeur::ajouterBac(const Bac& bac)
{
    bacs.push_back(new Bac(bac));
}
