/**
 * @file        configurationdistributeur.h
 * @brief       Déclaration de la classe ConfigurationDistributeur.
 * @details     La classe ConfigurationDistributeur \c Cette classe permet de définir la
 * configuration d'un distributeur
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
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

class Distributeur;
class IHMJustFeed;
class Produit;

/**
 * @class       ConfigurationDistributeur
 * @brief       Déclaration de la classe ConfigurationDistributeur.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la
 * configuration d'un distributeur
 */
class ConfigurationDistributeur : public QDialog
{
    Q_OBJECT
  private:
    Distributeur* distributeur; //!< le distributeur à configurer
    IHMJustFeed*  ihmJustFeed;  //!< l'ihm principale
    // Widgets
    QLabel*          nomDistributeur; //!< nom du distributeur et son numero
    QVector<QLabel*> labelsBac;       //!< conteneur de QLabel de bac
    QVector<QLabel*> labelsProduit;   //!< conteneur de QLabel de produit
    QVector<QLabel*> labelsPrix;      //!< conteneur de QLabel de prix
    QPushButton*     boutonAjoutBac;
    /**
     * @todo Il faut un bouton Supprimer par bac
     */
    QPushButton*             boutonSuppressionBac;
    QVector<QDoubleSpinBox*> editionsNouveauPrix; //!< conteneur de QLineEdit de etidion prix
    QVector<QComboBox*>
      choixNouveauProduit; //!< conteneur de QComboBox pour changer le produit du bac
    QVector<QPushButton*> boutonsChangerPrix; //!< conteneur de QLineEdit de bouton changer prix
    QVector<QPushButton*>
                 boutonsChangerProduit; //!< conteneur de QLineEdit de bouton changer produit
    QVBoxLayout* layoutBacs;

    void initialiserGUI();
    void instancierWidgets();
    void initialiserWidgets();
    void positionnerWidgets();
    void initialiserEvenements();
    int  instancierNouveauBac();
    void initialiserNouveauBac(int numeroBac);
    void positionnerNouveauBac(int numeroBac);
    void connecterNouveauBac(int numeroBac);

  public:
    explicit ConfigurationDistributeur(Distributeur* distributeur, IHMJustFeed* parent = 0);
    ~ConfigurationDistributeur();

  private slots:
    void selectionnerNouveauProduit(int numeroBac);
    void changerLePrix(int numeroBac);
    void changerLeProduit(int numeroBac);
    void ajouterBac();
    /**
     * @todo Supprimer un bac
     */
    // void supprimerBac();
};

#endif // CONFIGURATIONDISTRIBUTEUR_H
