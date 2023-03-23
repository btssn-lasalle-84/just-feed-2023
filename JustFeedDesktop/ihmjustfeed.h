/**
 * @file        ihmjustfeed.h
 * @brief       Définition de la classe ihmjustfeed.
 * @detail      La classe ihmjustfeed \c Cette classe permet de définir les attributs et les méthodes de la classe.
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
*/
#ifndef IHMJUSTFEED_H
#define IHMJUSTFEED_H

#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>

class IHMJustFeed : public QWidget
{
    Q_OBJECT
private :

public:

    IHMJustFeed(QWidget *parent = nullptr);
    /**
     * @brief Constructeur par défault de la classe IHMJustFeed
     * @see IHMJustFeed
     */
    ~IHMJustFeed();
    /**
     * @brief Destructeur par défault de la classe IHMJustFeed
     * @see IHMJustFeed
     */
};
#endif // IHMJUSTFEED_H
