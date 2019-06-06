#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

//Wrapper class for the temperature sensors.

#define TEMPSENSOR_1 true

#if TEMPSENSOR_1
    #include "OneWire.h"
    #include <DallasTemperature.h>
    #define ONE_WIRE_BUS 41
#endif

class TempSensor
{
    #if TEMPSENSOR_1
        OneWire * oneWire;
        DallasTemperature * sensors;
    #endif

public:
#if TEMPSENSOR_1
    TempSensor()
    {
        oneWire = new OneWire(ONE_WIRE_BUS);
        sensors = new DallasTemperature(oneWire);

        sensors->begin();
    }

    int getTemp()
    {
        sensors->requestTemperatures();

        return sensors->getTempCByIndex(0);
    }
#endif

};

#endif