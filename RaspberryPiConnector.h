#ifndef RASPBERRYPICONNECTOR_H
#define RASPBERRYPICONNECTOR_H

#include <QObject>
#include <thread>

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
    void gpioListener(RaspberryPiConnector* rpiConnector);
    void gpioActivateChangedCallback();

    bool gpioListenerRunning = true;
    bool gpioActive = false;
    bool buttonCanBePressed = true;
    std::thread listenerThread;
};

#endif // RASPBERRYPICONNECTOR_H
