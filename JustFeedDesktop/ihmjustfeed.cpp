/**
 * @file        ihmjustfeed.cpp
 * @brief       Définition de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @author      Rouanet Nicolas
 * @version     0.2
 * @date        2023
 */

#include "ihmjustfeed.h"
#include "basededonnees.h"
#include "configurationdistributeur.h"
#include "distributeur.h"
#include "intervention.h"
#include "planificationintervention.h"
#include "bac.h"
#include "produit.h"
#include "operateur.h"
#include "communication.h"

/**
 * @brief constructeur par défaut de la classe IHMJustFeed
 */
IHMJustFeed::IHMJustFeed(QWidget* parent) :
    QWidget(parent), baseDeDonnees(BaseDeDonnees::getInstance()),
    configurationDistributeur(nullptr), planificationIntervention(nullptr),
    numeroDistributeurSelectionne(-1), nbLignesDistributeurs(0)
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonnees->connecter();
    initialiserProduits();
    initialiserDistributeurs();
    initialiserOperateurs();
    initialiserInterventions();
    initialiserGUI();
    chargerListeOperateurs();
    chargerDistributeurs();
    initialiserCommunication();
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
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

// Méthodes publiques

/**
 * @brief retourne le distributeur dont le nom est passé en
 * paramètre
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
 * @brief retourne le produit
 */
Produit* IHMJustFeed::getProduit(int index) const
{
    return produits[index];
}

/**
 * @brief retourne le nom du produit
 */
QString IHMJustFeed::getNomProduit(int index) const
{
    return produits[index]->getNom();
}

/**
 * @brief retourne le prix de produit
 */
double IHMJustFeed::getPrixProduit(int index) const
{
    return produits[index]->getPrix();
}

/**
 * @brief retourne le nombre de produits disponibles
 */
int IHMJustFeed::getNbProduits() const
{
    return produits.size();
}

// Slots

/**
 * @brief affiche une fenetre
 */
void IHMJustFeed::afficherFenetre(IHMJustFeed::Fenetre fenetre)
{
    fenetres->setCurrentIndex(fenetre);
}

/**
 * @brief affiche la fenetre principale
 */
void IHMJustFeed::afficherFenetreAccueil()
{
    metAJourLesInformationsIntervention();
    afficherFenetre(IHMJustFeed::Fenetre::FAccueil);
}

/**
 * @brief affiche la fenetre d'un distributeur
 */
void IHMJustFeed::afficherFenetreDistributeur()
{
    afficherFenetre(IHMJustFeed::Fenetre::FDistributeur);
}

/**
 * @brief affiche la fenetre intervention
 */
void IHMJustFeed::afficherFenetreIntervention()
{
    qDebug() << Q_FUNC_INFO;
    afficherFenetre(IHMJustFeed::Fenetre::FIntervention);
}

/**
 * @brief configure un distributeur
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
 * @brief planifie une intervention
 */
void IHMJustFeed::planifierIntervention()
{
    qDebug() << Q_FUNC_INFO;
    recupererDistributeursAIntervenir();
    // aucun distributeur sélectionné ?
    if(listeDistributeursAIntervenir.size() < 1)
        return;
    // crée et affiche la boîte de dialogue
    if(planificationIntervention == nullptr)
    {
        planificationIntervention =
          new PlanificationIntervention(listeDistributeursAIntervenir, this);
    }
    else
        return;
    planificationIntervention->exec();
    delete planificationIntervention;
    planificationIntervention = nullptr;
    effacerDistributeursAIntervenir();
    boutonPlanifier->setEnabled(false);
}

/**
 * @brief sélectionne un distributeur à configurer
 */
void IHMJustFeed::selectionnerDistributeur(int numeroDistributeur)
{
    qDebug() << Q_FUNC_INFO << "numeroDistributeur" << numeroDistributeur;
    numeroDistributeurSelectionne = numeroDistributeur;
}

/**
 * @brief sélectionne le distributeur pour l'affichage
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
 * @brief sélectionne le distributeur pour l'affichage
 */
void IHMJustFeed::selectionnerDistributeur(QTableWidgetItem* item)
{
    if(item->column() <= COLONNE_DISTRIBUTEUR_CODEPOSTAL)
    {
        QTableWidgetItem* nomDistributeur;
        nomDistributeur = tableWidgetDistributeurs->item(item->row(), COLONNE_DISTRIBUTEUR_NOM);
        qDebug() << Q_FUNC_INFO << "ligne" << item->row() << "colonne" << item->column()
                 << "distributeur"
                 << getDistributeur(nomDistributeur->data(0).toString())->getNom();
        afficherDistributeur(getDistributeur(nomDistributeur->data(0).toString()));
    }
    else if(item->column() == COLONNE_DISTRIBUTEUR_INTERVENTION_DETAIL)
    {
        QTableWidgetItem* nomDistributeur;
        nomDistributeur = tableWidgetDistributeurs->item(item->row(), COLONNE_DISTRIBUTEUR_NOM);
        qDebug() << Q_FUNC_INFO << "ligne" << item->row() << "colonne" << item->column()
                 << "distributeur"
                 << getDistributeur(nomDistributeur->data(0).toString())->getNom();
        afficherIntervention(getDistributeur(nomDistributeur->data(0).toString()));
    }
}

/**
 * @brief sélectionne le distributeur pour intervenir
 */
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

/**
 * @brief affiche ou cache la carte
 */
void IHMJustFeed::afficherCarte()
{
    qDebug() << Q_FUNC_INFO;
    vueCarte->setVisible(!vueCarte->isVisible());
    if(vueCarte->isVisible())
        boutonAfficherCarte->setText("Masquer la carte");
    else
        boutonAfficherCarte->setText("Afficher la carte");
}

/**
 * @brief imprime une intervention
 */
void IHMJustFeed::imprimerIntervention()
{
    qDebug() << Q_FUNC_INFO;
    QPrinter imprimer;
       QPrintDialog printDialog(&imprimer);
       if (printDialog.exec() == QDialog::Accepted) {
           QPainter peinture(&imprimer);
           fenetreIntervention->render(&peinture);
           peinture.end();
       }
}

// Méthodes privées

/**
 * @brief initialise la GUI
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
 * @brief instancie les widgets de la GUI
 */
void IHMJustFeed::instancierWidgets()
{
    // Les fenêtres
    gui                 = new QWidget(this);
    fenetres            = new QStackedWidget(this);
    fenetreAccueil      = new QWidget(this);
    fenetreDistributeur = new QWidget(this);
    fenetreIntervention = new QWidget(this);

    // Les boutons
    boutonPlanifier           = new QPushButton("Planifier", this);
    boutonConfigurer          = new QPushButton("Configurer", this);
    boutonValiderDistributeur = new QPushButton("Valider", this);
    boutonValiderIntervention = new QPushButton("Valider", this);
    boutonAfficherCarte       = new QPushButton("Afficher la carte", this);

    // Les labels
    nomDistributeur             = new QLabel(this);
    adresseDistributeur         = new QLabel(this);
    villeDistributeur           = new QLabel(this);
    descriptionDistributeur     = new QLabel(this);
    miseEnServiceDistributeur   = new QLabel(this);
    positionDistributeur        = new QLabel(this);
    interventionNomOperateur     = new QLabel(this);
    interventionNomDistributeur = new QLabel(this);
    dateIntervention            = new QLabel(this);
    aRemplirIntervention        = new QLabel(this);
    aDepannerIntervention       = new QLabel(this);
    etatIntervention            = new QLabel(this);
    nouveauOperateur            = new QComboBox(this);
    nouvelleDateIntervention    = new QDateEdit(this);
    boutonImpression            = new QPushButton(this);

    // Les layouts
    layoutIntervention             = new QHBoxLayout();
    layoutBoutonsInterventions     = new QHBoxLayout();
    layoutInformationsIntervention = new QVBoxLayout();

    // La vue pour la carte
    vueCarte = new QWebView(this);

    // Les listes
    listeDistributeurs = new QComboBox(this);
}

/**
 * @brief initialise les widgets de la GUI
 */
void IHMJustFeed::initialiserWidgets()
{
    // Les fenêtres
    fenetres->addWidget(fenetreAccueil);
    fenetres->addWidget(fenetreDistributeur);
    fenetres->addWidget(fenetreIntervention);

    // La table
    initialiserTable();

    // Les listes
    for(int i = 0; i < distributeurs.size(); i++)
    {
        listeDistributeurs->addItem(distributeurs[i]->getNom());
    }

    // Le bouton configurer
    if(distributeurs.size() < 1)
        boutonConfigurer->setEnabled(false);

    // Les distributeurs sélectionnés
    if(recupererDistributeursAIntervenir())
        boutonPlanifier->setEnabled(true);
    else
        boutonPlanifier->setEnabled(false);
}

/**
 * @brief initialise le QTableWidget des distributeurs
 */
void IHMJustFeed::initialiserTable()
{
    tableWidgetDistributeurs = new QTableWidget(this);

    // Les colonnes
    nomColonnes << "Enseigne"
                << "Adresse"
                << "Ville"
                << "Code Postal"
                << "Etat intervention "
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
 * @brief positionne les widgets dans la GUI
 */
void IHMJustFeed::positionnerWidgets()
{
    // Les layouts
    QVBoxLayout* layoutPrincipal           = new QVBoxLayout();
    QVBoxLayout* layoutFenetrePrincipale   = new QVBoxLayout();
    layoutFenetreDistributeur              = new QVBoxLayout();
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
    layoutBoutonsDistributeur->addWidget(boutonAfficherCarte);
    layoutBoutonsDistributeur->addWidget(boutonValiderDistributeur);
    layoutFenetreDistributeur->addLayout(layoutBoutonsDistributeur);
    fenetreDistributeur->setLayout(layoutFenetreDistributeur);
    // La GUI
    layoutPrincipal->addWidget(fenetres);
    gui->setLayout(layoutPrincipal);
    this->setLayout(layoutPrincipal);
}

/**
 * @brief initialise les connexions signal/slot
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
    connect(boutonValiderDistributeur, SIGNAL(clicked()), this, SLOT(afficherFenetreAccueil()));
    connect(boutonValiderIntervention, SIGNAL(clicked()), this, SLOT(afficherFenetreAccueil()));
    connect(boutonAfficherCarte, SIGNAL(clicked()), this, SLOT(afficherCarte()));
    connect(boutonImpression, SIGNAL(clicked()), this, SLOT(imprimerIntervention()));
}

/**
 * @brief initialise les distributeurs avec les bacs et les produits
 */
void IHMJustFeed::initialiserCommunication()
{
    QString     requete = "SELECT * FROM ServeurTTN;";
    QStringList infoCommunication;
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    baseDeDonnees->recuperer(requete, infoCommunication);
    bool estActif;
    if(infoCommunication[Communication::TableCommunication::EST_ACTIF] == "1")
    {
        estActif = true;
    }
    else
        estActif = false;
    communication = new Communication(
      infoCommunication[Communication::TableCommunication::ID_SERVEUR_TTN].toInt(),
      infoCommunication[Communication::TableCommunication::HOSTNAME_COMMUNICATION],
      infoCommunication[Communication::TableCommunication::PORT].toInt(),
      infoCommunication[Communication::TableCommunication::USERANME],
      infoCommunication[Communication::TableCommunication::PASSWORD_COMMUNICATION],
      infoCommunication[Communication::TableCommunication::APPLICATION_ID],
      estActif,
      this);
}

/**
 * @brief initialise les distributeurs avec les bacs et les produits
 */
void IHMJustFeed::initialiserDistributeurs()
{
    /*qDebug() << Q_FUNC_INFO << "SANS BDD";
    distributeurs.push_back(new Distributeur(1,
                                             "distributeur-1-sim",
                                             "Grand Frais",
                                             "Zone du Coudoulet Rond point du Péage Sud",
                                             "84100",
                                             "Orange",
                                             "Distributeur de fruits secs",
                                             QDate::fromString("2022-01-08", "yyyy-MM-dd"),
                                             { "44.11161", "4.84856", "0" }));
    distributeurs.push_back(new Distributeur(2,
                                             "distributeur-2-sim",
                                             "Carrefour",
                                             "390 Rue Jean Marie Tjibaou",
                                             "84000",
                                             "Avignon",
                                             "Distributeur de fruits secs",
                                             QDate::fromString("2022-03-09", "yyyy-MM-dd"),
                                             { "43.92844", "4.79247", "0" }));
    distributeurs.push_back(new Distributeur(3,
                                             "distributeur-3",
                                             "Cosy Primeurs",
                                             "292 Route de Boulbon",
                                             "13570",
                                             "Barbentane",
                                             "Distributeur de fruits secs",
                                             QDate::fromString("2022-01-10", "yyyy-MM-dd"),
                                             { "43.90252", "4.75280", "0" }));

    distributeurs[0]->ajouterBac(Bac(1, produits[0], 50, 50, 10));
    distributeurs[0]->ajouterBac(Bac(2, produits[1], 30, 100, 8));
    distributeurs[0]->ajouterBac(Bac(3, produits[2], 2, 30, 9));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[0]->getNom() << "NbBacs"
             << distributeurs[0]->getNbBacs();
    distributeurs[1]->ajouterBac(Bac(4, produits[3], 0, 12, 18));
    distributeurs[1]->ajouterBac(Bac(5, produits[4], 0, 12, 18));
    distributeurs[1]->ajouterBac(Bac(6, produits[5], 0, 12, 18));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[1]->getNom() << "NbBacs"
             << distributeurs[1]->getNbBacs();
    distributeurs[2]->ajouterBac(Bac(7, produits[6], 9, 12, 21));
    distributeurs[2]->ajouterBac(Bac(8, produits[7], 6, 12, 21));
    distributeurs[2]->ajouterBac(Bac(9, produits[8], 10.8, 12, 21));
    qDebug() << Q_FUNC_INFO << "Distributeur" << distributeurs[2]->getNom() << "NbBacs"
             << distributeurs[2]->getNbBacs();
    */
    qDebug() << Q_FUNC_INFO << "BDD";
    QString requete = "SELECT * FROM Distributeur";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    QStringList          distributeur;
    QVector<QStringList> distributeursRecuperes;
    bool                 retour;
    retour = baseDeDonnees->recuperer(requete, distributeursRecuperes);
    qDebug() << Q_FUNC_INFO << "distributeursRecuperes" << distributeursRecuperes;
    if(retour != false)
    {
        for(int i = 0; i < distributeursRecuperes.size(); i++)
        {
            distributeur                      = distributeursRecuperes.at(i);
            Distributeur* nouveauDistributeur = new Distributeur(distributeur);
            distributeurs.push_back(nouveauDistributeur);

            QString idDistributeur = distributeur.at(Distributeur::TableDistributeur::ID);
            requete                = "SELECT Bac.* FROM Bac "
                                     "WHERE Bac.idDistributeur='" +
                      idDistributeur + "'";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            QStringList          bac;
            QVector<QStringList> bacsRecuperes;
            retour = baseDeDonnees->recuperer(requete, bacsRecuperes);
            qDebug() << Q_FUNC_INFO << "bacsRecuperes" << bacsRecuperes;
            if(retour)
            {
                for(int j = 0; j < bacsRecuperes.size(); j++)
                {
                    bac              = bacsRecuperes.at(j);
                    Produit* produit = recupererProduit(bac.at(Bac::TableBac::ID_PRODUIT).toInt());
                    if(produit != nullptr)
                    {
                        Bac* nouveauBac = new Bac(bac, produit);
                        nouveauDistributeur->ajouterBac(*nouveauBac);
                    }
                }
            }
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "retour" << retour;
    }

    if(distributeurs.size() > 0)
        numeroDistributeurSelectionne = 0;
    qDebug() << Q_FUNC_INFO << "nbDistributeurs" << distributeurs.size();
}

/**
 * @brief méthode qui initialise les différents produits disponibles
 */
void IHMJustFeed::initialiserProduits()
{
    /*qDebug() << Q_FUNC_INFO << "SANS BDD";
    Produit* pruneaux    = new Produit(1,
                                    "Pruneaux",
                                    "Maître Prunille",
                                    "Les Pruneaux d'Agen dénoyautés Maître Prunille sont une "
                                    "délicieuse friandise à déguster à tout moment de la journée.",
                                    "761234567890",
                                    1.15);
    Produit* abricot     = new Produit(2,
                                   "Abricots secs",
                                   "Maître Prunille",
                                   "L'abricot moelleux, une gourmandise tendre et fruitée !",
                                   "761234566000",
                                   1.13);
    Produit* cranberries = new Produit(3,
                                       "Cranberries",
                                       "SEEBERGER",
                                       "Cranberries tranchées sucrées séchées",
                                       "761234569000",
                                       2.1);
    Produit* banane =
      new Produit(4, "Banane CHIPS", " BIO VILLAGE", "Banane CHIPS bio ", "761234560008", 0.76);
    Produit* raisin    = new Produit(5,
                                  "Raisin sec",
                                  "Petit Prix",
                                  "Raisins secs, huile végétale (graine de coton)",
                                  "761264569090",
                                  0.39);
    Produit* fruitsSec = new Produit(6,
                                     "fruits sec",
                                     "FRUIDYLLIC",
                                     "Peut se manger tel que sans préparation.",
                                     "761234960940",
                                     1.06);
    Produit* cacahuete =
      new Produit(7,
                  "Cacahuète",
                  "Carrefour",
                  "Arachide crue blanche décortiquée pour cuisiner ou pâtisserie",
                  "761234561000",
                  0.49);
    Produit* soja =
      new Produit(8, "Soja", "OFAL BIO", "SOJA jaune biologique.", "761234529000", 0.96);
    Produit* basilic = new Produit(9,
                                   "Basilic",
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

    */ qDebug() << Q_FUNC_INFO << "BDD";
    QString requete = "SELECT * FROM Produit";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    bool                 retour;
    QVector<QStringList> listeProduits;
    retour = baseDeDonnees->recuperer(requete, listeProduits);
    if(retour != false)
    {
        for(int i = 0; i < listeProduits.size(); i++)
        {
            Produit* nouveauProduit = new Produit(listeProduits.at(i));
            produits.push_back(nouveauProduit);
        }
    }

    qDebug() << Q_FUNC_INFO << "nbProduits" << produits.size();
}

/**
 * @brief méthode initialise les différents operateur
 */
void IHMJustFeed::initialiserOperateurs()
{
    operateurs.clear();
    QString requete = "SELECT * FROM Operateur";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    QVector<QStringList> operateursRecupereres;
    baseDeDonnees->recuperer(requete, operateursRecupereres);
    for(int i = 0; i < operateursRecupereres.size(); i++)
    {
        Operateur* operateur = new Operateur(operateursRecupereres[i]);
        operateurs.push_back(operateur);
    }
    qDebug() << Q_FUNC_INFO << "nbOperateurs" << operateurs.size();
}

/**
 * @brief méthode initialise les différentes interventions
 */
void IHMJustFeed::initialiserInterventions()
{
    interventions.clear();
    QVector<QStringList> interventionsBdd;
    QString              requete = "SELECT * FROM Intervention";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    baseDeDonnees->recuperer(requete, interventionsBdd);
    qDebug() << Q_FUNC_INFO << "interventionsBdd" << interventionsBdd.size();
    for(int i = 0; i < interventionsBdd.size(); i++)
    {
        bool aRemplir  = false;
        bool aDepanner = false;
        if(interventionsBdd[i][Intervention::TableIntervention::A_REMPLIR] == "1")
        {
            aRemplir = true;
        }
        if(interventionsBdd[i][Intervention::TableIntervention::A_DEPANNER] == "1")
        {
            aDepanner = true;
        }
        qDebug() << Q_FUNC_INFO
                 << interventionsBdd[i][Intervention::TableIntervention::DATE_INTERVENTION];
        interventions.push_back(new Intervention(
          interventionsBdd[i][Intervention::TableIntervention::ID].toInt(),
          interventionsBdd[i][Intervention::TableIntervention::ID_OPERATEUR].toInt(),
          interventionsBdd[i][Intervention::TableIntervention::ID_DISTRIBUTEUR].toInt(),
          QDate::fromString(interventionsBdd[i][Intervention::TableIntervention::DATE_INTERVENTION],
                            "yyyy-MM-dd"),
          aRemplir,
          aDepanner,
          interventionsBdd[i][Intervention::TableIntervention::ETAT]));
    }
    qDebug() << Q_FUNC_INFO << "interventions" << interventions.size();
}
/**
 * @brief charge et affiche les distributeurs disponibles
 */
void IHMJustFeed::chargerDistributeurs()
{
    for(int i = 0; i < distributeurs.size(); ++i)
    {
        afficherDistributeurTable(*distributeurs.at(i));
    }
}

/**
 * @brief affiche un distributeur dans le QTableWidget
 */
void IHMJustFeed::afficherDistributeurTable(const Distributeur& distributeur)
{
    qDebug() << Q_FUNC_INFO << "nom" << distributeur.getNom();

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
    QString infoIntervention;
    for(int i = 0; i < interventions.size(); i++)
    {
        if(distributeur.getId() == interventions[i]->getIdDistributeur())
        {
            infoIntervention = interventions[i]->getEtatFormate();
        }
    }

    itemDetailIntervention = new QTableWidgetItem(infoIntervention);
    itemDetailIntervention->setFlags(Qt::ItemIsEnabled);
    itemDetailIntervention->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    qDebug() << Q_FUNC_INFO << "nbLignesDistributeur" << nbLignesDistributeurs;

    // Ajoute une nouvelle ligne
    tableWidgetDistributeurs->setRowCount(++nb);
    // Insère les informations dans la table
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_NOM, itemEnseigne);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_ADRESSE, itemAdresse);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_VILLE, itemVille);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_CODEPOSTAL, itemCodePostal);
    tableWidgetDistributeurs->setItem(nb - 1,
                                      COLONNE_DISTRIBUTEUR_INTERVENTION_DETAIL,
                                      itemDetailIntervention);
    tableWidgetDistributeurs->setItem(nb - 1, COLONNE_DISTRIBUTEUR_INTERVENTION, itemIntervention);

    int nbBacs         = distributeur.getNbBacs();
    int maxRemplissage = MAX_REMPLISSAGE;

    for(int i = 0; i < nbBacs; i++)
    {
        int pourcentageRemplissage = distributeur.getBac(i)->getPourcentageRemplissage();

        if(pourcentageRemplissage < maxRemplissage)
        {
            maxRemplissage = pourcentageRemplissage;
        }
    }

    if(maxRemplissage < BAC_VIDE)
    {
        itemEnseigne->setBackgroundColor(Qt::red);
    }
    else if(maxRemplissage < BAC_MOITIE)
    {
        itemEnseigne->setBackgroundColor(Qt::yellow);
    }
    else
    {
        itemEnseigne->setBackgroundColor(Qt::green);
    }
    // Se replace au début de la table
    tableWidgetDistributeurs->scrollToItem(tableWidgetDistributeurs->item(0, 1));
    tableWidgetDistributeurs->setCurrentCell(0, 1);

    // La hauteur a changé !
    tableWidgetDistributeurs->setFixedHeight(
      tableWidgetDistributeurs->verticalHeader()->length() +
      tableWidgetDistributeurs->horizontalHeader()->height());
}

/**
 * @brief affiche les détails d'un distributeur
 * @param distributeur
 */
void IHMJustFeed::afficherDistributeur(Distributeur* distributeur)
{
    qDebug() << Q_FUNC_INFO << "nom" << distributeur->getNom();

    effacerEtatsFenetre();
    creerEtatDistributeur(distributeur);
    afficherFenetreDistributeur();
}

/**
 * @brief affiche les détails d'une intervention pour ce distributeur
 * @param distributeur
 */
void IHMJustFeed::afficherIntervention(Distributeur* distributeur)
{
    qDebug() << Q_FUNC_INFO << "nom" << distributeur->getNom();
    effacerEtatsFenetre();
    creerEtatIntervention(distributeur);
    afficherFenetreIntervention();
}

/**
 * @brief efface le contenu du QTableWidget des distributeurs
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
 * @brief initialise le contenu du QTableWidget des distributeurs
 * @fn IHMJustFeed::effacerTableDistributeurs
 */
void IHMJustFeed::effacerTableDistributeurs()
{
    qDebug() << Q_FUNC_INFO;

    effacerTableau(0, 0);
    nbLignesDistributeurs = 0;
}

/**
 * @brief détermine la liste des distributeurs à intervenir
 * @return int le nombre de distributeurs
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

/**
 * @brief efface la liste des distributeurs à intervenir
 */
void IHMJustFeed::effacerDistributeursAIntervenir()
{
    listeDistributeursAIntervenir.clear();
    for(int i = 0; i < tableWidgetDistributeurs->rowCount(); ++i)
    {
        tableWidgetDistributeurs->item(i, COLONNE_DISTRIBUTEUR_INTERVENTION)
          ->setCheckState(Qt::Unchecked);
    }
}

/**
 * @brief crée les widgets de la fenêtre d 'affichage d'un distributeur
 * @param distributeur le distributeur à afficher
 */
void IHMJustFeed::creerEtatDistributeur(Distributeur* distributeur)
{
    // La fenêtre distributeur
    QHBoxLayout* layoutDistributeur             = new QHBoxLayout();
    QVBoxLayout* layoutInformationsDistributeur = new QVBoxLayout();
    QVBoxLayout* layoutCarteDistributeur        = new QVBoxLayout();
    QHBoxLayout* layoutBoutonsDistributeur      = new QHBoxLayout();
    QGridLayout* layoutBacs                     = new QGridLayout();

    QFont texte;
    // texte.setPointSize(TAILLE_POLICE);
    texte.setBold(true);
    nomDistributeur->setFont(texte);
    layoutInformationsDistributeur->addWidget(nomDistributeur);
    layoutInformationsDistributeur->addWidget(descriptionDistributeur);
    layoutInformationsDistributeur->addWidget(adresseDistributeur);
    layoutInformationsDistributeur->addWidget(villeDistributeur);
    layoutInformationsDistributeur->addWidget(miseEnServiceDistributeur);
    layoutInformationsDistributeur->addWidget(positionDistributeur);

    layoutCarteDistributeur->addWidget(vueCarte);

    layoutBoutonsDistributeur->addStretch();
    layoutBoutonsDistributeur->addWidget(boutonAfficherCarte);
    layoutBoutonsDistributeur->addWidget(boutonValiderDistributeur);

    // les informations d'un distributeur
    nomDistributeur->setText(distributeur->getNom());
    adresseDistributeur->setText(distributeur->getAdresse());
    villeDistributeur->setText(distributeur->getCodePostal() + QString(" ") +
                               distributeur->getVille());
    descriptionDistributeur->setText(distributeur->getDescription());
    QDate   dateMiseService = distributeur->getDateMiseService();
    QString miseEnService =
      QString("Date de mise en service : %1").arg(dateMiseService.toString("dd/MM/yyyy"));
    QString localisation = QString("Localisation : %1°, %2°")
                             .arg(distributeur->getPosition().latitude)
                             .arg(distributeur->getPosition().longitude);
    positionDistributeur->setText(localisation);
    miseEnServiceDistributeur->setText(miseEnService);

    chargerCarte(distributeur);

    int nbBacs = distributeur->getNbBacs();

    for(int i = 0; i < nbBacs; i++)
    {
        QLabel* nomProduit = new QLabel(distributeur->getBac(i)->getNomProduit(), this);
        nomProduit->setAlignment(Qt::AlignCenter);
        layoutBacs->addWidget(nomProduit, 1, i, Qt::AlignCenter);

        QProgressBar* volumeRestant = new QProgressBar(this);
        volumeRestant->setOrientation(Qt::Vertical);
        volumeRestant->setRange(0, 100);
        volumeRestant->setValue(distributeur->getBac(i)->getPourcentageRemplissage());
        // affichage du remplissage : 35% de l'écran
        volumeRestant->setFixedSize(volumeRestant->width(),
                                    QGuiApplication::primaryScreen()->availableGeometry().height() *
                                      0.35);
        volumeRestant->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

        if(distributeur->getBac(i)->getPourcentageRemplissage() < BAC_VIDE)
        {
            volumeRestant->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        }
        else if(distributeur->getBac(i)->getPourcentageRemplissage() < BAC_MOITIE)
        {
            volumeRestant->setStyleSheet("QProgressBar::chunk { background-color: orange; }");
        }
        else
        {
            volumeRestant->setStyleSheet("QProgressBar::chunk { background-color: green; }");
        }

        layoutBacs->addWidget(volumeRestant, 2, i, Qt::AlignCenter);

        QLabel* hygrometrie       = new QLabel(this);
        int     valeurHygrometrie = distributeur->getBac(i)->getHygrometrie();
        hygrometrie->setText(
          QString("Hygrométrie : %1 %").arg(distributeur->getBac(i)->getHygrometrie()));

        if(valeurHygrometrie >= HYGROMETRIE_MIN_VALIDE &&
           valeurHygrometrie <= HYGROMETRIE_MAX_VALIDE)
        {
            hygrometrie->setStyleSheet("color: green;");
        }
        else if((valeurHygrometrie >= HYGROMETRIE_MIN_NON_VALIDE &&
                 valeurHygrometrie < HYGROMETRIE_MIN_VALIDE) ||
                (valeurHygrometrie > HYGROMETRIE_MAX_VALIDE &&
                 valeurHygrometrie <= HYGROMETRIE_MAX_NON_VALIDE))
        {
            hygrometrie->setStyleSheet("color: orange;");
        }
        else
        {
            hygrometrie->setStyleSheet("color: red;");
        }
        layoutBacs->addWidget(hygrometrie, 3, i, Qt::AlignCenter);
    }

    // positionnement
    layoutDistributeur->addLayout(layoutInformationsDistributeur);
    layoutDistributeur->addLayout(layoutCarteDistributeur);
    layoutFenetreDistributeur->addLayout(layoutDistributeur);
    layoutFenetreDistributeur->addLayout(layoutBacs);
    layoutFenetreDistributeur->addLayout(layoutBoutonsDistributeur);
    fenetreDistributeur->setLayout(layoutFenetreDistributeur);
}

/**
 * @brief crée les widgets de la fenêtre d 'affichage d'une intervention
 * @param distributeur, le distributeur lié à l'intervention
 */
void IHMJustFeed::creerEtatIntervention(Distributeur* distributeur)
{
    qDebug() << Q_FUNC_INFO << "distributeur" << distributeur->getNom();

    // la fenêtre intervention
    interventionNomOperateur->setAlignment(Qt::AlignCenter);
    interventionNomDistributeur->setAlignment(Qt::AlignCenter);
    dateIntervention->setAlignment(Qt::AlignCenter);
    aRemplirIntervention->setAlignment(Qt::AlignCenter);
    aDepannerIntervention->setAlignment(Qt::AlignCenter);
    etatIntervention->setAlignment(Qt::AlignCenter);
    nouvelleDateIntervention->setAlignment(Qt::AlignCenter);
    boutonImpression->setText("Imprimer");
    layoutBoutonsInterventions->addStretch();
    layoutBoutonsInterventions->addWidget(nouveauOperateur);
    layoutBoutonsInterventions->addWidget(nouvelleDateIntervention);
    layoutBoutonsInterventions->addWidget(boutonImpression);
    layoutBoutonsInterventions->addWidget(boutonValiderIntervention);

    idIntervention = ID_INTERVENTION_NON_DEFINI;
    QString nomOperateur;
    for(int i = 0; i < interventions.size(); i++)
    {
        if(interventions[i]->getIdDistributeur() == distributeur->getId())
        {
            nouvelleDateIntervention->setDate(interventions[i]->getDateIntervention());
            idIntervention = interventions[i]->getIdIntervention();
            qDebug() << Q_FUNC_INFO << "idIntervention" << idIntervention;
            for(int j = 0; j < operateurs.size(); j++)
            {
                if(operateurs[j]->getId() == interventions[i]->getIdOperateur())
                {
                    nomOperateur = operateurs[j]->getNom();
                    break;
                }
            }

            interventionNomOperateur->setText("Opérateur : " + nomOperateur);
            interventionNomDistributeur->setText("Distributeur : " + distributeur->getNom());
            dateIntervention->setText(
              "Date : " + interventions[i]->getDateIntervention().toString("dd/MM/yyyy"));
            qDebug() << Q_FUNC_INFO << "dateIntervention"
                     << interventions[i]->getDateIntervention();
            if(interventions[i]->getARemplir())
            {
                aRemplirIntervention->setText("À remplir  : Oui");
            }
            else
            {
                aRemplirIntervention->setText("À remplir : Non");
            }
            if(interventions[i]->getADepanner())
            {
                aDepannerIntervention->setText("À depanner  : Oui");
            }
            else
            {
                aDepannerIntervention->setText("À depanner : Non");
            }

            etatIntervention->setText(interventions[i]->getEtatFormate());
        }
    }

    listeApprovisionnement.clear();
    if(idIntervention != ID_INTERVENTION_NON_DEFINI)
    {
        QString requete = "SELECT * FROM Approvisionnement WHERE idIntervention = " +
                          QString::number(idIntervention) + " ORDER BY idBac ASC;";
        baseDeDonnees->recuperer(requete, listeApprovisionnement);
        qDebug() << Q_FUNC_INFO << "requete" << requete;
        QLabel* idBac;
        QLabel* poidsAPrevoir;
        QLabel* produitAPrevoir;
        qDebug() << Q_FUNC_INFO << "listeApprovisionnement" << listeApprovisionnement;

        for(int i = 0; i < listeApprovisionnement.size(); i++)
        {
            layoutsApprovisionnement.push_back(new QHBoxLayout);
            idBac         = new QLabel(this);
            poidsAPrevoir = new QLabel(this);
            produitAPrevoir = new QLabel(this);
            idBac->setText("Approvisionnement bac n°" +
                           listeApprovisionnement[i][Intervention::TableApprovisionnement::ID_BAC]);
            /**
             * @todo Gérer l'unité !!!
             */
            poidsAPrevoir->setText(
              "Poids à prevoir : " +
              listeApprovisionnement[i][Intervention::TableApprovisionnement::POIDS_A_PREVOIR] +
              " g");
            produitAPrevoir->setText("Produit à prevoir : " + distributeur->getBacId(listeApprovisionnement[i][Intervention::TableApprovisionnement::ID_BAC].toInt())->getNomProduit());
            layoutsApprovisionnement[i]->addWidget(idBac);
            layoutsApprovisionnement[i]->addWidget(poidsAPrevoir);
            layoutsApprovisionnement[i]->addWidget(produitAPrevoir);
        }
    }

    // positionnement
    layoutIntervention->addWidget(interventionNomDistributeur);
    layoutIntervention->addWidget(interventionNomOperateur);
    layoutIntervention->addWidget(dateIntervention);
    layoutIntervention->addWidget(aRemplirIntervention);
    layoutIntervention->addWidget(aDepannerIntervention);
    layoutIntervention->addWidget(etatIntervention);

    layoutInformationsIntervention->addLayout(layoutIntervention);
    for(int i = 0; i < listeApprovisionnement.size(); i++)
    {
        layoutInformationsIntervention->addLayout(layoutsApprovisionnement[i]);
    }
    layoutInformationsIntervention->addLayout(layoutBoutonsInterventions);
    fenetreIntervention->setLayout(layoutInformationsIntervention);
}

/**
 * @brief méthode qui efface les widgets des fenêtres d'affichage
 * @fn IHMJustFeed::effacerEtatsFenetre
 */
void IHMJustFeed::effacerEtatsFenetre()
{
    qDebug() << Q_FUNC_INFO;

    // Fenêtre FDistributeur
    QLayoutItem* item;
    while((item = layoutFenetreDistributeur->takeAt(0)) != nullptr)
    {
        QGridLayout* layoutBacs = dynamic_cast<QGridLayout*>(item->layout());
        if(layoutBacs != nullptr)
        {
            QLayoutItem* itemBac;
            while((itemBac = layoutBacs->takeAt(0)) != nullptr)
            {
                QWidget* widget = itemBac->widget();
                if(widget != nullptr)
                {
                    delete widget;
                }
                delete itemBac;
            }
        }
        delete item;
    }

    // Fenêtre FIntervention
    for(int i = 0; i < layoutsApprovisionnement.size(); i++)
    {
        while((item = layoutsApprovisionnement[i]->takeAt(0)) != nullptr)
        {
            QWidget* widget = item->widget();
            if(widget != nullptr)
            {
                delete widget;
            }
            delete item;
        }
    }
    // layoutBoutonsDistributeur
}

/**
 * @brief méthode qui récupére un Produit à partir de son id
 * @fn IHMJustFeed::recupererProduit
 * @param idProduit
 */
Produit* IHMJustFeed::recupererProduit(int idProduit)
{
    for(int i = 0; i < produits.size(); ++i)
    {
        if(produits[i]->getId() == idProduit)
            return produits[i];
    }
    return nullptr;
}

/**
 * @brief change les information d'une intervention, l'operateur ainsi que la date d'intervention
 */
void IHMJustFeed::metAJourLesInformationsIntervention()
{
    QString requete = "UPDATE Intervention SET dateIntervention = '"+
            nouvelleDateIntervention->date().toString("yyyy-MM-dd")+"' "
            "WHERE idIntervention = "+QString::number(idIntervention)+";";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    baseDeDonnees->executer(requete);
    int idNouveauOperateur;

    if(nouveauOperateur->currentText() != "Opérateur")
    {
        for(int i = 0; i < operateurs.size(); i++)
        {
            if(operateurs[i]->getNom() == nouveauOperateur->currentText())
            {
                idNouveauOperateur = operateurs[i]->getId();
            }
        }
        requete = "UPDATE Intervention SET idOperateur = '"+ QString::number(idNouveauOperateur)
                +"' WHERE idIntervention = "+QString::number(idIntervention)+";";
        qDebug() << Q_FUNC_INFO << "requete" << requete;
        baseDeDonnees->executer(requete);

        for(int i = 0; i < interventions.size(); i++)
        {
            if(interventions[i]->getIdIntervention() == idIntervention)
            {
                interventions[i]->setDateIntervention(nouvelleDateIntervention->date());
                interventions[i]->setIdOperateur(idNouveauOperateur);
            }
        }
    }
}

/**
 * @brief charge la carte de localisation d'un distributeur
 * @param distributeur
 */
void IHMJustFeed::chargerCarte(Distributeur* distributeur)
{
    /**
     * @see https://www.google.com/maps/search/?api=1&query=43.90252,4.75280
     * @see https://maps.google.com/maps?&z=15&q=43.90252,4.75280&ll=43.90252,4.75280
     * @see https://www.google.com/maps/place/43.90252+4.75280/@43.90252,4.75280,15z
     * @see
     * https://www.google.com/maps/@?api=1&map_action=map&basemap=satellite&center=43.90252,4.75280&zoom=15
     * @see
     * https://www.google.com/maps/dir/?api=1&origin=Paris%2CFrance&destination=Cherbourg%2CFrance&travelmode=driving
     */

    QString delimiteur = "%2C";
    QString url =
      "https://www.openstreetmap.org/export/embed.html?bbox=" +
      distributeur->getPosition().longitude + delimiteur + distributeur->getPosition().latitude +
      QString(",") + distributeur->getPosition().longitude + delimiteur +
      distributeur->getPosition().latitude + QString("&marker=") +
      distributeur->getPosition().latitude + QString(",") + distributeur->getPosition().longitude;
    // vueCarte->load(QUrl(url));
    vueCarte->setVisible(false);
    boutonAfficherCarte->setText("Afficher la carte");
    vueCarte->load(QUrl("https://www.google.fr/maps/@" + distributeur->getPosition().latitude +
                        "," + distributeur->getPosition().longitude + ",15z"));
}

/**
 * @brief Charge la liste des opérateurs connus
 */
void IHMJustFeed::chargerListeOperateurs()
{
    qDebug() << Q_FUNC_INFO;
    nouveauOperateur->clear();
    nouveauOperateur->addItem("Opérateur");
    for(int i = 0; i < operateurs.size(); i++)
    {
        qDebug() << Q_FUNC_INFO;
        nouveauOperateur->addItem(operateurs[i]->getNom());
    }
}
