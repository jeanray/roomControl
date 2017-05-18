#include "SystemControl.h"

/*
** Constructors and destructors
*/

// SystemControl::SystemControl() {}

SystemControl::SystemControl(const int inTempSensorArrayLength,
							 const int inHumidSensorArryLength)
{
	// Create an array of pointers to the abstract base class TemperatureSensor
	tempArray = new TemperatureSensor*[inTempSensorArrayLength];
	tempArraySize = inTempSensorArrayLength;

	// Initialize all pointers to nullptr
	for (int i = 0; i < tempArraySize; i++)
	{
		tempArray[i] = NULL;
	}
	// Create an array of pointers to the abstract base class HumiditySensor
	humidArray = new HumiditySensor*[inHumidSensorArryLength];
	humidArraySize = inHumidSensorArryLength;

	// Initialize all pointers to nullptr
	for (int i = 0; i < humidArraySize; i++)
	{
		humidArray[i] = NULL;
	}
}

SystemControl::~SystemControl() {}

/*
** Public Functions
*/
float SystemControl::getAvgTemp(InfoCookie cookie)
{
	float avgTemperature = 0;
	int instanceCount = 0;
	int recordedCount = 0;
	ItemLocation location = cookie.location;
	ItemLocation tempLocation;
	while (tempArray[instanceCount] != NULL)
	{
		tempLocation
			= ((BasicSensor*)tempArray[instanceCount])->getInfo().location;
		if (tempLocation == location)
		{
			avgTemperature += tempArray[instanceCount]->getTemp();
			recordedCount++;
		}
		++instanceCount;
	}
	if (instanceCount != 0)
	{
		avgTemperature = (avgTemperature / (float)recordedCount);
	}
	else
	{
		// Do nothing, already 0
	}
	return avgTemperature;
}

float SystemControl::getAvgTemp()
{
	float avgTemperature = 0;
	int instanceCount = 0;

	// Cycle through all valid (non-NULL) pointers to temperature sensors stored
	// in tempArray and store all temperature readings.
	while (tempArray[instanceCount] != NULL)
	{
		avgTemperature = avgTemperature + tempArray[instanceCount]->getTemp();
		++instanceCount;
	}

	// Make sure we do not divide by zero (!!!) and get the average temperature
	// reading.
	if (instanceCount != 0)
	{
		avgTemperature = (avgTemperature / (float)instanceCount);
	}
	else
	{
		// Else do nothing, avgTemperature is set to 0 by default.
	}

	// Return the average temperature.
	return avgTemperature;
}

float SystemControl::getAvgHumid()
{
	float avgHumidity = 0;
	int instanceCount = 0;

	// Cycle through all valid (non-NULL) pointers to temperature sensors stored
	// in tempArray and store all temperature readings.
	while (humidArray[instanceCount] != NULL)
	{
		avgHumidity = avgHumidity + humidArray[instanceCount]->getHumidity();
		++instanceCount;
	}

	// Make sure we do not divide by zero (!!!) and get the average temperature
	// reading.
	if (instanceCount != 0)
	{
		avgHumidity = (avgHumidity / (float)instanceCount);
	}
	else
	{
		// Else do nothing, avgTemperature is set to 0 by default.
	}

	// Return the average humidity.
	return avgHumidity;
}

float SystemControl::getAvgHumid(InfoCookie cookie)
{
	float avgHumidity = 0;
	int instanceCount = 0;
	int recordedCount = 0;
	ItemLocation location = cookie.location;
	ItemLocation tempLocation;
	BasicSensor *tempBasic = NULL;
	while (humidArray[instanceCount] != NULL)
	{
		// tempBasic = ; safdsad
		tempLocation
			= ((BasicSensor*)tempArray[instanceCount])->getInfo().location;
		if (tempLocation == location)
		{
			avgHumidity += humidArray[instanceCount]->getHumidity();
			recordedCount++;
		}
		++instanceCount;
	}
	if (instanceCount != 0)
	{
		avgHumidity = (avgHumidity / (float)instanceCount);
	}
	else
	{
		// Do nothing, already 0
	}
	return avgHumidity;
}

void SystemControl::addSensor(const SensorType inSensorType,
							  const int inSensorPin,
							  const InfoCookie inSensorInfo)
{
	// Choose an action depending on the sensor type sent to the function
	switch (inSensorType)
	{
	case DHT_11:
		addDHT11(inSensorPin, inSensorInfo);
		break;
	case DHT_22:
		addDHT22(inSensorPin, inSensorInfo);
		break;
	case Therm_LM35:
		addThermLM35(inSensorPin, inSensorInfo);
		break;
	case Invalid_Type:
	default:
		break;
	}
}

/*
** Private functions
*/

void SystemControl::addTempSensor(TemperatureSensor* newSensor)
{
	int instanceCounter = 0;
	// Cycle through tempArray until first free slot is found (when it is NULL)
	while ((instanceCounter < tempArraySize)
		&& tempArray[instanceCounter] != NULL)
	{
		++instanceCounter;
	}
	// Assign the newSensor pointer to this spot in tempArray
	tempArray[instanceCounter] = (TemperatureSensor*)newSensor;
}

void SystemControl::addHumidSensor(HumiditySensor* newSensor)
{
	int instanceCounter = 0;
	// Cycle through tempArray until first free slot is found (when it is NULL)
	while ((instanceCounter < humidArraySize)
		&& humidArray[instanceCounter] != NULL)
	{
		++instanceCounter;
	}
	// Assign the newSensor pointer to this spot in tempArray
	humidArray[instanceCounter] = (HumiditySensor*)newSensor;
}

void SystemControl::addDHT11(const int inSensorPin,
							 const InfoCookie inSensorInfo)
{
	// Create a new instance of a DHT11 sensor
	// Since the new keyword is used the object created will persist when
	// exiting the scope
	DHTSensor* newSensor = new DHTSensor(inSensorPin, inSensorInfo, DHT11);

	// Add the temperature sensor to the internal array
	addTempSensor(newSensor);

	// Add the humidity sensor to the internal array
	addHumidSensor(newSensor);
}

void SystemControl::addDHT22(const int inSensorPin,
							 const InfoCookie inSensorInfo)
{
	// Create a new instance of a DHT22 sensor
	// Since the new keyword is used the object created will persist when
	// exiting the scope
	DHTSensor* newSensor = new DHTSensor(inSensorPin, inSensorInfo, DHT22);
	// Add the temperature sensor to the internal array
	addTempSensor(newSensor);

	// Add the humidity sensor to the internal array
	addHumidSensor(newSensor);
}

void SystemControl::addThermLM35(const int inSensorPin,
								 const InfoCookie inSensorInfo)
{
	// Create a new instance of a LM35 sensor
	// Since the new keyword is used the object created will persist when
	// exiting the scope
	ThermistorSensor* newSensor
		= new ThermistorSensor(inSensorPin, inSensorInfo);
	// Add the temperature sensor to the internal array
	addTempSensor(newSensor);
}
