#include "CO2.h"

COManager::COManager(IOManager * _IOManager)
{
    IOManagerSave = _IOManager;
}

void COManager::run()
{

}

void COManager::dateRun(int hour)
{
    #if INTERVALRUNNING
        if (hour - lastRunTime >= ONTIME)
        {
            lastRunTime = hour;
            CO2Status = !CO2Status;
            IOManagerSave->setCO(CO2Status);
        }
    #else
        if (hour == ONTIME)
        {
            IOManagerSave->setCO(HIGH);
        }
        else if(hour == OFFTIME)
        {
            IOManagerSave->setCO(LOW);
        }
    #endif    
}