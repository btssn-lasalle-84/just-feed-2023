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
    id(ID_DISTRIBUTEUR_NON_DEFINI), deviceID(""), bacs(), nom(""), adresse(""), codePostal(""), ville(""),
    description(""), dateMiseEnService(QDate::currentDate()), position{ "", "", "0" },
    aIntervenir(false)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur d'initialisation de la classe Distributeur
 */
Distributeur::Distributeur(int          id,
                           QString      deviceID,
                           QString      nom,
                           QString      adresse,
                           QString      codePostal,
                           QString      ville,
                           QString      description,
                           QDate        dateMiseEnService,
                           Localisation position) :
    id(id),
    deviceID(deviceID), bacs(), nom(nom), adresse(adresse), codePostal(codePostal), ville(ville),
    description(description), dateMiseEnService(dateMiseEnService), position(position),
    aIntervenir(false)
{
    qDebug() << Q_FUNC_INFO << "deviceID" << deviceID << "nom" << nom << "adresse"
             << "codePostal" << codePostal << "ville" << ville << "dateMiseEnService"
             << "description" << description << dateMiseEnService << "latitude" << position.latitude
             << "longitude" << position.longitude << "aIntervenir" << aIntervenir;
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
 * @brief Accesseur de l'attribut id
 * @return un QString qui represente l'id du distributeur
 */
int Distributeur::getIdDistributeur() const
{
    return this->id;
}

/**
 * @brief Accesseur de l'attribut identifiant
 * @return un QString qui represente l'identifiant du distributeur
 */
QString Distributeur::getDeviceID() const
{
    return this->deviceID;
}

/**
 * @brief Accesseur de l'attribut hygrometrie
 * @return un entier qui represente la mesure de la quantité de vapeur d'eau
 * contenue de l'air humide du distributeur
 * @param numeroBac
 */
int Distributeur::getHygrometrieBac(int numeroBac) const
{
    return bacs[numeroBac]->getHygrometrie();
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
 * @return bool
 */
bool Distributeur::getAIntervenir() const
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
 * @brief Accesseur pour récupérer un bac
 * @return Bac
 */
Bac* Distributeur::getBac(int numeroBac) const
{
    if(numeroBac >= 0 && numeroBac < bacs.size())
    {
        return bacs[numeroBac];
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
 * @brief Mutateur de l'attribut id
 * @param deviceID id du distributeur
 */
void Distributeur::setIdDistributeur(const int id)
{
    this->id = id;
}

/**
 * @brief Mutateur de l'attribut identifiant
 * @param deviceID identifiant du distributeur
 */
void Distributeur::setDeviceID(const QString deviceID)
{
    this->deviceID = deviceID;
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
 * @param description
 */
void Distributeur::setDescription(const QString& description)
{
    this->description = description;
}

/**
 * @brief Mutateur de l'attribut produit
 * @param numeroBac
 * @param prix
 */
void Distributeur::setPrixProduit(const int& numeroBac, const double& prix)
{
    if(numeroBac >= 0 && numeroBac < bacs.size())
        this->bacs[numeroBac]->setPrixProduit(prix);
}

/**
 * @brief Mutateur de l'attribut AIntervenir
 * @param aIntervenir
 */
void Distributeur::setAIntervenir(bool aIntervenir)
{
    this->aIntervenir = aIntervenir;
}

/**
 * @brief Ajoute un bac dans le distributeur
 * @param bac
 */
void Distributeur::ajouterBac(const Bac& bac)
{
    bacs.push_back(new Bac(bac));
}

/**
 * @brief Supprime un bac dans le distributeur
 * @param numeroBacASupprimer
 */
void Distributeur::supprimerBac(const int numeroBacASupprimer)
{
    if(numeroBacASupprimer >= 0 && numeroBacASupprimer < bacs.size())
    {
        qDebug() << Q_FUNC_INFO << "numeroBacASupprimer" << numeroBacASupprimer;
        delete bacs[numeroBacASupprimer];
        bacs.remove(numeroBacASupprimer);
        qDebug() << Q_FUNC_INFO << "NbBacs" << bacs.size();
    }
}
