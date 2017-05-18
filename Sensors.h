#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "AbstractTypes.h"
#include "DHT.h"

class DHTSensor : public BasicSensor,
                  public TemperatureSensor,
                  public HumiditySensor,
                  public DHT
{
public:
    DHTSensor(uint8_t pin, InfoCookie inSensorInfo, uint8_t type)
        : BasicSensor(inSensorInfo)
        , DHT(pin, type)
    {
        // Call the initializer for the base DHT class
        DHT::begin();
        // Set a default value to the last* variables so that they do not give
        // "strange" data in case the first read value is NaN
        lastTemperature = 25;
        lastHumidity = 35;
    }
    ~DHTSensor() {}
    virtual float getHumidity();
    virtual float getTemp();

private:
    float lastTemperature;
    float lastHumidity;
};

class ThermistorSensor : public BasicSensor, public TemperatureSensor
{
public:
    ThermistorSensor(uint8_t inPin, InfoCookie inSensorInfo)
        : BasicSensor(inSensorInfo)
    {
        setup(inPin);
    }
    virtual ~ThermistorSensor() {}
    virtual float getTemp();

private:
    void setup(uint8_t inPin);
    uint8_t pinNumber;
    float measuredResistance;
    float thermistorResistance;
    float temperature;
    float lastTemperature;
    float lastHumidity;
};

#endif
