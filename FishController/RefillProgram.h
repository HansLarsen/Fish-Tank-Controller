#ifndef REFILLPROGRAM_H
#define REFILLPROGRAM_H

#include "Arduino.h"
#include "Task.h"

class RefillProgram : public Task
{
public:
    RefillProgram(
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
        bool flipButtons = false
    );
    virtual void run() override;
    virtual void dateRun() override;

    bool refillIsActive = false;
    bool smallFillIsActive = false;

protected:
    void buttonCheckerTopUp(int time);
    void buttonCheckerCycle(int time);
    void emergencyChecker();

    int drainPin;
    int refillPin;
    int topFloatPin;
    int toppestFloatPin;
    int buttomFloatPin;
    int buttomestFloatPin;
    int indFillLED;
    int indDrainLED;
    int indAboveFull;
    int indBelowBottom;
    int buttonTopUp;
    int buttonWaterChange;
    bool flipButtons;

    int buttonTime = 0;
    int buttonTime2 = 0;

    bool goingUp = false;
    int smallFillTime = 0;
};

#endif