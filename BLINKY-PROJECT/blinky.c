#include <msp430fr2433.h> 
int main(void) {
 WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
// Disable the GPIO power-on default high-impedance mode
// to activate previously configured port settings
PM5CTL0 &= ~LOCKLPM5; //off
P1DIR |= BIT0; // Set P1.0 as output
 for(;;) {
volatile unsigned int i; // prevent optimization
P1OUT ^= BIT0; // Toggle P1.0 using XOR
 
 i = 20000; // SW Delay
 do
 i--;
 while(i != 0);
 }
 return 0;
}
