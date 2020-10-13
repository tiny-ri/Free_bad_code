#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Book");
    a.setApplicationVersion("0.2");
    a.setOrganizationName("Mephi");
    a.setOrganizationDomain("mephi.ru");

    MainWindow w;
    w.show();
    return a.exec();
}

