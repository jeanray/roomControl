#include <Arduino.h>
#include "SystemControl.h"
#include "Utilities.h"

// Static const ints are better than defines as these do not pollute the global
// namespace in the same manner.
// Remember to keep both static and const keywords for these, if not they will
// occupy storage in RAM permanently, which we would like to avoid
static const int dht11SensorPin = 7;
static const int dht22SensorPin = 8;
static const int thermistorlm35SensorPin = A0;

// Create a new instance of SystemControl with room for 4 temperature instances
// and 4 humidity instances.
SystemControl mySystemControl(4, 4);

// Take a measurement every 0.5s and print to serial interface
static const unsigned long dTime = 5000;
unsigned long lastSerialPrint = 0;
InfoCookie insideCookie = { inside };
float roomTemp = 0;

static const unsigned long radStateChangeTime = 1000*60;
static const float radHighThresh = 23;
static const float radLowThresh = 19;
static const bool radInverting = false;
static const int radPin = 4;

Heater radiator = Heater(radStateChangeTime, radHighThresh, radLowThresh,
						 insideCookie, radInverting, radPin, &roomTemp);

void setup()
{
    // Start serial
    Serial.begin(9600);
    delay(1000);
    Serial.println("Testing roomControl!");
    mySystemControl.addSensor(DHT_11, dht11SensorPin, insideCookie);
    mySystemControl.addSensor(DHT_22, dht22SensorPin, insideCookie);
    mySystemControl.addSensor(Therm_LM35, thermistorlm35SensorPin,
                              insideCookie);
}

void loop()
{
    roomTemp = mySystemControl.getAvgTemp(insideCookie);
    radiator.evalState();

    if (millis() - lastSerialPrint > dTime)
    {
        lastSerialPrint = millis();
        Serial.println(roomTemp);
        Serial.println(mySystemControl.getAvgHumid(insideCookie));
    }
}
