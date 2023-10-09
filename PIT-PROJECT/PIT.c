#include <msp430.h>

// WDT refers to watchdog timer //
void main(void){ 
	WDTCLT = WDTPW + WDTHOLD; //Stop watchdog timer 
	PM5CTL0 &= ~LOCKLPM5; //off

	P1OUT |= BIT0 + BIT3;
	P1DIR = BIT0; //Set pin with LED1 to output

	//P2.3 input switch (all writes 1 byte)
	P2DIR &= ~BIT3; //Set p2.3 as input bit
	P2OUT |= BIT3;

	for(;;){ //Loop forever
		if((P2IN & BIT3) ==0){ //Check for button press
			P1OUT &= ~BIT0; //If button pressed, turn LED1 off
		}

		else{
			P1OUT |BIT0; //If button not pressed, turn LED1 on
		}
	}
} 