#include "MusicalDRV8825.h"
const int dir_pin = 11;
const int step_pin = 13;
String row_your_boat_notes[] = {	"C", "C", "C", "D", "E",
							"E", "D", "E", "F", "G", 
							"C", "C", "C", "G", "G",
							"G", "E", "E", "E", "C",
							"C", "C", "G", "F", "E",
							"D", "C" };
float row_your_boat_durations[] = {	0.25, 0.25, 0.25, 0.125, 0.25,
								0.25, 0.125, 0.25, 0.125, 0.5,
								0.125, 0.125, 0.125, 0.125, 0.125,
								0.125, 0.125, 0.125, 0.125, 0.125,
								0.125, 0.125, 0.25, 0.125, 0.25,
								0.125, 0.5 };
int tempo = 100;
void setup() {
	MusicalDRV8825 stepper(step_pin, dir_pin, tempo);
	stepper.playSong(row_your_boat_notes, row_your_boat_durations, 27);
}

void loop() {}
