#include "WakeUp.h"
#include "Pins.h"
#include <RTClibExtended.h>
#include <Wire.h>

volatile int intFlag = LOW;
byte year, month, date, DoW, hour, minute, second;
#define WAKEPIN 3 

void WakeUpClass::init()
{
	pinMode(VCC_RTC, OUTPUT);
	digitalWrite(VCC_RTC, HIGH);
	pinMode(GND_RTC, OUTPUT);
	digitalWrite(GND_RTC, LOW);
	delay(500);

	Wire.begin();
	rtc.begin();
	    //DateTime (uint16_t year, uint8_t month, uint8_t day,
	    //uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
	    
	//DateTime dt(2017, 12, 7, 17, 43);
	//rtc.adjust(dt);
	//pinMode(WAKEPIN, INPUT_PULLUP);
	////
	//rtc.writeSqwPinMode(DS3231_OFF);
	//attachInterrupt(digitalPinToInterrupt(WAKEPIN), alarmIsr, FALLING);
}

void WakeUpClass::loop()
{
	//if(intFlag == HIGH)
	//{
		//intFlag = LOW;
		//WakeUp.clearAlarm1();
		////MainPortal.callBackLightOff();
		//rtc.alarmInterrupt(1, true);
	//}
}


float WakeUpClass::getTemperature()
{
//	return rtc.getTemperature();
}

String WakeUpClass::nombre2digit(uint16_t nb)
{
	String val = "";
	if (nb < 10)
	val = "0" + String(nb);
	else
	val = String(nb);
	
	return val;
}

String WakeUpClass::getTimeString()
{
	return getTimeString(RTC_DS3231::now());
}

String WakeUpClass::getDateString()
{
	return getDateString(RTC_DS3231::now());
}

String WakeUpClass::getDateString(DateTime time)
{
	String sep = ":";
	return nombre2digit(time.hour()) + sep + nombre2digit(time.minute()) + " " + nombre2digit(time.day()) + "/" + nombre2digit(time.month()) + "/" + nombre2digit(time.year()-2000);
}

String WakeUpClass::getTimeString(DateTime time)
{
	String sep = ":";
	return nombre2digit(time.hour()) + sep + nombre2digit(time.minute());
}

bool initialized;

void WakeUpClass::callFunctionAfterDelay(int minutesIn)
{
	DateTime t = RTC_DS3231::now();
	int minutes = t.minute() + (t.hour() * 60);
	minutes += minutesIn;
	byte hoursOfst		= minutesIn / 60;
	byte minutesOfst	= minutes % 60;

	if(!initialized)
	{
		initialized = true;
	}

	byte secondsOfst = 1;
	hoursOfst = 0;
	minutesOfst = 0;
//	min = seconds / 60;
	//Serial.println("callFunctionAfterDelay, Hours: " + String(hoursOfst) + " Minutes: " + String(minutesOfst));

	rtc.setAlarm(ALM1_MATCH_MINUTES | ALM1_MATCH_HOURS | ALM1_MATCH_SECONDS, secondsOfst, minutesOfst, hoursOfst, 0);
	rtc.clearAlarm(1);
	rtc.alarmInterrupt(1, true);	
}

static void alarmIsr()
{
	WakeUp.alarmIsrWasCalled = true;
}

static void WakeUpClass::onAlarm1()
{
	intFlag = HIGH;
	Serial.println("onAlarm1");
}

void SendReport() {
	
	//do something quick, flip a flag, and handle in loop();
}

WakeUpClass WakeUp;

