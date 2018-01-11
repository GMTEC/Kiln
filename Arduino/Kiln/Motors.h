// Motors.h

#ifndef _MOTORS_h
#define _MOTORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class MotorsClass
{
 protected:


 public:
	void init();
	void update();
};

void drive(int motor,int state1,int state2);
extern MotorsClass Motors;

#endif

