#include "AirpumpManager.h"

AirpumpManager::AirpumpManager(IOManager* _IOManager)
{
    ManagerPointer = _IOManager;
}

void AirpumpManager::run()
{
}

void AirpumpManager::dateRun(int hour)
{
    #if INTERVAL_TIMER
        if (hour - lastRunTime >= ONTIME)
        {
            ManagerPointer->setAirPump();
        }
    #else
        if (airPumpStatus == true)
        {
            if (hour > OFFTIME)
            {
                airPumpStatus = false;
                ManagerPointer->setAirpump(airPumpStatus);
            }
        }
        else if (airPumpStatus == false)
        {
            if (hour > ONTIME)
            {
                airPumpStatus = false;
                ManagerPointer->setAirpump(airPumpStatus);
            }
        }
    #endif
}