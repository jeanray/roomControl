#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
public:
    Timer() {}
    Timer(const unsigned long inDeltaTime) { setup(inDeltaTime); }

    ~Timer() {}

    void setup(const unsigned long inDeltaTime)
    {
        setDeltaTime(inDeltaTime);
        reset();
    }

    void setDeltaTime(const unsigned long inDeltaTime)
    {
        deltaTime = inDeltaTime;
    }

    boolean checkTime()
    {
        boolean returnValue = false;
        if ((deltaTime == 0) || ((millis() - lastTime) > deltaTime))
        {
            returnValue = true;
            reset();
        }
        return returnValue;
    }

    void reset() { lastTime = millis(); }

    unsigned long getDeltaTime() { return deltaTime; }

private:
    unsigned long deltaTime;
    unsigned long lastTime;
};

#endif // TIMER_H
