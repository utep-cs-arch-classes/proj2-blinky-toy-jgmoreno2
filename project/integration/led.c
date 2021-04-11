#include <msp430.h>
#include "led.h"
#include "switches.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;// bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update(){
  if (switch1_state_changed && switch1_state_down) {
    char ledFlags = redVal[red_on] | greenVal[green_on]; /* by default, no LEDs on */

    P1OUT &= (0xff^LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;
    led_changed = 0;// set bits for on leds
  } else if (switch2_state_changed) {
    char ledFlags = 0;

    ledFlags |= switch2_state_down ? LED_GREEN : 0;
    ledFlags |= switch2_state_down ? LED_RED : 1;

    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
  } else if (switch3_state_changed) {
    char ledFlags = 0;

    ledFlags |= switch3_state_down ? LED_GREEN : 1;
    ledFlags |= switch3_state_down ? LED_RED : 1;
    
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

