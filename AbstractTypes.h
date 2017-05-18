#ifndef ABSTRACTTYPES_H
#define ABSTRACTTYPES_H

#include <Arduino.h>
#include "Timer.h"

enum SwitchState
{
    invalidState = 0,
    on,
    off
};

enum ItemLocation
{
    invalidLocation = 0,
    inside,
    outside
};

struct InfoCookie
{
    ItemLocation location;
};

class BasicSensor
{
public:
    BasicSensor(InfoCookie inSensorInfo) { setInfo(inSensorInfo); }
    virtual ~BasicSensor() {}
    virtual InfoCookie getInfo() { return sensorInfo; }
    InfoCookie sensorInfo;

protected:
    void setInfo(InfoCookie inSensorInfo) { sensorInfo = inSensorInfo; }
};

class TemperatureSensor
{
public:
    TemperatureSensor() {}
    virtual ~TemperatureSensor() {}
    virtual float getTemp() = 0;

protected:
};

class HumiditySensor
{
public:
    HumiditySensor() {}
    virtual ~HumiditySensor() {}
    virtual float getHumidity() = 0;

protected:
};

class BasicSwitch
{
public:
    BasicSwitch(InfoCookie inSwitchInfo, const unsigned long stateChangeTimer)
    {
        setInfo(inSwitchInfo);
        switchTimer.setup(stateChangeTimer);
    }
    virtual ~BasicSwitch() {}
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
	virtual void forceOn() = 0;
	virtual void forceOff() = 0;
    SwitchState getState() { return state; }
    InfoCookie getInfo() { return switchInfo; }

protected:
    InfoCookie switchInfo;
    SwitchState state = invalidState;
    Timer switchTimer;
    virtual void setup(int) = 0;
    void setInfo(InfoCookie inSwitchInfo) { switchInfo = inSwitchInfo; }
};

#endif // ABSTRACTTYPES_H
