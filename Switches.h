#ifndef SWITCHES_H
#define SWITCHES_H

#include "AbstractTypes.h"

class Relay : public BasicSwitch
{
public:
    Relay(int inPin, InfoCookie inSwitchInfo,
          const unsigned long stateChangeTime = 300000)
        : BasicSwitch(inSwitchInfo, stateChangeTime)
    {
        onLevel = HIGH;
        offLevel = LOW;
        setup(inPin);
    }
	~Relay(){}
    virtual void switchOn();
    virtual void switchOff();
    virtual void forceOn();
    virtual void forceOff();

protected:
    virtual void setup(int inPin);
    int pin;
    int onLevel;
    int offLevel;
};

class InvertingRelay : public Relay
{
public:
    InvertingRelay(int inPin, InfoCookie inSwitchInfo,
                   const unsigned long stateChangeTime = 300000)
        : Relay(inPin, inSwitchInfo, stateChangeTime)
    {
        onLevel = LOW;
        offLevel = HIGH;
        setup(inPin);
    }
	~InvertingRelay(){}

protected:
    virtual void setup(int inPin);
};
#endif // SWITCHES_H