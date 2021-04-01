#ifndef MUSICAL_DRV8825
#define MUSICAL_DRV8825
#include "Arduino.h"

class MusicalDRV8825 {
	private:
		const int step_pin;
		const int dir_pin;
		int tempo;
		const int notes[12];
		const int freqs[12];
		int * periods;
	public:
		/**
		 * Constructor. Initializes step and dir pins,
		 * initializes the tempo, and calculates the periods.
		 * 
		 * @param step_pin the step pin number
		 * @param dir_pin the dir pin number
		 * @param tempo the tempo in beats per minute
		 */
		MusicalDRV8825(int, int, int);
		
		/**
		 * Destructor. Resets initialized pins to the low state
		 * and frees dynamically allocated memory.
		 */
		~MusicalDRV8825();
		
		/**
		 * Plays a single note.
		 * @param note the note to be played (e.g. "C" or "F#")
		 * @param int the duration of the note in ms
		 */
		void playNote(String, int);

		/**
		 * Plays a song. If notes_to_play is greater than or equal to 
		 * the length of the song, then the entire song will be played.
		 * 
		 * @param notes an array of notes to be played (e.g. "C", "F", "B")
		 * @param note_durations an array describing the type of note
		 * 	(e.g. 0.25 for a quarter note, 0.125 for an eigth note)
		 * @param notes_to_play the number of notes to play before stopping
		 */
		void playSong(String[], float[], int);

		/**
		 * Sets the tempo variable
		 * 
		 * @param tempo_arg the new tempo
		 */
		void setTempo(int);

		/**
		 * Gets the tempo
		 * 
		 * @return the current tempo
		 */
		int getTempo();
};
#endif
