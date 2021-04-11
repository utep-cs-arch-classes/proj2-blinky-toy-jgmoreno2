#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch1_state_changed = 1;
  switch2_state_changed = 1;
  switch3_state_changed = 1;
  switch4_state_changed = 1;
  led_update();
}

void led_update(){
  if (switch1_state_changed) {
    char ledFlags = 0; /* by default, no LEDs on */

    ledFlags |= switch1_state_down ? LED_GREEN : 0;
    ledFlags |= switch1_state_down ? 0 : LED_RED;

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  } else if (switch2_state_changed) {
    char ledFlags = 0;

    ledFlags |= switch2_state_down ? 0 : LED_GREEN;
    ledFlags |= switch2_state_down ? 0 : LED_RED;

    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
  } else if (switch3_state_changed) {
    char ledFlags = 0;

    ledFlags |= switch3_state_down ? LED_GREEN : 0;
    ledFlags |= switch3_state_down ? 0 : LED_RED;
    
    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
  } else if (switch4_state_changed) {
    char ledFlags = 0;

    ledFlags |= switch4_state_down ? LED_GREEN : 0;
    ledFlags | switch4_state_down ? LED_RED : 0;

    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |- ledFlags;
  }
  switch1_state_changed = 0;
  switch2_state_changed = 0;
  switch3_state_changed = 0;
  switch4_state_changed = 0;
}

