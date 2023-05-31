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
#include "basededonnees.h"
/**
 * @brief constructeur par défaut de la classe ConfigurationDistributeur
 */
ConfigurationDistributeur::ConfigurationDistributeur(Distributeur* distributeur,
                                                     IHMJustFeed*  parent) :
    QDialog(parent),
    distributeur(distributeur), ihmJustFeed(parent), baseDeDonnees(BaseDeDonnees::getInstance())
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
    baseDeDonnees->detruireInstance();
}

// Slots

/**
 * @brief méthode qui sélectionne un produit dans la liste
 */
void ConfigurationDistributeur::selectionnerNouveauProduit(int indiceBac)
{
    labelsPrix[indiceBac]->setText(
      QString::number(ihmJustFeed->getPrixProduit(choixNouveauProduit[indiceBac]->currentIndex())) +
      " €");
}

/**
 * @brief méthode qui change le prix d'un produit
 */
void ConfigurationDistributeur::changerLePrix(const int indiceBac)
{
    QString nouveauPrix = QString::number(editionsNouveauPrix[indiceBac]->value());
    labelsPrix[indiceBac]->setText("Prix : " + nouveauPrix + " €");
    distributeur->setPrixProduit(indiceBac, editionsNouveauPrix[indiceBac]->value());
    // editionsNouveauPrix[numeroBac]->setValue(0.);
}

/**
 * @brief méthode qui change le produit d'un bac
 */
void ConfigurationDistributeur::changerLeProduit(const int indiceBac)
{
    QString nouveauProduit = choixNouveauProduit[indiceBac]->currentText();
    labelsProduit[indiceBac]->setText(" : " + nouveauProduit);
    distributeur->getBac(indiceBac)->setProduit(
      ihmJustFeed->getProduit(choixNouveauProduit[indiceBac]->currentIndex()));

    QString nouveauPrix =
      QString::number(ihmJustFeed->getPrixProduit(choixNouveauProduit[indiceBac]->currentIndex()));
    labelsPrix[indiceBac]->setText(nouveauPrix);

    selectionnerNouveauProduit(indiceBac);
}

/**
 * @brief méthode qui ajoute un bac
 */
void ConfigurationDistributeur::ajouterBac()
{
    int indiceBac = instancierNouveauBac();
    qDebug() << Q_FUNC_INFO << "distributeur" << distributeur->getNom() << "NbBacs"
             << distributeur->getNbBacs();
    initialiserNouveauBac(indiceBac);
    positionnerNouveauBac(indiceBac);
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        labelsBac[i]->setText("Bac n°" + QString::number(i + 1));
    }
    connecterNouveauBac(indiceBac);
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
    boutonValide = new QPushButton(this);
    boutonValide->setText("Valider");
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
        labelsBac[i]->setText("Bac n°" + QString::number(i + 1) + " : ");
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
    QVector<QHBoxLayout*> layoutsDistributeur(distributeur->getNbBacs() + 1);
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
    layoutsDistributeur[distributeur->getNbBacs()] = new QHBoxLayout();
    layoutsDistributeur[distributeur->getNbBacs()]->addWidget(boutonValide);
    layoutsDistributeur[distributeur->getNbBacs()]->addStretch();
    layoutBacs->addLayout(layoutsDistributeur[distributeur->getNbBacs()]);
    setLayout(layoutBacs);
}

/**
 * @brief méthode qui initialise les connexions signal/slot
 */
void ConfigurationDistributeur::initialiserEvenements()
{
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        connect(boutonsChangerPrix[i], &QPushButton::clicked, this, [this, i]() {
            changerLePrix(i);
        });
        connect(boutonsChangerProduit[i], &QPushButton::clicked, this, [this, i]() {
            changerLeProduit(i);
        });
        connect(boutonSuppressionBac[i], &QPushButton::clicked, this, [this, i]() {
            supprimerBac(i);
        });
    }
    connect(boutonValide, SIGNAL(clicked()), this, SLOT(valider()));
    connect(boutonAjoutBac, SIGNAL(clicked()), this, SLOT(ajouterBac()));
}

/**
 * @brief méthode qui instancie un nouveau bac
 * @return int le numéro du nouveau bac
 */
int ConfigurationDistributeur::instancierNouveauBac()
{
    Bac bac;
    qDebug() << Q_FUNC_INFO << "distributeur" << distributeur->getNbBacs();
    distributeur->ajouterBac(bac);
    qDebug() << Q_FUNC_INFO << "distributeur" << distributeur->getNbBacs();
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
void ConfigurationDistributeur::initialiserNouveauBac(int indiceBac)
{
    labelsBac[indiceBac]->setText("Bac numero : " + QString::number(indiceBac) + " : ");
    labelsBac[indiceBac]->setAlignment(Qt::AlignCenter);
    labelsProduit[indiceBac]->setText(" : " + distributeur->getBac(indiceBac)->getNomProduit());
    labelsProduit[indiceBac]->setAlignment(Qt::AlignCenter);
    labelsPrix[indiceBac]->setText(
      "Prix : " + QString::number(distributeur->getBac(indiceBac)->getPrixProduit()) + " €");
    labelsPrix[indiceBac]->setAlignment(Qt::AlignCenter);
    editionsNouveauPrix[indiceBac]->setAlignment(Qt::AlignCenter);
    boutonsChangerPrix[indiceBac]->setText("Changer prix");
    boutonsChangerProduit[indiceBac]->setText("Changer produit");
    boutonSuppressionBac[indiceBac]->setText("Supprimer");
    for(int j = 0; j < ihmJustFeed->getNbProduits(); j++)
    {
        choixNouveauProduit[indiceBac]->addItem(ihmJustFeed->getNomProduit(j));
    }
}

/**
 * @brief méthode qui positionne le nouveau bac
 */
void ConfigurationDistributeur::positionnerNouveauBac(int indiceBac)
{
    QHBoxLayout* layoutBac = new QHBoxLayout();
    layoutBac->addWidget(labelsBac[indiceBac]);
    layoutBac->addWidget(labelsProduit[indiceBac]);
    layoutBac->addWidget(choixNouveauProduit[indiceBac]);
    layoutBac->addWidget(boutonsChangerProduit[indiceBac]);
    layoutBac->addWidget(labelsPrix[indiceBac]);
    layoutBac->addWidget(editionsNouveauPrix[indiceBac]);
    layoutBac->addWidget(boutonsChangerPrix[indiceBac]);
    layoutBac->addWidget(boutonSuppressionBac[indiceBac]);
    layoutBacs->addLayout(layoutBac);
}

/**
 * @brief méthode qui connecte le nouveau bac
 */
void ConfigurationDistributeur::connecterNouveauBac(int indiceBac)
{
    for(int i = indiceBac; i < distributeur->getNbBacs(); i++)
    {
        connect(boutonsChangerPrix[i], &QPushButton::clicked, this, [this, i]() {
            changerLePrix(i);
        });
        connect(boutonsChangerProduit[i], &QPushButton::clicked, this, [this, i]() {
            changerLeProduit(i);
        });
        connect(boutonSuppressionBac[i], &QPushButton::clicked, this, [this, i]() {
            supprimerBac(i);
        });
    }
}

/**
 * @brief méthode qui supprime un bac
 * @param numeroBac
 */
void ConfigurationDistributeur::supprimerBac(const int indiceBac)
{
    if(distributeur->getNbBacs() != 1)
    {
        supprimerBaseDeDonnees(indiceBac);
        distributeur->supprimerBac(indiceBac);
        delete labelsBac[indiceBac];
        delete labelsProduit[indiceBac];
        delete labelsPrix[indiceBac];
        delete editionsNouveauPrix[indiceBac];
        delete choixNouveauProduit[indiceBac];
        delete boutonsChangerPrix[indiceBac];
        delete boutonsChangerProduit[indiceBac];
        delete boutonSuppressionBac[indiceBac];
        labelsBac.removeAt(indiceBac);
        labelsProduit.removeAt(indiceBac);
        labelsPrix.removeAt(indiceBac);
        editionsNouveauPrix.removeAt(indiceBac);
        choixNouveauProduit.removeAt(indiceBac);
        boutonsChangerPrix.removeAt(indiceBac);
        boutonsChangerProduit.removeAt(indiceBac);
        boutonSuppressionBac.removeAt(indiceBac);
        for(int i = 0; i < distributeur->getNbBacs(); i++)
        {
            labelsBac[i]->setText("Bac n°" + QString::number(i + 1));
        }
    }
}

void ConfigurationDistributeur::valider()
{
    for(int i = 0; i < distributeur->getNbBacs(); i++)
    {
        QString produit = labelsProduit[i]->text().section(':', 1).trimmed();
        QString requete = "SELECT idProduit FROM Produit WHERE nomProduit = '" + produit + "';";
        QString idProduit;
        qDebug() << Q_FUNC_INFO << "requete" << requete;
        baseDeDonnees->recuperer(requete, idProduit);
        qDebug() << Q_FUNC_INFO << "idProduit" << idProduit;
        requete = "UPDATE Bac SET idProduit = " + idProduit +
                  " WHERE idBac =" + QString::number(distributeur->getBac(i)->getIdBac()) + ";";
        qDebug() << Q_FUNC_INFO << "requete" << requete;
        baseDeDonnees->executer(requete);

        int     startIndex = labelsPrix[i]->text().indexOf(QRegExp("\\d"));
        int     endIndex   = labelsPrix[i]->text().lastIndexOf(QRegExp("\\d"));
        QString prix       = labelsPrix[i]->text().mid(startIndex, endIndex - startIndex + 1);
        if(editionsNouveauPrix[i]->value() != 0.)
        {
            requete = "UPDATE Produit SET prix =" + prix + " WHERE idProduit = " + idProduit + ";";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
        }
    }
    this->close();
}

void ConfigurationDistributeur::supprimerBaseDeDonnees(const int indiceBac)
{
    qDebug() << Q_FUNC_INFO;
    QString requete = "DELETE FROM Bac WHERE idBac = '" +
                      QString::number(distributeur->getBac(indiceBac)->getIdBac()) + "';";
    // baseDeDonnees->executer(requete);
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    requete = "UPDATE Distributeur SET nbBacs = '" + QString::number(distributeur->getNbBacs()) +
              "' WHERE idDistributeur = " + QString::number(distributeur->getId()) + ";";
    // baseDeDonnees->executer(requete);
    qDebug() << Q_FUNC_INFO << "requete" << requete;
}
