// SSR.h

#ifndef _SSR_h
#define _SSR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class SSRClass
{
 protected:

 public:
	void init();
	void updateRelayState();
	void setPower(int pwr);
};

extern SSRClass SSR;

#endif

