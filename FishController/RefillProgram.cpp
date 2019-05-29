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
    pinMode(drainPin, OUTPUT);
    refillPin = _refillPin;
    pinMode(refillPin, OUTPUT);
    topFloatPin = _topFloatPin;
    pinMode(topFloatPin, INPUT);
    toppestFloatPin = _toppestFloatPin;
    pinMode(toppestFloatPin, INPUT);
    buttomFloatPin = _buttomFloatPin;
    pinMode(buttomFloatPin, INPUT);
    buttomestFloatPin = _buttomestFloatPin;
    pinMode(buttomestFloatPin, INPUT);
    indFillLED = _indFillLED;
    pinMode(indFillLED, OUTPUT);
    indDrainLED = _indDrainLED;
    pinMode(indDrainLED, OUTPUT);
    indAboveFull = _indAboveFull;
    pinMode(indAboveFull, OUTPUT);
    indBelowBottom = _indBelowBottom;
    pinMode(indBelowBottom, OUTPUT);
    buttonTopUp = _buttonTopUp;
    pinMode(buttonTopUp, INPUT);
    buttonWaterChange = _buttonWaterChange;
    pinMode(buttonWaterChange, INPUT);
    flipButtons = _flipButtons;

    digitalWrite(drainPin, HIGH);
    digitalWrite(refillPin, HIGH);
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

    if (topButtonDebounce == nullptr && buttonState)
    {
        topButtonDebounce = new Button(time, 100);
    }
    else if (topButtonDebounce->canRun(time) && topButtonDebounce != nullptr && buttonState && smallFillTime == 0 && !smallFillIsActive) //Start filling
    {
        delete topButtonDebounce;
        topButtonDebounce = nullptr;

        smallFillTime = time;
        smallFillIsActive = true;
        digitalWrite(refillPin, LOW);
        digitalWrite(indFillLED, HIGH);
    }
    else if (topButtonDebounce->canRun(time) && buttonState == false)
    {
        delete topButtonDebounce;
        topButtonDebounce = nullptr;
    }
    else if (smallFillIsActive && time - smallFillTime >= SMALLFILLTIMER) //Stop filling
    {
        digitalWrite(refillPin, HIGH);
        digitalWrite(indFillLED, LOW);
        smallFillTime = 0;
        smallFillIsActive = false;
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

    if (bottomButtonDebounce == nullptr && buttonState)
    {
        bottomButtonDebounce = new Button(time, 100);
    }
    else if (bottomButtonDebounce->canRun(time) && bottomButtonDebounce != nullptr && buttonState) //Start filling
    {
        delete bottomButtonDebounce;
        bottomButtonDebounce = nullptr;


        Serial.println("Activating Superpowers");
        refillIsActive = true;
    }
    else if (bottomButtonDebounce->canRun(time) && buttonState == false)
    {
        delete bottomButtonDebounce;
        bottomButtonDebounce = nullptr;
    }

    if(refillIsActive)
    {
        if (goingUp)
        {
            Serial.println("Going Up");
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
        Serial.println("BottomFloat");
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
        Serial.println("TopFloat");
    }
    else
    {
        digitalWrite(indAboveFull, LOW);
    }
    
}