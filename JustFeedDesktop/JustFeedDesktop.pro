QT       += core gui widgets sql
QT       += webkitwidgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    bac.cpp \
    basededonnees.cpp \
    communication.cpp \
    configurationdistributeur.cpp \
    distributeur.cpp \
    intervention.cpp \
    main.cpp \
    ihmjustfeed.cpp \
    planificationintervention.cpp \
    produit.cpp \
    serveur.cpp \
    statistiques.cpp

HEADERS += \
    bac.h \
    basededonnees.h \
    communication.h \
    configurationdistributeur.h \
    distributeur.h \
    ihmjustfeed.h \
    intervention.h \
    planificationintervention.h \
    produit.h \
    serveur.h \
    statistiques.h

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
