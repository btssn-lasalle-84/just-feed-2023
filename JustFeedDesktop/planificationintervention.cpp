/**
 * @file        planificationintervention.cpp
 * @brief       Définition de la classe PlanificationIntervention.
 * @details     La classe PlanificationIntervention \c Cette classe permet de planifier une
 * intervention
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.2
 * @date        2023
 */

#include "planificationintervention.h"
#include "bac.h"
#include "basededonnees.h"
#include "intervention.h"
#include "distributeur.h"
#include "ihmjustfeed.h"

/**
 * @todo Améliorer la gestion des interventions (à faire et en cours) déjà planifiées
 */

/**
 * @brief Constructeur de la classe PlanificationIntervention
 */
PlanificationIntervention::PlanificationIntervention(
  QVector<Distributeur*> listeDistributeursAIntervenir,
  IHMJustFeed*           parent) :
    QDialog(parent),
    ihmJustFeed(parent), baseDeDonnees(BaseDeDonnees::getInstance()), intervention(nullptr),
    dateIntervention(QDate::currentDate()), distributeurs(listeDistributeursAIntervenir),
    effectuable(false)
{
    qDebug() << Q_FUNC_INFO << "dateIntervention" << dateIntervention << "nb distributeurs"
             << listeDistributeursAIntervenir.size();
    initialiserBoiteDeDialogue();
}

/**
 * @brief Destructeur de la classe Intervention
 */
PlanificationIntervention::~PlanificationIntervention()
{
    if(intervention != nullptr)
        delete intervention;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief méthode qui permet de selectionner les bacs
 * @return void
 */
void PlanificationIntervention::selectionnerBac()
{
    QCheckBox* selectionBac = qobject_cast<QCheckBox*>(sender());
    qDebug() << Q_FUNC_INFO << "checkbox bac" << selectionBac->objectName() << "etat"
             << selectionBac->checkState();

    int numeroDistributeur = selectionBac->objectName().section("-", 0, 0).toInt();
    int numeroBac          = selectionBac->objectName().section("-", 1, 1).toInt();

    qDebug() << Q_FUNC_INFO << "distributeur" << distributeurs[numeroDistributeur]->getNom()
             << "bac" << distributeurs[numeroDistributeur]->getBac(numeroBac)->getNomProduit()
             << "remplissage"
             << labelsDesCheckboxRemplissage[numeroDistributeur][numeroBac]->checkState()
             << "dépannage"
             << labelsDesCheckboxDepannage[numeroDistributeur][numeroBac]->checkState();

    if(labelsDesCheckboxDepannage[numeroDistributeur][numeroBac]->checkState() == Qt::Checked)
    {
        distributeurs[numeroDistributeur]->getBac(numeroBac)->setADepanner(true);
    }
    else
    {
        distributeurs[numeroDistributeur]->getBac(numeroBac)->setADepanner(false);
    }
    if(labelsDesCheckboxRemplissage[numeroDistributeur][numeroBac]->checkState() == Qt::Checked)
    {
        distributeurs[numeroDistributeur]->getBac(numeroBac)->setARemplir(true);
    }
    else
    {
        distributeurs[numeroDistributeur]->getBac(numeroBac)->setARemplir(false);
    }

    autoriserCreation();
}

/**
 * @brief Si un changement dans le choix de l'opérateur
 * @return void
 */
void PlanificationIntervention::selectionnerOperateur()
{
    autoriserCreation();
}

/**
 * @brief Pour créer une intervention planifiée
 * @return void
 */
void PlanificationIntervention::creerUneIntervention()
{
    if(!effectuable)
        return;
    intervention = new Intervention(distributeurs);
    intervention->setDateIntervention(editionDate->date());
    int idOperateurInt = recupererIdOperateur();
    if(idOperateurInt > 0)
    {
        intervention->setIdOperateur(idOperateurInt);
        intervention->creer();
        this->close();
    }
}
// Méthodes privées

/**
 * @brief Initialise la boîte de dialogue
 */
void PlanificationIntervention::initialiserBoiteDeDialogue()
{
    qDebug() << Q_FUNC_INFO;
    instancierWidgets();
    initialiserWidgets();
    initialiserEtatDistributeur();
    positionnerWidgets();
    initialiserEvenements();
    setWindowTitle(TITRE_INTERVENTION);
}

/**
 * @brief Instancie les widgets de la boîte de dialogue
 */
void PlanificationIntervention::instancierWidgets()
{
    qDebug() << Q_FUNC_INFO;
    boutonItervention = new QPushButton(this);
    editionDate       = new QDateEdit(QDate::currentDate(), this);
    listeOperateurs   = new QComboBox(this);

    for(int i = 0; i < distributeurs.size(); i++)
    {
        nomDistributeurs.push_back(new QLabel(this));
        labelsBac.clear();
        labelsProduit.clear();
        labelsPourcentage.clear();
        labelsCheckboxDepannage.clear();
        labelsCheckboxRemplissage.clear();
        labelsHygrometrie.clear();
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            QCheckBox* checkboxDepannage   = new QCheckBox(this);
            QCheckBox* checkboxRemplissage = new QCheckBox(this);
            checkboxDepannage->setObjectName(QString::number(i) + "-" + QString::number(j));
            checkboxRemplissage->setObjectName(QString::number(i) + "-" + QString::number(j));
            labelsCheckboxDepannage.push_back(checkboxDepannage);
            labelsCheckboxRemplissage.push_back(checkboxRemplissage);
            labelsBac.push_back(new QLabel(this));
            labelsProduit.push_back(new QLabel(this));
            labelsPourcentage.push_back(new QLabel(this));
            labelsHygrometrie.push_back(new QLabel(this));
        }
        labelsDesCheckboxDepannage.push_back(labelsCheckboxDepannage);
        labelsDesCheckboxRemplissage.push_back(labelsCheckboxRemplissage);
        labelsDesBacs.push_back(labelsBac);
        labelsDesProduits.push_back(labelsProduit);
        labelsDesPourcentage.push_back(labelsPourcentage);
        labelsDesHygrometries.push_back(labelsHygrometrie);
    }
}

/**
 * @brief Initialise les widgets de la boîte de dialogue
 */
void PlanificationIntervention::initialiserWidgets()
{
    qDebug() << Q_FUNC_INFO;
    boutonItervention->setText("Créer l'intervention");
    boutonItervention->setEnabled(false);
    editionDate->setDisplayFormat("dd/MM/yyyy");
    chargerListeOperateurs();
    for(int i = 0; i < distributeurs.size(); i++)
    {
        nomDistributeurs[i]->setText("Distributeur -> " + distributeurs[i]->getNom());
        nomDistributeurs[i]->setAlignment(Qt::AlignCenter);
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            qDebug() << Q_FUNC_INFO << "produit" << distributeurs[i]->getBac(j)->getNomProduit()
                     << "poidsActuel" << distributeurs[i]->getBac(j)->getPoidsActuel()
                     << "poidsTotal" << distributeurs[i]->getBac(j)->getPoidsTotal()
                     << "pourcentageRemplissage"
                     << distributeurs[i]->getBac(j)->getPourcentageRemplissage();
            labelsDesBacs[i][j]->setText("Bac n°" + QString::number(j + 1));
            labelsDesBacs[i][j]->setAlignment(Qt::AlignCenter);
            labelsDesProduits[i][j]->setText("Produit : " +
                                             distributeurs[i]->getBac(j)->getNomProduit());
            labelsDesProduits[i][j]->setAlignment(Qt::AlignCenter);
            labelsDesPourcentage[i][j]->setText(
              "Poids à prévoir : " +
              QString::number(distributeurs[i]->getBac(j)->getQuantiteARemplir()) +
              " g ou Kg (à définir)");
            labelsDesPourcentage[i][j]->setAlignment(Qt::AlignCenter);
            labelsDesCheckboxDepannage[i][j]->setCheckState(Qt::Unchecked);
            labelsDesCheckboxDepannage[i][j]->setText("Dépanner");
            labelsDesCheckboxRemplissage[i][j]->setCheckState(Qt::Unchecked);
            labelsDesCheckboxRemplissage[i][j]->setText("Remplir");

            labelsDesHygrometries[i][j]->setText(
              "Hygrometrie : " + QString::number(distributeurs[i]->getHygrometrieBac(j)) + "%");
            labelsDesHygrometries[i][j]->setAlignment(Qt::AlignCenter);
        }
    }
}

/**
 * @brief Positionne les widgets dans la boîte de dialogue
 */
void PlanificationIntervention::positionnerWidgets()
{
    qDebug() << Q_FUNC_INFO;
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;
    layoutDistributeurs          = new QHBoxLayout;
    int totalBac                 = 0;
    for(int i = 0; i < distributeurs.size(); i++)
    {
        totalBac += distributeurs[i]->getNbBacs();
    }
    QVector<QHBoxLayout*> layoutBac(totalBac);
    QVector<QVBoxLayout*> layoutInfoDistributeurs(nomDistributeurs.size());
    QHBoxLayout*          layoutFormulaire = new QHBoxLayout;
    layoutFormulaire->addWidget(listeOperateurs);
    for(int i = 0; i < distributeurs.size(); i++)
    {
        layoutInfoDistributeurs[i] = new QVBoxLayout();
        layoutInfoDistributeurs[i]->addWidget(nomDistributeurs[i]);
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            layoutBac[j] = new QHBoxLayout();
            layoutBac[j]->addStretch();
            layoutBac[j]->addWidget(labelsDesBacs[i][j]);
            layoutBac[j]->addWidget(labelsDesCheckboxRemplissage[i][j]);
            layoutBac[j]->addWidget(labelsDesCheckboxDepannage[i][j]);
            layoutBac[j]->addStretch();
            layoutInfoDistributeurs[i]->addLayout(layoutBac[j]);
            layoutInfoDistributeurs[i]->addWidget(labelsDesProduits[i][j]);
            layoutInfoDistributeurs[i]->addWidget(labelsDesPourcentage[i][j]);
            layoutInfoDistributeurs[i]->addWidget(labelsDesHygrometries[i][j]);
        }
        layoutDistributeurs->addLayout(layoutInfoDistributeurs[i]);
    }
    layoutFormulaire->addWidget(editionDate);
    layoutFormulaire->addWidget(boutonItervention);
    layoutPrincipal->addLayout(layoutDistributeurs);
    layoutPrincipal->addLayout(layoutFormulaire);
    setLayout(layoutPrincipal);
}

/**
 * @brief Initialise la gestion d'évènements (signal/slot)
 */
void PlanificationIntervention::initialiserEvenements()
{
    for(int i = 0; i < distributeurs.size(); i++)
    {
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            connect(labelsDesCheckboxDepannage[i][j],
                    SIGNAL(clicked(bool)),
                    this,
                    SLOT(selectionnerBac()));
            connect(labelsDesCheckboxRemplissage[i][j],
                    SIGNAL(clicked(bool)),
                    this,
                    SLOT(selectionnerBac()));
        }
    }
    connect(boutonItervention, SIGNAL(clicked()), this, SLOT(creerUneIntervention()));
    connect(listeOperateurs, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionnerOperateur()));
}

/**
 * @brief Vérifie si une opération d'intervention a été sélectionnée
 */
bool PlanificationIntervention::estEffectuable()
{
    if(listeOperateurs->currentIndex() == 0)
        return false;
    effectuable = false;
    for(int i = 0; i < distributeurs.size(); ++i)
    {
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            if(distributeurs[i]->getBac(j)->getADepanner())
            {
                effectuable = true;
                return effectuable;
            }
            if(distributeurs[i]->getBac(j)->getARemplir())
            {
                effectuable = true;
                return effectuable;
            }
        }
    }
    return effectuable;
}

/**
 * @brief Initialise les couleurs des bacs en fonction des
 * pourcentages
 */
void PlanificationIntervention::initialiserEtatDistributeur()
{
    for(int i = 0; i < distributeurs.size(); i++)
    {
        for(int j = 0; j < distributeurs[i]->getNbBacs(); j++)
        {
            qDebug() << Q_FUNC_INFO << "PourcentageRemplissage"
                     << distributeurs[i]->getBac(j)->getPourcentageRemplissage();
            if((distributeurs[i]->getBac(j)->getPourcentageRemplissage() >= ZERO) &&
               (distributeurs[i]->getBac(j)->getPourcentageRemplissage() <= TRENTE))
            {
                labelsDesBacs[i][j]->setStyleSheet(COULEUR_BAC_VIDE);
            }
            else if((distributeurs[i]->getBac(j)->getPourcentageRemplissage() > TRENTE) &&
                    (distributeurs[i]->getBac(j)->getPourcentageRemplissage() <= SOIXANTE))
            {
                labelsDesBacs[i][j]->setStyleSheet(COULEUR_PRESQUE_BAC_VIDE);
            }
            else if((distributeurs[i]->getBac(j)->getPourcentageRemplissage() > SOIXANTE) &&
                    (distributeurs[i]->getBac(j)->getPourcentageRemplissage() <= CENT))
            {
                labelsDesBacs[i][j]->setStyleSheet(COULEUR_BAC_PLEIN);
            }

            qDebug() << Q_FUNC_INFO << "HygrometrieBac" << distributeurs[i]->getHygrometrieBac(j);
            if((distributeurs[i]->getHygrometrieBac(j)) >= ZERO &&
               (distributeurs[i]->getHygrometrieBac(j) <= QUINZE))
            {
                labelsDesHygrometries[i][j]->setStyleSheet(COULEUR_HYGROMETRIE_ANORMALE);
            }
            else if((distributeurs[i]->getHygrometrieBac(j)) > QUINZE &&
                    (distributeurs[i]->getHygrometrieBac(j) <= CINQUANTE))
            {
                labelsDesHygrometries[i][j]->setStyleSheet(COULEUR_HYGROMETRIE_A_SURVEILLER);
            }
            else if((distributeurs[i]->getHygrometrieBac(j)) > CINQUANTE &&
                    (distributeurs[i]->getHygrometrieBac(j) <= CENT))
            {
                labelsDesHygrometries[i][j]->setStyleSheet(COULEUR_HYGROMETRIE_NORMALE);
            }

            qDebug() << Q_FUNC_INFO << "ADepanner" << distributeurs[i]->getBac(j)->getADepanner();
            if((distributeurs[i]->getBac(j)->getADepanner()))
            {
                labelsDesCheckboxDepannage[i][j]->setEnabled(false);
            }

            qDebug() << Q_FUNC_INFO << "ARemplir" << distributeurs[i]->getBac(j)->getARemplir();
            if((distributeurs[i]->getBac(j)->getARemplir()))
            {
                labelsDesCheckboxRemplissage[i][j]->setEnabled(false);
            }
        }
    }
}

/**
 * @brief Charge la liste des opérateurs connus
 */
void PlanificationIntervention::chargerListeOperateurs()
{
    QString              requete = "SELECT idOperateur,nom,prenom FROM Operateur";
    QVector<QStringList> listeOperateursBdd;
    baseDeDonnees->recuperer(requete, listeOperateursBdd);
    listeOperateurs->addItem("Opérateur"); // nom de la liste
    for(int i = 0; i < listeOperateursBdd.size(); i++)
    {
        idOperateurs.push_back(listeOperateursBdd[i].at(CHAMP_NOM_IDOPERATEUR).toInt());
        listeOperateurs->addItem(listeOperateursBdd[i].at(CHAMP_NOM_OPERATEUR) + " " +
                                 listeOperateursBdd[i].at(CHAMP_PRENOM_OPERATEUR));
    }
}

/**
 * @brief Récupère l'id d'un opérateur
 */
int PlanificationIntervention::recupererIdOperateur()
{
    if(listeOperateurs->currentIndex() == 0)
        return 0;
    return idOperateurs[listeOperateurs->currentIndex() - 1];
}

/**
 * @brief Permet de gérer le bouton de création d'une intervention
 */
void PlanificationIntervention::autoriserCreation()
{
    if(estEffectuable())
        boutonItervention->setEnabled(true);
    else
        boutonItervention->setEnabled(false);
}
