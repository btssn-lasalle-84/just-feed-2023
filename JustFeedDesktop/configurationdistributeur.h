/**
 * @file        configurationdistributeur.h
 * @brief       Déclaration de la classe ConfigurationDistributeur.
 * @details     La classe ConfigurationDistributeur \c Cette classe permet de définir la
 * configuration d'un distributeur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.2
 * @date        2023
 */

#ifndef CONFIGURATIONDISTRIBUTEUR_H
#define CONFIGURATIONDISTRIBUTEUR_H

#include <QtWidgets>
#include <QString>

/**
 * @def TITRE_CONFIGURATION_DISTRIBUTEUR
 * @brief Définit le titre de la boîte de dialogue
 */
#define TITRE_CONFIGURATION_DISTRIBUTEUR QString("Configuration")
#define NB_BAC_MAX                       6
class Distributeur;
class IHMJustFeed;
class Produit;
class BaseDeDonnees;

/**
 * @class       ConfigurationDistributeur
 * @brief       Déclaration de la classe ConfigurationDistributeur.
 * @details     La classe ConfigurationDistributeur \c Cette classe permet de définir la
 * configuration d'un distributeur
 */
class ConfigurationDistributeur : public QDialog
{
    Q_OBJECT
  private:
    Distributeur*  distributeur;  //!< le distributeur à configurer
    IHMJustFeed*   ihmJustFeed;   //!< l'ihm principale
    BaseDeDonnees* baseDeDonnees; //!< association vers la base de données
    // Widgets
    QLabel*                  nomDistributeur;      //!< nom du distributeur et son numero
    QVector<QLabel*>         labelsBac;            //!< conteneur de QLabel de bac
    QVector<QLabel*>         labelsProduit;        //!< conteneur de QLabel de produit
    QVector<QLabel*>         labelsPrix;           //!< conteneur de QLabel de prix
    QPushButton*             boutonAjoutBac;       //!< bouton pour ajouter un bac
    QVector<QPushButton*>    boutonSuppressionBac; //!< bouton supprimer pour chaque bac
    QPushButton*             boutonValide;         //!< bouton valider
    QVector<QDoubleSpinBox*> editionsNouveauPrix;  //!< conteneur de QLineEdit de etidion prix
    QVector<QComboBox*>
                          choixNouveauProduit; //!< conteneur de listes déroulantes pour choisir un produit du bac
    QVector<QPushButton*> boutonsChangerPrix;    //!< conteneur de boutons pour changer le prix
    QVector<QPushButton*> boutonsChangerProduit; //!< conteneur de boutons changer le produit
    QVBoxLayout*          layoutBacs; //!< positionnement des bacs dans la boîte de dialogue

    void initialiserBoiteDeDialogue();
    void instancierWidgets();
    void initialiserWidgets();
    void positionnerWidgets();
    void initialiserEvenements();
    int  instancierNouveauBac();
    void initialiserNouveauBac(int indiceBac);
    void positionnerNouveauBac(int indiceBac);
    void connecterNouveauBac(int indiceBac);

  public:
    explicit ConfigurationDistributeur(Distributeur* distributeur, IHMJustFeed* parent = 0);
    ~ConfigurationDistributeur();

  private slots:
    void selectionnerNouveauProduit(int indiceBac);
    void changerLePrix(int indiceBac);
    void changerLeProduit(int indiceBac);
    void ajouterBac();
    void ajouterBacBdd();
    void supprimerBac(const int indiceBac);
    void supprimerBacBaseDeDonnees(const int indiceBac);
    void valider();
};

#endif // CONFIGURATIONDISTRIBUTEUR_H
