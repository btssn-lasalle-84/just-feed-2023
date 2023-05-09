/**
 * @file        planificationintervention.h
 * @brief       Déclaration de la classe PlanificationIntervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.2
 * @date        2023
 */
#ifndef PLANIFICATION_INTERVENTION_H
#define PLANIFICATION_INTERVENTION_H

#include <QtWidgets>
#include <QDate>
#include <QTime>
#include <QString>
#include <QVector>

/**
 * @def TITRE_INTERVENTION
 * @brief Définit le titre de la boîte de dialogue
 */
#define TITRE_INTERVENTION QString("Planifier une intervention")
#define ZERO               0
#define QUINZE             15
#define TRENTE             30
#define CINQUANTE          50
#define SOIXANTE           60
#define CENT               100
#define OPERATEUR          1

class Intervention;
class Distributeur;
class Produit;
class IHMJustFeed;
class BaseDeDonnees;

class PlanificationIntervention : public QDialog
{
    Q_OBJECT
  private:
    IHMJustFeed*           ihmJustFeed;       //!< association vers l'ihm principale
    BaseDeDonnees*         baseDeDonnees;     //!< association vers la base de données
    Intervention*          intervention;      //!< association vers la classe Intervention
    QDate                  dateIntervention;  //!< la date de l'intervention
    QVector<Distributeur*> distributeurs;     //!< les distributeurs sur lesquels il faut intervenir
    bool                   effectuable;       //!< si l'intervention peut être créé
    QVector<QLabel*>       nomDistributeurs;  //!< nom du distributeur et son numero
    QVector<QLabel*>       labelsBac;         //!< conteneur de QLabel de bac
    QVector<QLabel*>       labelsHygrometrie; //!< conteneur de QLabel d'hygrometrie
    QVector<QVector<QLabel*> >
      labelsDesHygrometries; //!< conteneur de vecteurs de QLabel pour les hygrometries
    QVector<QVector<QLabel*> >
                               labelsDesBacs; //!< conteneur de vecteurs de QLabel pour stocker les bacs
    QVector<QLabel*>           labelsProduit;     //!< conteneur de QLabel de produit
    QVector<QVector<QLabel*> > labelsDesProduits; //!< conteneur de vecteurs de QLabel pour stocker
                                                  //!< les produits
    QVector<QLabel*>           labelsPourcentage; //!< conteneur de QLabel de produit
    QVector<QVector<QLabel*> > labelsDesPourcentage;
    QVBoxLayout*               layoutBacs; //!< positionnement des bacs dans la boîte de dialogue
    QHBoxLayout*               layoutDistributeurs; //!< positionnement des distributeurs et le
                                                    //!< contenu dans la boîte de dialogue
    QHBoxLayout*        layoutBac; //!< layout qui contient le nom du bac et un checkBox
    QVector<QCheckBox*> labelsCheckboxDepannage;   //!< vecteur de checkBox depannage
    QVector<QCheckBox*> labelsCheckboxRemplissage; //!< vecteur de checkBox remplissage
    QVector<QVector<QCheckBox*> >
                                  labelsDesCheckboxDepannage; //!< conteneur de vecteurs de checkBox Depannage
    QVector<QVector<QCheckBox*> > labelsDesCheckboxRemplissage; //!< conteneur de vecteurs de
                                                                //!< checkBox Remplissage
    QPushButton* boutonItervention; //!< bouton pour créer une intervention
    QDateEdit*   editionDate;       //!< choix de la date

    void initialiserBoiteDeDialogue();
    void instancierWidgets();
    void initialiserWidgets();
    void initialiserEtatDistributeur();
    void positionnerWidgets();
    void initialiserEvenements();
    bool estEffectuable();

  public:
    explicit PlanificationIntervention(QVector<Distributeur*> listeDistributeursAIntervenir,
                                       IHMJustFeed*           parent = 0);
    ~PlanificationIntervention();

  public slots:
    void selectionnerBac();
    void creerUneIntervention();
};

#endif // PLANIFICATION_INTERVENTION_H
