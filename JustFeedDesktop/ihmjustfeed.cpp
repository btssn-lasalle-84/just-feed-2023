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
#include "basededonnees.h"

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
 * @brief méthode qui affiche la fenetre
 */
void IHMJustFeed::afficherFenetreIntervention()
{
    afficherFenetre(IHMJustFeed::Fenetre::FIntervention);
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
    recupererDistributeursAIntervenir();
    // aucun distributeur sélectionné ?
    if(listeDistributeursAIntervenir.size() < 1)
        return;
    // crée et affiche la boîte de dialogue
    if(intervention == nullptr)
    {
        intervention = new Intervention(listeDistributeursAIntervenir, this);
    }
    else
        return;
    intervention->exec();
    delete intervention;
    intervention = nullptr;
    effacerDistributeursAIntervenir();
    boutonPlanifier->setEnabled(false);
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

/**
 * @brief méthode qui sélectionne le distributeur pour l'affichage
 */
void IHMJustFeed::selectionnerDistributeur(QTableWidgetItem* item)
{
    QTableWidgetItem* nomDistributeur;
    nomDistributeur = tableWidgetDistributeurs->item(item->row(), COLONNE_DISTRIBUTEUR_NOM);
    qDebug() << Q_FUNC_INFO << "distributeur"
             << getDistributeur(nomDistributeur->data(0).toString())->getNom();
    afficherDistributeur(getDistributeur(nomDistributeur->data(0).toString()));
}

void IHMJustFeed::selectionnerDistributeurAIntervenir(QTableWidgetItem* item)
{
    if(item->column() == COLONNE_DISTRIBUTEUR_INTERVENTION)
    {
        if(recupererDistributeursAIntervenir())
            boutonPlanifier->setEnabled(true);
        else
            boutonPlanifier->setEnabled(false);
    }
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
    boutonPlanifier  = new QPushButton("Planifier", this);
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
    initialiserTable();

    // Les listes
    for(int i = 0; i < distributeurs.size(); i++)
    {
        listeDistributeurs->addItem(distributeurs[i]->getNom());
    }
    if(distributeurs.size() < 1)
        boutonConfigurer->setEnabled(false);
    if(recupererDistributeursAIntervenir())
        boutonPlanifier->setEnabled(true);
    else
        boutonPlanifier->setEnabled(false);
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
    layoutBoutonsAccueil->addWidget(boutonPlanifier);
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
void IHMJustFeed::initialiserTable()
{
    tableWidgetDistributeurs = new QTableWidget(this);

    // Les colonnes
    nomColonnes << "Enseigne"
                << "Adresse"
                << "Ville"
                << "Code Postal"
                << "Intervention";

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
    /*connect(tableWidgetDistributeurs,
            SIGNAL(cellClicked(int, int)),
            this,
            SLOT(selectionnerDistributeur(int, int)));*/
    connect(tableWidgetDistributeurs,
            SIGNAL(itemPressed(QTableWidgetItem*)),
            this,
            SLOT(selectionnerDistributeur(QTableWidgetItem*)));
    connect(tableWidgetDistributeurs,
            SIGNAL(itemClicked(QTableWidgetItem*)),
            this,
            SLOT(selectionnerDistributeurAIntervenir(QTableWidgetItem*)));
    connect(listeDistributeurs,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(selectionnerDistributeur(int)));
    connect(boutonConfigurer, SIGNAL(clicked()), this, SLOT(configurerDistributeur()));
    connect(boutonPlanifier, SIGNAL(clicked()), this, SLOT(planifierIntervention()));
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
                                             "Grand Frais",
                                             "Zone du Coudoulet Rond point du Péage Sud",
                                             "84100",
                                             "Orange",
                                             "Distributeur de fruits secs",
                                             QDate::fromString("2022-01-08", "yyyy-MM-dd"),
                                             { "44.11161", "4.84856", "0" }));
    distributeurs.push_back(new Distributeur("distributeur-2-sim",
                                             "Carrefour",
                                             "390 Rue Jean Marie Tjibaou",
                                             "84000",
                                             "Avignon",
                                             "Distributeur de fruits secs",
                                             QDate::fromString("2022-03-09", "yyyy-MM-dd"),
                                             { "43.92844", "4.79247", "0" }));
    distributeurs.push_back(new Distributeur("distributeur-3",
                                             "Cosy Primeurs",
                                             "292 Route de Boulbon",
                                             "13570",
                                             "Barbentane",
                                             "Distributeur de fruits secs",
                                             QDate::fromString("2022-01-10", "yyyy-MM-dd"),
                                             { "43.90252", "4.75280", "0" }));

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

    distributeurs[0]->setHygrometrie(25);
    distributeurs[0]->ajouterBac(Bac(pruneaux, 5, 10));
    distributeurs[0]->ajouterBac(Bac(abricot, 4.5, 15));
    distributeurs[0]->ajouterBac(Bac(cranberries, 3, 12));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[0]->getNom() << "NbBacs"
             << distributeurs[0]->getNbBacs();
    distributeurs[1]->setHygrometrie(18);
    distributeurs[1]->ajouterBac(Bac(banane, 0, 12));
    distributeurs[1]->ajouterBac(Bac(raisin, 0, 12));
    distributeurs[1]->ajouterBac(Bac(fruitsSec, 0, 12));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[1]->getNom() << "NbBacs"
             << distributeurs[1]->getNbBacs();
    distributeurs[2]->setHygrometrie(21);
    distributeurs[2]->ajouterBac(Bac(cacahuete, 9, 12));
    distributeurs[2]->ajouterBac(Bac(soja, 6, 12));
    distributeurs[2]->ajouterBac(Bac(basilic, 10.8, 12));
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
    qDebug() << Q_FUNC_INFO << distributeur.getNom();

    QFont texte;
    // texte.setPointSize(TAILLE_POLICE);
    texte.setBold(true);

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

    itemIntervention = new QTableWidgetItem();
    itemIntervention->setCheckState(Qt::Unchecked);
    itemIntervention->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    nbLignesDistributeurs += 1;
    qDebug() << Q_FUNC_INFO << "nbLignesDistributeur" << nbLignesDistributeurs;

    // Ajoute une nouvelle ligne
    tableWidgetDistributeurs->setRowCount(++nb);
    // Insère les informations dans la table
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_NOM, itemEnseigne);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_ADRESSE, itemAdresse);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_VILLE, itemVille);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_CODEPOSTAL, itemCodePostal);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_INTERVENTION, itemIntervention);

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

/**
 * @brief méthode qui détermine la liste des distributeurs à intervenir
 * @fn IHMJustFeed::recupererDistributeursAIntervenir
 * @return le nombre de distributeurs
 */
int IHMJustFeed::recupererDistributeursAIntervenir()
{
    listeDistributeursAIntervenir.clear();
    for(int i = 0; i < tableWidgetDistributeurs->rowCount(); ++i)
    {
        QTableWidgetItem* item =
          tableWidgetDistributeurs->item(i, COLONNE_DISTRIBUTEUR_INTERVENTION);
        if(item->checkState() == Qt::Checked)
        {
            qDebug() << Q_FUNC_INFO << distributeurs[i]->getNom();
            listeDistributeursAIntervenir.push_back(distributeurs[i]);
        }
    }
    return listeDistributeursAIntervenir.size();
}

void IHMJustFeed::effacerDistributeursAIntervenir()
{
    listeDistributeursAIntervenir.clear();
    for(int i = 0; i < tableWidgetDistributeurs->rowCount(); ++i)
    {
        tableWidgetDistributeurs->item(i, COLONNE_DISTRIBUTEUR_INTERVENTION)
          ->setCheckState(Qt::Unchecked);
    }
}
