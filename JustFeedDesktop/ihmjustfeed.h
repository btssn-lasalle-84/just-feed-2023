/**
 * @file        ihmjustfeed.h
 * @brief       Déclaration de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @author      Rouanet Nicolas
 * @version     0.1
 * @date        2023
 */
#ifndef IHMJUSTFEED_H
#define IHMJUSTFEED_H

#include <QtWidgets>
#include <QString>
#include <QVector>

class Distributeur;
class ConfigurationDistributeur;
class Produit;

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
        NbColonnesDistributeur
    };

    Q_OBJECT
  private:
    QVector<Distributeur*> distributeurs;                 //!< les distributeur
    QVector<Produit*>      produits;                      //!< les produits
    int                    numeroDistributeurSelectionne; //!< le distributeur sélectionné
    ConfigurationDistributeur*
                configurationDistributeur; //!< la boîte de dialogue pour configurer un distributeur
    QStringList nomColonnes;               //!< la liste des noms de colonne
    int         nbLignesDistributeurs;     //!< le nombre de lignes dans la table

    // Widgets
    QWidget*        gui;                      //!< le widget central
    QStackedWidget* fenetres;                 //!< la pile de fenêtres
    QWidget*        fenetreAccueil;           //!< la fenêtre d'accueil
    QWidget*        fenetreDistributeur;      //!< la fenêtre d'un distributeur
    QTableWidget*   tableWidgetDistributeurs; //!< l'affichage sous forme de table
    QPushButton*    boutonIntervenir;
    QPushButton*    boutonConfigurer;
    QPushButton*    boutonValider;
    QComboBox*      listeDistributeurs; //!< liste de distributeurs
    QVBoxLayout*    layoutFenetreDistributeur;
    QProgressBar*   volumeRestant;
    QLabel*         nomDistributeur;
    QLabel*         adresseDistributeur;
    QLabel*         codePostalDistributeur;
    QLabel*         villeDistributeur;
    QLabel*         descriptionDistributeur;
    QLabel*         miseEnServiceDistributeur;
    QLabel*         positionDistributeur;

    void initialiserGUI();
    void instancierWidgets();
    void initialiserWidgets();
    void initialiseTable();
    void positionnerWidgets();
    void initialiserEvenements();
    void initialiserDistributeurs();
    void initialiserProduits();
    void chargerDistributeurs();
    void afficherDistributeurTable(const Distributeur& distributeur);
    void afficherDistributeur(Distributeur* distributeur);
    void effacerTableau(int ligne, int colonne);
    void effacerTableDistributeurs();
    void effacerEtatDistributeur();

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
    void configurerDistributeur();
    void selectionnerDistributeur(int numeroDistributeur);
    void selectionnerDistributeur(int ligne, int colonne);
};

#endif // IHMJUSTFEED_H
