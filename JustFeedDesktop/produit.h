#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>

class Produit
{
private :
    double prix; //<! prix au 100 grammes du produit
    QString nom; //<! nom du produit

public:
    Produit();
    Produit(int prix, QString nom);
    ~Produit();

    // Accesseurs
    double getPrix() const;
    QString getNom() const;

    //Mutateurs
    void setPrix(const double prix);
    void setNom(const QString nom);
};

#endif // PRODUIT_H
