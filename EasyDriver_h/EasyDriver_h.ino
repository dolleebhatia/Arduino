/*
  EasyDriver.h - Arduino Library for EasyDriver 3.0 stepper driver board from Sparkfun.com
  
  Based on:
  Stepper.h - - Stepper library for Wiring/Arduino - Version 0.4
  Original library     (0.1) by Tom Igoe.
  Two-wire modifications   (0.2) by Sebastian Gassner
  Combination version   (0.3) by Tom Igoe and David Mellis
  Bug fix for four-wire   (0.4) by Tom Igoe, bug fix from Noah Shibley


      I wanted This library to be a simple drop-in replacement for the standard stepper lib.
      just change some defines and go!!

                                                Makenb "at" gmail.com      8/28/09


*/

// ensure this library description is only included once
#ifndef EasyDriver_h
#define EasyDriver_h

// library interface description
class Stepper {
  public:
    // constructors:
    Stepper(int number_of_steps, int dir_pin, int step_pin);

    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int number_of_steps);

    int version(void);

  private:
    void stepMotor(int this_step);
    
    int direction;        // Direction of rotation
    int speed;          // Speed in RPMs
    unsigned long step_delay;    // delay between steps, in ms, based on speed
    int number_of_steps;      // total number of steps this motor can take
//    int pin_count;        // whether you're driving the motor with 2 or 4 pins
    int step_number;        // which step the motor is on
    
    // motor pin numbers:
    int dir_pin;
    int step_pin;
    
    long last_step_time;      // time stamp in ms of when the last step was taken
};

#endif

