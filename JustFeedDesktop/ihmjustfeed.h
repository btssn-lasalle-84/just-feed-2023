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

#define DISTRIBUTEUR_1  0
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
    QVector<Distributeur*> distributeurs; //!< les distributeurs
    QLabel *nomDistributeur; //!< nom du distributeur et son numero
    QVector<QLabel*> labelBac; //!< conteneur de QLabel de bac
    QVector<QLabel*> labelProduit; //!< conteneur de QLabel de produit
    QVector<QLabel*> labelPrix; //!< conteneur de QLabel de prix
    QPushButton *qboutonAjoutBac;
    QPushButton *qboutonSuppressionBac;
    QVector<QLineEdit*> lineChangerPrix; //!<conteneur de QLineEdit de etidion prix
    QVector<QLineEdit*> lineChangerProduit; //!< conteneur de QLineEdit de etidion produit
    QVector<QPushButton*> qboutonChangerPrix; //!< conteneur de QLineEdit de bouton changer prix
    QVector<QPushButton*> qboutonChangerProduit; //!< conteneur de QLineEdit de bouton changer produit
    QVBoxLayout* mainLayout;

    void                   initialiserGUI();
    void                   instancierWigets();
    void                   initialiserWigets();
    void                   positionnerWigets();
    void                   initialiserDistributeurs();

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();
    void initialiserConnect();
    void initialiserNouveauWidget();
    void positionnerNouveauWigets(int nbrBacs);
    void instancierNouveauWidget();
    void initialiserNouveauWidget(int nbrBacs);
    void positionnerNouveauWidget(int nbrBacs);
    void connecterNouveauWidget(int nbrBacs);

private slots:
    void changerLePrix(int numeroBac);
    void changerLeProduit(int numeroBac);
    void ajoutBac();
    void supprimerBac(int numerobac);
};

#endif // IHMJUSTFEED_H
