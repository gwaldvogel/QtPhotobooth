#include "GPIOWorkerThread.h"

#include <GPIOClass.h>

void GPIOWorkerThread::run()
{
    GPIOClass* gpio = new GPIOClass("22");
    gpio->setdir_gpio("in");
    string input;
    bool before = false;
    while(m_running)
    {
        before = gpioStatus;
        gpio->getval_gpio(input);
        if (input == "0") {
            gpioStatus = false;
        }
        else
        {
            gpioStatus = true;
        }

        if(before != gpioStatus)
            emit gpioStatusChanged(gpioStatus);
    }
    delete gpio;
}
