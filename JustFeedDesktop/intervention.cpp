/**
 * @file        intervention.cpp
 * @brief       Définition de la classe Intervention.
 * @details     La classe intervention \c Cette classe permet de définir une
 * intervention
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "intervention.h"
#include "bac.h"
#include "basededonnees.h"
#include "distributeur.h"

/**
 * @brief Constructeur de la classe Intervention
 */
Intervention::Intervention(QVector<Distributeur*> listeDistributeursAIntervenir) :
    baseDeDonnees(BaseDeDonnees::getInstance()), dateIntervention(QDate::currentDate()),
    heureIntervention(QTime::currentTime()), distributeurs(listeDistributeursAIntervenir),
    effectuee(false)
{
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateIntervention;
    qDebug() << Q_FUNC_INFO << "nb distributeurs" << listeDistributeursAIntervenir.size();
}

/**
 * @brief Destructeur de la classe Intervention
 */
Intervention::~Intervention()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Accesseur de l'attribut dateIntervention
 * @return QDate représente la date de l'intervention sur le
 * distributeur au format
 */
QDate Intervention::getDateIntervention() const
{
    return this->dateIntervention;
}

/**
 * @brief Accesseur de l'attribut heureIntervention
 * @return QTime représente l'heure de l'intervention sur le
 * distributeur
 */
QTime Intervention::getHeureIntervention() const
{
    return this->heureIntervention;
}
/**
 * @brief Accesseur de l'attribut distributeurAIntervenir
 * @return QVector<Distributeur*> represente les distributeurs surlequels il
 * faut intervenir
 */
QVector<Distributeur*> Intervention::getDistributeurs() const
{
    return this->distributeurs;
}

/**
 * @brief Accesseur de l'attribut effectuee
 * @return effectuee
 */
bool Intervention::estEffectuee() const
{
    return this->effectuee;
}

/**
 * @brief Accesseur de l'attribut AIntervenir
 * @return !effectuee
 */
bool Intervention::estAIntervenir() const
{
    return !this->effectuee;
}

/**
 * @brief Mutateur de l'attribut distributeurAIntervenir
 * @param distributeur distributeur sur lequel il faut intervenir
 */
void Intervention::ajouterDistributeur(Distributeur* distributeur)
{
    this->distributeurs.push_back(distributeur);
}

/**
 * @brief Mutateur de l'attribut dateIntervention
 * @param dateIntervention
 */
void Intervention::setDateIntervention(const QDate& dateIntervention)
{
    this->dateIntervention = dateIntervention;
}

/**
 * @brief Mutateur de l'attribut heureIntervention
 * @param heureIntervention
 */
void Intervention::setHeureIntervention(const QTime& heureIntervention)
{
    this->heureIntervention = heureIntervention;
}

/**
 * @brief Mutateur de l'attribut effectuee
 * @param effectuee
 */
void Intervention::effectuer(const bool effectuee)
{
    this->effectuee = effectuee;
}

void Intervention::intervenir(bool aIntervenir)
{
    this->effectuee = !aIntervenir;
}

/**
 * @brief méthode pour créer une intervention
 * @return void
 */
void Intervention::creer()
{
    /**
     * @todo Gérer l'opérateur à qui est affectée l'intervention
     */
    qDebug() << Q_FUNC_INFO << "dateIntervention" << this->getDateIntervention();
    QString dateFormatee = this->getDateIntervention().toString("yyyy/MM/dd");
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateFormatee;

    for(int i = 0; i < distributeurs.size(); i++)
    {
        this->setARemplir(false);
        this->setADepanner(false);
        affecterEtatIntervention(i);

        qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[i]->getNom() << "aRemplir"
                 << this->getARemplir() << "aDepanner" << this->getADepanner();
        ajouterIntervention(i);
    }
    intervenir(true);

    for(int i = 0; i < distributeurs.size(); ++i)
    {
        ajouterApprovisionnement(i);
    }
}

/**
 * @brief méthode qui affecte a l'intervention si elle est à remplir, depanner ou les deux
 * @return void
 */
void Intervention::affecterEtatIntervention(int const idDistributeur)
{
    for(int j = 0; j < distributeurs[idDistributeur]->getNbBacs(); j++)
    {
        qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[idDistributeur]->getNom()
                 << "bac" << distributeurs[idDistributeur]->getBac(j)->getNomProduit() << "aRemplir"
                 << distributeurs[idDistributeur]->getBac(j)->getARemplir() << "aDepanner"
                 << distributeurs[idDistributeur]->getBac(j)->getADepanner();
        if(distributeurs[idDistributeur]->getBac(j)->getARemplir() &&
           distributeurs[idDistributeur]->getBac(j)->getADepanner() &&
           !distributeurs[idDistributeur]->getBac(j)->getAttribuer())
        {
            this->setARemplir(true);
            this->setADepanner(true);
            break;
        }
        else if((distributeurs[idDistributeur]->getBac(j)->getARemplir()) &&
                (!distributeurs[idDistributeur]->getBac(j)->getADepanner() &&
                 !distributeurs[idDistributeur]->getBac(j)->getAttribuer()))
        {
            this->setARemplir(true);
            break;
        }
        else if(distributeurs[idDistributeur]->getBac(j)->getADepanner() &&
                (!distributeurs[idDistributeur]->getBac(j)->getARemplir() &&
                 !distributeurs[idDistributeur]->getBac(j)->getAttribuer()))
        {
            this->setADepanner(true);
            break;
        }
    }
}

/**
 * @brief méthode qui ajoute dans la bdd une intervention
 * @return void
 */
void Intervention::ajouterIntervention(const int idDistributeur)
{
    QString requete;
    if(this->getARemplir() || this->getADepanner())
    {
        if(!interventionEstPlanifie(distributeurs[idDistributeur]->getIdDistributeur()))
        {
            requete = "INSERT INTO Intervention (idOperateur, idDistributeur, dateIntervention, "
                      "etat, aRemplir, aDepanner) VALUES (1, " +
                      QString::number(distributeurs[idDistributeur]->getIdDistributeur()) + ", " +
                      "'" + this->getDateIntervention().toString("yyyy-MM-dd") + "'" +
                      ", 'A_FAIRE', " + QString::number(this->getARemplir()) + ", " +
                      QString::number(this->getADepanner()) + ");";
            qDebug() << Q_FUNC_INFO << "requete INSERT" << requete;
            // baseDeDonnees->executer(requete);
            requete = "SELECT LAST_INSERT_ID(idIntervention) FROM Intervention;";
            /**
             *@todo refaire cette requete, elle ne prend la bonne valeur
             */
            qDebug() << Q_FUNC_INFO << "requete LAST_INSERT_ID" << requete;
            QString recuperationNumeroIntervention;
            baseDeDonnees->recuperer(requete, recuperationNumeroIntervention);
            bool conversion;
            this->numeroIntervention = recuperationNumeroIntervention.toInt(&conversion);
            qDebug() << Q_FUNC_INFO << "numeroIntervention" << this->numeroIntervention;
        }
    }
}

/**
 * @brief méthode qui ajoute dans la bdd les approvisionnement des bacs
 * @return void
 */
void Intervention::ajouterApprovisionnement(const int idDistributeur)
{
    QString requete;
    for(int j = 0; j < distributeurs[idDistributeur]->getNbBacs(); j++)
    {
        if(distributeurs[idDistributeur]->getBac(j)->getARemplir() &&
           !distributeurs[idDistributeur]->getBac(j)->getAttribuer())
        {
            if(interventionEstPlanifie(distributeurs[idDistributeur]->getIdDistributeur()))
            {
                requete = "SELECT idIntervention FROM Intervention WHERE idDistributeur = " +
                          QString::number(distributeurs[idDistributeur]->getIdDistributeur()) + ";";
                QString idIntervention;
                baseDeDonnees->recuperer(requete, idIntervention);

                requete = "INSERT INTO Approvisionnement (idIntervention, idBac, "
                          "heureApprovisionnement) VALUES (" +
                          idIntervention + ", " +
                          QString::number(distributeurs[idDistributeur]->getBac(j)->getIdBac()) +
                          ", " + "'" + this->getHeureIntervention().toString("hh:mm:ss") + "'" +
                          ");";
                // baseDeDonnees->executer(requete);
                distributeurs[idDistributeur]->getBac(j)->setAttribuer(true);
                qDebug() << Q_FUNC_INFO << "requete approvisonnement" << requete;
            }
            else
            {
                requete = "INSERT INTO Approvisionnement (idIntervention, idBac, "
                          "heureApprovisionnement) VALUES (" +
                          QString::number(this->numeroIntervention) + ", " +
                          QString::number(distributeurs[idDistributeur]->getBac(j)->getIdBac()) +
                          ", " + "'" + this->getHeureIntervention().toString("hh:mm:ss") + "'" +
                          ");";
                // baseDeDonnees->executer(requete);
                distributeurs[idDistributeur]->getBac(j)->setAttribuer(true);
                qDebug() << Q_FUNC_INFO << "requete approvisonnement" << requete;
            }
        }
    }
}

/**
 * @brief méthode qui vérifie si le distributeur à déja une intervention en cour sur celui-ci
 * @return void
 */
bool Intervention::interventionEstPlanifie(const int idDistributeur)
{
    QString requete;
    requete = "SELECT idDistributeur FROM Intervention";
    QVector<QString> interventionBdd;
    baseDeDonnees->recuperer(requete, interventionBdd);
    bool conversion;
    for(int i = 0; i < interventionBdd.size(); i++)
    {
        if(interventionBdd[i].toInt(&conversion) == idDistributeur)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Accesseur de l'attribut aRemplir
 * @return un bool
 */
bool Intervention::getARemplir() const
{
    return this->remplir;
}

/**
 * @brief Accesseur de l'attribut aDepanner
 * @return bool
 */
bool Intervention::getADepanner() const
{
    return this->depanner;
}

/**
 * @brief Accesseur de l'attribut numeroIntervention
 * @return int
 */
int Intervention::getNumeroIntervention() const
{
    return numeroIntervention;
}

/**
 * @brief Mutateur de l'attribut aRemplir
 * @param aRemplir
 */
void Intervention::setARemplir(const bool& aRemplir)
{
    this->remplir = aRemplir;
}

/**
 * @brief Mutateur de l'attribut aDepanner
 * @param aDepanner
 */
void Intervention::setADepanner(const bool& aDepanner)
{
    this->depanner = aDepanner;
}

/**
 * @brief Mutateur de l'attribut numeroIntervention
 * @param numeroIntervention
 */
void Intervention::setNumeroIntervention(const int numeroIntervention)
{
    this->numeroIntervention = numeroIntervention;
}
