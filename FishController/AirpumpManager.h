#ifndef AIRPUMPMANAGER_H
#define AIRPUMPMANAGER_H

//Interval timer, turns the pump on and off with the interval of ONTIME.
#define INTERVAL_TIMER false
#define OFFTIME 24
#define ONTIME 3

#include "Arduino.h"
#include "Task.h"
#include "IOManager.h"

class AirpumpManager : public Task
{
public:
    AirpumpManager(IOManager* _IOManager);
    virtual void run() override;
    virtual void dateRun(int) override;

protected:
    IOManager* ManagerPointer;
    #if INTERVAL_TIMER
        int lastRunTime = 0;
    #else
        bool airPumpStatus = false;
    #endif
};

#endif
