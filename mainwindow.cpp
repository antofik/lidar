#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <qmath.h>
#include <mocklidar.h>
#include <QTimer>
#include "lidar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int size = 10;
    int x0 = 250;
    int y0 = 250;
    int radius = 200;
    qreal k = 3.1415926535/180;

    for(int i=0;i<360;i++) {
        map[i] = 999999;
        QLabel *l = new QLabel(ui->frame);
        l->setText(".");
        //l->setStyleSheet("background:gray;border-radius:5px");
        int x = x0 + radius * qCos(i * k);
        int y = y0 + radius * qSin(i * k);
        l->setGeometry(x, y, size, size);
        points[i] = l;
    }

    QLabel *center = new QLabel(ui->frame);
    center->setStyleSheet("background:green;border-radius:5px");
    center->setGeometry(x0, y0, size, size);

    Lidar *reader = new Lidar();
    MockLidar *lidar = new MockLidar();
    connect(reader, SIGNAL(data(int,int, int,int, int, int)), lidar, SLOT(data(int,int,int,int,int,int)));
    connect(lidar, SIGNAL(point(int,int)), this, SLOT(point(int,int)));
    QTimer::singleShot(0, lidar, SLOT(start()));    
    QTimer::singleShot(0, this, SLOT(display()));


    /***
     *
     *  Use start_from_serial() to read data from serial port (lidar)
     *  User start_from_file() to read data from binary file
     *
     ***/
    //QTimer::singleShot(0, reader, SLOT(start_from_file()));
    QTimer::singleShot(0, reader, SLOT(start_from_serial()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::point(int angle, int distance)
{
    map[angle] = distance/4;
}

void MainWindow::display()
{
    int size = 10;
    int x0 = 250;
    int y0 = 250;
    qreal k = 3.1415926535/180;

    for(int i=0;i<360;i++)
    {
        int x = x0 + map[i] * qCos(i*k);
        int y = y0 + map[i] * qSin(i*k);
        points[i]->setGeometry(x, y, size, size);
    }

    QTimer::singleShot(0, this, SLOT(display()));
}
