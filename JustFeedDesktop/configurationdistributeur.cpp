/**
 * @file        configurationdistributeur.cpp
 * @brief       Définition de la classe ConfigurationDistributeur.
 * @details     La classe ConfigurationDistributeur \c Cette classe permet de
 * définir la configuration d'un distributeur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "configurationdistributeur.h"
#include "bac.h"
#include "distributeur.h"
#include "ihmjustfeed.h"
#include "produit.h"

/**
 * @brief constructeur par défaut de la classe ConfigurationDistributeur
 */
ConfigurationDistributeur::ConfigurationDistributeur(Distributeur* distributeur,
                                                     IHMJustFeed*  parent) :
    QDialog(parent),
    distributeur(distributeur), ihmJustFeed(parent)
{
    qDebug() << Q_FUNC_INFO << "deviceID" << distributeur->getDeviceID() << "nom"
             << distributeur->getNom() << "description" << distributeur->getDescription()
             << "adresse" << distributeur->getAdresse() << "codePostal"
             << distributeur->getCodePostal() << "ville" << distributeur->getVille() << "latitude"
             << distributeur->getPosition().latitude << "longitude"
             << distributeur->getPosition().longitude << "dateMiseEnService"
             << distributeur->getDateMiseService() << "aIntervenir"
             << distributeur->getAIntervenir();

    initialiserBoiteDeDialogue();
}

/**
 * @brief destructeur de la classe ConfigurationDistributeur
 */
ConfigurationDistributeur::~ConfigurationDistributeur()
{
    qDebug() << Q_FUNC_INFO;
}

// Slots

/**
 * @brief méthode qui sélectionne un produit dans la liste
 */
void ConfigurationDistributeur::selectionnerNouveauProduit(int numeroBac)
{
    labelsPrix[numeroBac]->setText(
      "Prix : " +
      QString::number(ihmJustFeed->getPrixProduit(choixNouveauProduit[numeroBac]->currentIndex())) +
      " €");
}

/**
 * @brief méthode qui change le prix d'un produit
 */
void ConfigurationDistributeur::changerLePrix(const int numeroBac)
{
    QString nouveauPrix = QString::number(editionsNouveauPrix[numeroBac]->value());
    labelsPrix[numeroBac]->setText("Prix : " + nouveauPrix + " €");
    distributeur->setPrixProduit(numeroBac, editionsNouveauPrix[numeroBac]->value());
    // editionsNouveauPrix[numeroBac]->setValue(0.);
}

/**
 * @brief méthode qui change le produit d'un bac
 */
void ConfigurationDistributeur::changerLeProduit(const int numeroBac)
{
    QString nouveauProduit = choixNouveauProduit[numeroBac]->currentText();
    labelsProduit[numeroBac]->setText(" : " + nouveauProduit);
    distributeur->getBac(numeroBac)->setProduit(
      ihmJustFeed->getProduit(choixNouveauProduit[numeroBac]->currentIndex()));

    QString nouveauPrix =
      QString::number(ihmJustFeed->getPrixProduit(choixNouveauProduit[numeroBac]->currentIndex()));
    labelsPrix[numeroBac]->setText("Prix : " + nouveauPrix + " €");
}

/**
 * @brief méthode qui ajoute un bac
 */
void ConfigurationDistributeur::ajouterBac()
{
    int numeroBac = instancierNouveauBac();
    qDebug() << Q_FUNC_INFO << "distributeur" << distributeur->getNom() << "NbBacs"
             << distributeur->getNbBacs();
    initialiserNouveauBac(numeroBac);
    positionnerNouveauBac(numeroBac);
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        labelsBac[i]->setText("Bac n°" + QString::number(i + 1));
    }
    connecterNouveauBac(numeroBac);
}

// Méthodes privées

/**
 * @brief méthode qui initialise la boîte de dialogue
 */
void ConfigurationDistributeur::initialiserBoiteDeDialogue()
{
    instancierWidgets();
    initialiserWidgets();
    positionnerWidgets();
    initialiserEvenements();
    setWindowTitle(TITRE_CONFIGURATION_DISTRIBUTEUR);
}

/**
 * @brief méthode qui instancie les widgets de la boîte de dialogue
 */
void ConfigurationDistributeur::instancierWidgets()
{
    nomDistributeur = new QLabel(this);
    nomDistributeur->setText("Distributeur : " + distributeur->getNom());
    nomDistributeur->setAlignment(Qt::AlignCenter);
    boutonAjoutBac = new QPushButton(this);
    boutonAjoutBac->setText("Ajouter un bac");
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        labelsBac.push_back(new QLabel(this));
        labelsProduit.push_back(new QLabel(this));
        labelsPrix.push_back(new QLabel(this));
        editionsNouveauPrix.push_back(new QDoubleSpinBox(this));
        choixNouveauProduit.push_back(new QComboBox(this));
        boutonsChangerPrix.push_back(new QPushButton(this));
        boutonsChangerProduit.push_back(new QPushButton(this));
        boutonSuppressionBac.push_back(new QPushButton(this));
    }
}

/**
 * @brief méthode qui initialise les widgets de la boîte de dialogue
 */
void ConfigurationDistributeur::initialiserWidgets()
{
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        labelsBac[i]->setText("Bac n°" + QString::number(i + 1));
        labelsBac[i]->setAlignment(Qt::AlignCenter);
        labelsProduit[i]->setText(" : " + distributeur->getBac(i)->getNomProduit());
        labelsProduit[i]->setAlignment(Qt::AlignCenter);
        labelsPrix[i]->setText(
          "Prix : " + QString::number(distributeur->getBac(i)->getPrixProduit()) + " €");
        labelsPrix[i]->setAlignment(Qt::AlignCenter);
        // editionsNouveauPrix[i]->setValue(distributeur->getProduitPrix(i));
        editionsNouveauPrix[i]->setAlignment(Qt::AlignCenter);
        boutonsChangerPrix[i]->setText("Changer prix");
        boutonsChangerProduit[i]->setText("Changer produit");
        boutonSuppressionBac[i]->setText("Supprimer");
        for(int j = 0; j < ihmJustFeed->getNbProduits(); j++)
        {
            choixNouveauProduit[i]->addItem(ihmJustFeed->getNomProduit(j));
        }
    }
}

/**
 * @brief méthode qui positionne les widgets dans la boîte de dialogue
 */
void ConfigurationDistributeur::positionnerWidgets()
{
    layoutBacs               = new QVBoxLayout();
    QHBoxLayout* layoutTitre = new QHBoxLayout();

    layoutTitre->addWidget(nomDistributeur);
    layoutTitre->addStretch();
    layoutTitre->addWidget(boutonAjoutBac);
    layoutBacs->addLayout(layoutTitre);
    QVector<QHBoxLayout*> layoutsDistributeur(distributeur->getNbBacs());
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        layoutsDistributeur[i] = new QHBoxLayout();
        layoutsDistributeur[i]->addWidget(labelsBac[i]);
        layoutsDistributeur[i]->addWidget(labelsProduit[i]);
        layoutsDistributeur[i]->addWidget(choixNouveauProduit[i]);
        layoutsDistributeur[i]->addWidget(boutonsChangerProduit[i]);
        layoutsDistributeur[i]->addWidget(labelsPrix[i]);
        layoutsDistributeur[i]->addWidget(editionsNouveauPrix[i]);
        layoutsDistributeur[i]->addStretch();
        layoutsDistributeur[i]->addWidget(boutonsChangerPrix[i]);
        layoutsDistributeur[i]->addWidget(boutonSuppressionBac[i]);
        // layoutsDistributeur[i]->addStretch();
        layoutBacs->addLayout(layoutsDistributeur[i]);
    }
    setLayout(layoutBacs);
}

/**
 * @brief méthode qui initialise les connexions signal/slot
 */
void ConfigurationDistributeur::initialiserEvenements()
{
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        connect(choixNouveauProduit[i],
                QOverload<int>::of(&QComboBox::currentIndexChanged),
                this,
                [this, i]()
                {
                    selectionnerNouveauProduit(i);
                });
        connect(boutonsChangerPrix[i],
                &QPushButton::clicked,
                this,
                [this, i]()
                {
                    changerLePrix(i);
                });
        connect(boutonsChangerProduit[i],
                &QPushButton::clicked,
                this,
                [this, i]()
                {
                    changerLeProduit(i);
                });
        connect(boutonSuppressionBac[i],
                &QPushButton::clicked,
                this,
                [this, i]()
                {
                    supprimerBac(i);
                });
    }
    connect(boutonAjoutBac, SIGNAL(clicked()), this, SLOT(ajouterBac()));
}

/**
 * @brief méthode qui instancie un nouveau bac
 * @return int le numéro du nouveau bac
 */
int ConfigurationDistributeur::instancierNouveauBac()
{
    Bac bac;
    distributeur->ajouterBac(bac);
    labelsBac.push_back(new QLabel(this));
    labelsProduit.push_back(new QLabel(this));
    labelsPrix.push_back(new QLabel(this));
    editionsNouveauPrix.push_back(new QDoubleSpinBox(this));
    choixNouveauProduit.push_back(new QComboBox(this));
    boutonsChangerPrix.push_back(new QPushButton(this));
    boutonsChangerProduit.push_back(new QPushButton(this));
    boutonSuppressionBac.push_back(new QPushButton(this));
    return (distributeur->getNbBacs() - 1);
}

/**
 * @brief méthode qui initialise le nouveau bac
 */
void ConfigurationDistributeur::initialiserNouveauBac(int numeroBac)
{
    labelsBac[numeroBac]->setText("Bac numero : " + QString::number(numeroBac));
    labelsBac[numeroBac]->setAlignment(Qt::AlignCenter);
    labelsProduit[numeroBac]->setText(" : " + distributeur->getBac(numeroBac)->getNomProduit());
    labelsProduit[numeroBac]->setAlignment(Qt::AlignCenter);
    labelsPrix[numeroBac]->setText(
      "Prix : " + QString::number(distributeur->getBac(numeroBac)->getPrixProduit()) + " €");
    labelsPrix[numeroBac]->setAlignment(Qt::AlignCenter);
    editionsNouveauPrix[numeroBac]->setAlignment(Qt::AlignCenter);
    boutonsChangerPrix[numeroBac]->setText("Changer prix");
    boutonsChangerProduit[numeroBac]->setText("Changer produit");
    boutonSuppressionBac[numeroBac]->setText("Supprimer");
    for(int j = 0; j < ihmJustFeed->getNbProduits(); j++)
    {
        choixNouveauProduit[numeroBac]->addItem(ihmJustFeed->getNomProduit(j));
    }
}

/**
 * @brief méthode qui positionne le nouveau bac
 */
void ConfigurationDistributeur::positionnerNouveauBac(int numeroBac)
{
    QHBoxLayout* layoutBac = new QHBoxLayout();
    layoutBac->addWidget(labelsBac[numeroBac]);
    layoutBac->addWidget(labelsProduit[numeroBac]);
    layoutBac->addWidget(choixNouveauProduit[numeroBac]);
    layoutBac->addWidget(boutonsChangerProduit[numeroBac]);
    layoutBac->addWidget(labelsPrix[numeroBac]);
    layoutBac->addWidget(editionsNouveauPrix[numeroBac]);
    layoutBac->addWidget(boutonsChangerPrix[numeroBac]);
    layoutBac->addWidget(boutonSuppressionBac[numeroBac]);
    layoutBacs->addLayout(layoutBac);
}

/**
 * @brief méthode qui connecte le nouveau bac
 */
void ConfigurationDistributeur::connecterNouveauBac(int numeroBac)
{
    for(int i = numeroBac; i < distributeur->getNbBacs(); i++)
    {
        connect(boutonsChangerPrix[i],
                &QPushButton::clicked,
                this,
                [this, i]()
                {
                    changerLePrix(i);
                });
        connect(boutonsChangerProduit[i],
                &QPushButton::clicked,
                this,
                [this, i]()
                {
                    changerLeProduit(i);
                });
        connect(boutonSuppressionBac[i],
                &QPushButton::clicked,
                this,
                [this, i]()
                {
                    supprimerBac(i);
                });
    }
}

/**
 * @brief méthode qui supprime un bac
 * @param numeroBac
 */
void ConfigurationDistributeur::supprimerBac(const int numeroBac)
{
    distributeur->supprimerBac(numeroBac);
    delete labelsBac[numeroBac];
    delete labelsProduit[numeroBac];
    delete labelsPrix[numeroBac];
    delete editionsNouveauPrix[numeroBac];
    delete choixNouveauProduit[numeroBac];
    delete boutonsChangerPrix[numeroBac];
    delete boutonsChangerProduit[numeroBac];
    delete boutonSuppressionBac[numeroBac];
    labelsBac.removeAt(numeroBac);
    labelsProduit.removeAt(numeroBac);
    labelsPrix.removeAt(numeroBac);
    editionsNouveauPrix.removeAt(numeroBac);
    choixNouveauProduit.removeAt(numeroBac);
    boutonsChangerPrix.removeAt(numeroBac);
    boutonsChangerProduit.removeAt(numeroBac);
    boutonSuppressionBac.removeAt(numeroBac);

    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        labelsBac[i]->setText("Bac n°" + QString::number(i + 1));
    }
}
