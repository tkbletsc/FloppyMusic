// Use FloppyMusic by Tyler Bletsch (Tyler.Bletsch@gmail.com) to play a few songs.

#include "pitches.h"
#include <TimerOne.h> // FloppyMusic requires the TimerOne library (http://playground.arduino.cc/code/timer1)
#include <FloppyMusic.h>

FloppyMusic f(3,2); // DIRECTION, STEP

int melody_starwars[] = {
  NOTE_C2, 12,  // note, duration (8=eighth note, etc.)
  NOTE_C2, 12,
  NOTE_C2, 12,
  NOTE_F2, 2, 
  NOTE_C3, 2, 
  NOTE_AS2, 12,
  NOTE_A2, 12,
  NOTE_G2, 12,
  NOTE_F3, 2,
  NOTE_C3, 4,
  NOTE_AS2, 12,
  NOTE_A2, 12,
  NOTE_G2, 12,
  NOTE_F3, 2,
  NOTE_C3, 4,
  NOTE_AS2, 12,
  NOTE_A2, 12,
  NOTE_AS2, 12,
  NOTE_G2, 2,
};
int n_melody_starwars = sizeof(melody_starwars)/sizeof(*melody_starwars);

int melody_shave[] = {
  NOTE_C4, 4, 
  NOTE_G3, 8, 
  NOTE_G3, 8, 
  NOTE_A3, 4, 
  NOTE_G3, 4, 
  0,       4, 
  NOTE_B3, 4, 
  NOTE_C4, 4,
};
int n_melody_shave = sizeof(melody_shave)/sizeof(*melody_shave);

void play_song(int melody[], int num_notes) {
  for (int i=0; i<num_notes; i+=2) {
    int note = melody[i];
    int duration = 1500/melody[i+1];

    // to calculate the note duration, take one second divided by the note type.
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    f.set_freq(note);
    delay(duration);

    int pauseBetweenNotes = duration / 3;
    f.set_freq(0);
    delay(pauseBetweenNotes);

  }
}

void setup() {
  Serial.begin(9600);  
  Serial.println("SETUP init");
  f.begin();
  delay(300);
}

void loop() {
  Serial.println("Playing 'Shave and a Haircut'");
  play_song(melody_shave,n_melody_shave);
  delay(500);
  
  Serial.println("Playing 'Star Wars' intro");
  play_song(melody_starwars,n_melody_starwars);
  delay(500);
}



