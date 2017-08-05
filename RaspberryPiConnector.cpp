#include "RaspberryPiConnector.h"

RaspberryPiConnector::RaspberryPiConnector(QObject *parent)
    : QObject(parent)
{
#ifdef __RASPBERRYPI
    workerThread = new GPIOWorkerThread();
    connect(workerThread, &GPIOWorkerThread::gpioStatusChanged, this, &RaspberryPiConnector::gpioStatusWasChanged);
    connect(workerThread, &GPIOWorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
#endif
}

RaspberryPiConnector::~RaspberryPiConnector()
{
#ifdef __RASPBERRYPI
    workerThread->m_running = false;
#endif
}

bool RaspberryPiConnector::isButtonPressed()
{
    return gpioActive;
}

void RaspberryPiConnector::gpioStatusWasChanged(bool status)
{
    gpioActive = status;
    emit buttonPressedChanged();
}
