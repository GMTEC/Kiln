// PageSetPoints.h

#ifndef _PAGESETPOINTS_h
#define _PAGESETPOINTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class PageSetPointsClass
{
 protected:


 public:
	void init();
	bool loop();
	static void onCancelSetPoints(void *ptr);
	static void onOKSetPoints(void *ptr);
	String getText(String objName, int index, uint16_t len=3);
	bool setText(String objName, int index, String str);
	uint32_t getValue(String objName, int index);
	bool setValue(String objName, int index, uint32_t number);
	long getLong(String objName, uint16_t len);
	long getTimeInSecondsFromObjects(String objHour, String objMin, int index);
private:
void refreshPage();
};

extern PageSetPointsClass PageSetPoints;

#endif

