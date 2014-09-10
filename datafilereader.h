#ifndef DATAFILEREADER_H
#define DATAFILEREADER_H

#include <QObject>

class datafilereader : public QObject
{
    Q_OBJECT
public:
    explicit datafilereader(QObject *parent = 0);

signals:
    void read(int index, int value);

public slots:
    void start();
};

#endif // DATAFILEREADER_H
