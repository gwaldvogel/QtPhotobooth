#include "RaspberryPiConnector.h"

RaspberryPiConnector::RaspberryPiConnector(QObject *parent)
    : QObject(parent)
    , workerThread(new GPIOWorkerThread())
{
    connect(workerThread, &GPIOWorkerThread::gpioStatusChanged, this, &RaspberryPiConnector::gpioStatusWasChanged);
    connect(workerThread, &GPIOWorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

RaspberryPiConnector::~RaspberryPiConnector()
{
    workerThread->m_running = false;
}

bool RaspberryPiConnector::buttonPressed()
{
    return gpioActive;
}

void RaspberryPiConnector::gpioStatusWasChanged(bool status)
{
    gpioActive = status;
    emit buttonPressedChanged();
}
