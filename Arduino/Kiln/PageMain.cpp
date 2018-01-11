// 
#include "PageMain.h"
#include "PIDTemperature.h"

#include "NextionIncludes.h"
#include "StateMachine.h"
#include "TempWaveForm.h"
#include "WakeUp.h"
#include "Sound.h"
#include "PageSetPoints.h"
#include "SetPoints.h"
int x, y;
NexText			tempTxt(0, 3, "temp");
NexText			statusTxt(0, 9, "status");
NexText			detStatusTxt(0, 2, "det");
NexButton		startBut(0, 1, "start");
NexButton		pauseBut(0, 5, "pause");
NexProgressBar	powerBar(0, 4, "pwr");

NexButton		cancelSetPoints(2, 31, "bp2cancel");
NexButton		okSetPoints(2, 28, "bp2ok");

NexButton		enterConfigBut(0, 8, "set");
NexButton		exitConfigBut(3, 1, "backtomain");
//
NexTouch *nex_listen_list[] =
{
	&startBut,
	&pauseBut,
	&statusTxt,
	&enterConfigBut,
	&exitConfigBut,
	&cancelSetPoints,
	&okSetPoints,
	NULL
};

char buffer[80] = {0};
String strBuffer;

#define LEVEL_HIGH      (100)
#define LEVEL_LOW       (0)

static void PageMainClass::onStartStop(void *ptr = nullptr)
{
	//NexButton *btn = (NexButton *)ptr;
	Serial.println("onStart");
	StateMachine.startButState = true;
	StateMachine.update();
	StateMachine.update();
	PIDTemperature.setTemperature(0);
}

static void PageMainClass::onPause(void *ptr)
{
	//NexButton *btn = (NexButton *)ptr;
	Serial.println("onPause");
	StateMachine.pauseButState = true;
	StateMachine.update();
	StateMachine.update();
}

static void PageMainClass::onStatusText(void *ptr)
{
	Serial.println("onStatusText");
	sendCommand("page 2");
}

static void PageMainClass::onEnterConfigMenu(void *ptr)
{
	Serial.println("onEnterConfigMenu");
	//sendCommand("page 2");
}

static void PageMainClass::onExitConfigMenu(void *ptr)
{
	Serial.println("onExitConfigMenu");
	//sendCommand("page 0");
}

void PageMainClass::refreshStartButton(ButtonState state)
{
	int pic;
	switch(state)
	{
		case BUT_ON: pic = 4; break;
		case BUT_OFF: pic = 2; break;
		case BUT_ON_DIS: pic = 5; break;
		case BUT_OFF_DIS: pic = 8; break;
	}
	String str = "start.pic=" + String(pic);
	sendCommand(str.c_str());
}

void PageMainClass::refreshPauseButton(ButtonState state)
{
		int pic;
		switch(state)
		{
			case BUT_ON: pic = 9; break;
			case BUT_OFF: pic = 6; break;
			case BUT_ON_DIS: pic = 10; break;
			case BUT_OFF_DIS: pic = 7; break;
		}
		String str = "pause.pic=" + String(pic);
		sendCommand(str.c_str());
}

void PageMainClass::refreshStatusText(String txt)
{
	txt.getBytes(buffer, 16);
	statusTxt.setText(buffer);
}

void PageMainClass::refreshStatusTextColor(uint32_t col)
{
	statusTxt.Set_background_color_bco(col);
}

void PageMainClass::refreshFromState(ButtonState param1, ButtonState param2, String txt, uint32_t col)
{
	PageMain.refreshStartButton(param1);
	PageMain.refreshPauseButton(param2);
	PageMain.refreshStatusText(txt);
	PageMain.refreshStatusTextColor(col);
}

void PageMainClass::init()
{
	nexInit();
	sendCommand("thsp=300");
	sendCommand("thup=1");
	sendCommand("sendxy=0");
	PageSetPoints.init();

	startBut.attachPop(onStartStop);
    pauseBut.attachPop(onPause);
	statusTxt.attachPop(onStatusText);
	enterConfigBut.attachPop(onEnterConfigMenu);
	exitConfigBut.attachPop(onExitConfigMenu);
	
	cancelSetPoints.attachPop(PageSetPoints.onCancelSetPoints);
	okSetPoints.attachPop(PageSetPoints.onOKSetPoints);
	
	statusTxt.getText(buffer, 10);
	Serial.println(buffer);
	dbSerialPrintln("Initialization ..............");
	//main.show();
	tempTxt.setText("000");
	sendCommand("click status, 1");
	sendCommand("click start, 1");
	TempWaveForm.init();
}

bool PageMainClass::loop()
{
	//PageSetPoints.loop();
	nexLoop(nex_listen_list);
}

void PageMainClass::update()
{
	PIDTemperature.readTemperature();
	powerBar.setValue(PIDTemperature.getPower());
	strBuffer = PIDTemperature.getTemperature();
  	tempTxt.setText(strBuffer.c_str());  //memset(buffer, 0, sizeof(buffer));

	strBuffer = WakeUp.getTimeString() + " ";

	strBuffer += " - " + String(SetPointsProdAndDef.prodSetPoints.getRemainingTime());
	strBuffer += " - " + String(SetPointsProdAndDef.prodSetPoints.getTempToReach()) + "°";

	detStatusTxt.setText(strBuffer.c_str());
	
	//TempWaveForm.drawValue(x, y);
	//x++;
	//y++;
}

void PageMainClass::drawSetPoints(SetPoints setPoints)
{
	int setTime, setTemp, setIndex;
	bool setCursor;
	int iter = 0;

	while (true)
	{
		setPoints.getSetPoint(iter++, &setTime, &setTemp, &setCursor, &setIndex);
		if(setTime == 0)
			break;
		//wafeForm.addValue(1)
	}
}

PageMainClass PageMain;
