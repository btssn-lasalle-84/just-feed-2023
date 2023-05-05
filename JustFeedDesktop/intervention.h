/**
 * @file        Intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QDate>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QTime>
#include <QVector>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QtWidgets>

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

class Distributeur;
class Produit;
class IHMJustFeed;
class BaseDeDonnees;

class Intervention : public QDialog
{
    Q_OBJECT
  private:
    IHMJustFeed*               ihmJustFeed; //!< association vers l'ihm principale
    BaseDeDonnees*             baseDeDonnees;
    QDate                      dateIntervention;  //!< la date de l'intervention
    QTime                      heureIntervention; //!< l'heure de l'intervention
    QVector<Distributeur*>     distributeurs; //!< les distributeurs sur lesquels il faut intervenir
    bool                       effectuee;     //!< si l'intervention a été effectuée
    int                        totalBac;      //!< nombre total de bac
    QVector<QLabel*>           nomDistributeurs;  //!< nom du distributeur et son numero
    QVector<QLabel*>           labelsBac;         //!< conteneur de QLabel de bac
    QVector<QLabel*>           labelsHygrometrie; //!< conteneur de QLabel d'hygrometrie
    QVector<QVector<QLabel*> > labelsDesHygrometries;
    //!< vecteur de vecteur de QLabel, pour stocker ;les
    //!< hygrometries
    //!
    QVector<QVector<QLabel*> >
                               labelsDesBacs; //!< vecteur de vecteur de QLabel, pour stocker les bacs
    QVector<QLabel*>           labelsProduit;     //!< conteneur de QLabel de produit
    QVector<QVector<QLabel*> > labelsDesProduits; //!< vecteur de vecteur de QLabel, pour stocker
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
                                  labelsDesCheckboxDepannage; //!< vecteur de vecteur de checkBox Depannage
    QVector<QVector<QCheckBox*> > labelsDesCheckboxRemplissage; //!< vecteur de vecteur de checkBox
                                                                //!< Remplissage
    QPushButton* boutonItervention; //!< bouton qui créé une intervention
    QDateEdit*   dateEdit;          //!< choix de la date
    QTimeEdit*   heureEdit;         //!< choix de l'heure
    void         initialiserBoiteDeDialogue();
    void         instancierWidgets();
    void         initialiserWidgets();
    void         initialiserEtatDistributeur();
    void         positionnerWidgets();
    void         initialiserEvenements();

  public:
    explicit Intervention(QVector<Distributeur*> listeDistributeursAIntervenir,
                          BaseDeDonnees*         baseDeDonnees,
                          IHMJustFeed*           parent = 0);
    ~Intervention();

    // Accesseurs
    QDate                  getDateIntervention() const;
    QTime                  getHeureIntervention() const;
    QVector<Distributeur*> getDistributeurs() const;
    bool                   estEffectuee() const;
    bool                   estAIntervenir() const;

    // Mutateurs
    void setDateIntervention(const QDate& dateIntervention);
    void setHeureIntervention(const QTime& heureIntervention);
    void ajouterDistributeur(Distributeur* distributeur);
    void effectuer(bool effectuee);
    void intervenir(bool aIntervenir);

  public slots:
    void selectionnerBac();
    void creerUneIntervention();
};
#endif // INTERVENTION_H
