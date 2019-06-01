#include "IOManager.h"

IOManager::IOManager()
{
    pinMode(DrainPin, OUTPUT);
    pinMode(RefillPin, OUTPUT);

    pinMode(indFillLED, OUTPUT);
    pinMode(indDrainLED, OUTPUT);
    pinMode(indAboveFull, OUTPUT);
    pinMode(indBelowBottom, OUTPUT);
    pinMode(indDayLight, OUTPUT);
    pinMode(indNightLight, OUTPUT);

    pinMode(buttonTopUp, INPUT);
    pinMode(buttonWaterChange, INPUT);
    pinMode(lightOnButton, INPUT);
    pinMode(lightOffButton, INPUT);

    pinMode(topFloatPin, INPUT);
    pinMode(toppestFloatPin, INPUT);
    pinMode(buttomFloatPin, INPUT);
    pinMode(buttomestFloatPin, INPUT);
}

void IOManager::run()
{
    //Toppest Float.
    bool toppestFloatState = digitalRead(toppestFloatPin);
    #if flipFloats
        toppestFloatState = !toppestFloatState;
    #endif

    if (toppestFloatState == LOW)
    {
        Serial.println("Above High");
        fillState = HIGH;
        #if flipLEDS
            digitalWrite(indAboveFull, LOW);
        #else
            digitalWrite(indAboveFull, HIGH);
        #endif
    }
    else
    {
        #if flipLEDS
            digitalWrite(indAboveFull, HIGH);
        #else
            digitalWrite(indAboveFull, LOW);
        #endif
    }

    //Bottomest Float.
    bool bottomestFloatState = digitalRead(buttomestFloatPin);
    #if flipFloats
        bottomestFloatState = !bottomestFloatState;
    #endif

    if (bottomestFloatState == LOW)
    {
        Serial.println("Below LOW");
        fillState = HIGH;
        #if flipLEDS
            digitalWrite(indBelowBottom, LOW);
        #else
            digitalWrite(indBelowBottom, HIGH);
        #endif
    }
    else
    {
        #if flipLEDS
            digitalWrite(indBelowBottom, HIGH);
        #else
            digitalWrite(indBelowBottom, LOW);
        #endif
    }

    //Reading Floats
    bool topFloatState = digitalRead(topFloatPin);
    bool bottomFloatState = digitalRead(buttomFloatPin);
    #if flipFloats
        topFloatState = !topFloatState;
        bottomFloatState = !bottomFloatState;
    #endif
    if (topFloatState != topFloatStateOld)
    {
        topFloatStateOld = topFloatState;
        for (int i = 0; i < ButtonArrayDepth; i++)
        {
            ButtonArray[i]->topFloat(topFloatState);
        }
    }
    if (bottomFloatState != bottomFloatStateOld)
    {
        bottomFloatStateOld = bottomFloatState;
        for (int i = 0; i < ButtonArrayDepth; i++)
        {
            ButtonArray[i]->bottomFloat(bottomFloatState);
        }
    }


    //Writing Solenoids.
    #if flipSolenoids
        digitalWrite(DrainPin, !drainState);
        digitalWrite(RefillPin, !fillState);
    #else   
        digitalWrite(DrainPin, drainState);
        digitalWrite(RefillPin, fillState);
    #endif

    //Writing LED Status.
    #if flipLEDS
        digitalWrite(indDrainLED, !drainState);
        digitalWrite(indFillLED, !fillState);
        digitalWrite(indDayLight, !dayLightState);
        digitalWrite(indNightLight, !nightLightState);
        digitalWrite(indAirPump, !airPumpStatus):
    #else
        digitalWrite(indDrainLED, drainState);
        digitalWrite(indFillLED, fillState);
        digitalWrite(indDayLight, dayLightState);
        digitalWrite(indNightLight, nightLightState);
        digitalWrite(indAirPump, airPumpStatus);
    #endif

    //Debouncing.
    bool TopUpButton = digitalRead(buttonTopUp);
    bool WaterChangeButton = digitalRead(buttonWaterChange);
    bool LightOnButton = digitalRead(lightOnButton);
    bool LightOffButton = digitalRead(lightOffButton);

    #if flipButtons
        TopUpButton = !TopUpButton;
        WaterChangeButton = !WaterChangeButton;
        LightOnButton = !LightOnButton;
        LightOffButton = !LightOffButton;
    #endif

    int timeNow = millis();
    //Water Change Buttons
    if (buttonTimer == 0)
    {
        if (TopUpButton || WaterChangeButton)
        {
            buttonTimer = timeNow;
        }
    }
    else if( (TopUpButton || WaterChangeButton) && timeNow - buttonTimer >= DebounceTime )
    {
        buttonTimer = 0;
        for (int i = 0; i < ButtonArrayDepth; i++)
        {
            if(TopUpButton)
            {
                ButtonArray[i]->topButton();
            }
            if(WaterChangeButton)
            {
                ButtonArray[i]->changeButton();
            }
        }
    }

    //DayLight Buttons
    if (buttonTimer2 == 0)
    {
        if (LightOnButton || LightOffButton)
        {
            buttonTimer2 = timeNow;
        }
    }
    else if( (LightOnButton || LightOffButton) && timeNow - buttonTimer2 >= DebounceTime)
    {
        buttonTimer2 = 0;
        if (LightOnButton)
        {
            dayLightState = !dayLightState;
        }
        else if (LightOffButton)
        {
            nightLightState = !nightLightState;
        }
    }

    //DayNightLight
    #if flipLight
        digitalWrite(dayLights, !dayLightState);
        digitalWrite(nightLights, !nightLightState);
    #else
        digitalWrite(dayLights, dayLightState);
        digitalWrite(nightLights, nightLightState);
    #endif

    //Airpump
    #if flipAirpump
        digitalWrite(AirPump, !airPumpStatus);
    #else
        digitalWrite(AirPump, airPumpStatus)
    #endif
}

void IOManager::dateRun(int)
{
    return;
}

void IOManager::registerToInputs(funPoint runner)
{
    int i = ButtonArrayDepth;
    ButtonArrayDepth++;

    ButtonArray[i] = runner;
    
    return;
}

//HIGH, true is one: LOW, false is off.
void IOManager::fill(bool state)
{
    fillState = state;
}

//HIGH, true is one: LOW, false is off.
void IOManager::drain(bool state)
{
    drainState = state;
}

void IOManager::dayLight(bool currentDayState)
{
    dayLightState = currentDayState;
}

void IOManager::nightLight(bool currentNightState)
{
    nightLightState = currentNightState;
}

void IOManager::setAirpump(bool currentAirpumpState)
{
    airPumpStatus = currentAirpumpState;
}