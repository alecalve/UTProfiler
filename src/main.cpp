#include <QApplication>

#include "qt/mainwindow.h"
#include "uvmanager.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
