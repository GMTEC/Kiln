// 
#include "NextionIncludes.h"
#include "PageSetPoints.h"
#include "PageMain.h"
#include "persistentData.h"

static char buffer[80] = {};

void PageSetPointsClass::init()
{
	refreshPage();
}

static void PageSetPointsClass::onCancelSetPoints(void *ptr)
{
	Serial.println("onCancelSetPoints");
	//sendCommand("page 2");
}

static void PageSetPointsClass::onOKSetPoints(void *ptr)
{
	Serial.println("onOKSetPoints");

	for(int index = 0; index < MAX_SEGMENTS; index++)
	{
		SetPointsProdAndDef.defSetPoints.timeSP[index]		= PageSetPoints.getTimeInSecondsFromObjects("th", "tm", index);
		SetPointsProdAndDef.defSetPoints.degPerHourSP[index]	= atoi(PageSetPoints.getText("mr", index).c_str());
		SetPointsProdAndDef.defSetPoints.tempSP[index]		= atoi(PageSetPoints.getText("tt", index).c_str());
		SetPointsProdAndDef.defSetPoints.enabledSP[index]	= PageSetPoints.getValue("c", index);

		Serial.println("Time: " + String( PageSetPoints.getTimeInSecondsFromObjects("th", "tm", index)));
		Serial.println("Enabled: " + String(SetPointsProdAndDef.defSetPoints.tempSP[index]));
		//Serial.println("T°: " + String(PageSetPoints.getIntFromObject("tt" + String(index))));
	}

	SetPointsProdAndDef.defToProd();
}

long PageSetPointsClass::getTimeInSecondsFromObjects(String objHour, String objMin, int index)
{
	return atol(getText(objHour, index).c_str()) * 60 +  atol(getText(objMin, index).c_str());
}

void PageSetPointsClass::refreshPage()
{
	for(int index = 0; index < MAX_SEGMENTS; index++)
	{
		//Serial.println("refreshPage " + String(SetPointsProdAndDef.defSetPoints.tempSP[index]));
		setText("mr", index, String(SetPointsProdAndDef.defSetPoints.degPerHourSP[index]));
		setText("tt", index, String(SetPointsProdAndDef.defSetPoints.tempSP[index]));
		setText("th", index, String(SetPointsProdAndDef.defSetPoints.timeSP[index] / 60));
		setText("tm", index, String(SetPointsProdAndDef.defSetPoints.timeSP[index] % 60));
		setValue("c", index, SetPointsProdAndDef.defSetPoints.enabledSP[index]);
	}
}

String PageSetPointsClass::getText(String objName, int index, uint16_t len=3)
{
	char buf[80] = {0};
	uint16_t charNumber;
	String cmd;
	cmd += "get setpoints.";
	cmd += objName + String(index) + ".txt";
	sendCommand(cmd.c_str());
	charNumber =  recvRetString(buf,len);

	return String(buf);
}

bool PageSetPointsClass::setText(String objName, int index, String str)
{
	String cmd;
	cmd += "setpoints." + objName + String(index);
	cmd += ".txt=\"";
	cmd += str;
	cmd += "\"";
	sendCommand(cmd.c_str());
	//Serial.println("setText: " + cmd);
	
	return recvRetCommandFinished();
}

uint32_t PageSetPointsClass::getValue(String objName, int index)
{
	String cmd = String("get ");
	cmd += "setpoints." + objName + String(index);
	cmd += ".val";
	sendCommand(cmd.c_str());
	uint32_t number;
	recvRetNumber(&number);
	Serial.println("GetValue: " + cmd + ": " + String(number));

	return number;
}

bool PageSetPointsClass::setValue(String objName, int index, uint32_t number)
{
	char buf[10] = {0};
	String cmd;
	utoa(number, buf, 10);
	cmd += "setpoints." + objName + String(index);
	cmd += ".val=";
	cmd += buf;
	Serial.println("setValue: " + cmd);

	sendCommand(cmd.c_str());
	return recvRetCommandFinished();
}

long PageSetPointsClass::getLong(String objName, uint16_t len)
{
	uint16_t charNumber;
	String cmd;
	cmd += "get ";
	cmd += objName;
	cmd += ".txt";
	sendCommand(cmd.c_str());
	charNumber =  recvRetString(buffer,len);
	return atol(buffer);
}

PageSetPointsClass PageSetPoints;

