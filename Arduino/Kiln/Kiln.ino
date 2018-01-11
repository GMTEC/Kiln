#include "PageSetPoints.h"
#include "PageSetPoints.h"
#include "Sound.h"
#include "TempWaveForm.h"
#include "SetPoints.h"
#include "PIDTemperature.h"
#include "PageMain.h"
#include "KSensor.h"
//#include "Motors.h"
#include "SSR.h"
#include "StateMachine.h"
#include "WakeUp.h"
//#include "FlexiTimer2.h"
#include "Libs/MsTimer2.h"

#define SIMULATOR
/*
 * Kiln.ino
 *
 * Created: 10/11/2017 4:13:31 PM
 * Author: GUY
 */ 
int ticks = 0;
bool toggle;

#define  UPDATE_TIME 1000
#define  DEBOUNCE_TIME 10

//static void onSetPointTimerTerminated()
//{
	//Serial.println("onSetPointTimerTerminated!!!!!!!");
	//FlexiTimer2::stop();
//}

void setup()
{
	Serial.begin(115200);

	  /* add setup code here, setup code runs once when the processor starts */
	pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
	WakeUp.init();
	KSensor.init();
	SSR.init();
	//Motors.init();
	//RTC.init();
	PIDTemperature.init();
	PageMain.init();
	StateMachine.init();
	Sound.playMelody();

	//long brol = 8;
	//FlexiTimer2::set(brol * 1000, onSetPointTimerTerminated); // call every 5000 1ms "ticks"
	//FlexiTimer2::start();
}

void loop()
{

 	//int brol  = KSensor.getTemperature();
 	//Serial.println("\nTemp: " + String(brol));
	//Serial.println("Count: " + String(FlexiTimer2::count / 1000));
	//delay (1000);
	//return;

   while(ticks++ < UPDATE_TIME)
	{
		if(PageMain.loop())
			break;
		ticks += DEBOUNCE_TIME;
		delay(DEBOUNCE_TIME);
	}
	ticks = 0;
	StateMachine.update();
	/* add main program code here, this code starts again each time it ends */
	digitalWrite(LED_BUILTIN, toggle);   // Turn the LED on (Note that LOW is the voltage level
	toggle = !toggle;

	//KSensor.update();
	//Motors.update();
	//RTC.update();
//	SetPointsProdAndDef.update();
	PageMain.update();
}
