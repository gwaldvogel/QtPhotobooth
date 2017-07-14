#ifndef GPIOWORKERTHREAD_H
#define GPIOWORKERTHREAD_H

#include <QThread>

class GPIOWorkerThread : public QThread
{
    Q_OBJECT
public:
    void run() override;
    bool m_running = true;
    bool gpioStatus = false;

signals:
    void gpioStatusChanged(bool result);
};

#endif // GPIOWORKERTHREAD_H
