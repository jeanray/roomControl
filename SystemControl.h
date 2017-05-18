#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H
#include "Sensors.h"
#include "Switches.h"

enum SensorType
{
    Invalid_Type = 0,
    DHT_11,
    DHT_22,
    Therm_LM35
};

class SystemControl
{
public:
    SystemControl(const int inTempSensorArrayLength,
                  const int inHumidSensorArryLength);
    ~SystemControl();
    float getAvgTemp(InfoCookie cookie);
    float getAvgTemp();
    float getAvgHumid(InfoCookie cookie);
    float getAvgHumid();
    void addSensor(const SensorType inSensorType, const int inSensorPin,
                   const InfoCookie inSensorInfo);

private:
    // Array of pointers to abstract base class TemperatureSensor
    TemperatureSensor** tempArray;
    int tempArraySize;
    // Array of pointers to abstract base class HumiditySensor
    HumiditySensor** humidArray;
    int humidArraySize;
    // Function declarations for adding individual sensors
    void addDHT11(const int inSensorPin, const InfoCookie inSensorInfo);
    void addDHT22(const int inSensorPin, const InfoCookie inSensorInfo);
    void addThermLM35(const int inSensorPin, const InfoCookie inSensorInfo);
    void addTempSensor(TemperatureSensor* newSensor);
    void addHumidSensor(HumiditySensor* newSensor);
};
#endif // SYSTEMCONTROL_H
