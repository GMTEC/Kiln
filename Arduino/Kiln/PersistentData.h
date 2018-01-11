// PersistentData.h

#ifndef _PERSISTENTDATA_h
#define _PERSISTENTDATA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
	#include "Libs/AT24CX.h"
	
class PersistentDataClass
{
 protected:

 public:
	void init();
	void readSetPoint(int index, int* rising, int* temp, int* time, int* enabled);
	void writeSetPoint(int index, int rising, int temp, int time, int enabled);
};

extern PersistentDataClass PersistentData;

#endif

