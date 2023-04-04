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
class IHMJustFeed : public QWidget
{
    Q_OBJECT
  private:

    QStringList    nomColonnes;          //!< Liste de nom des colonnes
    int            nbLignesDistributeurs; //!< Nombre de lignes dans la table
    QTableWidget*   tableWidgetDistributeurs; //!< Affichage sous forme de table
    QWidget*        centralWidget; //!< Widget central
    QPushButton*    boutonCharger;
    QPushButton*    boutonEffacer;
    QPushButton*    boutonRetour;
    QLabel*         labelNomDistributeur;
    QLabel*         nomDistributeur;
    QLabel*         labelLatitude;
    QLabel*         latitude;
    QLabel*         labelLongitude;
    QLabel*         longitude;
    QLabel*         labelEnseigne;
    QLabel*         enseigne;
    QLabel*         labelType;
    QLabel*         type;
    QLabel*         labelAdresse;
    QLabel*         adresse;
    QLabel*         labelCreation;
    QLabel*         creation;

    QVector<Distributeur*> distributeurs; //!< les distributeurs
    void                   initialiserGUI();
    void                   instancierWigets();
    void                   initialiserWigets();
    void                   positionnerWigets();
    void                   initialiserDistributeurs();
    void                   listerDistributeurs();


    enum ColonneDistributeur
    {
        COLONNE_DISTRIBUTEURS_NOM,         //!< Emplacment du nom
        COLONNE_DISTRIBUTEURS_LATITUDE,      //!< Emplacment du prenom
        COLONNE_DISTRIBUTEURS_LONGITUDE, //!< Emplacment de l'identifiant
        COLONNE_DISTRIBUTEURS_ENSEIGNE,        //!< Emplacment du code
        COLONNE_DISTRIBUTEURS_TYPE,       //!< Emplacment de l'état actif
        COLONNE_DISTRIBUTEURS_ADRESSE,
        COLONNE_DISTRIBUTEURS_CREATION,
        NB_COLONNES
    };

    enum ChampsDistributeur
    {
        TABLE_DISTRIBUTEUR_ID_UTILISATEUR, //!< Emplacment de l'idUtilisateur
        TABLE_DISTRIBUTEUR_NOM,            //!< Emplacment du nom
        TABLE_DISTRIBUTEUR_PRENOM,         //!< Emplacment du prenom
        TABLE_DISTRIBUTEUR_IDENTIFIANT,    //!< Emplacment de l'identifiant
        TABLE_DISTRIBUTEUR_CODE,           //!< Emplacment du code
        TABLE_DISTRIBUTEUR_ACTIF,          //!< Emplacment de l'état actif
    };

    enum Fenetre
    {
        Fenetre1 = 0,
        Fenetre2,
        NbFenetres
    };

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();
  //  void                   afficherDistributeurTable (QStringList distributeur);

  private slots:
};

#endif // IHMJUSTFEED_H
