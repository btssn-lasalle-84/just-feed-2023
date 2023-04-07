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
        COLONNE_DISTRIBUTEUR_NOM,
        COLONNE_DISTRIBUTEUR_LOCALISATION,
        COLONNE_DISTRIBUTEUR_ENSEIGNE,
        COLONNE_DISTRIBUTEUR_TYPE,
        COLONNE_DISTRIBUTEUR_ADRESSE,
        COLONNE_DISTRIBUTEUR_DATE,
        NB_COLONNES
    };

    Q_OBJECT
  private:
    QVector<Distributeur*> distributeurs; //!< les distributeurs

    QStringList nomColonnes;           //!< Liste de nom des colonnes
    int         nbLignesDistributeurs; //!< Nombre de lignes dans la table

    // Widgets
    QWidget*        gui;
    QStackedWidget* fenetres;
    QTableWidget*   tableWidgetDistributeurs; //!< Affichage sous forme de table
    QPushButton*    boutonIntervenir;
    QPushButton*    boutonConfigurer;

    QPushButton* boutonQuitter;

    QLabel* deviceIDDistributeur;
    QLabel* positionDistributeur;
    QLabel* nomDistributeur;
    QLabel* adresseDistributeur;
    QLabel* codePostalDistributeur;
    QLabel* villeDistributeur;
    QLabel* descriptionDistributeur;
    QLabel* miseEnServiceDistributeur;

    void initialiserGUI();
    void instancierWigets();
    void initialiserWigets();
    void positionnerWigets();
    void initialiserDistributeurs();
    void effacerTableau(int ligne, int colonne);
    void effacerTableDistributeurs();

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();
    void afficherDistributeurTable(Distributeur distributeur);
    void gererEvenements();

  private slots:

  public slots:
    void afficherFenetre(IHMJustFeed::Fenetre fenetre);
    void afficherFenetreAccueil();
};

#endif // IHMJUSTFEED_H
