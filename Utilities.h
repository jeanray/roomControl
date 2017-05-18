#ifndef HEATER_H
#define HEATER_H

#include "Switches.h"
#include "AbstractTypes.h"

class Heater
{
public:
    Heater(unsigned long stateChangeTime, float highThresh, float lowThresh,
           InfoCookie cookie, bool inverting, int pin, float* roomTempRef)
    {
        this->highThresh = highThresh;
        this->lowThresh = lowThresh;
        this->cookie = cookie;
        this->roomTempRef = roomTempRef;
        if (inverting)
        {
            this->sw = new InvertingRelay(pin, cookie, stateChangeTime);
        }
        else
        {
            this->sw = new Relay(pin, cookie, stateChangeTime);
        }
    }
	~Heater()
	{
		if (sw)
		{
			sw->forceOff();
			delete sw;
			sw = NULL;
		}
	}
    void evalState()
    {
        if (*roomTempRef > highThresh)
        {
            sw->switchOff();
        }
        else if (*roomTempRef < lowThresh)
        {
            sw->switchOn();
        }
        else
        {
            // Do nothing, let the state of the switch remain the same
        }
    }

private:
    InfoCookie cookie;
    BasicSwitch *sw;
    float highThresh;
    float lowThresh;
    float *roomTempRef;
};

#endif // HEATER_H
