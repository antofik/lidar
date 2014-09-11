#include "lidar.h"
#include "datafilereader.h"
#include "serialreader.h"

Lidar::Lidar(QObject *parent) : QObject(parent)
{
    static QThread thread;
    moveToThread(&thread);
    thread.start();
}

void Lidar::start_from_serial()
{
#ifdef Q_OS_LINUX
    const char * device = "/dev/ttyACM4";
    LidarMotor = new SMC(device);
    LidarMotor->smcExitSafeStart();
    LidarMotor->smcSetTargetSpeed(820); //TODO control motor
#endif

    serialreader *reader = new serialreader();
    connect(reader, SIGNAL(read(int,int)), this, SLOT(read(int,int)));
    QTimer::singleShot(0, reader, SIGNAL(start()));
}

void Lidar::start_from_file()
{
    datafilereader *reader = new datafilereader();
    connect(reader, SIGNAL(read(int,int)), this, SLOT(read(int,int)));
    QTimer::singleShot(0, reader, SIGNAL(start()));
}

void Lidar::stop()
{
    // TODO: stop
}

int Lidar::checksum(int data[])
{
    uint value = 0;
    for(int i=0;i<10;i++) {
        uint word = data[2*i] + (data[2*i+1] << 8);
        value = (value << 1) + word;
    }

    value = (value & 0x7FFF) + (value >> 15);
    value = value & 0x7FFF;
    return (int)value;
}

void Lidar::read(int index, int value)
{
    const int length = 22;
    const int marker = 0xFA;

    static int packet[length];
    static int pointer = 0;

    if (value == marker) {
        if (pointer == length) {
            int angle = (packet[1] - 0xA0) << 2;
            int speed = (packet[3] << 8) + packet[2];
            /*int d1 = packet[5] & 0x80 == 0 ? packet[4] : -1;
            int d2 = packet[9] & 0x80 == 0 ? packet[8] : -1;
            int d3 = packet[13] & 0x80 == 0 ? packet[12] : -1;
            int d4 = packet[17] & 0x80 == 0 ? packet[16] : -1;
            */
            const int mask = 0x1f;
            unsigned int d1 = packet[4] + ((packet[5] & mask) << 8);
            unsigned int d2 = packet[8] + ((packet[9] & mask) << 8);
            unsigned int d3 = packet[12] + ((packet[13] & mask) << 8);
            unsigned int d4 = packet[16] + ((packet[17] & mask) << 8);

            const unsigned int errorMask = 0xC0;
            if ((packet[5] & errorMask) != 0) d1 = -1;
            if ((packet[9] & errorMask) != 0) d2 = -1;
            if ((packet[13] & errorMask) != 0) d3 = -1;
            if ((packet[17] & errorMask) != 0) d4 = -1;

            int chk1 = (packet[21]  << 8) + packet[20];
            int chk2 = checksum(packet);

            std::cout << "speed:" << speed/60 << std::endl;
            std::cout.flush();

            if (chk1==chk2)
                emit data(speed, angle, d1, d2, d3, d4);
        }
        pointer = 0;
    }

    if (pointer < length)
        packet[pointer] = value;
    pointer++;
}
