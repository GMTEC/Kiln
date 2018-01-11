// Sound.h

#ifndef _SOUND_h
#define _SOUND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Libs/Pitches.h"


class SoundClass
{
 protected:


 public:
	void init();
	void playMelody(int param1 = 0);
	void playSequence(int param1);
};

extern SoundClass Sound;

#endif

