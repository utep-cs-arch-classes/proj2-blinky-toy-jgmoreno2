#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char switch1_state_down, switch1_state_changed, switch2_state_down, switch2_state_changed, switch3_state_down, switch3_state_changed, switch4_state_down, switch4_state_changed; /* effectively boolean */

static char 
switch1_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SW1);	/* if switch up, sense down */
  P2IES &= (p2val | ~SW1);	/* if switch down, sense up */
  return p2val;
}

static char
switch2_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SW2);
  P2IES &= (p2val | ~SW2);
  return p2val;
}

static char
switch3_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SW3);
  P2IES &= (p2val | ~SW3);
  return p2val;
}

static char
switch4_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SW4);
  P2IES &= (p2val | ~SW4);
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch1_update_interrupt_sense();
  switch2_update_interrupt_sense();
  switch3_update_interrupt_sense();
  switch4_update_interrupt_sense();
  led_update();
}

void
switch1_interrupt_handler()
{
  char p2val = switch1_update_interrupt_sense();
  switch1_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch1_state_changed = 1;
  select_machine();
  led_update();
}

void
switch2_interrupt_handler()
{
  char p2val = switch2_update_interrupt_sense();
  switch2_state_down = (p2val & SW2) ? 0 : 1;
  switch2_state_changed = 1;
  select_machine();
  led_update();
}

void switch3_interrupt_handler()
{
  char p2val = switch3_update_interrupt_sense();
  switch3_state_down = (p2val & SW3) ? 0 : 1;
  switch3_state_changed = 1;
  select_machine();
  led_update();
}

void switch4_interrupt_handler()
{
  char p2val = switch4_update_interrupt_sense();
  switch4_state_down = (p2val & SW4) ? 0 : 1;
  switch4_state_changed = 1;
  select_machine();
  led_update();
}
