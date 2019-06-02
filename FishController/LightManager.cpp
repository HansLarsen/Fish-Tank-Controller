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
    Serial.println("Light manager: " + String(currentHour));
    if (currentHour >= DAYOFFTIME)
    {
        if (dayLightStatus == HIGH)
        {
            Serial.println("Daylighs off");
            ManagerSaved->dayLight(false);
            dayLightStatus = LOW;
        }
    }
    else if (currentHour >= DAYONTIME)
    {
        if (dayLightStatus == LOW)
        {
            Serial.println("Daylighs on");
            ManagerSaved->dayLight(true);
            dayLightStatus = HIGH;
        }
    }

    if (currentHour >= NIGHTONTIME)
    {
        if (nightLightStatus == LOW)
        {
            Serial.println("Nightlight on");
            ManagerSaved->nightLight(true);
            nightLightStatus = HIGH;
        }
    }
    else if (currentHour >= NIGHTOFFTIME)
    {
        if (nightLightStatus == HIGH)
        {
            Serial.println("Nightlight off");
            ManagerSaved->nightLight(false);
            nightLightStatus = LOW;
        }
    }
}