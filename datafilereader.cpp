#include "datafilereader.h"
#include <QThread>
#include <Qt>
#include <QtCore>
#include <iostream>
#include <fstream>

datafilereader::datafilereader(QObject *parent) :
    QObject(parent)
{
    static QThread thread;
    moveToThread(&thread);
    thread.start();
}

void datafilereader::start()
{
    std::ifstream file("F:/Programming/Robotics/data1", std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        std::streampos size;
        char* memblock;

        size = file.tellg();
        memblock = new char[size];
        file.seekg (0, std::ios::beg);
        file.read (memblock, size);
        file.close();

        for(int i=0;i<size;i+=4) {
            unsigned char ch = memblock[i];
            emit read(i,(int)ch);

            QTime dieTime= QTime::currentTime().addMSecs(1);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
}
