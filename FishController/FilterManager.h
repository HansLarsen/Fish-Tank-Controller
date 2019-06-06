#ifndef FILTERMANAGER
#define FILTERMANAGER

#include "IOManager.h"
#include "Task.h"
#include "TemperatureSensor.h"

class FilterManager : public Task
{
public:
    FilterManager(IOManager* _IOManager);
    virtual void run();
    virtual void dateRun(int);

protected:
    IOManager * IOManagerSave;
};

#endif