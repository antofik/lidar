#include "mainwindow.h"
#include <QApplication>

#ifdef Q_OS_LINUX
#include "Arduino.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void setup(){}

void loop(){}
