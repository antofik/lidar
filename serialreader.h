#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>

class serialreader : public QObject
{
    Q_OBJECT
public:
    explicit serialreader(QObject *parent = 0);    
    void stop();

signals:
    void read(int index, int value);

public slots:
    void start();

private:
    bool running;

};

#endif // SERIALREADER_H
