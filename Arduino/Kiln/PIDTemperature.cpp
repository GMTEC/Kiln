#include "AutoPID.h"
// 
#include "AutoPID.h"
#include "PIDTemperature.h"
#include "KSensor.h"
#include "SSR.h"
#include "StateMachine.h"
#include "Translations.h"

double temperature, setPoint, outputVal;
int power;

#define OUTPUT_MIN 0
#define OUTPUT_MAX 50
#define KP .25
#define KI .0012
#define KD 0
//#define SIMULATOR 1

AutoPID tempPID(&temperature, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void PIDTemperatureClass::init()
{
  //if temperature is more than 4 degrees below or above setpoint, OUTPUT will be set to min or max respectively
	temperature = 1;
	tempPID.setBangBang(50, 50);
	//set PID update interval to 4000ms
	tempPID.setTimeStep(1000);
	setPoint = 0;
	readTemperature();
}

void PIDTemperatureClass::readTemperature()
{
	#if defined(SIMULATOR)
	temperature = 10;
	//temperature += 0.5;
	//if(temperature > 40)
		//temperature = 40;
	#else
		temperature  = KSensor.getTemperature();
	#endif

	//Serial.println("Temp: " + String(brol));
}

void PIDTemperatureClass::update()
{
	if(temperature == -1)
		StateMachine.setError(ERROR_KSENSOR_DISCONNECTED);
	tempPID.run();
	power = int(outputVal * 1);
	//Serial.println("setPower: " + String(power));
	SSR.setPower(power);
}

void PIDTemperatureClass::setSetPointTemperature(double temp)
{
//	Serial.println("setSetPointTemperature: " + String(temp));
	setPoint = temp; // Variable used by the PID
	update();
	SSR.updateRelayState();
}

void PIDTemperatureClass::setTemperature(int param1)
{
	temperature = 0;
}

double PIDTemperatureClass::getSetPoint()
{
	return setPoint;
}

int PIDTemperatureClass::getTemperature()
{
	return temperature;
}

int PIDTemperatureClass::getPower()
{
	return power;
}

PIDTemperatureClass PIDTemperature;

