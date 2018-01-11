// RTC.h

#ifndef _RTC_h
#define _RTC_h
#include "RTClibExtended.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class RTCClass
{
 protected:
	RTC_DS3231 rtc;


 public:
	void init();
	void update();
};

extern RTCClass RTC;

#endif

