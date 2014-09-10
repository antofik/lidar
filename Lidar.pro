QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lidar
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        mocklidar.cpp \
        datafilereader.cpp \
        serialreader.cpp \
        lidar.cpp

HEADERS  += mainwindow.h \
        mocklidar.h \
        datafilereader.h \
        serialreader.h \
        lidar.h

FORMS    += mainwindow.ui

unix{
    SOURCES += smc-wrapper/smc.cpp
    HEADERS += smc-wrapper/smc.h
    LIBS += /home/ubuntu/c_enviroment/*.so
    INCLUDEPATH += /usr/include/
    INCLUDEPATH += smc-wrapper
    INCLUDEPATH += /home/ubuntu/c_enviroment/hardware
    INCLUDEPATH += /home/ubuntu/c_enviroment/hardware/arduino
    INCLUDEPATH += /home/ubuntu/c_enviroment/hardware/arduino/cores
    INCLUDEPATH += /home/ubuntu/c_enviroment/hardware/arduino/cores/arduino
    INCLUDEPATH += /home/ubuntu/c_enviroment/hardware/arduino/variants
    INCLUDEPATH += /home/ubuntu/c_enviroment/hardware/arduino/variants/sunxi
    INCLUDEPATH += /home/ubuntu/c_enviroment/libraries
    INCLUDEPATH += /home/ubuntu/c_enviroment/libraries/SPI
    INCLUDEPATH += /home/ubuntu/c_enviroment/ibraries/Wire
    INCLUDEPATH += /home/ubuntu/c_enviroment/libraries/PN532_SPI
}

win32 {

}
