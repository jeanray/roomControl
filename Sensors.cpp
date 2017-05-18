#include "Sensors.h"
#include "math.h"

/*
** Functions for DHTSensor
*/

// TODO Add a check to give an alert in case of too many NaN values
float DHTSensor::getHumidity()
{
    // Call the DHT base class implementation for reading humidity
    float readHumidity = DHT::readHumidity();
    if (isnanf(readHumidity))
    {
        readHumidity = lastHumidity;
    }
    else
    {
        lastHumidity = readHumidity;
    }
    return readHumidity;
}

// TODO Add a check to give an alert in case of too many NaN values
float DHTSensor::getTemp()
{
    // Call the DHT base class implementation for reading temperature
    float readTemperature = DHT::readTemperature();
    if (isnanf(readTemperature))
    {
        readTemperature = lastTemperature;
    }
    else
    {
        lastTemperature = readTemperature;
    }
    return readTemperature;
}

/*
** Functions for ThermistorSensor
*/

void ThermistorSensor::setup(uint8_t inPin)
{
    pinNumber = inPin;
    pinMode(pinNumber, INPUT);
    measuredResistance = 9890;
    thermistorResistance = 10000;
}

float ThermistorSensor::getTemp()
{
    float tempVal = analogRead(pinNumber);
    tempVal = measuredResistance * ((1024.0 / tempVal) - 1);
    tempVal = log(tempVal);
    tempVal = 1 / (0.001129148 + (0.000234125 * tempVal)
                   + (0.0000000876741 * tempVal * tempVal * tempVal));
    return tempVal - 273.15;
}
