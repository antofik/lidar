#ifndef MOCKLIDAR_H
#define MOCKLIDAR_H

#include <QObject>
#include <Qt>
#include <QtCore>
#include <QTimer>

class MockLidar : public QObject
{
    Q_OBJECT
public:
    explicit MockLidar(QObject *parent = 0);

signals:
    void point(int angle, int distance);

public slots:
    void start();
    void data(int,int,int,int,int,int);

private slots:
    void measure();
    void move();

private:
    int width = 250;
    int height = 250;
    qreal x = 50;
    qreal y = 50;
    int angle = 90;
    bool moving = true;
    qreal velocity = 100;
    qreal moveDelta = 0.05;
};

#endif // MOCKLIDAR_H
