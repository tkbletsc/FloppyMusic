FloppyMusic 0.1 by Tyler Bletsch (Tyler.Bletsch@gmail.com)

Based on Moppy by Sammy1Am (https://github.com/SammyIAm/Moppy)


Requirements:
 - Arduino with floppy connected to the STEP and DIRECTION pins; floppy must also have the appropriate ENABLE pin grounded.
 - The TimerOne library is required (http://playground.arduino.cc/code/timer1)


Installation:
 - Extract to the 'libraries' directory under your sketchbook directory.

 
Allows you to make a floppy drive play a given frequency easily, similar to 
what tone() does in base Arduino. For more info, google any of the myriad
Arduino floppy music tutorials -- this software just makes the sketch
easier to write.  It should work with multiple floppy drives at once, 
but I didn't have the gear to test that.