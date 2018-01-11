// SetPoints.h

#ifndef _SETPOINTS_h
#define _SETPOINTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
	#include "Libs/QList.h";

#define MAX_SEGMENTS 4

class SetPoints
{
	public:
	long timeSP[MAX_SEGMENTS];
	int tempSP[MAX_SEGMENTS];
	bool enabledSP[MAX_SEGMENTS];
	int degPerHourSP[MAX_SEGMENTS];
	int totalTime;

	void onStop();
	int getTempToReach();
	public:
	SetPoints();
	firstSetPoint(int degHour, int temp, int time, int enabled);

	String getRemainingTime();
	addSetPoint(int degHour, int temp, int time, int enabled);
	getSetPoint(int inIter, int *inTime, int *inTemp, bool *inCursor, int *inIndex);
	void setSetPointTimer(int minutes);
	int getTemperatureToReach();
	static void callBackAfterDelay();

	void update();
	void startSetPoint(uint8_t index);
	bool onStart();
	bool nextSetPointExist();
	void setRange();
private:
bool checkForNextStep();
bool nearTemperature(long temp);
};

class SetPointsClass
{
	public:
	SetPointsClass();
	fromMemory();
	toMemory();
	prodToDef();
	defToProd();
	SetPoints prodSetPoints;
	SetPoints defSetPoints;
};

static void onSetPointTimerTerminated();
extern SetPointsClass SetPointsProdAndDef;

#endif

