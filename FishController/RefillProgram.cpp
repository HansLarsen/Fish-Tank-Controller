#include "RefillProgram.h"
#define SMALLFILLTIMER 1000

RefillProgram::RefillProgram(
        int _drainPin, 
        int _refillPin, 
        int _topFloatPin, 
        int _toppestFloatPin,
        int _buttomFloatPin,
        int _buttomestFloatPin,
        int _indFillLED,
        int _indDrainLED,
        int _indAboveFull,
        int _indBelowBottom,
        int _buttonTopUp,
        int _buttonWaterChange,
        bool _flipButtons = false
)
{
    drainPin = _drainPin;
    refillPin = _refillPin;
    topFloatPin = _topFloatPin;
    toppestFloatPin = _toppestFloatPin;
    buttomFloatPin = _buttomFloatPin;
    buttomestFloatPin = _buttomestFloatPin;
    indFillLED = _indFillLED;
    indDrainLED = _indDrainLED;
    indAboveFull = _indAboveFull;
    indBelowBottom = _indBelowBottom;
    buttonTopUp = _buttonTopUp;
    buttonWaterChange = _buttonWaterChange;
    flipButtons = _flipButtons;
}

void RefillProgram::run(){
    int now = millis();
    buttonCheckerTopUp(now);
    buttonCheckerCycle(now);
}

void RefillProgram::buttonCheckerTopUp(int time)
{
    bool buttonState = digitalRead(buttonTopUp);
    if (flipButtons)
    {
        buttonState = !buttonState;
    }

    if (buttonState && time - buttonTime >= 100 && smallFillTime == 0)
    {
        smallFillTime = time;
        smallFillIsActive = true;
        digitalWrite(refillPin, LOW);
        digitalWrite(indFillLED, HIGH);
    }
    else if (buttonState && smallFillTime == 0)
    {
        buttonTime = time;
    }
    else if (smallFillIsActive && time - smallFillTime >= SMALLFILLTIMER)
    {
        digitalWrite(refillPin, HIGH);
        digitalWrite(indFillLED, LOW);
    }
    else if (time - buttonTime > 100)
    {
        buttonTime = 0;
    }
}
void RefillProgram::buttonCheckerCycle(int time)
{
    bool buttonState = digitalRead(buttonWaterChange);
    bool topFloatStatus = digitalRead(topFloatPin);
    bool bottomFloatStatus = digitalRead(buttomFloatPin);
    
    if (flipButtons)
    {
        buttonState = !buttonState;
    }

    if (buttonState && time - buttonTime2 >= 100 && smallFillTime == 0)
    {
        refillIsActive = true;
    }
    else
    {
        buttonTime2 = 0;
    }

    if(refillIsActive)
    {
        if (goingUp)
        {
            if (topFloatStatus == HIGH)
            {
                goingUp = false;
                refillIsActive = false;
                digitalWrite(refillPin, HIGH);
                digitalWrite(indFillLED, LOW);
            }
            else
            {
                digitalWrite(refillPin, LOW);
                digitalWrite(indFillLED, HIGH);
            }
        }
        else
        {
            if (bottomFloatStatus == HIGH)
            {
                digitalWrite(drainPin, LOW);
                digitalWrite(indDrainLED, HIGH);
            }
            else
            {
                digitalWrite(drainPin, HIGH);
                digitalWrite(indDrainLED, LOW);
                goingUp = true;
            }
        }
    }
}

void RefillProgram::dateRun()
{
    refillIsActive = true;
}

void RefillProgram::emergencyChecker()
{
    bool topFloatStatus = digitalRead(toppestFloatPin);
    bool bottomFloatStatus = digitalRead(buttomestFloatPin);

    if (bottomFloatStatus == LOW)
    {
        digitalWrite(drainPin, HIGH);
        digitalWrite(indDrainLED, LOW);
        digitalWrite(indBelowBottom, HIGH);
    }
    else
    {
        digitalWrite(indBelowBottom, LOW);
    }
    
    if (topFloatStatus == HIGH)
    {
        digitalWrite(refillPin, HIGH);
        digitalWrite(indFillLED, LOW);
        digitalWrite(indAboveFull, HIGH);
    }
    else
    {
        digitalWrite(indAboveFull, LOW);
    }
    
}