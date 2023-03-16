#ifndef DISTRIBUTEUR_H
#define DISTRIBUTEUR_H

struct Produits
{

};

struct Localisation
{

};

class Distributeur
{
public:
    Distributeur();
private:
    int identifiant;
    int prix;
    Produits produit;
    int poidsTotal;
    int poidsActuelle;
    int hydroetrie;
    Localisation position;
};

#endif // DISTRIBUTEUR_H
