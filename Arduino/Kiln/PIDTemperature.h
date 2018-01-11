// PIDTemperature.h

#ifndef _PIDTEMPERATURE_h
#define _PIDTEMPERATURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//pid settings and gains

class PIDTemperatureClass
{
 protected:

 public:
	void init();
	void readTemperature();
	void update();
	int getTemperature();
	double getSetPoint();
	int getPower();
	void setSetPointTemperature(double temp);

void setTemperature(int param1);
};

extern PIDTemperatureClass PIDTemperature;

#endif

