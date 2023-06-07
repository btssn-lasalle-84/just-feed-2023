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

// Pourcentage de remplissage
#define ZERO      0
#define HUIT      8
#define DIX       10
#define QUINZE    15
#define DIX_HUIT  18
#define TRENTE    30
#define CINQUANTE 50
#define SOIXANTE  60
#define CENT      100

// Couleurs des niveaux
#define COULEUR_BAC_VIDE         QString("color: #FF0000;")
#define COULEUR_PRESQUE_BAC_VIDE QString("color: #FFA500;")
#define COULEUR_BAC_PLEIN        QString("color: #023518;")

#define COULEUR_HYGROMETRIE_ANORMALE     QString("color: #FF0000;")
#define COULEUR_HYGROMETRIE_A_SURVEILLER QString("color: #FFA500;")
#define COULEUR_HYGROMETRIE_NORMALE      QString("color: #023518;")

// Table Operateur
#define CHAMP_NOM_IDOPERATEUR  0
#define CHAMP_NOM_OPERATEUR    1
#define CHAMP_PRENOM_OPERATEUR 2

class Intervention;
class Distributeur;
class Produit;
class IHMJustFeed;
class BaseDeDonnees;

/**
 * @brief permet de planifier une intervention
 */
class PlanificationIntervention : public QDialog
{
    Q_OBJECT
  private:
    IHMJustFeed*           ihmJustFeed;       //!< association vers l'ihm principale
    BaseDeDonnees*         baseDeDonnees;     //!< association vers la base de données
    Intervention*          intervention;      //!< association vers la classe Intervention
    QDate                  dateIntervention;  //!< la date de l'intervention
    QVector<Distributeur*> distributeurs;     //!< les distributeurs sur lesquels il faut intervenir
    bool                   effectuable;       //!< si l'intervention peut être créée
    QComboBox*             listeOperateurs;   //!< liste d'operateurs
    QVector<int>           idOperateurs;      //!< les idOperateur
    QVector<QLabel*>       nomDistributeurs;  //!< les noms de distributeur et leur numero
    QVector<QLabel*>       labelsBac;         //!< les bac
    QVector<QLabel*>       labelsHygrometrie; //!< les hygrometries
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
    QDateEdit*   editionDate;       //!< choix de la date d'intervention

    void initialiserBoiteDeDialogue();
    void instancierWidgets();
    void initialiserWidgets();
    void initialiserEtatDistributeur();
    void positionnerWidgets();
    void initialiserEvenements();
    bool estEffectuable();
    void chargerListeOperateurs();
    int  recupererIdOperateur();
    void autoriserCreation();
    bool bacEstAttribueRemplissage(const int idDistributeur, const int idBac);
    bool distributeurEstAttribueDepannage(const int idDistributeur);

  public:
    explicit PlanificationIntervention(QVector<Distributeur*> listeDistributeursAIntervenir,
                                       IHMJustFeed*           parent = 0);
    ~PlanificationIntervention();

  public slots:
    void selectionnerBac();
    void selectionnerOperateur();
    void creerUneIntervention();
};

#endif // PLANIFICATION_INTERVENTION_H
