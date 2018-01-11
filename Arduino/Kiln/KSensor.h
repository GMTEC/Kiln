// KSensor.h

#ifndef _KSENSOR_h
#define _KSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <max6675.h>

class KSensorClass
{
 protected:


 public:
	void init();
	void update();
	int getTemperature();
};

extern KSensorClass KSensor;

#endif

