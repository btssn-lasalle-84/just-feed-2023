/**
 * @file        ihmjustfeed.h
 * @brief       Déclaration de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @author      Rouanet Nicolas
 * @version     0.2
 * @date        2023
 */

#ifndef IHMJUSTFEED_H
#define IHMJUSTFEED_H

#include <QString>
#include <QVector>
#include <QtWidgets>
#include <QWebView>

class Distributeur;
class ConfigurationDistributeur;
class Produit;
class PlanificationIntervention;
class BaseDeDonnees;

/**
 * @def TITRE_APPLICATION
 * @brief Définit le titre de l'application
 */
#define TITRE_APPLICATION QString("JustFeed")

/**
 * @def VERSION_APPLICATION
 * @brief Définit la version de l'application
 */
#define VERSION_APPLICATION QString("v0.1")

#define TAILLE_POLICE 14

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
        COLONNE_DISTRIBUTEUR_NOM, //!< Emplacement du nom
        COLONNE_DISTRIBUTEUR_ADRESSE,
        COLONNE_DISTRIBUTEUR_VILLE,
        COLONNE_DISTRIBUTEUR_CODEPOSTAL,
        COLONNE_DISTRIBUTEUR_INTERVENTION,
        NbColonnesDistributeur
    };

    Q_OBJECT
  private:
    // Attributs
    BaseDeDonnees*             baseDeDonnees;
    ConfigurationDistributeur* configurationDistributeur; //!< la boîte de dialogue pour configurer
    //!< un distributeur
    PlanificationIntervention*
                           planificationIntervention; //!< la boîte de dialogue pour créer une intervention
    QVector<Distributeur*> distributeurs;             //!< les distributeurs
    QVector<Distributeur*> listeDistributeursAIntervenir; //!< les distributeurs à intervenir
    QVector<Produit*>      produits;                      //!< les produits
    int                    numeroDistributeurSelectionne; //!< le distributeur sélectionné
    QStringList            nomColonnes;                   //!< la liste des noms de colonne
    int                    nbLignesDistributeurs;         //!< le nombre de lignes dans la table
    // Widgets
    QWidget*          gui;                      //!< le widget central
    QStackedWidget*   fenetres;                 //!< la pile de fenêtres
    QWidget*          fenetreAccueil;           //!< la fenêtre d'accueil
    QWidget*          fenetreDistributeur;      //!< la fenêtre d'un distributeur
    QTableWidget*     tableWidgetDistributeurs; //!< l'affichage sous forme de table
    QTableWidgetItem *itemEnseigne, *itemAdresse, *itemVille, *itemCodePostal,
      *itemIntervention; //!< les éléments de la table
    QPushButton*  boutonPlanifier;
    QPushButton*  boutonConfigurer;
    QPushButton*  boutonValider;
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
    QWebView*     vueCarte;

    void initialiserGUI();
    void instancierWidgets();
    void initialiserWidgets();
    void initialiserTable();
    void positionnerWidgets();
    void initialiserEvenements();
    void initialiserDistributeurs();
    void initialiserProduits();
    void chargerDistributeurs();
    void afficherDistributeurTable(const Distributeur& distributeur);
    void afficherDistributeur(Distributeur* distributeur);
    void effacerTableau(int ligne, int colonne);
    void effacerTableDistributeurs();
    int  recupererDistributeursAIntervenir();
    void effacerDistributeursAIntervenir();
    void creerEtatDistributeur(Distributeur* distributeur);
    void effacerEtatDistributeur();
    void chargerCarte(Distributeur* distributeur);

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();

    Distributeur* getDistributeur(QString nom) const;
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
};

#endif // IHMJUSTFEED_H
