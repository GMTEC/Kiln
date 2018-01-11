// 

#include "KSensor.h"
// ThermoCouple
int thermo_so_pin  = 50;
int thermo_cs_pin  = 51;
int thermo_sck_pin = 52;
MAX6675 thermocouple(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);

void KSensorClass::init()
{
}

void KSensorClass::update()
{
	//Serial.print("Temp: ");
	//Serial.println(thermocouple.readCelsius());
}

int KSensorClass::getTemperature()
{
	return thermocouple.readCelsius();
}

KSensorClass KSensor;
