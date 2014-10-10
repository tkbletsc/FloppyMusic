// FloppyMusic by Tyler Bletsch (Tyler.Bletsch@gmail.com)

#include <FloppyMusic.h>

FloppyMusic* first = NULL;

// to keep directions straight
#define FORWARD  LOW
#define BACKWARD HIGH

bool first_run = true;

#if DEBUG_FLOPPY
char dbg[102] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
int dbg_i=0;
#define DBG_PUTCHAR(c) { dbg[dbg_i] = (c); dbg_i = (dbg_i+1)%100; }
#else
#define DBG_PUTCHAR(c) { }
#endif

void FloppyMusic::set_step(bool b) {
    step_state = b;
    if (b) { *pin_step_port |=  pin_step_mask; }
    else   { *pin_step_port &= ~pin_step_mask; }
}

void FloppyMusic::set_dir(bool b) {
    dir_state = b;
    if (b) { *pin_dir_port |=  pin_dir_mask; }
    else   { *pin_dir_port &= ~pin_dir_mask; }
}

FloppyMusic::FloppyMusic(uint8_t _pin_dir, uint8_t _pin_step) {
    pin_dir = _pin_dir;
    pin_step = _pin_step;
    
    pin_dir_port  = portOutputRegister(digitalPinToPort(pin_dir));
    pin_dir_mask  = digitalPinToBitMask(pin_dir);
    
    pin_step_port  = portOutputRegister(digitalPinToPort(pin_step));
    pin_step_mask  = digitalPinToBitMask(pin_step);
    
    pinMode(pin_dir, OUTPUT);
    pinMode(pin_step, OUTPUT);
    
    pos = 0;
    freq = 0;
    period = 0;
    period_left = 0;
}

int x=0;

void timer_tick() {
	for ( FloppyMusic *p = first; p; p = p->next) {
        p->tick();
	}
}

void FloppyMusic::tick() {
    //DBG_PUTCHAR('t')
    period_left--;
    if (period_left==0) {
        steps_in_freq++;
        //DBG_PUTCHAR('T')
        period_left = period;
        set_step(!step_state); // also sets step_state
        
        if (dir_state==FORWARD) {
            pos++;
            DBG_PUTCHAR('+');
            if (pos >= FLOPPY_MAX_POSITION) {
                dirs_in_freq++;
                DBG_PUTCHAR('B');
                set_dir(BACKWARD); // also sets dir_state
            }
        } else if (dir_state==BACKWARD) {
            pos--;
            DBG_PUTCHAR('-');
            if (pos <= 0) {
                dirs_in_freq++;
                DBG_PUTCHAR('F');
                set_dir(FORWARD); // also sets dir_state
            }
        }
    }

}

void FloppyMusic::begin() {
    dir_state = FORWARD;
    step_state = HIGH;
    
	next = first;
	first = this;
    
    reset();
    
    if (first_run) {
        first_run = false;
        Timer1.initialize(TIMER_PERIOD); // Set up a timer at the defined resolution
        Timer1.attachInterrupt(timer_tick); // Attach the tick function
    }
    
}

void FloppyMusic::reset() {
    digitalWrite(pin_dir, BACKWARD); // forward
    for (int i=0; i<FLOPPY_MAX_POSITION; i++) {
        set_step(1);
        delay(2);
        set_step(0);
        delay(2);
    }
    
    pos = 0;
    
    set_dir(FORWARD);
}

void FloppyMusic::set_freq(float f) {
    steps_in_freq=0;
    dirs_in_freq=0;
	freq = f;
    if (freq) {
        period = 1.0 / freq * (1000000.0/TIMER_PERIOD/2);
        period_left = period;
    } else {
        period = 0;
    }
#if DEBUG_FLOPPY
    Serial.print("f=");
    Serial.print(freq);
    Serial.print(", p=");
    Serial.println(period);
#endif
}

void FloppyMusic::print_debug_log() {
#if DEBUG_FLOPPY
    DBG_PUTCHAR('>');
    Serial.println("debug_log{");
    Serial.println(dbg);
    Serial.println("}");
#else
    Serial.println("DEBUG_FLOPPY is disabled.");
#endif
}

