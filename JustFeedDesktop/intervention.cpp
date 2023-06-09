/**
 * @file        intervention.cpp
 * @brief       Définition de la classe Intervention.
 * @details     La classe intervention \c Cette classe permet de définir une
 * intervention
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     1.1
 * @date        2023
 */

#include "intervention.h"
#include "bac.h"
#include "basededonnees.h"
#include "distributeur.h"
#include "operateur.h"

/**
 * @brief Constructeur de la classe Intervention
 */
Intervention::Intervention(QVector<Distributeur*> listeDistributeursAIntervenir) :
    baseDeDonnees(BaseDeDonnees::getInstance()), dateIntervention(QDate::currentDate()),
    distributeurs(listeDistributeursAIntervenir), aRemplir(false), aDepanner(false),
    idIntervention(ID_INTERVENTION_NON_DEFINI), idOperateur(ID_OPERATEUR_NON_DEFINI),
    idDistributeur(ID_DISTRIBUTEUR_NON_DEFINI), etat(INCONNU)
{
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateIntervention << "nb distributeurs"
             << listeDistributeursAIntervenir.size();
}

/**
 * @brief Constructeur de la classe Intervention
 */
Intervention::Intervention(int     idIntervention,
                           int     idOperateur,
                           int     idDistributeur,
                           QDate   dateIntervention,
                           bool    aRemplir,
                           bool    aDepanner,
                           QString etat) :
    baseDeDonnees(BaseDeDonnees::getInstance()),
    dateIntervention(dateIntervention), aRemplir(aRemplir), aDepanner(aDepanner),
    idIntervention(idIntervention), idOperateur(idOperateur), idDistributeur(idDistributeur),
    etat(Intervention::getEtat(etat))
{
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateIntervention << "idIntervention"
             << idIntervention << "idOperateur" << idOperateur << "idDistributeur" << idDistributeur
             << "aRemplir" << aRemplir << "aDepanner" << aDepanner << "etat" << etat;
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
 * @return QDate représente la date de l'intervention au format
 */
QDate Intervention::getDateIntervention() const
{
    return this->dateIntervention;
}

/**
 * @brief Accesseur de l'attribut distributeurAIntervenir
 * @return QVector<Distributeur*> represente les distributeurs sur lesquels il
 * faut intervenir
 */
QVector<Distributeur*> Intervention::getDistributeurs() const
{
    return this->distributeurs;
}

/**
 * @brief Retourne l'état effectuee de l'intervention
 * @return bool
 */
bool Intervention::estEffectuee() const
{
    if(etat == VALIDEE)
        return true;
    else
        return false;
}

/**
 * @brief Retourne un booléen s'il faut intervenir
 * @return bool
 */
bool Intervention::estAIntervenir() const
{
    if(etat == A_FAIRE)
        return true;
    else
        return false;
}

/**
 * @brief Modifie la dateIntervention
 * @param dateIntervention
 */
void Intervention::setDateIntervention(const QDate& dateIntervention)
{
    this->dateIntervention = dateIntervention;
}

/**
 * @brief Accesseur de l'attribut aRemplir
 * @return un bool
 */
bool Intervention::getARemplir() const
{
    return this->aRemplir;
}

/**
 * @brief Accesseur de l'attribut aDepanner
 * @return bool
 */
bool Intervention::getADepanner() const
{
    return this->aDepanner;
}

/**
 * @brief Accesseur de l'attribut idIntervention
 * @return int
 */
int Intervention::getIdIntervention() const
{
    return idIntervention;
}

/**
 * @brief Accesseur de l'attribut idOperateur
 * @return int
 */
int Intervention::getIdOperateur() const
{
    return this->idOperateur;
}

/**
 * @brief Accesseur de l'attribut idDistributeur
 * @return int
 */
int Intervention::getIdDistributeur() const
{
    return this->idDistributeur;
}

/**
 * @brief Accesseur de l'attribut etat
 * @return QString formaté pour la base de données
 */
QString Intervention::getEtat() const
{
    return Intervention::getEtat(this->etat);
}

/**
 * @brief Accesseur de l'attribut etat
 * @return QString formatée pour un affichage
 */
QString Intervention::getEtatFormate() const
{
    return Intervention::getEtatFormate(this->etat);
}

/**
 * @brief Mutateur de l'attribut aRemplir
 * @param aRemplir
 */
void Intervention::setARemplir(const bool& aRemplir)
{
    this->aRemplir = aRemplir;
}

/**
 * @brief Mutateur de l'attribut aDepanner
 * @param aDepanner
 */
void Intervention::setADepanner(const bool& aDepanner)
{
    this->aDepanner = aDepanner;
}

/**
 * @brief Mutateur de l'attribut idOperateur
 * @param idOperateur
 */
void Intervention::setIdOperateur(const int& idOperateur)
{
    this->idOperateur = idOperateur;
}

/**
 * @brief Mutateur de l'attribut idIntervention
 * @param numeroIntervention
 */
void Intervention::setIdIntervention(const int& numeroIntervention)
{
    this->idIntervention = numeroIntervention;
}

/**
 * @brief Mutateur de l'attribut idDistributeur
 * @param numeroDistributeur
 */
void Intervention::setIdDistributeur(const int& numeroDistributeur)
{
    this->idDistributeur = numeroDistributeur;
}

/**
 * @brief Mutateur de l'attribut etat
 * @param etat
 */
void Intervention::setEtat(const QString& etat)
{
    this->etat = Intervention::getEtat(etat);
}

/**
 * @brief Ajoute un distributeur sur lequel il faut intervenir
 * @param distributeur distributeur sur lequel il faut intervenir
 */
void Intervention::ajouterDistributeur(Distributeur* distributeur)
{
    this->distributeurs.push_back(distributeur);
}

/**
 * @brief Modifie l'état de l'intervention
 * @param effectuee
 */
void Intervention::effectuer(bool effectuee)
{
    if(effectuee)
        this->etat = VALIDEE;
    else
        this->etat = A_FAIRE;
}

/**
 * @brief Modifie l'état de l'intervention
 * @param aIntervenir
 */
void Intervention::intervenir(bool aIntervenir)
{
    effectuer(!aIntervenir);
}

/**
 * @brief Crée une nouvelle intervention
 */
void Intervention::creer()
{
    for(int i = 0; i < distributeurs.size(); i++)
    {
        affecterEtatIntervention(i);
        qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[i]->getNom() << "aRemplir"
                 << this->getARemplir() << "aDepanner" << this->getADepanner();
        this->idIntervention = ajouterIntervention(i);
    }
    if(this->idIntervention != ID_INTERVENTION_NON_DEFINI)
    {
        intervenir(true);
        for(int i = 0; i < distributeurs.size(); ++i)
        {
            ajouterApprovisionnement(i);
        }
    }
}

/**
 * @brief Modifie l'état de l'intervention si elle est à remplir, à depanner ou les deux
 * @param indexDistributeur
 */
void Intervention::affecterEtatIntervention(int indexDistributeur)
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
           !distributeurs[indexDistributeur]->getBac(j)->getAIntervenir())
        {
            this->setARemplir(true);
            this->setADepanner(true);
            break;
        }
        else if((distributeurs[indexDistributeur]->getBac(j)->getARemplir()) &&
                !distributeurs[indexDistributeur]->getBac(j)->getAIntervenir())
        {
            this->setARemplir(true);
            break;
        }
        else if(distributeurs[indexDistributeur]->getBac(j)->getADepanner() &&
                !distributeurs[indexDistributeur]->getBac(j)->getAIntervenir())
        {
            this->setADepanner(true);
            break;
        }
    }
}

/**
 * @brief Insére une nouvelle intervention dans la bdd
 * @param indexDistributeur
 * @return int le numéro d'intervention ou -1 en cas d'échec
 */
int Intervention::ajouterIntervention(int indexDistributeur)
{
    int     numeroIntervention = estPlanifiee(distributeurs[indexDistributeur]->getId());
    QString requete;
    if(this->getARemplir() || this->getADepanner())
    {
        if(numeroIntervention == ID_INTERVENTION_NON_DEFINI)
        {
            requete = "INSERT INTO Intervention (idOperateur, idDistributeur, dateIntervention, "
                      "etat, aRemplir, aDepanner) VALUES (" +
                      QString::number(getIdOperateur()) + ", " +
                      QString::number(distributeurs[indexDistributeur]->getId()) + ", " + "'" +
                      this->getDateIntervention().toString("yyyy-MM-dd") + "'" + ", 'A_FAIRE', " +
                      QString::number(this->getARemplir()) + ", " +
                      QString::number(this->getADepanner()) + ");";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
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
                return ID_INTERVENTION_NON_DEFINI;
        }

        if(this->getADepanner())
        {
            requete = "UPDATE Intervention SET aDepanner = 1 AND operateur = " +
                      QString::number(getIdOperateur()) +
                      " WHERE idIntervention = " + QString::number(numeroIntervention) + ";";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
            //!< @todo update l'operateur si il a changé
        }

        if(this->getARemplir())
        {
            requete = "UPDATE Intervention SET aRemplir = 1, idOperateur = " +
                      QString::number(getIdOperateur()) +
                      " WHERE idIntervention = " + QString::number(numeroIntervention) + ";";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);

            //!< @todo update l'operateur si il a changé
        }
    }

    return numeroIntervention;
}

/**
 * @brief Ajoute les approvisionnements nécessaires des bacs dans la bdd
 * @param indexDistributeur
 */
void Intervention::ajouterApprovisionnement(int indexDistributeur)
{
    QString          requete = "SELECT idBac FROM Approvisionnement";
    QVector<QString> listeDeBacPlanifie;
    baseDeDonnees->recuperer(requete, listeDeBacPlanifie);

    for(int j = 0; j < distributeurs[indexDistributeur]->getNbBacs(); j++)
    {
        if(distributeurs[indexDistributeur]->getBac(j)->getARemplir() &&
           !estBacAttribue(indexDistributeur, j))
        {
            qDebug() << Q_FUNC_INFO << "bacEstAttribue" << estBacAttribue(indexDistributeur, j);
            if(estPlanifiee(distributeurs[indexDistributeur]->getId()))
            {
                requete = "INSERT INTO Approvisionnement (idIntervention, idBac, "
                          "poidsAPrevoir, heureApprovisionnement) VALUES (" +
                          QString::number(idIntervention) + ", " +
                          QString::number(distributeurs[indexDistributeur]->getBac(j)->getIdBac()) +
                          ", " +
                          QString::number(
                            distributeurs[indexDistributeur]->getBac(j)->getQuantiteARemplir()) +
                          ", " + "'');";
                qDebug() << Q_FUNC_INFO << "requete" << requete;
                baseDeDonnees->executer(requete);
            }
        }
    }
}

/**
 * @brief Vérifie si le bac est deja attribué
 * @param idDistributeur
 * @param idBac
 * @return bool
 */
bool Intervention::estBacAttribue(int idDistributeur, int idBac)
{
    QString          requete = "SELECT idBac FROM Approvisionnement WHERE effectue = 0;";
    QVector<QString> listeDeBacPlanifie;
    baseDeDonnees->recuperer(requete, listeDeBacPlanifie);
    qDebug() << Q_FUNC_INFO << "requete" << requete;

    for(int i = 0; i < listeDeBacPlanifie.size(); i++)
    {
        if(listeDeBacPlanifie[i].toInt() ==
           distributeurs[idDistributeur]->getBac(idBac)->getIdBac())
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Vérifie si le distributeur a déja une intervention à faire ou en cours
 * @return bool l'idIntervention ou -1 sinon
 */
int Intervention::estPlanifiee(int idDistributeur)
{
    QString requete;
    requete = "SELECT idIntervention,idDistributeur FROM Intervention WHERE idDistributeur = " +
              QString::number(idDistributeur) + " AND (etat = 'A_FAIRE' OR etat = 'EN_COURS');";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    QVector<QStringList> idInterventionsBdd;
    baseDeDonnees->recuperer(requete, idInterventionsBdd);

    for(int i = 0; i < idInterventionsBdd.size(); i++)
    {
        if(idInterventionsBdd[i].at(1).toInt() == idDistributeur)
        {
            return idInterventionsBdd[i].at(0).toInt();
        }
    }
    return ID_INTERVENTION_NON_DEFINI;
}

/**
 * @brief Retourne l'état sous forme de QString
 * @param etat
 * @return QString
 */
QString Intervention::getEtat(EtatIntervention etat)
{
    if(etat >= A_FAIRE && etat < NB_ETATS)
    {
        QVector<QString> etats = { "A_FAIRE", "VALIDEE", "EN_COURS" };
        return etats[etat];
    }
    return QString();
}

/**
 * @brief Retourne l'état sous forme de EtatIntervention
 * @param etat
 * @return EtatIntervention
 */
Intervention::EtatIntervention Intervention::getEtat(const QString& etat)
{
    QVector<QString> etats = { "A_FAIRE", "VALIDEE", "EN_COURS" };
    for(int i = 0; i < etats.size(); ++i)
    {
        if(etats[i] == etat)
            return EtatIntervention(i);
    }
    return INCONNU;
}

/**
 * @brief Retourne l'état sous forme de QString
 * @param etat
 * @return QString
 */
QString Intervention::getEtatFormate(EtatIntervention etat)
{
    if(etat >= A_FAIRE && etat < NB_ETATS)
    {
        QVector<QString> etats = { "À FAIRE", "VALIDÉE", "EN COURS" };
        return etats[etat];
    }
    return QString();
}
