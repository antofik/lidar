#include "serialreader.h"

#include <Qt>
#include <QtCore>
#include <QTime>
#include <QThread>
#include <iostream>
#include <fstream>

#ifdef Q_OS_LINUX
#include "Arduino.h"
#include "Serial.h"
#endif

serialreader::serialreader(QObject *parent) :
    QObject(parent)
{
    static QThread thread;
    moveToThread(&thread);
    thread.start();
}

void serialreader::start()
{
#ifdef Q_OS_LINUX
    Serial.begin(115200);

    std::cout << "serial started" << std::endl;

    running = true;
    while(running)
    {        
        if (Serial.available() > 0)
        {
            int value = Serial.read();

            /*unsigned char ch = value;
            FILE* fh;
            fh = fopen("data.bin","ab+");
            fwrite(&ch, sizeof(ch),1,fh);
            fclose(fh);*/
            //std::cout << "~" << value << std::endl;

            emit read(-1, value);
        }
        serialEventRun();
    }
#endif
}

void serialreader::stop()
{
    running = false;
}
