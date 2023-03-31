QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    bac.cpp \
    communication.cpp \
    distributeur.cpp \
    intervention.cpp \
    main.cpp \
    ihmjustfeed.cpp \
    produit.cpp \
    serveur.cpp \
    statistiques.cpp

HEADERS += \
    bac.h \
    communication.h \
    distributeur.h \
    ihmjustfeed.h \
    intervention.h \
    produit.h \
    serveur.h \
    statistiques.h

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
