// 
#include <RTClibExtended.h>
#include <Wire.h>

#include "RTC.h"

void RTCClass::init()
{
	Wire.begin();
	rtc.begin();
	//rtc.adjust(DateTime(2017, 10, 22, 19, 48, 0));
}

void RTCClass::update()
{
	DateTime t = rtc.now();
	//Serial.println("Hours: " + String(t.hour()) + " Minutes: " + String(t.minute()) + "Seconds: " + String(t.second()));
}


RTCClass RTC;

