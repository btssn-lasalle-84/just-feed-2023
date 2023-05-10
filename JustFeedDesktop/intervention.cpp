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

    QString requete;
    for(int i = 0; i < distributeurs.size(); i++)
    {
        this->setARemplir(false);
        this->setADepanner(false);
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[i]->getNom() << "bac"
                     << distributeurs[i]->getBac(j)->getNomProduit() << "aRemplir"
                     << distributeurs[i]->getBac(j)->getARemplir() << "aDepanner"
                     << distributeurs[i]->getBac(j)->getADepanner();
            if(distributeurs[i]->getBac(j)->getARemplir() &&
               distributeurs[i]->getBac(j)->getADepanner())
            {
                this->setARemplir(true);
                this->setADepanner(true);
                break;
            }
            else if((distributeurs[i]->getBac(j)->getARemplir()) &&
                    (!distributeurs[i]->getBac(j)->getARemplir()))
            {
                this->setARemplir(true);
                break;
            }
            else if(distributeurs[i]->getBac(j)->getADepanner() &&
                    (!distributeurs[i]->getBac(j)->getADepanner()))
            {
                this->setADepanner(true);
                break;
            }
        }
        /**
         * @fixme Corriger le problème de détection d'une intervention pour un distributeur
         */
        qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[i]->getNom() << "aRemplir"
                 << this->getARemplir() << "aDepanner" << this->getADepanner();
        if(this->getARemplir() || this->getADepanner())
        {
            requete =
              "INSERT INTO Intervention (idOperateur, idDistributeur, dateIntervention, etat, "
              "aRemplir, aDepanner) VALUES (1, " +
              QString::number(distributeurs[i]->getIdDistributeur()) + ", " +
              this->getDateIntervention().toString("yyyy-MM-dd") + ", 'A_FAIRE', " +
              QString::number(this->getARemplir()) + ", " + QString::number(this->getADepanner()) +
              ");";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            // baseDeDonnees->executer(requete);
            /**
             * @todo Récupérer l'id de l'intervention avec SELECT LAST_INSERT_ID() et ajouter un
             * attribut pour cela
             */
        }
    }

    intervenir(true);

    /**
     * @todo Fabriquer la requête pour insérer un nouvel approvisionnement pour chaque bac si
     * besoin et finaliser la structure de la table Approvisionnement
     * @see Il faut l'id de l'intervention créée précédemment
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

bool Intervention::getARemplir() const
{
    return this->remplir;
}

bool Intervention::getADepanner() const
{
    return this->depanner;
}

void Intervention::setARemplir(const bool& aRemplir)
{
    this->remplir = aRemplir;
}

void Intervention::setADepanner(const bool& aDepanner)
{
    this->depanner = aDepanner;
}
