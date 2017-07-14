#include "RaspberryPiConnector.h"
#include <GPIOClass.h>
#include <functional>

RaspberryPiConnector::RaspberryPiConnector(QObject *parent)
    : QObject(parent)
    , listenerThread(&RaspberryPiConnector::gpioListener, this)
{
}

RaspberryPiConnector::~RaspberryPiConnector()
{
    gpioListenerRunning = false;
    listenerThread.join();
}

bool RaspberryPiConnector::buttonPressed()
{
    return gpioActive;
}

void RaspberryPiConnector::gpioListener(RaspberryPiConnector* rpiConnector)
{
    GPIOClass* gpio = new GPIOClass("22");
    gpio->setdir_gpio("in");
    string input;
    bool before = false;
    while(gpioListenerRunning)
    {
        before = gpioActive;
        gpio->getval_gpio(input);
        if (input == "0") {
            gpioActive = buttonCanBePressed ? false : gpioActive;
        }
        else
        {
            gpioActive = buttonCanBePressed ? true : gpioActive;
        }

        if(before != gpioActive)
            this->gpioActivateChangedCallback();
    }
    delete gpio;
}

void RaspberryPiConnector::gpioActivateChangedCallback()
{
    emit buttonPressedChanged();
}
