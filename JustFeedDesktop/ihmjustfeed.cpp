/**
 * @file        ihmjustfeed.cpp
 * @brief       Définition de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "ihmjustfeed.h"
#include "distributeur.h"
#include "produit.h"
#include "bac.h"

/**
 * @brief Constructeur par défaut de la classe IHMJustFeed
 */

IHMJustFeed::IHMJustFeed(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;
    initialiserDistributeurs();
    initialiserGUI();
}

/**
 * @brief Destructeur de la classe IHMJustFeed
 */
IHMJustFeed::~IHMJustFeed()
{
    for(int i = 0; i < distributeurs.size(); ++i)
    {
        delete distributeurs[i];
    }
    qDebug() << Q_FUNC_INFO;
}

// Méthodes publiques

/**
 * @brief méthode qui instancie un nouveau bac
 * @return int le numéro du nouveau bac
 */
int IHMJustFeed::instancierNouveauBac()
{
    Bac bac;
    distributeurs[numeroDistributeurSelectionne]->ajouterBac(bac);
    labelsBac.push_back(new QLabel(this));
    labelsProduit.push_back(new QLabel(this));
    labelsPrix.push_back(new QLabel(this));
    editionsNouveauPrix.push_back(new QLineEdit(this));
    choixNouveauProduit.push_back(new QLineEdit(this));
    boutonsChangerPrix.push_back(new QPushButton(this));
    boutonsChangerProduit.push_back(new QPushButton(this));
    return (distributeurs[numeroDistributeurSelectionne]->getNbBacs() - 1);
}

/**
 * @brief méthode qui initialise le nouveau bac
 */
void IHMJustFeed::initialiserNouveauBac(int numeroBac)
{
    labelsBac[numeroBac]->setText("Bac numero : " + QString::number(numeroBac));
    labelsBac[numeroBac]->setAlignment(Qt::AlignCenter);
    labelsProduit[numeroBac]->setText(
      "Produit : " + distributeurs[numeroDistributeurSelectionne]->getNomProduitBac(numeroBac));
    labelsProduit[numeroBac]->setAlignment(Qt::AlignCenter);
    labelsPrix[numeroBac]->setText(
      "Prix : " +
      QString::number(distributeurs[numeroDistributeurSelectionne]->getProduitPrix(numeroBac)) +
      " €");
    labelsPrix[numeroBac]->setAlignment(Qt::AlignCenter);
    editionsNouveauPrix[numeroBac]->setAlignment(Qt::AlignCenter);
    boutonsChangerPrix[numeroBac]->setText("changer prix");
    boutonsChangerProduit[numeroBac]->setText("changer produit");
}

/**
 * @brief méthode qui positionne le nouveau bac
 */
void IHMJustFeed::positionnerNouveauBac(int numeroBac)
{
    QHBoxLayout* layoutBac = new QHBoxLayout();
    layoutBac->addWidget(labelsBac[numeroBac]);
    layoutBac->addWidget(labelsProduit[numeroBac]);
    layoutBac->addWidget(choixNouveauProduit[numeroBac]);
    layoutBac->addWidget(boutonsChangerProduit[numeroBac]);
    layoutBac->addWidget(labelsPrix[numeroBac]);
    layoutBac->addWidget(editionsNouveauPrix[numeroBac]);
    layoutBac->addWidget(boutonsChangerPrix[numeroBac]);
    layoutBacs->addLayout(layoutBac);
}

/**
 * @brief méthode qui connecte le nouveau bac
 */
void IHMJustFeed::connecterNouveauBac(int numeroBac)
{
    for(int i = numeroBac; i < distributeurs[numeroDistributeurSelectionne]->getNbBacs(); i++)
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
    }
}

// Slots

/**
 * @brief méthode qui change le prix d'un produit
 */
void IHMJustFeed::changerLePrix(const int numeroBac)
{
    QString nouveauPrix = editionsNouveauPrix[numeroBac]->text();
    labelsPrix[numeroBac]->setText("Prix : " + nouveauPrix + " €");
    editionsNouveauPrix[numeroBac]->setText("");
}

/**
 * @brief méthode qui change le produit d'un bac
 */
void IHMJustFeed::changerLeProduit(const int numeroBac)
{
    QString nouveauProduit = choixNouveauProduit[numeroBac]->text();
    labelsProduit[numeroBac]->setText("Produit : " + nouveauProduit);
    choixNouveauProduit[numeroBac]->setText("");
}

/**
 * @brief méthode qui ajoute un bac
 */
void IHMJustFeed::ajouterBac()
{
    int numeroBac = instancierNouveauBac();
    qDebug() << Q_FUNC_INFO << "distributeur"
             << distributeurs[numeroDistributeurSelectionne]->getNom() << "NbBacs"
             << distributeurs[numeroDistributeurSelectionne]->getNbBacs();
    initialiserNouveauBac(numeroBac);
    positionnerNouveauBac(numeroBac);
    for(int i = 0; i < distributeurs[numeroDistributeurSelectionne]->getNbBacs(); i++)
    {
        labelsBac[i]->setText("Bac numéro : " + QString::number(i));
    }
    connecterNouveauBac(numeroBac);
}

// Méthodes privées

/**
 * @brief Méthode qui initialise la GUI
 */
void IHMJustFeed::initialiserGUI()
{
    instancierWidgets();
    initialiserWidgets();
    positionnerWidgets();
    initialiserEvenements();

    // La fenêtre principale
    setWindowTitle(TITRE_APPLICATION + " " + VERSION_APPLICATION);
    /*QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    resize(screenGeometry.width(), screenGeometry.height());*/
}

/**
 * @brief Méthode qui instancie les widgets de la GUI
 */
void IHMJustFeed::instancierWidgets()
{
    nomDistributeur = new QLabel(this);
    nomDistributeur->setText("Distributeur : " +
                             distributeurs[numeroDistributeurSelectionne]->getNom());
    nomDistributeur->setAlignment(Qt::AlignCenter);
    boutonAjoutBac = new QPushButton(this);
    boutonAjoutBac->setText("Ajouter un bac");
    boutonSuppressionBac = new QPushButton(this);
    boutonSuppressionBac->setText("Supprimer un bac");
    for(int i = 0; i < distributeurs[numeroDistributeurSelectionne]->getNbBacs(); i++)
    {
        labelsBac.push_back(new QLabel(this));
        labelsProduit.push_back(new QLabel(this));
        labelsPrix.push_back(new QLabel(this));
        editionsNouveauPrix.push_back(new QLineEdit(this));
        choixNouveauProduit.push_back(new QLineEdit(this));
        boutonsChangerPrix.push_back(new QPushButton(this));
        boutonsChangerProduit.push_back(new QPushButton(this));
    }
}

/**
 * @brief Méthode qui initialise les widgets de la GUI
 */
void IHMJustFeed::initialiserWidgets()
{
    for(int i = 0; i < distributeurs[numeroDistributeurSelectionne]->getNbBacs(); i++)
    {
        labelsBac[i]->setText("Bac numéro : " + QString::number(i));
        labelsBac[i]->setAlignment(Qt::AlignCenter);
        labelsProduit[i]->setText(
          "Produit : " + distributeurs[numeroDistributeurSelectionne]->getNomProduitBac(i));
        labelsProduit[i]->setAlignment(Qt::AlignCenter);
        labelsPrix[i]->setText(
          "Prix : " +
          QString::number(distributeurs[numeroDistributeurSelectionne]->getProduitPrix(i)) + " €");
        labelsPrix[i]->setAlignment(Qt::AlignCenter);
        editionsNouveauPrix[i]->setAlignment(Qt::AlignCenter);
        boutonsChangerPrix[i]->setText("Changer prix");
        boutonsChangerProduit[i]->setText("Changer produit");
    }
}

/**
 * @brief Méthode qui positionne les widgets dans la GUI
 */
void IHMJustFeed::positionnerWidgets()
{
    layoutBacs               = new QVBoxLayout();
    QHBoxLayout* layoutTitre = new QHBoxLayout();

    layoutTitre->addWidget(nomDistributeur);
    layoutTitre->addWidget(boutonAjoutBac);
    layoutTitre->addWidget(boutonSuppressionBac);
    layoutBacs->addLayout(layoutTitre);
    QVector<QHBoxLayout*> layoutsDistributeur(
      distributeurs[numeroDistributeurSelectionne]->getNbBacs());
    ;
    for(int i = 0; i < distributeurs[numeroDistributeurSelectionne]->getNbBacs(); i++)
    {
        layoutsDistributeur[i] = new QHBoxLayout();
        layoutsDistributeur[i]->addWidget(labelsBac[i]);
        layoutsDistributeur[i]->addWidget(labelsProduit[i]);
        layoutsDistributeur[i]->addWidget(choixNouveauProduit[i]);
        layoutsDistributeur[i]->addWidget(boutonsChangerProduit[i]);
        layoutsDistributeur[i]->addWidget(labelsPrix[i]);
        layoutsDistributeur[i]->addWidget(editionsNouveauPrix[i]);
        layoutsDistributeur[i]->addWidget(boutonsChangerPrix[i]);
        layoutBacs->addLayout(layoutsDistributeur[i]);
    }
    setLayout(layoutBacs);
}

/**
 * @brief méthode qui initialise les connexion signal/slot
 */
void IHMJustFeed::initialiserEvenements()
{
    for(int i = 0; i < distributeurs[numeroDistributeurSelectionne]->getNbBacs(); i++)
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
    }
    connect(boutonAjoutBac, SIGNAL(clicked()), this, SLOT(ajouterBac()));
}

/**
 * @brief méthode qui initianlise les distributeurs avec les bacs et les produits
 */
void IHMJustFeed::initialiserDistributeurs()
{
    distributeurs.push_back(new Distributeur("distributeur-1-sim",
                                             { "44.11161", "4.84856", "0" },
                                             "Grand Frais",
                                             "Distributeur de fruits secs",
                                             "Zone du Coudoulet Rond point du Péage Sud",
                                             "84100",
                                             "Orange",
                                             QDate::fromString("2022-01-08", "yyyy-MM-dd")));
    distributeurs.push_back(new Distributeur("distributeur-2-sim",
                                             { "43.92844", "4.79247", "0" },
                                             "Carrefour",
                                             "Distributeur de fruits secs",
                                             "390 Rue Jean Marie Tjibaou",
                                             "84000",
                                             "Avignon",
                                             QDate::fromString("2022-03-09", "yyyy-MM-dd")));
    distributeurs.push_back(new Distributeur("distributeur-3",
                                             { "43.90252", "4.75280", "0" },
                                             "Cosy Primeurs",
                                             "Distributeur de fruits secs",
                                             "292 Route de Boulbon",
                                             "13570",
                                             "Barbentane",
                                             QDate::fromString("2022-01-10", "yyyy-MM-dd")));

    Produit* pruneaux    = new Produit("pruneaux",
                                    "Maître Prunille",
                                    "Les Pruneaux d'Agen dénoyautés Maître Prunille sont une "
                                       "délicieuse friandise à déguster à tout moment de la journée.",
                                    "761234567890",
                                    1.15);
    Produit* abricot     = new Produit("Abricots secs",
                                   "Maître Prunille",
                                   "L'abricot moelleux, une gourmandise tendre et fruitée !",
                                   "761234566000",
                                   1.13);
    Produit* cranberries = new Produit("Cranberries",
                                       "SEEBERGER",
                                       "Cranberries tranchées sucrées séchées",
                                       "761234569000",
                                       2.1);
    Produit* banane =
      new Produit("Banane CHIPS", " BIO VILLAGE", "Banane CHIPS bio ", "761234560008", 0.76);
    Produit* raisin    = new Produit("Raisin sec",
                                  "Petit Prix",
                                  "Raisins secs, huile végétale (graine de coton)",
                                  "761264569090",
                                  0.39);
    Produit* fruitsSec = new Produit("fruits sec",
                                     "FRUIDYLLIC",
                                     "Peut se manger tel que sans préparation.",
                                     "761234960940",
                                     1.06);
    Produit* cacahuete =
      new Produit("Cacahuète",
                  "Carrefour",
                  "Arachide crue blanche décortiquée pour cuisiner ou pâtisserie",
                  "761234561000",
                  0.49);
    Produit* soja = new Produit("Soja", "OFAL BIO", "SOJA jaune biologique.", "761234529000", 0.96);
    Produit* basilic = new Produit("Basilic",
                                   "DUCROS",
                                   "Basilic déshydraté issu de l'agriculture biologique",
                                   "761234679900",
                                   17.18);

    distributeurs[0]->ajouterBac(Bac(pruneaux, 0, 0.));
    distributeurs[0]->ajouterBac(Bac(abricot, 0, 0.));
    distributeurs[0]->ajouterBac(Bac(cranberries, 0, 0.));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[0]->getNom() << "NbBacs"
             << distributeurs[0]->getNbBacs();
    distributeurs[1]->ajouterBac(Bac(banane, 0, 0.));
    distributeurs[1]->ajouterBac(Bac(raisin, 0, 0.));
    distributeurs[1]->ajouterBac(Bac(fruitsSec, 0, 0.));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[1]->getNom() << "NbBacs"
             << distributeurs[1]->getNbBacs();
    distributeurs[2]->ajouterBac(Bac(cacahuete, 0, 0.));
    distributeurs[2]->ajouterBac(Bac(soja, 0, 0.));
    distributeurs[2]->ajouterBac(Bac(basilic, 0, 0.));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[2]->getNom() << "NbBacs"
             << distributeurs[2]->getNbBacs();

    numeroDistributeurSelectionne = 0; // pour les tests
}
