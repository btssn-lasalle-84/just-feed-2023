/**
 * @file        ihmjustfeed.cpp
 * @brief       Définition de la classe IHMJustFeed.
 * @details      La classe IHMJustFeed \c Cette classe permet de définir la GUI
 * de l'application EcoClassroomDesktop
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "ihmjustfeed.h"

/**
 * @brief Constructeur par défaut de la classe IHMJustFeed
 * @see ~IHMJustFeed
 */
IHMJustFeed::IHMJustFeed(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;
    setWindowTitle(TITRE_APPLICATION + " " + VERSION_APPLICATION);
    /*resize(qApp->desktop()->availableGeometry(this).width(),
           qApp->desktop()->availableGeometry(this).height());
    setMinimumSize(qApp->desktop()->availableGeometry(this).width(),
                   qApp->desktop()->availableGeometry(this).height());*/
    distributeurs.push_back(new Distributeur());
    show();
}

/**
 * @brief Destructeur de la classe IHMJustFeed
 * @see IHMJustFeed
 */
IHMJustFeed::~IHMJustFeed()
{
    qDebug() << Q_FUNC_INFO;
}
