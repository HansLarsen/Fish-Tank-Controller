#include "LightManager.h"

LightManager::LightManager(IOManager * _IOManager)
{
    ManagerSaved = _IOManager;
}

void LightManager::run()
{

}

void LightManager::dateRun(int currentHour)
{
    if (currentHour > DAYOFFTIME)
    {
        if (dayLightStatus == HIGH)
        {
            ManagerSaved->dayLight(false);
            dayLightStatus = LOW;
        }
    }
    else if (currentHour > DAYONTIME)
    {
        if (dayLightStatus == LOW)
        {
            ManagerSaved->dayLight(true);
            dayLightStatus = HIGH;
        }
    }

    if (currentHour > NIGHTONTIME)
    {
        if (nightLightStatus == LOW)
        {
            ManagerSaved->dayLight(true);
            nightLightStatus = HIGH;
        }
    }
    else if (currentHour > NIGHTOFFTIME)
    {
        if (nightLightStatus == HIGH)
        {
            ManagerSaved->dayLight(false);
            nightLightStatus = LOW;
        }
    }
}