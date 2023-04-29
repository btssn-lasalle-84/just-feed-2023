/**
 * @file        Intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QDateTime>
#include <QTime>
#include <QVector>
#include <QtWidgets>
#include <QDate>

/**
 * @def TITRE_INTERVENTION
 * @brief Définit le titre de la boîte de dialogue
 */
#define TITRE_INTERVENTION QString("Planifier une intervention")

class Distributeur;
class Produit;
class IHMJustFeed;
class bac;

class Intervention : public QDialog
{
    Q_OBJECT
  private:
    IHMJustFeed*           ihmJustFeed;      //!< association vers l'ihm principale
    QDate                  dateIntervention; //!< la date de l'intervention
    QVector<Distributeur*> distributeurs;    //!< les distributeurs sur lesquels il faut intervenir
    bool                   effectuee;        //!< si l'intervention a été effectuée
    QVector<QLabel*>       nomDistributeurs; //!< nom du distributeur et son numero
    QVector<QLabel*>       labelsBac;        //!< conteneur de QLabel de bac
    QVector<QVector<QLabel*>> labelsDesBacs; //!< vecteur de vecteur de QLabel, pour stocker les bacs
    QVector<QLabel*>       labelsProduit;           //!< conteneur de QLabel de produit
    QVector<QVector<QLabel*>> labelsDesProduits;    //!< vecteur de vecteur de QLabel, pour stocker les produits
    QVector<QLabel*>       labelsPourcentage;           //!< conteneur de QLabel de produit
    QVector<QVector<QLabel*>> labelsDesPourcentage;
     QVBoxLayout*          layoutBacs; //!< positionnement des bacs dans la boîte de dialogue
     QHBoxLayout* layoutDistributeurs;

    void                   initialiserBoiteDeDialogue();
    void                   instancierWidgets();
    void                   initialiserWidgets();
    void                   positionnerWidgets();
    void                   initialiserEvenements();

  public:
    explicit Intervention(QVector<Distributeur*> listeDistributeursAIntervenir,
                          IHMJustFeed*           parent = 0);
    ~Intervention();

    // Accesseurs
    QDate                  getDateIntervention() const;
    QVector<Distributeur*> getDistributeurs() const;
    double                 getEffectuee() const;

    // Mutateurs
    void setDateIntervention(const QDate& dateIntervention);
    void ajouterDistributeur(Distributeur* distributeur);
    void setEffectuee(const bool effectuee);
    double poidsAPrevoir(const int numeroDistributeur, const int numeroBac);
};

#endif // INTERVENTION_H
