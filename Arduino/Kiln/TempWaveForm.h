// TempWaveForm.h

#ifndef _TEMPWAVEFORM_h
#define _TEMPWAVEFORM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class TempWaveFormClass
{
 protected:


 public:
	void init();
	void update();
	void addValue(int time, long temp);
	void setRange(int temp, long time);
	void drawValue(long time, int temp);
void moveTo(long timeSP, int tempSP);
void drawLineTo(long timeSP, int tempSP);
};

extern TempWaveFormClass TempWaveForm;

#endif

