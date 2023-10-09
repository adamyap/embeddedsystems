#include <msp430.h>
int main(void) {
 WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
P1DIR |= 0x01; // Set P1.0 as output
 for(;;) {
volatile unsigned int i; // prevent optimization
P1OUT ^= 0x01; // Toggle P1.0 using XOR
 i = 20000; // SW Delay
 do
 i--;
 while(i != 0);
 }
 return 0;
}
