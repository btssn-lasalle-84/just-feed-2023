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
#include "bac.h"
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
bool Intervention::estEffectuee() const
{
    return this->effectuee;
}

bool Intervention::estARemplir() const
{
    return this->aRemplir;
}

bool Intervention::estADepanner() const
{
    return this->aDepanner;
}

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

void Intervention::remplir(bool aRemplir)
{
    this->aRemplir = aRemplir;
}

void Intervention::depanner(bool aDepanner)
{
    this->aDepanner = aDepanner;
}

void Intervention::intervenir(bool aIntervenir)
{
    this->effectuee = !aIntervenir;
}

// Méthodes privées

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
    qDebug() << Q_FUNC_INFO;
    for(int i = 0; i < distributeurs.size(); i++)
    {
        nomDistributeurs.push_back(new QLabel(this));
        labelsBac.clear();
        labelsProduit.clear();
        labelsPourcentage.clear();
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            labelsBac.push_back(new QLabel(this));
            labelsProduit.push_back(new QLabel(this));
            labelsPourcentage.push_back(new QLabel(this));
        }
        labelsDesBacs.push_back(labelsBac);
        labelsDesProduits.push_back(labelsProduit);
        labelsDesPourcentage.push_back(labelsPourcentage);
    }
    qDebug() << Q_FUNC_INFO << labelsDesBacs;
}

/**
 * @brief Méthode qui initialise les widgets de la boîte de dialogue
 */
void Intervention::initialiserWidgets()
{
    qDebug() << Q_FUNC_INFO;
    for(int i = 0; i < distributeurs.size(); i++)
    {
        nomDistributeurs[i]->setText("Distributeur -> " + distributeurs[i]->getNom());
        nomDistributeurs[i]->setAlignment(Qt::AlignCenter);

        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            qDebug() << Q_FUNC_INFO << "produit" << distributeurs[i]->getNomProduitBac(j)
                     << "poidsActuel" << distributeurs[i]->getBac(j)->getPoidsActuel()
                     << "poidsTotal" << distributeurs[i]->getBac(j)->getPoidsTotal()
                     << "pourcentageRemplissage"
                     << distributeurs[i]->getBac(j)->getPourcentageRemplissage();
            labelsDesBacs[i][j]->setText("Numéro bac : " + QString::number(j + 1));
            labelsDesBacs[i][j]->setAlignment(Qt::AlignCenter);
            labelsDesProduits[i][j]->setText("Produit du bac : " +
                                             distributeurs[i]->getNomProduitBac(j));
            labelsDesProduits[i][j]->setAlignment(Qt::AlignCenter);
            labelsDesPourcentage[i][j]->setText(
              "Poids à prévoir : " +
              QString::number(distributeurs[i]->getBac(j)->getQuantiteARemplir()) +
              " g ou Kg (à définir)");
            labelsDesPourcentage[i][j]->setAlignment(Qt::AlignCenter);
        }
    }
}

/**
 * @brief Méthode qui positionne les widgets dans la boîte de dialogue
 */
void Intervention::positionnerWidgets()
{
    qDebug() << Q_FUNC_INFO;
    layoutDistributeurs = new QHBoxLayout;
    QVector<QVBoxLayout*> layoutInfoDistributeurs(nomDistributeurs.size());
    for(int i = 0; i < distributeurs.size(); i++)
    {
        layoutInfoDistributeurs[i] = new QVBoxLayout();
        layoutInfoDistributeurs[i]->addWidget(nomDistributeurs[i]);
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
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
