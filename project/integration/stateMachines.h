#ifndef stateMachine_included
#define stateMachine_included

// the following resemble the status of all states
unsigned char siren_on;
unsigned char flash_on;
unsigned char lights_on;
unsigned char left_signal_on;
unsigned char right_signal_on;

// machine functionality
void select_machine();
void siren_machine();
void flash_machine();
void left_signal_machine();
void right_signal_machine();

#endif // included
