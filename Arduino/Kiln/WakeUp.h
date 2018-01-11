// Sleeping.h

#ifndef _SLEEPING_h
#define _SLEEPING_h

#include "RTClibExtended.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class WakeUpClass
{
 protected:
 public:
	RTC_DS3231 rtc;
	bool alarmIsrWasCalled;
	void init();
	void loop();
	float getTemperature();
	String nombre2digit(uint16_t nb);
	String getTimeString();
	String getTimeString(DateTime time);
	String getDateString(DateTime time);
	String getDateString();
	void callFunctionAfterDelay(int minutesIn);
	static void callBackAfterDelay();
	static void onAlarm1();
	void clearAlarm1();
//	void adjustRTCClock(DataMinMax *ladate);
	void test();
private:
unsigned long lcdDisplayTimeout;
unsigned long lcdTimeoutMillis = 10000;
};

void resetLCDTimeout();
void alarmIsr();
void SendReport();
extern WakeUpClass WakeUp;

#endif

