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
    qDebug() << Q_FUNC_INFO << "dateIntervention" << this->getDateIntervention();
    QString dateFormatee = this->getDateIntervention().toString("yyyy/MM/dd");
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateFormatee;

    QString requete;
    /**
     * @todo Fabriquer la requête pour insérer une nouvelle intervention pour chaque distributeur
     * dans la table Intervention
     */
    /*
     * Exemple :
     * INSERT INTO Intervention (idOperateur, idDistributeur, dateIntervention, etat, aRemplir,
     * aDepanner) VALUES (1, 1, '2023-06-01', 'A_FAIRE', 1, 0);
     */
    intervenir(true);

    /**
     * @todo Fabriquer la requête pour insérer un nouvel approvisionnement pour chaque bac si besoin
     * et finaliser la structure de la table Approvisionnement
     */
    for(int i = 0; i < distributeurs.size(); ++i)
    {
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            if(distributeurs[i]->getBac(j)->getARemplir())
            {
            }
        }
    }
}
