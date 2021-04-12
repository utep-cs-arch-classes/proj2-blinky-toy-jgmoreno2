#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

// all below except lights_on resemble the status of a machine. ex: siren_on = 1 -> siren machine is on
unsigned char siren_on = 0;
unsigned char flash_on = 0;
unsigned char lights_on = 0;
unsigned char left_signal_on = 0;
unsigned char right_signal_on = 0;

// uses the most recently pushed button as an indicator for which machine to turn on. All others are turned off
void select_machine()
{
  if(switch1_state_down){
    siren_on = 1;
    flash_on = 0;
    left_signal_on = 0;
    right_signal_on = 0;
  } else if(switch2_state_down){
    siren_on = 0;
    flash_on = 1;
    left_signal_on = 0;
    right_signal_on = 0;
  } else if(switch3_state_down){
    siren_on = 0;
    flash_on = 0;
    left_signal_on = 1;
    right_signal_on = 0;
  } else if(switch4_state_down){
    siren_on = 0;
    flash_on = 0;
    left_signal_on = 0;
    right_signal_on = 1;
  }
}

//below functions signal for an led to be turned off or on

void turn_red_on() 
{
  red_on = 1;			
}

void turn_green_on()	
{
  green_on = 1;
}

void turn_red_off()
{
  red_on = 0;
}

void turn_green_off()
{
  green_on = 0;
}

// the following methods advance the state of their corresponding machine

void siren_machine() // machine that switches between red and green, alternating between high and low tones to mimick a police siren
{
  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: turn_red_on(); turn_green_off(); buzzer_set_period(1000); color = G; break;
  case G: turn_red_off(); turn_green_on(); buzzer_set_period(750); color = R; break;
  }

  led_changed = 1;
  led_update();
}

void flash_machine() // machine that switches between on and off lights and sound to mimick a car alarm being triggered
{
  switch(lights_on){
  case 0: turn_red_on(); turn_green_on(); buzzer_set_period(800); lights_on = 1; break;
  case 1: turn_red_off(); turn_green_off(); buzzer_set_period(0); lights_on = 0; break;
  }
 
  led_changed = 1;
  led_update();
}

void left_signal_machine() // machine that triggers red, green, then off lights and creates high and low sounds to mimick a turning signal
{
  static enum {R = 0, not1 = 1, G = 2, not2 = 3} color = not2;
  switch (color) {
  case G: turn_green_on(); buzzer_set_period(1000); color = not1; break;
  case not1: buzzer_set_period(0); color = R; break;
  case R: turn_red_on(); buzzer_set_period(1250); color = not2; break;
  case not2: turn_red_off(); turn_green_off(); buzzer_set_period(0); color = G; break;
  }

  led_changed = 1;
  led_update();
}

void right_signal_machine() // machine that does the same as the one above, with the exception that the lights move toward the right
{
  static enum {R = 0, not1 = 1, G = 2, not2 = 3} color = not2;
  switch (color) {
  case R: turn_red_on(); buzzer_set_period(1000); color = not1; break;
  case not1: buzzer_set_period(0); color = G; break;
  case G: turn_green_on(); buzzer_set_period(1250); color = not2; break;
  case not2: turn_red_off(); turn_green_off(); buzzer_set_period(0); color = R; break;
  }

  led_changed = 1;
  led_update();
}
