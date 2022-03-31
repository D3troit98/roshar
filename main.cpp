#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Wheel of time");
    QCoreApplication::setOrganizationDomain("Cosmere");
    QCoreApplication::setApplicationName("Roshar");


    MainWindow w;
    w.show();
    return a.exec();
}
