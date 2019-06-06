#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "Arduino.h"
#include "Task.h"

#define TaskListSize 5
#define DebounceTime 100
#define BuzzerTime 500

//Solenoids - HIGH is on.
#define flipSolenoids true
#define DrainPin 26
#define RefillPin 27
#define CO2Pin 28 
#define HeaterPin 29 
#define FilterPin 30 
#define BuzzerPin 36 

//Level floats
#define flipFloats false
#define topFloatPin 31
#define toppestFloatPin 33
#define buttomFloatPin 32
#define buttomestFloatPin 34

//LED Indicators
#define flipLEDS true
#define indFillLED 6
#define indDrainLED 7 
#define indAboveFull 8
#define indBelowBottom 9
#define indDayLight 4
#define indNightLight 5
#define indAirPump 3
#define indCO2On 10 
#define indHeaterOn 11 
#define indFliterOn 12 

//Buttons
#define flipButtons true
#define buttonTopUp 37
#define buttonWaterChange 38
#define lightOnButton 40
#define lightOffButton 39

//Lights
#define flipLight false
#define dayLights 24
#define nightLights 25

//Airpump
#define flipAirpump true
#define AirPump 23


typedef ButtonReturnClass * funPoint;

class IOManager : public Task
{
public:
    IOManager();

    //function, (TopUp, WaterChange)
    void registerToInputs(funPoint);

    //true, HIGH is on: false, LOW is off.
    void fill(bool);
    void drain(bool);

    bool fillStatus();
    bool drainStatus();

    void dayLight(bool);
    void nightLight(bool);

    void setAirpump();
    void setAirpump(bool);

    void setCO(bool);
    void setHeater(bool);
    void setFilter(bool);

    bool getHeaterStatus();
    void buzzer();
    

    virtual void run() override;
    virtual void dateRun(int) override;

    bool topFloatStateOld = LOW;
    bool bottomFloatStateOld = HIGH;
    
protected:
    int buttonTimer = 0;
    int buttonTimer2 = 0;

    //0 is TopUp, 1 is WaterChange
    funPoint ButtonArray[TaskListSize];
    int ButtonArrayDepth = 0;

    //High on, LOW off;
    bool fillState = LOW;
    bool drainState = LOW;

    bool dayLightState = HIGH;
    bool nightLightState = LOW;

    bool airPumpStatus = HIGH;

    bool CO2Status = LOW; //
    bool HeaterStatus = LOW; //Buzzer
    bool FilterStatus = HIGH; //

    int buzzerTimer = 0;
};

#endif