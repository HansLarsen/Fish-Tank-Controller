#ifndef REFILLPROGRAM_H
#define REFILLPROGRAM_H

#include "Arduino.h"
#include "Task.h"
#include "IOManager.h"

class RefillProgram : public ButtonReturnClass
{
public:
    RefillProgram(IOManager*);
    virtual void run() override;
    virtual void dateRun(int) override;

    virtual void topButton() override;
    virtual void changeButton() override;

    virtual void topFloat(bool) override;
    virtual void bottomFloat(bool) override;

    bool refillIsActive = false;
    bool smallFillIsActive = false;

protected:

    IOManager * managerPointer;

    bool goingUp = false;
    int smallFillTime = 0;
    int refillTimer = 0;
};

#endif