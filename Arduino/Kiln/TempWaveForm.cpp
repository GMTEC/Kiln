// 

#include "TempWaveForm.h"
#include "Nex/NexWaveform.h"
#include "Nex/NexText.h"
#include "PIDTemperature.h"
#include "PageMain.h"
//NexWaveform		wafeForm(0, 2, "s0");
double XScale, YScale;
uint32_t width = 312;
uint32_t height = 164;

int XOfst = 75;
int YOfst = 60;
double X0, Y0;
int XPos, YPos;
String strBuffer1;
char buffer1[80] = {0};

NexText			graphTxt(0, 9, "status");

void TempWaveFormClass::init()
{
	//wafeForm.Set_channel_0_color_pco0(32768);
	graphTxt.setText("");
	XScale = YScale = 1;
	setRange(100, 100);
	//graphTxt.getParameter(".w", width);
	//graphTxt.getParameter(".h", height);

//	Serial.println("Width: " + String(width )+", Height: " + String(height) );
	//sendCommand("draw 0,0,200,200,GREEN");
}

void TempWaveFormClass::update()
{
	//drawValue(XPos, PIDTemperature.getTemperature());
	//XPos ++;
	//wafeForm.addValue(0, temp);
	//wafeForm.Set_channel_0_color_pco0(	wafeForm.Set_channel_0_color_pco0(32768);
};

void TempWaveFormClass::addValue(int time, long temp)
{
		
}

void TempWaveFormClass::setRange(int temp, long time)
{
	XScale = width /double(time);
	YScale = height / double(temp);
	Serial.println("XScale: " + String(XScale )+", YScale: " + String(YScale) );
}

void TempWaveFormClass::drawValue(long time, int temp)
{
	double x, y;
	x = XOfst + (XScale * time);
	y = YOfst + height -(YScale * temp);
	strBuffer1 = "cir " + String(int(X0)) + "," + String(int(Y0)) +  "," + String(int(x)) + "," + String(int(y)) + ",RED";
	strBuffer1.getBytes(buffer1, strBuffer1.length()+1);

	Serial.println(buffer1);
	sendCommand(buffer1);	//sendCommand("draw 0,0,200,200,RED");
}

void TempWaveFormClass::moveTo(long timeSP, int tempSP)
{
	X0 = XOfst + (XScale * timeSP);
	Y0 = YOfst + height -(YScale * tempSP);
}

void TempWaveFormClass::drawLineTo(long timeSP, int tempSP)
{
	double x, y;
	x = XOfst + (XScale * timeSP);
	y = YOfst + height -(YScale * tempSP);
	//Serial.println("X: " + String(x));
	strBuffer1 = "line " + String(int(X0)) + "," + String(int(Y0)) +  "," + String(int(x)) + "," + String(int(y)) + ",RED";
	strBuffer1.getBytes(buffer1, strBuffer1.length()+1);
	X0 = x;
	Y0 = y;
	Serial.println(buffer1);
	sendCommand(buffer1);
}

TempWaveFormClass TempWaveForm;

