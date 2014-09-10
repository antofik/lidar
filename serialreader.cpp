#include "serialreader.h"

#include <Qt>
#include <QtCore>
#include <QTime>
#include <QThread>

#ifdef Q_OS_LINUX
#include <Arduino.h>
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

    running = true;
    while(running)
    {
        if (Serial.available() > 0)
        {
            int value = Serial.read();
            emit read(-1, value);
        }
    }
#endif
}

void serialreader::stop()
{
    running = false;
}
