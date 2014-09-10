#include "mocklidar.h"
#include "math.h"
#include <iostream>

MockLidar::MockLidar(QObject *parent) :
    QObject(parent)
{
}

void MockLidar::start()
{
    //QTimer *measureTimer = new QTimer();
    //QObject::connect(measureTimer, SIGNAL(timeout()), this, SLOT(measure()));
    //measureTimer->start(1);

    QTimer *moveTimer = new QTimer();
    QObject::connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(1000 * moveDelta);
}

void MockLidar::move()
{
    qreal k = 3.1415926535/180.0;
    qreal distance = moveDelta * velocity;

    qreal xn = x + distance * qCos(k * angle);
    qreal yn = y + distance * qSin(k * angle);

    if (xn > width) xn = width;
    if (yn > height) yn = height;
    if (xn<0) xn = 0;
    if (yn<0) yn = 0;

    if (qAbs(yn-y) < 0.01 || qAbs(xn-x) < 0.01)
    {
        angle = qrand() % 360;
    }
    else
    {
        x = xn;
        y = yn;
    }
}

void MockLidar::measure()
{
    static int angle = 0;
    angle = (angle + 1) % 360;
    qreal k = 3.1415926535/180.0;

    qreal cos = qCos(angle * k);
    qreal sin = qSin(angle * k);

    int v = qAbs(sin) > 0.001 ? (sin > 0 ? height - y : y) / qAbs(sin) : 99999;
    int h = qAbs(cos) > 0.001 ? (cos > 0 ? width - x : x) / qAbs(cos) : 99999;

    int distance = qMin(v, h);

    emit point(angle, distance);
}

void MockLidar::data(int speed, int angle, int l1, int l2, int l3, int l4)
{
    //std::cout<<"<"<<angle << std::endl;

    if (l1 != -1)
        emit point(angle, l1);
    if (l2 != -1)
        emit point(angle+1, l2);
    if (l3 != -1)
        emit point(angle+2, l3);
    if (l4 != -1)
        emit point(angle+3, l4);
}
