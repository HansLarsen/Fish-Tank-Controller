#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#define DAYONTIME 7
#define DAYOFFTIME 20
#define NIGHTONTIME 22
#define NIGHTOFFTIME 2

#include "Task.h"
#include "IOManager.h"

class LightManager : public Task
{
public:
    LightManager(IOManager* _IOManager);
    virtual void run() override;
    virtual void dateRun(int) override;

protected:
    IOManager* ManagerSaved;
    bool dayLightStatus = HIGH;
    bool nightLightStatus = LOW;
};

#endif