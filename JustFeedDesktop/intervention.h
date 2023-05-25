/**
 * @file        intervention.h
 * @brief       Déclaration de la classe Intervention.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.2
 * @date        2023
 */
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include <QDateTime>
#include <QVector>
#include <QString>
#include <QTime>

/**
 * @def ID_INTERVENTION_NON_DEFINI
 * @brief Définit la valeur d'un id non défini
 */
#define ID_INTERVENTION_NON_DEFINI -1

class Distributeur;
class Produit;
class BaseDeDonnees;

class Intervention
{
  public:
    /**
     * @enum TableIntervention
     * @brief Les colonnes de la table Intervention
     */
    enum TableIntervention
    {
        ID,
        ID_OPERATEUR,
        ID_DISTRIBUTEUR,
        DATE_INTERVENTION,
        A_REMPLIR,
        A_DEPANNER,
        ETAT
    };

    enum TableApprovisionnement
    {
        ID_APPROVISIONNEMENT,
        ID_INTERVENTION,
        ID_BAC,
        POIDS_A_PREVOIR,
        HEURE_APPROVISIONNEMENT
    };
    /**
     * @enum EtatIntervention
     * @brief Les différents états d'une intervention
     */
    enum EtatIntervention
    {
        INCONNU = -1,
        A_FAIRE,
        VALIDEE,
        EN_COURS,
        NB_ETATS
    };

  private:
    BaseDeDonnees*         baseDeDonnees;      //!< association avec la base de données
    QDate                  dateIntervention;   //!< la date de l'intervention
    QVector<QTime>         heuresIntervention; //!< l'heure de l'intervention
    QVector<Distributeur*> distributeurs;  //!< les distributeurs sur lesquels il faut intervenir
    bool                   aRemplir;       //!< si on doit remplir au moins un distributeur
    bool                   aDepanner;      //!< si on doit dépanner au moins un distributeur
    int                    idIntervention; //!< id de l'intervention
    int                    idOperateur;    //!< id de l'opérateur
    int                    idDistributeur; //!< id du distributeur au quel l'intervention appartient
    EtatIntervention       etat;           //!< etat de l'intervention

  public:
    explicit Intervention(QVector<Distributeur*> listeDistributeursAIntervenir);
    Intervention(int     idIntervention,
                 int     idOperateur,
                 int     idDistributeur,
                 QDate   dateIntervention,
                 bool    aRemplir,
                 bool    aDepanner,
                 QString etat);
    ~Intervention();

    QDate                  getDateIntervention() const;
    QVector<Distributeur*> getDistributeurs() const;
    bool                   getARemplir() const;
    bool                   getADepanner() const;
    int                    getIdIntervention() const;
    int                    getIdOperateur() const;
    int                    getIdDistributeur() const;
    QString                getEtat() const;
    QString                getEtatFormate() const;
    bool                   estEffectuee() const;
    bool                   estAIntervenir() const;
    void                   setDateIntervention(const QDate& dateIntervention);
    void                   setARemplir(const bool& aRemplir);
    void                   setADepanner(const bool& aDepanner);
    void                   setIdOperateur(const int& idOperateur);
    void                   setIdIntervention(const int& numeroIntervention);
    void                   setIdDistributeur(const int& numeroDistributeur);
    void                   setEtat(const QString& numeroDistributeur);
    void                   ajouterDistributeur(Distributeur* distributeur);
    void                   effectuer(bool effectuee);
    void                   intervenir(bool aIntervenir);
    void                   creer();
    void                   affecterEtatIntervention(int indexDistributeur);
    int                    ajouterIntervention(int indexDistributeur);
    void                   ajouterApprovisionnement(int indexDistributeur);
    int                    estPlanifiee(int idDistributeur);
    bool                   estBacAttribue(int idDistributeur, int idBac);

    static QString          getEtat(EtatIntervention etat);
    static EtatIntervention getEtat(const QString& etat);
    static QString          getEtatFormate(EtatIntervention etat);
};

#endif // INTERVENTION_H
