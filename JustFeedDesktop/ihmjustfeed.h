/**
 * @file        ihmjustfeed.h
 * @brief       Déclaration de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @author      Rouanet Nicolas
 * @version     1.1
 * @date        2023
 */

#ifndef IHMJUSTFEED_H
#define IHMJUSTFEED_H

#include <QString>
#include <QVector>
#include <QtWidgets>
#include <QWebView>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QPainter>
#include <QFont>
#include <QtMqtt/QtMqtt>

class Distributeur;
class ConfigurationDistributeur;
class Produit;
class PlanificationIntervention;
class BaseDeDonnees;
class Operateur;
class Intervention;
class Communication;

/**
 * @def TITRE_APPLICATION
 * @brief Définit le titre de l'application
 */
#define TITRE_APPLICATION QString("JustFeed")

/**
 * @def VERSION_APPLICATION
 * @brief Définit la version de l'application
 */
#define VERSION_APPLICATION QString("v0.2")

/**
 * @def SANS_BDD
 * @brief À définir pour ne pas utiliser l'accès à la base de données
 */
//#define SANS_BDD

#define TAILLE_POLICE   14
#define BAC_VIDE        30
#define BAC_MOITIE      50
#define MAX_REMPLISSAGE 100

#define HYGROMETRIE_MIN_VALIDE     10
#define HYGROMETRIE_MAX_VALIDE     15
#define HYGROMETRIE_MIN_NON_VALIDE 8
#define HYGROMETRIE_MAX_NON_VALIDE 18

#define UN 1

/**
 * @class       IHMJustFeed
 * @brief       Déclaration de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed
 */
class IHMJustFeed : public QWidget
{
    /**
     * @enum Fenetre
     * @brief Définit les différentes fenêtres de l'IHM
     *
     */
    enum Fenetre
    {
        FAccueil,
        FDistributeur,
        FIntervention,
        NbFenetres
    };
    /**
     * @enum ColonneDistributeur
     * @brief Définit les différentes colonnes du QTableWidget
     *
     */
    enum ColonneDistributeur
    {
        COLONNE_DISTRIBUTEUR_NOM,                 //!< Emplacement du nom
        COLONNE_DISTRIBUTEUR_ADRESSE,             //!< Emplacement de l'adresse
        COLONNE_DISTRIBUTEUR_VILLE,               //!< Emplacement de la ville
        COLONNE_DISTRIBUTEUR_CODEPOSTAL,          //!< Emplacement du code postal
        COLONNE_DISTRIBUTEUR_INTERVENTION_DETAIL, //!< Emplacement intervention
        COLONNE_DISTRIBUTEUR_INTERVENTION,        //!< Emplacement check box intervention
        NbColonnesDistributeur
    };
    /**
     * @enum TableApprovisionnement
     * @brief Définit les colonnes de la table approvisionnement
     *
     */

    Q_OBJECT
  private:
    // Attributs
    BaseDeDonnees*             baseDeDonnees; //!< association vers la classe BaseDeDonnees
    ConfigurationDistributeur* configurationDistributeur; //!< la boîte de dialogue pour configurer
    //!< un distributeur
    PlanificationIntervention*
                           planificationIntervention; //!< la boîte de dialogue pour créer une intervention
    QVector<Distributeur*> distributeurs;             //!< les distributeurs
    QVector<Operateur*>    operateurs;                //!< les operateurs
    QVector<Distributeur*> listeDistributeursAIntervenir; //!< les distributeurs à intervenir
    QVector<Produit*>      produits;                      //!< les produits
    QVector<Intervention*> interventions;                 //!< les interventions
    Communication*         communication;                 //!< la communication
    int                    numeroDistributeurSelectionne; //!< le distributeur sélectionné
    QStringList            nomColonnes;                   //!< la liste des noms de colonne
    int                    nbLignesDistributeurs;         //!< le nombre de lignes dans la table

    // Widgets
    QWidget*          gui;                      //!< le widget central
    QStackedWidget*   fenetres;                 //!< la pile de fenêtres
    QWidget*          fenetreAccueil;           //!< la fenêtre d'accueil
    QWidget*          fenetreDistributeur;      //!< la fenêtre d'un distributeur
    QWidget*          fenetreIntervention;      //!< la fenêtre d'une intervention
    QTableWidget*     tableWidgetDistributeurs; //!< l'affichage sous forme de table
    QTableWidgetItem *itemEnseigne, *itemAdresse, *itemVille, *itemCodePostal, *itemIntervention,
      *itemDetailIntervention; //!< les éléments de la table
    QPushButton*  boutonPlanifier;
    QPushButton*  boutonConfigurer;
    QPushButton*  boutonValiderDistributeur;
    QPushButton*  boutonValiderIntervention;
    QPushButton*  boutonAfficherCarte;
    QComboBox*    listeDistributeurs; //!< liste de distributeurs
    QVBoxLayout*  layoutFenetreDistributeur;
    QProgressBar* volumeRestant;
    QLabel*       nomDistributeur;
    QLabel*       adresseDistributeur;
    QLabel*       codePostalDistributeur;
    QLabel*       villeDistributeur;
    QLabel*       descriptionDistributeur;
    QLabel*       miseEnServiceDistributeur;
    QLabel*       positionDistributeur;
    QHBoxLayout*  layoutIntervention;         //!< layout intervention
    QHBoxLayout*  layoutBoutonsInterventions; //!< layout des boutons de l'intervention
    QVBoxLayout*
                         layoutInformationsIntervention; //!< layout contenant les informations de l'intervention
    QVector<QStringList> listeApprovisionnement;       //!< vecteur de liste qui contient les
                                                       //!< Approvisionnement lié à l'intervention
    QVector<QHBoxLayout*> layoutsApprovisionnement;    //!< layout des approvisionnement
    QLabel*               interventionNomOperateur;    //!< nom operateur
    QLabel*               interventionNomDistributeur; //!< nom distributeur
    QLabel*               dateIntervention;            //!< date planifié pour l'intervention
    QLabel*      aRemplirIntervention;     //!< bool pour savoir si le distributeur est à remplir
    QLabel*      aDepannerIntervention;    //!< bool pour savoir si le distributeur est à depanner
    QLabel*      etatIntervention;         //!< etat de l'intervention
    QComboBox*   nouveauOperateur;         //!< nouveau operateur
    QDateEdit*   nouvelleDateIntervention; //!< nouvelle date d'intervention
    QPushButton* boutonSauvegarderPDF;     //!< bouton pour sauvegarder en pdf une intervention
    QPushButton* boutonImpression;         //!< bouton pour imprimer une intervention
    int          idIntervention;           //!< id de l'intervention en cour de visualisation
    QWebView*    vueCarte;

    void     initialiserGUI();
    void     instancierWidgets();
    void     initialiserWidgets();
    void     initialiserTable();
    void     positionnerWidgets();
    void     initialiserEvenements();
    void     initialiserCommunication();
    void     initialiserDistributeurs();
    void     initialiserProduits();
    void     initialiserOperateurs();
    void     initialiserInterventions();
    void     chargerDistributeurs();
    void     afficherDistributeurTable(const Distributeur& distributeur);
    void     afficherDistributeur(Distributeur* distributeur);
    void     afficherIntervention(Distributeur* distributeur);
    void     effacerTableau(int ligne, int colonne);
    void     effacerTableDistributeurs();
    int      recupererDistributeursAIntervenir();
    void     effacerDistributeursAIntervenir();
    void     creerEtatDistributeur(Distributeur* distributeur);
    void     creerEtatIntervention(Distributeur* distributeur);
    void     effacerEtatsFenetre();
    void     chargerCarte(Distributeur* distributeur);
    void     chargerListeOperateurs();
    Produit* recupererProduit(int idProduit);
    void     mettreAJourInformationsIntervention();
    void     mettreAJourRemplissage(int idDistributeur, int remplissage, int indiceBac);
    void     mettreAJourHumidite(int idDistributeur, int hygrometries, int indiceBac);

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();

    Distributeur* getDistributeur(QString nom) const;
    int           getIdDistributeur(QString deviceID) const;
    Produit*      getProduit(int index) const;
    QString       getNomProduit(int index) const;
    double        getPrixProduit(int index) const;
    int           getNbProduits() const;

  public slots:
    void afficherFenetre(IHMJustFeed::Fenetre fenetre);
    void afficherFenetreAccueil();
    void afficherFenetreDistributeur();
    void afficherFenetreIntervention();
    void configurerDistributeur();
    void planifierIntervention();
    void selectionnerDistributeur(int numeroDistributeur);
    void selectionnerDistributeur(int ligne, int colonne);
    void selectionnerDistributeur(QTableWidgetItem* item);
    void selectionnerDistributeurAIntervenir(QTableWidgetItem* item);
    void afficherCarte();
    void genererPDFIntervention();
    void imprimerPDFIntervention();
    void decoderMessageMQTT(QByteArray message, QMqttTopicName topic);
};

#endif // IHMJUSTFEED_H
