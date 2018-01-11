// 
#include "Motors.h"
#include "Libs/L298N.h"
#include "Pins.h"


L298N driver(ENA,IN1,IN2,IN3,IN4,ENB);
int time_delay = 500;
int speed = 255; // from 0 to 255 !!!!
bool toggle1 = false;

void MotorsClass::init()
{
	//driver.full_stop(10);
}

void MotorsClass::update()
{
	toggle1 = !toggle1;
	//Serial.println("Motor Toggle");
	//
	//driver.drive_motor(L298N::MOTOR_A, toggle1 ? speed : 0);
	//driver.drive_motor(L298N::MOTOR_B, toggle1 ? speed : 0);
	//driver.setup_motors(0,1,0,1);

}


MotorsClass Motors;

