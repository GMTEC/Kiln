#include "StateMachine.h"
#include <FiniteStateMachine.h>
//#include <FlexiTimer2.h>

#include "PageMain.h"
#include "PIDTemperature.h"
#include "Wakeup.h"
#include "KSensor.h"
#include "Sound.h"
#include "Translations.h"
#include "Colors.h"
#include "PageSetPoints.h"

bool closingEnabled = true;
bool openingEnabled = true;

//MainPage *portal;
void noopUpdate() { }
State noop = State(noopUpdate);
FSM stateMachine = FSM(noop); //initialize state machine, start in state: noop

State idleState = State(idleEnter, idleUpdate, idleExit);
State initialisingState = State(initialisingEnter, initialisingUpdate, initialisingExit);
State startingState = State(startingEnter, startingUpdate, startingExit);
State runningState = State(runningEnter, runningUpdate, runningExit);
State pausingState = State(pausingEnter, pausingUpdate, pausingExit);
State stoppingState = State(stoppingEnter, stoppingUpdate, stoppingExit);
State stoppedState = State(stoppedEnter, stoppedUpdate, stoppedExit);
State inErrorState = State(inErrorEnter, inErrorUpdate, inErrorExit);
State configuringState = State(configuringEnter, configuringUpdate, configuringExit);

void StateMachineClass::init()
{
	PageMain.drawSetPoints(SetPointsProdAndDef.prodSetPoints);
	stateMachine.transitionTo(initialisingState);
}

void StateMachineClass::update()
{
	stateMachine.update();
}

void StateMachineClass::stop()
{
	stateMachine.immediateTransitionTo(stoppingState);
}

void StateMachineClass::checkStartPauseButton(State& butStart, State& butPause)
{
	if(StateMachine.startButState)
	{
		StateMachine.startButState = false;
		stateMachine.transitionTo(butStart);
	}
	if(StateMachine.pauseButState)
	{
		StateMachine.pauseButState = false;
		//stateMachine.transitionTo(butPause);
	}
}


void StateMachineClass::setError(String err)
{
	errorCode = err;
	inError = true;
}

void idleEnter()
{
}

void idleUpdate()
{
}

void idleExit()
{
}

void initialisingEnter()
{
	SetPointsProdAndDef.fromMemory();
	PageSetPoints.init();
	stateMachine.transitionTo(stoppedState);
}

void initialisingUpdate()
{
}

void initialisingExit()
{
}

void startingEnter()
{
	StateMachine.setError("");
	PageMain.refreshFromState(BUT_ON_DIS, BUT_ON_DIS, TEXT_STARTING, COL_STOPPED_STATE);
	//delay(1000);
	stateMachine.transitionTo(runningState);
	Sound.playSequence(2);
}

void startingUpdate()
{
	StateMachine.checkStartPauseButton(stoppedState, pausingState);
}

void startingExit()
{
}

void runningEnter()
{
	Serial.println("runningEnter");
	PageMain.refreshFromState(BUT_OFF, BUT_ON, TEXT_RUNNING, COL_RUNNING_STATE);
	SetPointsProdAndDef.prodSetPoints.onStart();
}

bool checkErrorConditions()
{
	if(StateMachine.errorCode == ERROR_KSENSOR_DISCONNECTED)
		stateMachine.transitionTo(stoppingState);
}

void runningUpdate()
{
	StateMachine.checkStartPauseButton(stoppingState, pausingState);
	SetPointsProdAndDef.prodSetPoints.update();
	if(!SetPointsProdAndDef.prodSetPoints.nextSetPointExist())
		stateMachine.transitionTo(stoppingState);
	checkErrorConditions();
}

void runningExit()
{
}

void pausingEnter()
{
	Serial.println("pausingEnter");

	PageMain.refreshFromState(BUT_OFF, BUT_ON, TEXT_PAUSE, COL_STOPPED_STATE);
}

void pausingUpdate()
{
}

void pausingExit()
{
}

void stoppingEnter()
{
	Serial.println("stoppingEnter");
	PageMain.refreshFromState(BUT_OFF_DIS, BUT_ON_DIS, TEXT_STOPPING, COL_STOPPED_STATE);
	SetPointsProdAndDef.prodSetPoints.onStop();
	if(StateMachine.errorCode == ERROR_KSENSOR_DISCONNECTED)
		stateMachine.immediateTransitionTo(inErrorState);
	Sound.playSequence(2);

}
#define OUTPUT_STOPPED 30

void stoppingUpdate()
{
	if(PIDTemperature.getTemperature() <= OUTPUT_STOPPED)
		stateMachine.transitionTo(stoppedState);

	StateMachine.checkStartPauseButton(runningState, pausingState);
}

void stoppingExit()
{
}

void stoppedEnter()
{
	Serial.println("stoppedEnter");
	PageMain.refreshFromState(BUT_ON, BUT_ON, TEXT_STOPPED, COL_STOPPED_STATE);
	PIDTemperature.setSetPointTemperature(0);
	checkErrorConditions();
}

void stoppedUpdate()
{
	StateMachine.checkStartPauseButton(startingState, pausingState);
}

void stoppedExit()
{
}

void inErrorEnter()
{
	Serial.println("inErrorEnter");
	PageMain.refreshFromState(BUT_ON, BUT_ON, TEXT_ERROR, COL_ERROR_STATE);
}

void inErrorUpdate()
{
	StateMachine.checkStartPauseButton(startingState, pausingState);
}

void inErrorExit()
{
}

void configuringEnter()
{
}

void configuringUpdate()
{
}

void configuringExit()
{
}

void stopTimeoutTimer()
{
	//FlexiTimer2::stop();
}


StateMachineClass StateMachine;

