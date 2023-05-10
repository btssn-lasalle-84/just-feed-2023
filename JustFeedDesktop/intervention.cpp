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
    distributeurs(listeDistributeursAIntervenir), effectuee(false)
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
     * @todo Gérer l'opérateur à qui est affectée l'intervention (une liste déroulante d'opérateurs
     * dans planificationintervention ?)
     */
    qDebug() << Q_FUNC_INFO << "dateIntervention" << this->getDateIntervention();
    QString dateFormatee = this->getDateIntervention().toString("yyyy/MM/dd");
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateFormatee;

    for(int i = 0; i < distributeurs.size(); i++)
    {
        affecterEtatIntervention(i);
        qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[i]->getNom() << "aRemplir"
                 << this->getARemplir() << "aDepanner" << this->getADepanner();
        this->idIntervention = ajouterIntervention(i);
    }
    if(this->idIntervention != -1)
    {
        intervenir(true);
        for(int i = 0; i < distributeurs.size(); ++i)
        {
            ajouterApprovisionnement(i);
        }
    }
}

/**
 * @brief méthode qui affecte a l'intervention si elle est à remplir, depanner ou les deux
 * @return void
 */
void Intervention::affecterEtatIntervention(int const indexDistributeur)
{
    this->setARemplir(false);
    this->setADepanner(false);
    for(int j = 0; j < distributeurs[indexDistributeur]->getNbBacs(); j++)
    {
        qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[indexDistributeur]->getNom()
                 << "bac" << distributeurs[indexDistributeur]->getBac(j)->getNomProduit()
                 << "aRemplir" << distributeurs[indexDistributeur]->getBac(j)->getARemplir()
                 << "aDepanner" << distributeurs[indexDistributeur]->getBac(j)->getADepanner();
        if(distributeurs[indexDistributeur]->getBac(j)->getARemplir() &&
           distributeurs[indexDistributeur]->getBac(j)->getADepanner() &&
           !distributeurs[indexDistributeur]->getBac(j)->getAttribuer())
        {
            this->setARemplir(true);
            this->setADepanner(true);
            break;
        }
        else if((distributeurs[indexDistributeur]->getBac(j)->getARemplir()) &&
                !distributeurs[indexDistributeur]->getBac(j)->getAttribuer())
        {
            this->setARemplir(true);
            break;
        }
        else if(distributeurs[indexDistributeur]->getBac(j)->getADepanner() &&
                !distributeurs[indexDistributeur]->getBac(j)->getAttribuer())
        {
            this->setADepanner(true);
            break;
        }
    }
}

/**
 * @brief méthode qui ajoute dans la bdd une intervention
 * @return int
 */
int Intervention::ajouterIntervention(const int indexDistributeur)
{
    qDebug() << Q_FUNC_INFO << "indexDistributeur" << indexDistributeur;
    QString requete;
    int     numeroIntervention = -1;
    if(this->getARemplir() || this->getADepanner())
    {
        if(!estPlanifiee(distributeurs[indexDistributeur]->getIdDistributeur()))
        {
            requete = "INSERT INTO Intervention (idOperateur, idDistributeur, dateIntervention, "
                      "etat, aRemplir, aDepanner) VALUES (1, " +
                      QString::number(distributeurs[indexDistributeur]->getIdDistributeur()) +
                      ", " + "'" + this->getDateIntervention().toString("yyyy-MM-dd") + "'" +
                      ", 'A_FAIRE', " + QString::number(this->getARemplir()) + ", " +
                      QString::number(this->getADepanner()) + ");";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
            /*
             * @fixme MAX() ce n'est pas pareil que LAST_INSERT_ID()
             */
            requete = "SELECT MAX(idIntervention) FROM Intervention;";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            QString idIntervention;
            baseDeDonnees->recuperer(requete, idIntervention);
            qDebug() << Q_FUNC_INFO << "idIntervention" << idIntervention;
            bool conversion;
            numeroIntervention = idIntervention.toInt(&conversion);
            if(conversion)
                return numeroIntervention;
            else
                return -1;
        }

        if(estPlanifiee(distributeurs[indexDistributeur]->getIdDistributeur()) &&
           this->getADepanner())
        {
            requete = "UPDATE Intervention SET aDepanner = 1 WHERE idDistributeur = " +
                      QString::number(distributeurs[indexDistributeur]->getIdDistributeur()) + ";";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
        }

        if(estPlanifiee(distributeurs[indexDistributeur]->getIdDistributeur()) &&
           this->getARemplir())
        {
            requete = "UPDATE Intervention SET aRemplir = 1 WHERE idDistributeur = " +
                      QString::number(distributeurs[indexDistributeur]->getIdDistributeur()) + ";";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
        }
    }
    return numeroIntervention;
}

/**
 * @brief méthode qui ajoute dans la bdd les approvisionnement des bacs
 * @return void
 */
void Intervention::ajouterApprovisionnement(const int indexDistributeur)
{
    QString requete;
    for(int j = 0; j < distributeurs[indexDistributeur]->getNbBacs(); j++)
    {
        if(distributeurs[indexDistributeur]->getBac(j)->getARemplir() &&
           !distributeurs[indexDistributeur]->getBac(j)->getAttribuer())
        {
            if(estPlanifiee(distributeurs[indexDistributeur]->getIdDistributeur()))
            {
                /**
                 * @todo On laisse tomber le poids à prévoir ?
                 */
                requete = "INSERT INTO Approvisionnement (idIntervention, idBac, "
                          "heureApprovisionnement) VALUES (" +
                          QString::number(idIntervention) + ", " +
                          QString::number(distributeurs[indexDistributeur]->getBac(j)->getIdBac()) +
                          ", " + "'');";
                qDebug() << Q_FUNC_INFO << "requete" << requete;
                baseDeDonnees->executer(requete);
                distributeurs[indexDistributeur]->getBac(j)->setAttribuer(true);
            }
        }
    }
}

/**
 * @brief Méthode qui vérifie si le distributeur a déja une intervention à faire ou en cours
 * @return bool
 */
bool Intervention::estPlanifiee(const int idDistributeur)
{
    qDebug() << Q_FUNC_INFO << "idDistributeur" << idDistributeur;
    QString requete;
    requete = "SELECT COUNT(*) FROM Intervention WHERE idDistributeur = " +
              QString::number(idDistributeur) + " AND (etat = 'A_FAIRE' OR etat = 'EN_COURS');";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    QString nbInterventions;
    baseDeDonnees->recuperer(requete, nbInterventions);
    qDebug() << Q_FUNC_INFO << "nbInterventions" << nbInterventions;
    return (nbInterventions.size() > 0);
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
int Intervention::getIdIntervention() const
{
    return idIntervention;
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
void Intervention::setIdIntervention(const int numeroIntervention)
{
    this->idIntervention = numeroIntervention;
}
