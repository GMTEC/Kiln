//
#include "SSR.h"
#include "Pins.h"
#include "Libs//Dimmer.h"
#include "PIDTemperature.h"


//byte toggle = 0;
Dimmer dimmer(SSRSignal, DIMMER_COUNT, 1.5, 50); // dimmer.set (0 -> 100);

void SSRClass::init()
{
	dimmer.begin();
	pinMode(SSRSignal, OUTPUT);
	digitalWrite(RelaySignal, HIGH);
	pinMode(RelaySignal, OUTPUT);
	digitalWrite(SSRSignal, HIGH);
	dimmer.set(0);
}

void SSRClass::updateRelayState()
{
	digitalWrite(RelaySignal, PIDTemperature.getSetPoint() == 0 ? HIGH : LOW);
}

void SSRClass::setPower(int pwr)
{
	dimmer.set(pwr);
	//Serial.println("Power: " + String(pwr));
	if(pwr == 0)
		dimmer.off();
	else if(pwr==100)
		dimmer.on();
}

SSRClass SSR;
