#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){
  static char blink_count = 0;
  if(++blink_count == 125){ // primary interval at which machines are advanced
    
    // if a machine is on, advance its state and reset the clock
    
    if(siren_on){
      siren_machine();
    }
    else if(flash_on){
      flash_machine();
    }
    else if(right_signal_on){
      right_signal_machine();
    }
    else if(left_signal_on){
      left_signal_machine();
    }
    blink_count = 0;
  } else if(blink_count == 63){ // half-time interval for machines that require double the states

    // if machine is on, advance its state
    
    if(left_signal_on){
      left_signal_machine();
    }
    else if(right_signal_on){
      right_signal_machine();
    }
  }
}
