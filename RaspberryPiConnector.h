#ifndef RASPBERRYPICONNECTOR_H
#define RASPBERRYPICONNECTOR_H

#include <QObject>
#include <thread>

#include <GPIOWorkerThread.h>

class RaspberryPiConnector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool buttonPressed READ buttonPressed NOTIFY buttonPressedChanged)

public:
    explicit RaspberryPiConnector(QObject *parent = nullptr);
    ~RaspberryPiConnector();
    bool buttonPressed();

signals:
    void buttonPressedChanged();

private:
    void gpioStatusWasChanged(bool status);
    bool gpioActive = false;
    bool buttonCanBePressed = true;

    GPIOWorkerThread* workerThread = NULL;
};

#endif // RASPBERRYPICONNECTOR_H
