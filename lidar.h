#ifndef LIDARREADER_H
#define LIDARREADER_H

#include <QObject>
#include <Qt>
#include <QtCore>
#include <QTimer>
#include <QThread>
#include <iostream>
#include <fstream>

#ifdef Q_OS_LINUX
#include "smc.h"
#endif


class Lidar : public QObject
{
    Q_OBJECT
public:
    explicit Lidar(QObject *parent = 0);
    int distance[360];

signals:
    void data(int,int,int,int,int,int);

public slots:
    void start_from_serial();
    void start_from_file();
    void stop();

private slots:
    void read(int,int);

private:
    QTimer timer;
    bool from_file;
    FILE* file;
    int checksum(int data[]);
#ifdef Q_OS_LINUX
    SMC *LidarMotor;
#endif

};

#endif // LIDARREADER_H
