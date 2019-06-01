#include "RefillProgram.h"
#define SMALLFILLTIMER 1000
//hours * min * secs * millis; to get hours to millis.
#define MAXCHANGETIME 0.5*60*60*1000

RefillProgram::RefillProgram(IOManager* Manager)
{
    managerPointer = Manager;
}

void RefillProgram::run()
{
    int timeNow = millis();
    if(refillIsActive)
    {
        if (timeNow - refillTimer >= MAXCHANGETIME)
        {
            Serial.println("Took to long to fill");
            managerPointer->fill(false);
            managerPointer->drain(false);
            refillTimer = 0;
            refillIsActive = false;
        }
    }
    else if(smallFillIsActive)
    {
        if(timeNow - smallFillTime >= SMALLFILLTIMER)
        {
            smallFillIsActive = false;
            managerPointer->fill(false);
        }
    }

}

void RefillProgram::dateRun(int hour)
{
    refillIsActive = true;
    managerPointer->drain(true);
    refillTimer = millis();
}

void RefillProgram::topButton()
{
    smallFillIsActive = true;
    smallFillTime = millis();
    managerPointer->fill(true);
}

void RefillProgram::changeButton()
{
    refillIsActive = true;
    managerPointer->drain(true);
    refillTimer = millis();
}

void RefillProgram::topFloat(bool topFloatStatus)
{
    if(topFloatStatus == HIGH)
    {
        smallFillIsActive = false;
        smallFillTime = 0;
        if (goingUp)
        {
            goingUp = false;
            managerPointer->fill(false);
            refillTimer = 0;
        }
    }
}

void RefillProgram::bottomFloat(bool bottomFloatStatus)
{
    if (refillIsActive && bottomFloatStatus == LOW)
    {
        goingUp = true;
        managerPointer->fill(true);
        managerPointer->drain(false);
    }
}