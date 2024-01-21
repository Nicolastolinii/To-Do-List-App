#include "mainwindow.h"
#include <QIcon>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon appIcon(":/icon.ico");
    w.setWindowIcon(appIcon);
    w.show();
    return a.exec();
}
