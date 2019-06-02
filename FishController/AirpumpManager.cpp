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

    if (hour >= OFFTIME)
    {
        Serial.println("Airpump off");
        airPumpStatus = false;
        ManagerPointer->setAirpump(airPumpStatus);
    }
    else if (hour >= ONTIME)
    {
        Serial.println("Airpump On");
        airPumpStatus = true;
        ManagerPointer->setAirpump(airPumpStatus);
    }
    #endif
}