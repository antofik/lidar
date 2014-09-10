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
    int width;
    int height;
    qreal x;
    qreal y;
    int angle;
    bool moving;
    qreal velocity;
    qreal moveDelta;
};

#endif // MOCKLIDAR_H
