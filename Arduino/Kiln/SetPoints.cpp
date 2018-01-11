// 

#include "SetPoints.h"
#include "WakeUp.h"
#include "Sound.h"
#include "StateMachine.h"
#include "PageMain.h"
#include "PIDTemperature.h"
#include "TempWaveForm.h"
#include "Libs/MsTimer2.h"
#include "Translations.h"
#include "PersistentData.h"

double tempToReach, rampTime;
int maxTemperature;
byte setPointsNumber;
uint8_t currentSetPoint;
bool timerSPTerminated;
double timeElapsed;
double curTemp;
int toleranceSetPoint = 2;
long remainingCountTime, stepTime;
int degHour;
long previousTempSP;
long stepTemp;
bool endOfSegment;

#define TIMER_RATIO 500
enum RampState { RAMP_NONE, RAMP_RISING, RAMP_FALLING };
RampState rampState;

void SetPoints::onStop()
{
	currentSetPoint = setPointsNumber;
	timerSPTerminated = false;
	update();
}

int SetPoints::getTempToReach()
{
	return tempToReach;
}

bool SetPoints::onStart()
{
	currentSetPoint = 0; //First set point is the current temperature;
	startSetPoint(currentSetPoint);
}

SetPoints::SetPoints()
{

}

SetPoints::firstSetPoint(int degHour, int temp, int time, int enabled)
{
	setPointsNumber = 0;
	addSetPoint(degHour, temp, time, enabled);
}

SetPoints::addSetPoint(int degHour, int temp, int time, int enabled)
{
	timeSP[setPointsNumber] = time;
	tempSP[setPointsNumber] = temp;
	enabledSP[setPointsNumber] = enabled;
	degPerHourSP[setPointsNumber++] = degHour;
	totalTime += time;
	maxTemperature = max(temp, maxTemperature);
}

SetPoints::getSetPoint(int inIter, int *time, int *temp, bool *cursor, int *index)
{
	*temp = temp[inIter];
	*time = time[inIter];
	*cursor = cursor[inIter];
	*index = index[inIter];
}

void SetPoints::setSetPointTimer(int seconds)
{
	Serial.println("\nsetTimer(): " + String(seconds));
	MsTimer2::set(long(seconds) * 1000, onSetPointTimerTerminated); // call every 5000 1ms "ticks"
	MsTimer2::start();
}

static void onSetPointTimerTerminated()
{
	//FlexiTimer2::stop();
	Serial.println("onSetPointTimerTerminated!!!!!!!");
	timerSPTerminated = true;
}

int SetPoints::getTemperatureToReach()
{
	curTemp = (double)PIDTemperature.getTemperature();
	checkForNextStep();

	if(rampState == RAMP_NONE)
	{
		tempToReach = stepTemp;
	}
	else
	{
		double dTime = stepTime - remainingCountTime;

		double a =  abs(rampTime / dTime);
		double b =  curTemp - (a * 0);
		tempToReach = a * remainingCountTime / 1000 + b;
		
		tempToReach = stepTemp; //TODO to change
	}
	//Serial.println("tempToReach: " + String(tempToReach));
	//Serial.println("\nCurrentSetPoint: " + String(currentSetPoint));
	//Serial.println("dTemp: " + String(dTemp));
	//Serial.println("dTime: " + String(dTime));
	//Serial.println("a: " + String(a));
	//Serial.println("b: " + String(a));
//	Serial.println("getTemperatureFromTime: " + String(time) + ", " +String(time1) + ", " +String(time2) + ", " +String(temp1) + ", " +String(temp2) );
	//Serial.println("Temperature to reach: " + String(tempToReach) + "Ramp: " + String(rampState));
	//Serial.println("Temperature: " + String(PIDTemperature.getTemperature()));
	//Serial.println("tempReachedSP:"  + String(rampState));

	return tempToReach;
}

String SetPoints::getRemainingTime()
{
	//Serial.println("Current SetPoint Time: " + String(stepTime));
	remainingCountTime = MsTimer2::count;
	long tim = stepTime - (remainingCountTime / 1000);
	//Serial.println("Timer Count: " + String(remainingCountTime));
	return String(tim / 3600) + "h" + String((tim / 60) % 60) + "m" + String(tim % 60) + "s";
}

void SetPoints::update() // called by StateMachine (runningUpdate)
{
	PIDTemperature.setSetPointTemperature(getTemperatureToReach());
	PIDTemperature.update();
}

bool SetPoints::nextSetPointExist()
{
	return (currentSetPoint < setPointsNumber);
}

void SetPoints::setRange()
{
	TempWaveForm.setRange(maxTemperature, totalTime);
	TempWaveForm.moveTo(timeSP[0], tempSP[0]);

	for(int index = 1; index < setPointsNumber; index ++)
	{
		long x = timeSP[index];
		TempWaveForm.drawLineTo(timeSP[index], tempSP[index]);
	}
}

bool SetPoints::checkForNextStep()
{
	if(!endOfSegment)
	{
		switch(rampState)
		{
			case RAMP_NONE: endOfSegment =  timerSPTerminated ; break; // Timer ended -> stepSPTerminated = true
			case RAMP_FALLING:
			case RAMP_RISING: endOfSegment = nearTemperature(stepTemp); break; // Adjust the Delta
		}
		if(endOfSegment)
		{
			endOfSegment = false;

			if(rampState == RAMP_NONE)
			{
				currentSetPoint ++;
				startSetPoint(currentSetPoint);
			}
			else
			{
				previousTempSP = curTemp;
				rampState = RAMP_NONE;
				setSetPointTimer(stepTime);
			}
		}
	}
	return endOfSegment;
}

bool SetPoints::nearTemperature(long temp)
{
	return abs(temp - curTemp) < toleranceSetPoint;
}

void SetPoints::startSetPoint(uint8_t index) // First or next SetPoint
{
	//Serial.println("Enabled 0: " + String(enabledSP[0]));
	//Serial.println("Enabled 1: " + String(enabledSP[1]));
	if(!enabledSP[currentSetPoint])
	{
		StateMachine.stop();
		MsTimer2::stop();
		return;
	}
	previousTempSP = curTemp;
	//Serial.println("startSetPoint(" + String(index) + ") !!!!!!!!");
	stepTemp = tempSP[currentSetPoint];
	stepTime = timeSP[currentSetPoint] * 60; // time in seconds
	degHour = degPerHourSP[currentSetPoint];

	if(degHour == 0)
		degHour = 50000; // TODO  adjust later to be realistic
	rampState = curTemp < stepTemp ? RAMP_RISING : RAMP_FALLING;
	rampTime = (abs(stepTemp - curTemp) / degHour) * 3600; // time in seconds

	PageMain.refreshStatusText(TEXT_RUNNING + String(tempSP[currentSetPoint]) + "°");

	Sound.playSequence(1);
}

SetPointsClass::SetPointsClass()
{
}

SetPointsClass::fromMemory()
{	
	int temp, degHour, enabled;
	int time;
	PersistentData.readSetPoint(0, &degHour, &temp, &time, &enabled);
	defSetPoints.firstSetPoint(degHour, temp, time, enabled); // Rising   SetPoint 1
	Serial.println("EnabledFromMemory: " + String(enabled));

	for(int index = 1; index < MAX_SEGMENTS; index ++)
	{
		PersistentData.readSetPoint(index, &degHour, &temp, &time, &enabled);
		Serial.println("EnabledFromMemory: " + String(enabled));
		defSetPoints.addSetPoint(degHour, temp, time, enabled);   //  SetPoint 2
	}
	defToProd();
}

SetPointsClass::toMemory()
{
	int temp, rising;
	long time;
	
	for(int index = 0; index < MAX_SEGMENTS; index ++)
	{
		Serial.println("Temp to memory: " + String(defSetPoints.tempSP[index]));
		Serial.println("Time to memory: " + String(defSetPoints.timeSP[index]));
		PersistentData.writeSetPoint(index, defSetPoints.degPerHourSP[index], defSetPoints.tempSP[index], defSetPoints.timeSP[index], defSetPoints.enabledSP[index]);
	}
}

SetPointsClass::prodToDef()
{
	Serial.println("ProdTodef()");
	for(int i=0; i < MAX_SEGMENTS; i++)
	{
		defSetPoints.tempSP[i]	= prodSetPoints.tempSP[i];
		defSetPoints.timeSP[i]	= prodSetPoints.timeSP[i];
		defSetPoints.enabledSP[i]	= prodSetPoints.enabledSP[i];
		defSetPoints.degPerHourSP[i]	= prodSetPoints.degPerHourSP[i];
		Serial.println("Temp from memory: " + String(defSetPoints.tempSP[i]));
		Serial.println("Time from memory: " + String(defSetPoints.timeSP[i]));
	}
}

SetPointsClass::defToProd()
{
	for(int i=0; i < MAX_SEGMENTS; i++)
	{
		prodSetPoints.tempSP[i]	= defSetPoints.tempSP[i];
		prodSetPoints.timeSP[i]	= defSetPoints.timeSP[i];
		prodSetPoints.enabledSP[i]	= defSetPoints.enabledSP[i];
		prodSetPoints.degPerHourSP[i]	= defSetPoints.degPerHourSP[i];
	}
	toMemory();
}

SetPointsClass SetPointsProdAndDef;
