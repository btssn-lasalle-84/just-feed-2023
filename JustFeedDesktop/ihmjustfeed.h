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
class ConfigurationDistributeur;

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
    ConfigurationDistributeur*
      configurationDistributeur; //!< la boîte de dialogue pour configurer un distributeur

    // Widgets
    QComboBox*   listeDistributeurs;              //!< liste de distributeurs
    QPushButton* boutonConfigurationDistributeur; //!< bouton de configuration d'un distributeur

    void initialiserGUI();
    void instancierWidgets();
    void initialiserWidgets();
    void positionnerWidgets();
    void initialiserEvenements();
    void initialiserDistributeurs();

  public:
    IHMJustFeed(QWidget* parent = nullptr);
    ~IHMJustFeed();

  private slots:
    void configurerDistributeur();
    void selectionnerDistributeur(int numeroDistributeur);
};

#endif // IHMJUSTFEED_H
