#ifndef COMANAGER
#define COMANAGER

#define INTERVALRUNNING false //Uses on time as hour delay between triggers.
#define ONTIME 10
#define OFFTIME 11

#include "arduino.h"
#include "Task.h"
#include "IOManager.h"

class COManager : public Task
{
public:
    COManager(IOManager *);

    virtual void run();
    virtual void dateRun(int);

protected:
    IOManager * IOManagerSave;
    #if INTERVALRUNNING
        bool CO2Status = LOW;
        int lastRunTime = 0;
    #endif
};

#endif