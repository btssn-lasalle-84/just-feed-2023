/**
 * @file        ihmjustfeed.cpp
 * @brief       Définition de la classe IHMJustFeed.
 * @details     La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application JustFeed (Desktop)
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "ihmjustfeed.h"
#include "distributeur.h"
#include "produit.h"
#include "bac.h"

/**
 * @brief Constructeur par défaut de la classe IHMJustFeed
 */

IHMJustFeed::IHMJustFeed(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;

    initialiserGUI();
    initialiserDistributeurs();
    show();
}

/**
 * @brief Destructeur de la classe IHMJustFeed
 */
IHMJustFeed::~IHMJustFeed()
{
    for(int i = 0; i < distributeurs.size(); ++i)
    {
        delete distributeurs[i];
    }
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief méthode qui initialise la GUI
 */
void IHMJustFeed::initialiserGUI()
{
    // La fenêtre principale
    setWindowTitle(TITRE_APPLICATION + " " + VERSION_APPLICATION);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    resize(screenGeometry.width(), screenGeometry.height());
}

/**
 * @brief méthode qui initianlise les distributeurs avec les bacs et les produits
 */
void IHMJustFeed::initialiserDistributeurs()
{
    distributeurs.push_back(new Distributeur("distributeur-1-sim",
                                             { "44.11161", "4.84856" },
                                             "Grand Frais",
                                             "Distributeur de fruits secs",
                                             "Zone du Coudoulet Rond point du Péage Sud",
                                             "84100",
                                             "Orange",
                                             QDate::fromString("2022-01-08", "yyyy-MM-dd")));
    distributeurs.push_back(new Distributeur("distributeur-2-sim",
                                             { "43.92844", "4.79247" },
                                             "Carrefour",
                                             "Distributeur de fruits secs",
                                             "390 Rue Jean Marie Tjibaou",
                                             "84000",
                                             "Avignon",
                                             QDate::fromString("2022-03-09", "yyyy-MM-dd")));
    distributeurs.push_back(new Distributeur("distributeur-3",
                                             { "43.90252", "4.75280" },
                                             "Cosy Primeurs",
                                             "Distributeur de fruits secs",
                                             "292 Route de Boulbon",
                                             "13570",
                                             "Barbentane",
                                             QDate::fromString("2022-01-10", "yyyy-MM-dd")));

    Produit *pruneaux = new Produit("pruneaux", "Maître Prunille", "Les Pruneaux d'Agen dénoyautés Maître Prunille sont une délicieuse friandise à déguster à tout moment de la journée.",
                                    "761234567890", 1.15);
    Produit *abricot = new Produit("Abricots secs", "Maître Prunille", "L'abricot moelleux, une gourmandise tendre et fruitée!",
                                    "761234566000", 1.13);
    Produit *Cranberries = new Produit("Cranberries", "SEEBERGER", "Cranberries tranchées sucrées séchées ",
                                    "761234569000", 2.1);
    Produit *Banane = new Produit("Banane CHIPS", " BIO VILLAGE", "Banane CHIPS bio ",
                                    "761234560008", 0.76);
    Produit *Raisin = new Produit("Raisin sec", "Petit Prix ", "Raisins secs, huile végétale (graine de coton)",
                                    "761264569090", 0.39);
    Produit *fruitsSec = new Produit("fruits sec", "FRUIDYLLIC", "peut se manger tel que sans préparation. ",
                                    "761234960940", 1.06);
    Produit *cacahuete = new Produit("Cacahuète", "carrefour", "arachide crue blanche décortiquée. pour cuisiner ou pâtisserie ",
                                    "761234561000", 0.49);
    Produit *soja = new Produit("soja", " OFAL BIO ", "SOJA jaune biologique.",
                                    "761234529000", 0.96);
    Produit *basilic = new Produit("Basilic", "DUCROS", "Basilic déshydraté issu de l'agriculture biologique",
                                    "761234679900", 17.18);

    distributeurs[0]->ajouterBac(Bac(pruneaux, 0, 0.));
    distributeurs[0]->ajouterBac(Bac(abricot, 0, 0.));
    distributeurs[0]->ajouterBac(Bac(Cranberries, 0, 0.));
    distributeurs[1]->ajouterBac(Bac(Banane, 0, 0.));
    distributeurs[1]->ajouterBac(Bac(Raisin, 0, 0.));
    distributeurs[1]->ajouterBac(Bac(fruitsSec, 0, 0.));
    distributeurs[2]->ajouterBac(Bac(cacahuete, 0, 0.));
    distributeurs[2]->ajouterBac(Bac(soja, 0, 0.));
    distributeurs[2]->ajouterBac(Bac(basilic, 0, 0.));
}

