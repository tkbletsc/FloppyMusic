// FloppyMusic by Tyler Bletsch (Tyler.Bletsch@gmail.com)

#ifndef FLOPPYMUSIC_H
#define FLOPPYMUSIC_H

#include "Arduino.h"

#include <stdint.h>
#include <TimerOne.h>

#define DEBUG_FLOPPY 0 // enable to get serial output from the module; also enables a low-level debug log (print_debug_log)

#define FLOPPY_MAX_POSITION 158
#define TIMER_PERIOD 40 // us

class FloppyMusic
{
  private:
    uint8_t pin_step;
    volatile uint8_t* pin_step_port; // used for fast writes
    uint8_t pin_step_mask; // used for fast writes
    
    uint8_t pin_dir;
    volatile uint8_t* pin_dir_port; // used for fast writes
    uint8_t pin_dir_mask; // used for fast writes
    
    uint16_t pos; // current position
    float freq; // frequency
    uint16_t period; // number of clock ticks per step
    uint16_t period_left; // remaining clock ticks for the current step
    bool dir_state; // current direction
    bool step_state; // current step
    
    void set_step(bool b); // fast write of the step pin; also sets step_state internally
    void set_dir(bool b);  // fast write of the dir  pin; also sets dir_state  internally
  public:
    int steps_in_freq; // public for debugging
    int dirs_in_freq;  // public for debugging
    
    class FloppyMusic *next; // public so global tick function can access it (i could have made a static method as a go-between, but meh)
    
    FloppyMusic(uint8_t pin_dir, uint8_t pin_step);
    void begin(); // initialize floppy and enable timer
    void set_freq(float f); // set the frequency to output; 0 for silence
    void tick(); // called by the global timer; public so global tick function can access it
    void reset(); // reset the floppy to home position
    void print_debug_log(); // serial print the ugly internal debug char buffer
};

#endif
