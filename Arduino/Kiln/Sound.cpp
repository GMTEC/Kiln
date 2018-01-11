// 

#include "Sound.h"
#include "Pins.h"
#include "Libs/MelodyUtils.h"

int melody[3][8] = {
	{NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4},
	{NOTE_DS8, 0, 0, 0, 0, 0, 0, 0},
	{NOTE_DS8, 0, 0, 0, 0, 0, 0, 0}
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[3][8] = {
	{4, 8, 8, 4, 4, 4, 4, 4},
	{4, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0}
};

void SoundClass::init()
{
	playSequence(1);
}

void SoundClass::playMelody(int param1 = 0)
{
	MelodyUtils mel(LOUDSPEAKER_PIN);
	mel.Glis(NOTE_C3, NOTE_C4, 1);
	delay(100);
	mel.Trem(NOTE_C3, 100, 10);
}

void SoundClass::playSequence(int param1)
{
	// iterate over the notes of the melody:
	for (int thisNote = 0; thisNote < 8; thisNote++) {

		// to calculate the note duration, take one second
		// divided by the note type.
		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		if(noteDurations[param1][thisNote] == 0) break;
		int noteDuration = 1000 / noteDurations[param1][thisNote];
		tone(8, melody[param1][thisNote], noteDuration);

		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		int pauseBetweenNotes = noteDuration * 1.30;
		delay(pauseBetweenNotes);
		// stop the tone playing:
		noTone(8);
	}
 }

SoundClass Sound;

