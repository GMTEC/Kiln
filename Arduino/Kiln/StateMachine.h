// StateMachine.h

#ifndef _STATEMACHINE_h
#define _STATEMACHINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FiniteStateMachine.h>
#include "PageMain.h"
#include "SetPoints.h"

void noopUpdate();
void idleEnter();
void idleUpdate();
void idleExit();

void initialisingEnter();
void initialisingUpdate();
void initialisingExit();

void startingEnter();
void startingUpdate();
void startingExit();

void runningEnter();
void runningUpdate();
void runningExit();

void pausingEnter();
void pausingUpdate();
void pausingExit();
void stoppingEnter();
void stoppingUpdate();
void stoppingExit();

void stoppedEnter();
void stoppedUpdate();
void stoppedExit();

void inErrorEnter();
void inErrorUpdate();
void inErrorExit();

void configuringEnter();
void configuringUpdate();
void configuringExit();


class StateMachineClass
{
 protected:

	int servo1Pin = 11;

 public:
	bool startButState;
	bool pauseButState;
	String errorCode;

	void init();
	void loop();
	void update();
	void stop();
	void startTimeout(void (*func)());
	void stopTimeoutTimer();
	void checkStartPauseButton(State& startingState, State& pausingState);
	void setError(String errorCode);
private:
bool inError;
};

extern StateMachineClass StateMachine;

#endif

