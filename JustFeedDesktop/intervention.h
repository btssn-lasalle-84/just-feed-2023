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
#include <QtWidgets>

/**
 * @def TITRE_INTERVENTION
 * @brief Définit le titre de la boîte de dialogue
 */
#define TITRE_INTERVENTION QString("Planifier une intervention")
#define ZERO 0
#define QUINZE 15
#define TRENTE 30
#define CINQUANTE 50
#define SOIXANTE 60
#define CENT 100

class Distributeur;
class Produit;
class IHMJustFeed;

class Intervention : public QDialog {
  Q_OBJECT
private:
  IHMJustFeed *ihmJustFeed; //!< association vers l'ihm principale
  QDate dateIntervention;   //!< la date de l'intervention
  QTime heureIntervention;  //!< l'heure de l'intervention
  QVector<Distributeur *>
      distributeurs; //!< les distributeurs sur lesquels il faut intervenir
  bool effectuee;    //!< si l'intervention a été effectuée
  bool aRemplir;     //!< Si l'intervention consiste à remplir
  bool aDepanner;    //!< Si l'intervention consiste à dépanner
  int totalBac;      //!< nombre total de bac
  QVector<QLabel *> nomDistributeurs;  //!< nom du distributeur et son numero
  QVector<QLabel *> labelsBac;         //!< conteneur de QLabel de bac
  QVector<QLabel *> labelsHygrometrie; //!< conteneur de QLabel d'hygrometrie
  QVector<QVector<QLabel *>> labelsDesHygrometries;
  //!< vecteur de vecteur de QLabel, pour stocker ;les
  //!< hygrometries
  //!
  QVector<QVector<QLabel *>>
      labelsDesBacs; //!< vecteur de vecteur de QLabel, pour stocker les bacs
  QVector<QLabel *> labelsProduit; //!< conteneur de QLabel de produit
  QVector<QVector<QLabel *>>
      labelsDesProduits; //!< vecteur de vecteur de QLabel, pour stocker les
                         //!< produits
  QVector<QLabel *> labelsPourcentage; //!< conteneur de QLabel de produit
  QVector<QVector<QLabel *>> labelsDesPourcentage;
  QVBoxLayout
      *layoutBacs; //!< positionnement des bacs dans la boîte de dialogue
  QHBoxLayout *layoutDistributeurs; //!< positionnement des distributeurs et le
                                    //!< contenu dans la boîte de dialogue
  QHBoxLayout *layoutBac; //!< layout qui contient le nom du bac et un checkBox
  QVector<QCheckBox *> labelsCheckbox; //!< vecteur de checkBox
  QVector<QVector<QCheckBox *>>
      labelsDesCheckbox;          //!< vecteur de vecteur de checkBox
  QPushButton *boutonItervention; //!< bouton qui créé une intervention
  QDateEdit *dateEdit;            //!< choix de la date
  QTimeEdit *heureEdit;           //!< choix de l'heure
  void initialiserBoiteDeDialogue();
  void instancierWidgets();
  void initialiserWidgets();
  void initialiserEtatDistributeur();
  void positionnerWidgets();
  void initialiserEvenements();

public:
  explicit Intervention(QVector<Distributeur *> listeDistributeursAIntervenir,
                        IHMJustFeed *parent = 0);
  ~Intervention();

  // Accesseurs
  QDate getDateIntervention() const;
  QVector<Distributeur *> getDistributeurs() const;
  bool estEffectuee() const;
  bool estARemplir() const;
  bool estADepanner() const;
  bool estAIntervenir() const;

  // Mutateurs
  void setDateIntervention(const QDate &dateIntervention);
  void ajouterDistributeur(Distributeur *distributeur);
  void effectuer(bool effectuee);
  void remplir(bool aRemplir);
  void depanner(bool aDepanner);
  void intervenir(bool aIntervenir);

public slots:
  void selectionnerBac();
  void creerUneIntervention();
};
#endif // INTERVENTION_H
