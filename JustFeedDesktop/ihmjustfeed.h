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
#define DISTRIBUTEUR_2  1
#define DISTRIBUTEUR_3  2
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
    QLabel *bac; //!< numero du bac
    QLabel *produit; //!< produit qui se trouve dans le bac
    QLabel *prix; //!< prix du produit
    QLineEdit *editionPrix; //!< zone qui permet de changer le prix
    QLineEdit *editionProduit; //!< zone qui permet de changer le produit
    QPushButton *boutonChangerPrix; //!< bouton pour changer le prix
    QPushButton *boutonChangerProduit; //!< bouton pour changer le produit
    QVector<QLabel*> labelBac; //!< conteneur de QLabel de bac
    QVector<QLabel*> labelProduit; //!< conteneur de QLabel de produit
    QVector<QLabel*> labelPrix; //!< conteneur de QLabel de prix
    QVector<QLineEdit*> lineChangerPrix; //!<conteneur de QLineEdit de etidion prix
    QVector<QLineEdit*> lineChangerProduit; //!< conteneur de QLineEdit de etidion produit
    QVector<QPushButton*> qboutonChangerPrix; //!< conteneur de QLineEdit de bouton changer prix
    QVector<QPushButton*> qboutonChangerProduit; //!< conteneur de QLineEdit de bouton changer produit

    void                   initialiserGUI();
    void                   instancierWigets();
    void                   initialiserWigets();
    void                   positionnerWigets();
    void                   initialiserDistributeurs();

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();

  private slots:
    void changerLePrix(int numeroBac);
    void changerLeProduit(int numeroBac);
};

#endif // IHMJUSTFEED_H
