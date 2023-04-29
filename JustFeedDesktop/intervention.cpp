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
#include "distributeur.h"
#include "ihmjustfeed.h"

/**
 * @brief Constructeur de la classe Intervention
 */
Intervention::Intervention(QVector<Distributeur*> listeDistributeursAIntervenir,
                           IHMJustFeed*           parent) :
    QDialog(parent),
    ihmJustFeed(parent), dateIntervention(QDate::currentDate()),
    distributeurs(listeDistributeursAIntervenir), effectuee(false)
{
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateIntervention;
    qDebug() << Q_FUNC_INFO << "nb distributeurs" << listeDistributeursAIntervenir.size();
    initialiserBoiteDeDialogue();
}

/**
 * @brief Destructeur de la classe Intervention
 */
Intervention::~Intervention()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Méthode qui initialise la boîte de dialogue
 */
void Intervention::initialiserBoiteDeDialogue()
{
    instancierWidgets();
    initialiserWidgets();
    positionnerWidgets();
    initialiserEvenements();
    setWindowTitle(TITRE_INTERVENTION);
}

/**
 * @brief Méthode qui instancie les widgets de la boîte de dialogue
 */
void Intervention::instancierWidgets()
{
    for(int i = 0; i < distributeurs.size(); i++)
    {
        nomDistributeurs.push_back(new QLabel(this));
        for(int j = 0; j < distributeurs[i]->getNbBacs() ; j++)
        {
            labelsBac.push_back(new QLabel(this));
            labelsProduit.push_back(new QLabel(this));
            labelsPourcentage.push_back(new QLabel(this));
        }
        labelsDesBacs.push_back(labelsBac);
        labelsDesProduits.push_back(labelsProduit);
        labelsDesPourcentage.push_back(labelsPourcentage);
    }
}

/**
 * @brief Méthode qui initialise les widgets de la boîte de dialogue
 */
void Intervention::initialiserWidgets()
{
    for(int i = 0; i < distributeurs.size(); i++)
    {
        nomDistributeurs[i]->setText("intervention : Distributeur -> " + distributeurs[i]->getNom());
        nomDistributeurs[i]->setAlignment(Qt::AlignCenter);

        for(int j = 0; j < distributeurs[i]->getNbBacs() ; j++)
        {
            if(distributeurs[i]->getAIntervenirBac(j) == true)
            {
                labelsDesBacs[i][j]->setText("Bac à Intervenir id : " + QString::number(j));
                labelsDesBacs[i][j]->setAlignment(Qt::AlignCenter);
                labelsDesProduits[i][j]->setText("Produit du bac : " + distributeurs[i]->getNomProduitBac(j));
                labelsDesProduits[i][j]->setAlignment(Qt::AlignCenter);
                labelsDesPourcentage[i][j]->setText("Poids à prevoir : " +  QString::number(poidsAPrevoir(i,j)) + " g ou Kg //à definir");
                labelsDesPourcentage[i][j]->setAlignment(Qt::AlignCenter);
            }
        }
    }
}

/**
 * @brief Méthode qui positionne les widgets dans la boîte de dialogue
 */
void Intervention::positionnerWidgets()
{
    qDebug() << Q_FUNC_INFO ;
    layoutDistributeurs = new QHBoxLayout;
    QVector<QVBoxLayout*> layoutInfoDistributeurs(nomDistributeurs.size());
    for(int i = 0; i < distributeurs.size(); i++)
    {
        layoutInfoDistributeurs[i] = new QVBoxLayout();
        layoutInfoDistributeurs[i]->addWidget(nomDistributeurs[i]);
        for(int j = 0; j < distributeurs[i]->getNbBacs() ; j++)
        {
            layoutInfoDistributeurs[i]->addWidget(labelsDesBacs[i][j]);
            layoutInfoDistributeurs[i]->addWidget(labelsDesProduits[i][j]);
            layoutInfoDistributeurs[i]->addWidget(labelsDesPourcentage[i][j]);
        }
        layoutDistributeurs->addLayout(layoutInfoDistributeurs[i]);
    }
    setLayout(layoutDistributeurs);
}

/**
 * @brief Méthode qui initialise les connexions signal/slot
 */
void Intervention::initialiserEvenements()
{
}

/**
 * @brief Accesseur de l'attribut dateIntervention
 * @return QDate représente la date de l'intervention sur le
 * distributeur
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
double Intervention::getEffectuee() const
{
    return this->effectuee;
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
void Intervention::setEffectuee(const bool effectuee)
{
    this->effectuee = effectuee;
}

/**
 * @brief fonction qui calcul le poids à ajouter dans un bac
 * @param numeroDistributeur
 * @param numeroBac
 */
double  Intervention::poidsAPrevoir(const int numeroDistributeur, const int numeroBac)
{
    if(distributeurs[numeroDistributeur]->getPourcentageBac(numeroBac) != 0 && distributeurs[numeroDistributeur]->getPoidsBac(numeroBac) != 0)
    {
        double poids = ((100 * distributeurs[numeroDistributeur]->getPoidsBac(numeroBac)) / distributeurs[numeroDistributeur]->getPourcentageBac(numeroBac));
        //qDebug() << Q_FUNC_INFO << distributeurs[numeroDistributeur]->getPoidsBac(numeroBac) << distributeurs[numeroDistributeur]->getPourcentageBac(numeroBac) << poids;
        return poids;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << distributeurs[numeroDistributeur]->getPoidsTotalBac(numeroBac);
        return distributeurs[numeroDistributeur]->getPoidsTotalBac(numeroBac);
    }
}
