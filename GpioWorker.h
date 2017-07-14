#ifndef GPIOWORKER_H
#define GPIOWORKER_H

#include <QObject>

class GpioWorker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter)
    {


    }

signals:
    void resultReady();
    void gpioPressed(bool pressed)
};

#endif // GPIOWORKER_H
