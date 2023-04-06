/**
 * @file        ihmjustfeed.h
 * @brief       Déclaration de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#ifndef IHMJUSTFEED_H
#define IHMJUSTFEED_H

#define TAILLE_POLICE 14

#include <QtWidgets>
#include <QString>
#include <QVector>
#include <QLabel>



class Distributeur;

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

/**
 * @class       IHMJustFeed
 * @brief       Déclaration de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed
 */
class IHMJustFeed : public QMainWindow
{

    enum Fenetre
        {
            Accueil,
            NbFenetres
        };

    enum ColonneDistributeur
    {
        COLONNE_DISTRIBUTEUR_NOM,         //!< Emplacment du nom
        COLONNE_DISTRIBUTEUR_LOCALISATION,      //!< Emplacment du prenom
        COLONNE_DISTRIBUTEUR_ENSEIGNE, //!< Emplacment de l'identifiant
        COLONNE_DISTRIBUTEUR_TYPE,        //!< Emplacment du code
        COLONNE_DISTRIBUTEUR_ADRESSE, //!< Emplacment de l'état actif
        COLONNE_DISTRIBUTEUR_DATE,
        NB_COLONNES
    };

    Q_OBJECT
  private:

    QStringList    nomColonnes;          //!< Liste de nom des colonnes
    int            nbLignesDistributeurs; //!< Nombre de lignes dans la table
    QWidget*        gui;
    QStackedWidget* fenetres;
    QTableWidget*   tableWidgetDistributeurs; //!< Affichage sous forme de table

    QLabel* titrePrincipal;
    QPushButton* boutonQuitter;
    QPushButton* boutonIntervenir;
    QPushButton* boutonConfigurer;

    QLabel* labelNom;
    QLabel* labelPosition;
    QLabel* labelAdresse;
    QLabel* labelCodePostal;
    QLabel* labelVille;
    QLabel* labelMiseEnService;



    QVector<Distributeur*> distributeurs;//!< les distributeurs
    void                   initialiserGUI();
    void                   instancierWigets();
    void                   initialiserWigets();
    void                   positionnerWigets();
    void                   initialiserDistributeurs();
    void                   effacerTableau(int ligne, int colonne);
    void                   effacerTableDistributeurs();

    void                   listerDistributeurs();

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();
    void afficherDistributeurTable(Distributeur distributeur);
    void                   paintEvent(QPaintEvent* dessin);
    void                   gererEvenements();

    void                   afficherDistributeurTable (QStringList distributeur);

  private slots:

  public slots :
    void afficherFenetre(IHMJustFeed::Fenetre fenetre);
    void afficherFenetreAccueil();
};

#endif // IHMJUSTFEED_H
