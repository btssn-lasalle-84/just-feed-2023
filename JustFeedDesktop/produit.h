/**
 * @file        produit.h
 * @brief       Déclaration de la classe Produit.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     1.1
 * @date        2023
 */

#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>

class Produit
{
    /**
     * @enum TableProduit
     * @brief Définit les différentes champs de la table Produit
     *
     */
    enum TableProduit
    {
        CHAMP_ID_PRODUIT, //!< Emplacement du nom
        CHAMP_NOM_PRODUIT,
        CHAMP_MARQUE,
        CHAMP_DESCRITION,
        CHAMP_CODE_EAN,
        CHAMP_PRIX,
        CHAMP_POIDS_UNITAIRE,
        CHAMP_VOLUME_UNITAIRE,
        NbChamps
    };

  private:
    int     id;          //!< id du produit
    QString nom;         //!< nom du produit
    QString marque;      //!< marque du produit
    QString description; //!< description du produit
    QString codeProduit; //!< code EAN 13 du produit
    double  prix;        //!< prix au 100 grammes du produit

  public:
    Produit();
    Produit(int     id,
            QString nom,
            QString marque,
            QString description,
            QString codeProduit,
            double  prix);
    Produit(QStringList produit);
    ~Produit();

    // Accesseurs
    int     getId() const;
    QString getNom() const;
    QString getMarque() const;
    QString getDescription() const;
    QString getCodeProduit() const;
    double  getPrix() const;

    // Mutateurs
    void setId(int id);
    void setNom(const QString& nom);
    void setMarque(const QString& marque);
    void setDescription(const QString& description);
    void setCodeProduit(const QString& codeProduit);
    void setPrix(const double prix);
};

#endif // PRODUIT_H
