// MainPage.h

#ifndef _MAINPAGE_h
#define _MAINPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
enum ButtonState { BUT_OFF, BUT_ON, BUT_OFF_DIS, BUT_ON_DIS };

#include "SetPoints.h"

class PageMainClass
{
 private:


 public:
	void init();
	bool loop();
	void update();
	void drawSetPoints(SetPoints setPoints);
	static void onStartStop(void *ptr = nullptr);
	static void onPause(void *ptr);
	static void onStatusText(void *ptr);
	static void onEnterConfigMenu(void *ptr);

	static void onExitConfigMenu(void *ptr);
	
	void onPause();
	void refreshStartButton(ButtonState state);
	void refreshPauseButton(ButtonState state);
	void refreshStatusText(String txt);
	void refreshStatusTextColor(uint32_t col);
	void refreshFromState(ButtonState param1, ButtonState param2, String txt, uint32_t col = 0XFFFFFF);
};

extern PageMainClass PageMain;

#endif

