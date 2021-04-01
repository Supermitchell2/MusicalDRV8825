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
