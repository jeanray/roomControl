#include "Switches.h"

void Relay::switchOn()
{
    if ((state != on) && switchTimer.checkTime())
    {
        digitalWrite(pin, onLevel);
        state = on;
    }
}

void Relay::switchOff()
{
    if ((state != off) && switchTimer.checkTime())
    {
        digitalWrite(pin, offLevel);
        state = off;
    }
}

void Relay::forceOn()
{
    digitalWrite(pin, onLevel);
    state = on;
}

void Relay::forceOff()
{
    digitalWrite(pin, offLevel);
    state = off;
}

void Relay::setup(int inPin)
{
    pin = inPin;
    pinMode(pin, OUTPUT);
    forceOff();
}

void InvertingRelay::setup(int inPin)
{
    pin = inPin;
    pinMode(pin, OUTPUT);
    forceOff();
}