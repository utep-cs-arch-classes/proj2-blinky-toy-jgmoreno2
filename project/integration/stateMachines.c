#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"

unsigned char siren_on = 0;
unsigned char flash_on = 0;
unsigned char lights_on = 0;
unsigned char left_signal_on = 0;
unsigned char right_signal_on = 0;

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

void turn_red_on()		/* always toggle! */
{
  red_on = 1;			/* always changes an led */
}

void turn_green_on()	/* only toggle green if red is on!  */
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

void siren_machine()		/* alternate between toggling red & green */
{
  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: turn_red_on(); turn_green_off(); color = G; break;
  case G: turn_red_off(); turn_green_on(); color = R; break;
  }

  led_changed = 1;
  led_update();
}

void flash_machine()
{
  switch(lights_on){
  case 0: turn_red_on(); turn_green_on(); lights_on = 1; break;
  case 1: turn_red_off(); turn_green_off(); lights_on = 0; break;
  }
 
  led_changed = 1;
  led_update();
}

void left_signal_machine()
{
  static enum {R = 0, G = 1, not = 2} color = not;
  switch (color) {
  case R: turn_red_on(); color = G; break;
  case G: turn_green_on(); color = not; break;
  case not: turn_red_off(); turn_green_off(); color = R; break;
  }

  led_changed = 1;
  led_update();
}

void right_signal_machine()
{
  static enum {R = 0, G = 1, not = 2} color = not;
  switch (color) {
  case R: turn_red_on(); color = not; break;
  case G: turn_green_on(); color = R; break;
  case not: turn_red_off(); turn_green_off(); color = G; break;
  }

  led_changed = 1;
  led_update();
}
