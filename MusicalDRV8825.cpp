/*
	MIT License
	
	Copyright (c) 2021 Mitchell Herbert
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */


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
