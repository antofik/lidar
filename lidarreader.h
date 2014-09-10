#ifndef LIDARREADER_H
#define LIDARREADER_H

#include <QObject>
#include <Qt>
#include <QtCore>
#include <QTimer>
#include <QThread>
#include <iostream>
#include <fstream>

class LidarReader : public QObject
{
    Q_OBJECT
public:
    explicit LidarReader(QObject *parent = 0);
    int distance[360];

signals:
    void data(int,int,int,int,int,int);

public slots:
    void start();
    void start_from_file();
    void stop();

private slots:
    void read(int,int);

private:
    QTimer timer;
    bool from_file;
    FILE* file;
    int checksum(int data[]);

};

#endif // LIDARREADER_H
