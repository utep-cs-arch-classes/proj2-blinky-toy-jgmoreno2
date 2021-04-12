#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){
  static char blink_count = 0;
  if(++blink_count == 125){
    if(siren_on){
      siren_machine();
    }
    if(flash_on){
      flash_machine();
    }
    if(right_signal_on){
      right_signal_machine();
    }
    if(left_signal_on){
      left_signal_machine();
    }
    blink_count = 0;
  } else if(blink_count == 63){
    if(right_signal_on){
      right_signal_machine();
    }
    if(left_signal_on){
      left_signal_machine();
    }
  }
}
