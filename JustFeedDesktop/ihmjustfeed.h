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
    QVector<Distributeur*> distributeurs;                 //!< les distributeurs
    int                    numeroDistributeurSelectionne; //!< le distributeur sélectionné
    // Widgets
    QLabel*          nomDistributeur; //!< nom du distributeur et son numero
    QVector<QLabel*> labelsBac;       //!< conteneur de QLabel de bac
    QVector<QLabel*> labelsProduit;   //!< conteneur de QLabel de produit
    QVector<QLabel*> labelsPrix;      //!< conteneur de QLabel de prix
    QPushButton*     boutonAjoutBac;
    QPushButton*     boutonSuppressionBac;
    /**
     * @todo Il faut utiliser un QSpinBox
     */
    QVector<QLineEdit*> editionsNouveauPrix; //!< conteneur de QLineEdit de etidion prix
    /**
     * @todo Il faut utiliser un QComboBox
     */
    QVector<QLineEdit*>   choixNouveauProduit; //!< conteneur de QLineEdit de etidion produit
    QVector<QPushButton*> boutonsChangerPrix;  //!< conteneur de QLineEdit de bouton changer prix
    QVector<QPushButton*>
                 boutonsChangerProduit; //!< conteneur de QLineEdit de bouton changer produit
    QVBoxLayout* layoutBacs;

    void initialiserGUI();
    void instancierWidgets();
    void initialiserWidgets();
    void positionnerWidgets();
    void initialiserEvenements();
    void initialiserDistributeurs();

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();

    int  instancierNouveauBac();
    void initialiserNouveauBac(int numeroBac);
    void positionnerNouveauBac(int numeroBac);
    void connecterNouveauBac(int numeroBac);

  private slots:
    void changerLePrix(int numeroBac);
    void changerLeProduit(int numeroBac);
    void ajouterBac();
    // void supprimerBac(int numerobac);
};

#endif // IHMJUSTFEED_H
