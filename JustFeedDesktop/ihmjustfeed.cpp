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

IHMJustFeed::IHMJustFeed(QWidget* parent) : QMainWindow(parent)
{
    qDebug() << Q_FUNC_INFO;
    initialiserGUI();
    initialiserDistributeurs();
    IHMJustFeed::gererEvenements();
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

/**
 * @brief Méthode qui initialise la GUI
 */
void IHMJustFeed::initialiserGUI()
{
    qDebug() << Q_FUNC_INFO;
    instancierWigets();
    initialiserWigets();

    // La fenêtre principale
    setWindowTitle(TITRE_APPLICATION + " " + VERSION_APPLICATION);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    resize(screenGeometry.width(), screenGeometry.height());
}

/**
 * @brief Méthode qui instancie les widgets de la GUI
 */
void IHMJustFeed::instancierWigets()
{
    qDebug() << Q_FUNC_INFO;
    boutonQuitter    = new QPushButton("X", this);
    boutonIntervenir = new QPushButton("Intervenir", this);
    boutonConfigurer = new QPushButton("Configurer", this);

    deviceIDDistributeur      = new QLabel(this);
    positionDistributeur      = new QLabel(this);
    nomDistributeur           = new QLabel(this);
    adresseDistributeur       = new QLabel(this);
    codePostalDistributeur    = new QLabel(this);
    villeDistributeur         = new QLabel(this);
    miseEnServiceDistributeur = new QLabel(this);
}

/**
 * @brief Méthode qui initialise les widgets de la GUI
 */
void IHMJustFeed::initialiserWigets()
{
    boutonQuitter->setGeometry(1815, 0, 50, 100);
    boutonIntervenir->setGeometry(1650, 900, 100, 100);
    boutonConfigurer->setGeometry(1750, 900, 100, 100);

    qDebug() << Q_FUNC_INFO;
    gui                     = new QWidget(this);
    fenetres                = new QStackedWidget(this);
    QWidget* fenetreAccueil = new QWidget(this);
    fenetres->addWidget(fenetreAccueil);

    // La table
    positionnerWigets();

    // Les layouts
    QVBoxLayout* layoutPrincipal         = new QVBoxLayout();
    QVBoxLayout* layoutFenetrePrincipale = new QVBoxLayout();
    QHBoxLayout* layoutF1Table           = new QHBoxLayout();

    // Positionnement
    // La fenêtre accueil
    layoutF1Table->addWidget(tableWidgetDistributeurs);
    layoutFenetrePrincipale->addLayout(layoutF1Table);
    layoutFenetrePrincipale->addStretch();
    fenetreAccueil->setLayout(layoutFenetrePrincipale);
    layoutF1Table->setAlignment(Qt::AlignCenter);

    // La GUI
    layoutPrincipal->addWidget(fenetres);
    gui->setLayout(layoutPrincipal);
    setCentralWidget(gui);
}

/**
 * @brief Méthode qui positionne les widgets dans la GUI
 */
void IHMJustFeed::positionnerWigets()
{
    qDebug() << Q_FUNC_INFO;
    tableWidgetDistributeurs = new QTableWidget(this);

    // Les colonnes
    nomColonnes << "Device ID"
                << "Localisation"
                << "Nom"
                << "Adresse"
                << "Code postal"
                << "Ville"
                << "Mise en Service";

    tableWidgetDistributeurs->setColumnCount(nomColonnes.count());
    tableWidgetDistributeurs->setHorizontalHeaderLabels(nomColonnes);
    // Vide (pas de lignes donc pas d'utilisateurs dans la table)
    tableWidgetDistributeurs->setRowCount(0);
    nbLignesDistributeurs = 0;
    // Redimensionnement automatique (inutile)
    // tableWidgetDistributeurs->resizeColumnsToContents();
    // Pas d'étiquettes numérotées sur le côté gauche
    tableWidgetDistributeurs->verticalHeader()->setHidden(true);
    // Taille
    // tableWidgetDistributeurs->setMinimumSize(QSize(0, 0));
    // Prend toute la largeur
    tableWidgetDistributeurs->setMinimumWidth(gui->width());
    // Hauteur fixe ?
    // tableWidgetDistributeurs->setMinimumHeight(gui->height());
    /*cf. setFixedSize()*/
    tableWidgetDistributeurs->setFixedHeight(
      tableWidgetDistributeurs->verticalHeader()->length() +
      tableWidgetDistributeurs->horizontalHeader()->height());
    // Largeur automatique des colonnes sur toute la largeur
    QHeaderView* headerView = tableWidgetDistributeurs->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    // Pas de scroll
    tableWidgetDistributeurs->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidgetDistributeurs->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

/**
 * @brief méthode qui initianlise les distributeurs avec les bacs et les produits
 */
void IHMJustFeed::initialiserDistributeurs()
{
    distributeurs.push_back(new Distributeur("distributeur-1-sim",
                                             { "44.11161", "4.84856" },
                                             "Grand Frais",
                                             "Distributeur de fruits secs",
                                             "Zone du Coudoulet Rond point du Péage Sud",
                                             "84100",
                                             "Orange",
                                             QDate::fromString("2022-01-08", "yyyy-MM-dd")));
    distributeurs.push_back(new Distributeur("distributeur-2-sim",
                                             { "43.92844", "4.79247" },
                                             "Carrefour",
                                             "Distributeur de fruits secs",
                                             "390 Rue Jean Marie Tjibaou",
                                             "84000",
                                             "Avignon",
                                             QDate::fromString("2022-03-09", "yyyy-MM-dd")));
    distributeurs.push_back(new Distributeur("distributeur-3",
                                             { "43.90252", "4.75280" },
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

    /**
     * @todo Pour chaque distributeur, l'afficher dans la table
     */
    qDebug() << Q_FUNC_INFO << "Nb salles" << distributeurs.size();

    for(int i = 0; i < distributeurs.size(); ++i)

    {
        afficherDistributeurTable(*distributeurs.at(i));
    }
}

/**
 * @brief méthode qui affiche les fenetres
 */
void IHMJustFeed::afficherFenetre(IHMJustFeed::Fenetre fenetre)
{
    fenetres->setCurrentIndex(fenetre);
}

/**
 * @brief méthode qui affiche la fenetre principale
 */

void IHMJustFeed::afficherFenetreAccueil()
{
    afficherFenetre(IHMJustFeed::Fenetre::Accueil);
}

/**
 * @brief méthode qui efface le tableau
 */

void IHMJustFeed::effacerTableau(int ligne, int colonne)
{
    Q_UNUSED(ligne)
    Q_UNUSED(colonne)
    // on réinitialise la table
    int nb = tableWidgetDistributeurs->rowCount();
    if(nb != 0)
    {
        // on les efface
        for(int n = 0; n < nb; n++)
            tableWidgetDistributeurs->removeRow(0);
    }
}

/**
 * @brief Efface le QTableWidget
 *
 * @fn IHM::effacerTableUtilisateurs
 */

void IHMJustFeed::effacerTableDistributeurs()
{
    qDebug() << Q_FUNC_INFO;

    effacerTableau(0, 0);
    nbLignesDistributeurs = 0;
}

void IHMJustFeed::afficherDistributeurTable(Distributeur distributeur)
{
    qDebug() << Q_FUNC_INFO << "nom";

    QFont texte;
    // texte.setPointSize(TAILLE_POLICE);
    texte.setBold(true);

    QTableWidgetItem *itemDeviceId, *itemNom, *itemPosition, *itemAdresse, *itemCodePostal,
      *itemVille, *itemMiseEnService;

    // Le nombre d'utilisateurs déjà présents dans la table
    int nb = tableWidgetDistributeurs->rowCount();

    // Affiche les informations dans la table
    itemDeviceId = new QTableWidgetItem(distributeur.getdeviceID());
    // Personnalise un item
    itemDeviceId->setFlags(Qt::ItemIsEnabled);
    itemDeviceId->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemDeviceId->setFont(texte);

    itemNom = new QTableWidgetItem(distributeur.getNom());
    // Personnalise un item
    itemNom->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemNom->setFont(texte);

    /* itemPosition = new QTableWidgetItem(distributeur.getPosition());
     itemPosition->setFlags(Qt::ItemIsEnabled);
     itemPosition->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
     itemPosition->setFont(texte);
 */
    itemAdresse = new QTableWidgetItem(distributeur.getAdresse());
    itemAdresse->setFlags(Qt::NoItemFlags);
    itemAdresse->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    itemCodePostal = new QTableWidgetItem(distributeur.getCodePostal());
    itemCodePostal->setFlags(Qt::NoItemFlags);
    itemCodePostal->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    itemVille = new QTableWidgetItem(distributeur.getVille());
    itemVille->setFlags(Qt::NoItemFlags);
    itemVille->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    /* itemMiseEnService = new QTableWidgetItem(distributeur.getDateMiseService());
     itemMiseEnService->setFlags(Qt::NoItemFlags);
     itemMiseEnService->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
 */
    nbLignesDistributeurs += 1;
    qDebug() << Q_FUNC_INFO << "nbLignesDistributeur" << nbLignesDistributeurs;

    // Ajoute une nouvelle ligne
    tableWidgetDistributeurs->setRowCount(++nb);
    // Insère les informations dans la table
    tableWidgetDistributeurs->setItem(nb - 1, 0, itemDeviceId);
    tableWidgetDistributeurs->setItem(nb - 1, 1, itemNom);
    tableWidgetDistributeurs->setItem(nb - 1, 2, itemPosition);
    tableWidgetDistributeurs->setItem(nb - 1, 3, itemAdresse);
    tableWidgetDistributeurs->setItem(nb - 1, 4, itemCodePostal);
    tableWidgetDistributeurs->setItem(nb - 1, 5, itemVille);
    tableWidgetDistributeurs->setItem(nb - 1, 6, itemMiseEnService);

    // Se replace au début de la table
    tableWidgetDistributeurs->scrollToItem(tableWidgetDistributeurs->item(0, 1));
    tableWidgetDistributeurs->setCurrentCell(0, 1);

    // La hauteur a changé !
    tableWidgetDistributeurs->setFixedHeight(
      tableWidgetDistributeurs->verticalHeader()->length() +
      tableWidgetDistributeurs->horizontalHeader()->height());
}

/**
 * @brief Assure la connexion des signaux et slots
 *
 * @fn IHM::gererEvenements
 */
void IHMJustFeed::gererEvenements()
{
    connect(boutonQuitter, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
}
