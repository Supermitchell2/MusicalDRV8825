#include "MusicalDRV8825.h"

MusicalDRV8825::MusicalDRV8825(int step_pin_arg, int dir_pin_arg, int tempo_arg) 
:notes{"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}
,freqs{261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493}
,step_pin(step_pin_arg)
,dir_pin(dir_pin_arg)
{
	pinMode(step_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
	digitalWrite(dir_pin, HIGH);
	if (tempo_arg > 0) {
		tempo = tempo_arg;
	} else {
		tempo = 1000;
	}
	int freqs_len = sizeof(freqs) / sizeof(freqs[0]);
	periods = new int[freqs_len];
	for (int i = 0; i < freqs_len; i++) {
		// Periods are in microseconds
		periods[i] = (1.0f / freqs[i]) * 1000000;
	}
}

MusicalDRV8825::~MusicalDRV8825() {
	digitalWrite(dir_pin, LOW);
	digitalWrite(step_pin, LOW);
	delete[] periods;
}

void MusicalDRV8825::playNote(String note, int duration) {
	float period = periods[0]; // The period of a C note in uS
	for (int i = 0; i < 12; i++) {
		if (note == notes[i]) {
			period = periods[i];
		}
	}
	for (int time_elapsed = 0; time_elapsed < duration; time_elapsed += (period / 1000)) {
		digitalWrite(step_pin, HIGH);
		delayMicroseconds(period);
		digitalWrite(step_pin, LOW);
	}
}

void MusicalDRV8825::playSong(String notes[], float note_durations[], int notes_to_play) {
	for (int i = 0; i < notes_to_play; i++) {
		if (notes[i] == '0' || note_durations[i] == '0') {
			break;
		}
		// Note that the expression inline is is equivalent to the following
		// expression. The result of the expression is a time in ms.
		// 1.0f / (tempo * (1.0f / (note_durations[i] * 4)) / 60) * 1000
		playNote(notes[i], 240000.0f * note_durations[i] / tempo);
	}
}

void MusicalDRV8825::setTempo(int tempo_arg) {
	tempo = tempo_arg;
}

int MusicalDRV8825::getTempo() {
	return tempo;
}
