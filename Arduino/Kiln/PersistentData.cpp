// 
#include "PersistentData.h"

#define SETPOINTS_INDEX 0

AT24CX mem(SETPOINTS_INDEX, 40);


void PersistentDataClass::init()
{
}

void PersistentDataClass::readSetPoint(int index, int* rising, int* temp, int* time, int* enabled)
{
	int pos = index * 8 + SETPOINTS_INDEX;
	*rising = mem.readInt(pos); pos += 2;
	*temp = mem.readInt(pos); pos += 2;
	*time = mem.readLong(pos); pos += 2;
	*enabled = mem.readInt(pos); pos += 2;
	Serial.println("TimeFromMemory: " + String((int)time) + "s");
}

void PersistentDataClass::writeSetPoint(int index, int rising, int temp, int time, int enabled)
{
	//Serial.println("writeSetPoint: " + String(temp) + "°");
	int pos = index * 8 + SETPOINTS_INDEX;
	mem.writeInt(pos, rising); pos+=2;
	mem.writeInt(pos, temp); pos+=2;
	mem.writeLong(pos, time); pos+=2;
	mem.writeInt(pos, enabled); pos+=2;
	
	pos = index * 8 + SETPOINTS_INDEX;
	temp = mem.readInt(pos); pos += 2;
	//Serial.println("ReadAfterWriteSetPoint: " + String(temp) + "°");
}

PersistentDataClass PersistentData;
