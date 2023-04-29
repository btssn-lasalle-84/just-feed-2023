#include <QApplication>
#include "ihmjustfeed.h"
#include "basededonnees.h"

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application Basketgame
 * @author  Salaun Matthieu
 * @author  Rouanet Nicolas
 * @version 1.0
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    IHMJustFeed  w;
    BaseDeDonnees *baseDeDonnees = BaseDeDonnees::getInstance();
    baseDeDonnees->connecter();
    w.show();

    return a.exec();
}
