#include "produit.h"

/**
 * @brief Constructeur par défaut de la classe produit
 */
Produit::Produit() : prix(0), nom("")
{

}

/**
 * @brief destructeur par défaut de la classe produit
 */
Produit::Produit(int prix, QString nom) : prix(prix), nom(nom)
{

}
