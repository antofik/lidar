QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lidar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mocklidar.cpp \
    lidarreader.cpp \
    datafilereader.cpp

HEADERS  += mainwindow.h \
    mocklidar.h \
    lidarreader.h \
    datafilereader.h

FORMS    += mainwindow.ui
