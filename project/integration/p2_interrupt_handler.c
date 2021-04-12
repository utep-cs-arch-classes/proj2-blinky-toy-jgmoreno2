#include <msp430.h>
#include "switches.h"

//handle interrupts only for port vector 2 so only the S1-S4 buttons are used

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  //for each switch, set a flag when it is changed and call interrupt handler
  if (P2IFG & SW1) {
    P2IFG &= ~SW1;
    switch1_interrupt_handler();
  } else if (P2IFG & SW2) {
    P2IFG &= ~SW2;
    switch2_interrupt_handler();
  } else if (P2IFG & SW3) {
    P2IFG &= ~SW3;
    switch3_interrupt_handler();
  } else if (P2IFG & SW4) {
    P2IFG &= ~SW4;
    switch4_interrupt_handler();
  }
}
