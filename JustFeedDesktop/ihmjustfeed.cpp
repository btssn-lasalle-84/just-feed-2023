/**
 * @file        ihmjustfeed.cpp
 * @brief       Définition de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @author      Rouanet Nicolas
 * @version     0.1
 * @date        2023
 */

#include "ihmjustfeed.h"
#include "distributeur.h"
#include "produit.h"
#include "bac.h"
#include "configurationdistributeur.h"
#include "intervention.h"

/**
 * @brief constructeur par défaut de la classe IHMJustFeed
 */
IHMJustFeed::IHMJustFeed(QWidget* parent) :
    QWidget(parent), configurationDistributeur(nullptr), intervention(nullptr)
{
    qDebug() << Q_FUNC_INFO;
    initialiserDistributeurs();
    initialiserProduits();
    initialiserGUI();
    chargerDistributeurs();
}

/**
 * @brief destructeur de la classe IHMJustFeed
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
 * @brief méthode qui retourne le distributeur dont le nom est passé en paramètre
 */
Distributeur* IHMJustFeed::getDistributeur(QString nom) const
{
    for(int i = 0; i < distributeurs.size(); ++i)
    {
        if(distributeurs[i]->getNom() == nom)
            return distributeurs[i];
    }
    return nullptr;
}

/**
 * @brief méthode qui retourne le produit
 */
Produit* IHMJustFeed::getProduit(int index) const
{
    return produits[index];
}

/**
 * @brief méthode qui retourne le nom du produit
 */
QString IHMJustFeed::getNomProduit(int index) const
{
    return produits[index]->getNom();
}

/**
 * @brief méthode qui retourne le prix de produit
 */
double IHMJustFeed::getPrixProduit(int index) const
{
    return produits[index]->getPrix();
}

/**
 * @brief méthode qui retourne le nombre de produits disponibles
 */
int IHMJustFeed::getNbProduits() const
{
    return produits.size();
}

// Slots

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
    afficherFenetre(IHMJustFeed::Fenetre::FAccueil);
}

/**
 * @brief méthode qui affiche la fenetre d'un distributeur
 */
void IHMJustFeed::afficherFenetreDistributeur()
{
    afficherFenetre(IHMJustFeed::Fenetre::FDistributeur);
}

/**
 * @brief méthode qui configure un distributeur
 */
void IHMJustFeed::configurerDistributeur()
{
    if(configurationDistributeur == nullptr)
    {
        if(numeroDistributeurSelectionne != -1)
            configurationDistributeur =
              new ConfigurationDistributeur(distributeurs[numeroDistributeurSelectionne], this);
        else
            return;
    }
    else
        return;
    configurationDistributeur->exec();
    delete configurationDistributeur;
    configurationDistributeur = nullptr;
}

/**
 * @brief méthode qui planifie une intervention
 */
void IHMJustFeed::planifierIntervention()
{
    qDebug() << Q_FUNC_INFO;
    if(intervention == nullptr)
    {
        intervention = new Intervention(this);
    }
    else
        return;
    intervention->exec();
    delete intervention;
    intervention = nullptr;
}

/**
 * @brief méthode qui sélectionne un distributeur à configurer
 */
void IHMJustFeed::selectionnerDistributeur(int numeroDistributeur)
{
    qDebug() << Q_FUNC_INFO << "numeroDistributeur" << numeroDistributeur;
    numeroDistributeurSelectionne = numeroDistributeur;
}

/**
 * @brief méthode qui sélectionne le distributeur pour l'affichage
 */
void IHMJustFeed::selectionnerDistributeur(int ligne, int colonne)
{
    Q_UNUSED(colonne)
    QTableWidgetItem* nomDistributeur;
    nomDistributeur = tableWidgetDistributeurs->item(ligne, COLONNE_DISTRIBUTEUR_NOM);
    qDebug() << Q_FUNC_INFO << "distributeur"
             << getDistributeur(nomDistributeur->data(0).toString())->getNom();
    afficherDistributeur(getDistributeur(nomDistributeur->data(0).toString()));
}

// Méthodes privées

/**
 * @brief méthode qui initialise la GUI
 */
void IHMJustFeed::initialiserGUI()
{
    instancierWidgets();
    initialiserWidgets();
    positionnerWidgets();
    initialiserEvenements();

    // La fenêtre principale
    setWindowTitle(TITRE_APPLICATION + " " + VERSION_APPLICATION);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    resize(screenGeometry.width(), screenGeometry.height());
}

/**
 * @brief méthode qui instancie les widgets de la GUI
 */
void IHMJustFeed::instancierWidgets()
{
    // Les fenêtres
    gui                 = new QWidget(this);
    fenetres            = new QStackedWidget(this);
    fenetreAccueil      = new QWidget(this);
    fenetreDistributeur = new QWidget(this);

    // Les boutons
    boutonIntervenir = new QPushButton("Intervenir", this);
    boutonConfigurer = new QPushButton("Configurer", this);
    boutonValider    = new QPushButton("Valider", this);

    // Les labels
    nomDistributeur           = new QLabel(this);
    adresseDistributeur       = new QLabel(this);
    codePostalDistributeur    = new QLabel(this);
    villeDistributeur         = new QLabel(this);
    descriptionDistributeur   = new QLabel(this);
    miseEnServiceDistributeur = new QLabel(this);
    positionDistributeur      = new QLabel(this);

    // Les listes
    listeDistributeurs = new QComboBox(this);
}

/**
 * @brief méthode qui initialise les widgets de la GUI
 */
void IHMJustFeed::initialiserWidgets()
{
    // Les fenêtres
    fenetres->addWidget(fenetreAccueil);
    fenetres->addWidget(fenetreDistributeur);

    // La table
    initialiseTable();

    // Les listes
    for(int i = 0; i < distributeurs.size(); i++)
    {
        listeDistributeurs->addItem(distributeurs[i]->getNom());
    }
}

/**
 * @brief méthode qui positionne les widgets dans la GUI
 */
void IHMJustFeed::positionnerWidgets()
{
    // Les layouts
    QVBoxLayout* layoutPrincipal           = new QVBoxLayout();
    QVBoxLayout* layoutFenetrePrincipale   = new QVBoxLayout();
    QVBoxLayout* layoutFenetreDistributeur = new QVBoxLayout();
    QHBoxLayout* layoutF1Table             = new QHBoxLayout();
    QHBoxLayout* layoutBoutonsAccueil      = new QHBoxLayout();
    QHBoxLayout* layoutBoutonsDistributeur = new QHBoxLayout();

    // Positionnement
    // La fenêtre accueil
    layoutF1Table->addWidget(tableWidgetDistributeurs);
    layoutF1Table->setAlignment(Qt::AlignCenter);
    layoutBoutonsAccueil->addStretch();
    layoutBoutonsAccueil->addWidget(listeDistributeurs);
    layoutBoutonsAccueil->addWidget(boutonConfigurer);
    layoutBoutonsAccueil->addWidget(boutonIntervenir);
    layoutFenetrePrincipale->addLayout(layoutF1Table);
    layoutFenetrePrincipale->addLayout(layoutBoutonsAccueil);
    layoutFenetrePrincipale->addStretch();
    fenetreAccueil->setLayout(layoutFenetrePrincipale);

    // La fenêtre distributeur
    layoutFenetreDistributeur->addWidget(nomDistributeur);
    layoutFenetreDistributeur->addWidget(adresseDistributeur);
    layoutFenetreDistributeur->addWidget(codePostalDistributeur);
    layoutFenetreDistributeur->addWidget(villeDistributeur);
    layoutFenetreDistributeur->addWidget(descriptionDistributeur);
    layoutFenetreDistributeur->addWidget(miseEnServiceDistributeur);
    layoutFenetreDistributeur->addWidget(positionDistributeur);
    layoutBoutonsDistributeur->addStretch();
    layoutBoutonsDistributeur->addWidget(boutonValider);
    layoutFenetreDistributeur->addLayout(layoutBoutonsDistributeur);
    fenetreDistributeur->setLayout(layoutFenetreDistributeur);

    // La GUI
    layoutPrincipal->addWidget(fenetres);
    gui->setLayout(layoutPrincipal);
    this->setLayout(layoutPrincipal);
}

/**
 * @brief méthode qui initialise le QTableWidget
 */
void IHMJustFeed::initialiseTable()
{
    tableWidgetDistributeurs = new QTableWidget(this);

    // Les colonnes
    nomColonnes << "Enseigne"
                << "Adresse"
                << "Ville"
                << "Code Postal";

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
 * @brief méthode qui initialise les connexion signal/slot
 */
void IHMJustFeed::initialiserEvenements()
{
    connect(tableWidgetDistributeurs,
            SIGNAL(cellClicked(int, int)),
            this,
            SLOT(selectionnerDistributeur(int, int)));
    connect(listeDistributeurs,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(selectionnerDistributeur(int)));
    connect(boutonConfigurer, SIGNAL(clicked()), this, SLOT(configurerDistributeur()));
    connect(boutonIntervenir, SIGNAL(clicked()), this, SLOT(planifierIntervention()));
    connect(boutonValider, SIGNAL(clicked()), this, SLOT(afficherFenetreAccueil()));
}

/**
 * @brief méthode qui initialise les distributeurs avec les bacs et les produits
 */
void IHMJustFeed::initialiserDistributeurs()
{
    /**
     * @todo Récupérer les données depuis la base de données
     */
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

    Produit* pruneaux    = new Produit("Pruneaux",
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

    produits.push_back(pruneaux);
    produits.push_back(abricot);
    produits.push_back(cranberries);
    produits.push_back(banane);
    produits.push_back(raisin);
    produits.push_back(fruitsSec);
    produits.push_back(cacahuete);
    produits.push_back(soja);
    produits.push_back(basilic);

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

/**
 * @brief méthode qui initialise les différents produits disponibles
 */
void IHMJustFeed::initialiserProduits()
{
    /**
     * @todo Récupérer les données depuis la base de données
     */
}

/**
 * @brief méthode qui charge et affiche les distributeurs disponibles
 */
void IHMJustFeed::chargerDistributeurs()
{
    for(int i = 0; i < distributeurs.size(); ++i)
    {
        afficherDistributeurTable(*distributeurs.at(i));
    }
}

/**
 * @brief méthode qui affiche un distributeur dans le QTableWidget
 * @fn IHMJustFeed::afficherDistributeurTable
 */
void IHMJustFeed::afficherDistributeurTable(const Distributeur& distributeur)
{
    qDebug() << Q_FUNC_INFO << "nom";

    QFont texte;
    // texte.setPointSize(TAILLE_POLICE);
    texte.setBold(true);

    QTableWidgetItem *itemEnseigne, *itemAdresse, *itemVille, *itemCodePostal;

    // Le nombre d'utilisateurs déjà présents dans la table
    int nb = tableWidgetDistributeurs->rowCount();

    // Affiche les informations dans la table
    itemEnseigne = new QTableWidgetItem(distributeur.getNom());
    // Personnalise un item
    itemEnseigne->setFlags(Qt::ItemIsEnabled);
    itemEnseigne->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    itemAdresse = new QTableWidgetItem(distributeur.getAdresse());
    itemAdresse->setFlags(Qt::ItemIsEnabled);
    itemAdresse->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    itemVille = new QTableWidgetItem(distributeur.getVille());
    itemVille->setFlags(Qt::ItemIsEnabled);
    itemVille->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    itemCodePostal = new QTableWidgetItem(distributeur.getCodePostal());
    itemCodePostal->setFlags(Qt::ItemIsEnabled);
    itemCodePostal->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    nbLignesDistributeurs += 1;
    qDebug() << Q_FUNC_INFO << "nbLignesDistributeur" << nbLignesDistributeurs;

    // Ajoute une nouvelle ligne
    tableWidgetDistributeurs->setRowCount(++nb);
    // Insère les informations dans la table
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_NOM, itemEnseigne);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_ADRESSE, itemAdresse);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_VILLE, itemVille);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_CODEPOSTAL, itemCodePostal);

    // Se replace au début de la table
    tableWidgetDistributeurs->scrollToItem(tableWidgetDistributeurs->item(0, 1));
    tableWidgetDistributeurs->setCurrentCell(0, 1);

    // La hauteur a changé !
    tableWidgetDistributeurs->setFixedHeight(
      tableWidgetDistributeurs->verticalHeader()->length() +
      tableWidgetDistributeurs->horizontalHeader()->height());
}

/**
 * @brief méthode qui affiche les détails d'un distributeur
 */
void IHMJustFeed::afficherDistributeur(Distributeur* distributeur)
{
    /**
     * @todo Afficher un distributeur
     */
    // pour les tests
    nomDistributeur->setText(distributeur->getNom());
    adresseDistributeur->setText(distributeur->getAdresse());
    codePostalDistributeur->setText(distributeur->getCodePostal());
    villeDistributeur->setText(distributeur->getVille());
    descriptionDistributeur->setText(distributeur->getDescription());
    miseEnServiceDistributeur->setText("");
    positionDistributeur->setText("");
    afficherFenetreDistributeur();
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
 * @brief méthode qui efface le QTableWidget
 * @fn IHMJustFeed::effacerTableDistributeurs
 */

void IHMJustFeed::effacerTableDistributeurs()
{
    qDebug() << Q_FUNC_INFO;

    effacerTableau(0, 0);
    nbLignesDistributeurs = 0;
}
