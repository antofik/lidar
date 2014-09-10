#include "lidarreader.h"
#include "datafilereader.h"

LidarReader::LidarReader(QObject *parent) : QObject(parent)
{
    static QThread thread;
    moveToThread(&thread);
    thread.start();
}

void LidarReader::start()
{
    from_file = false;
    // TODO: read from serial
}

void LidarReader::start_from_file()
{
    datafilereader *reader = new datafilereader();
    connect(reader, SIGNAL(read(int,int)), this, SLOT(read(int,int)));
    QTimer::singleShot(0, reader, SIGNAL(start()));

  /*  from_file = true;

    std::ifstream file("F:/Programming/Robotics/data1", std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        std::streampos size;
        char* memblock;

        size = file.tellg();
        memblock = new char[size];
        file.seekg (0, std::ios::beg);
        file.read (memblock, size);
        file.close();

        for(int i=0;i<size;i+=4) {
            std::cout << memblock[i];
        }
      }*/
}

void LidarReader::stop()
{

}

/*
def checksum(data):
    """Compute and return the checksum as an int."""
    # group the data by word, little-endian
    data_list = []
    for t in range(10):
        data_list.append( data[2*t] + (data[2*t+1]<<8) )

    # compute the checksum on 32 bits
    chk32 = 0
    for d in data_list:
        chk32 = (chk32 << 1) + d

    # return a value wrapped around on 15bits, and truncated to still fit into 15 bits
    checksum = (chk32 & 0x7FFF) + ( chk32 >> 15 ) # wrap around to fit into 15 bits
    checksum = checksum & 0x7FFF # truncate to 15 bits
    return int( checksum */

int LidarReader::checksum(int data[])
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

void LidarReader::read(int index, int value)
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
            int d1 = packet[4];
            int d2 = packet[8];
            int d3 = packet[12];
            int d4 = packet[16];

            int chk1 = (packet[21]  << 8) + packet[20];
            int chk2 = checksum(packet);

            if (chk1==chk2)
                emit data(speed, angle, d1, d2, d3, d4);
        }
        pointer = 0;
    }

    if (pointer < length)
        packet[pointer] = value;
    pointer++;
}
