#include "ihmjustfeed.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHMJustFeed w;
    w.showFullScreen();
    return a.exec();
}
