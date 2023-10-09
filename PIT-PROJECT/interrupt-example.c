#include <msp450.h>

int main(void)
{
  WDTCTL = WTDPW + WDTHOLD; //Stop watchdog timer//
    //Disable GPIO power on default high impedance mode to activate previously configured port settings//
    PM5CTL0 &= ~LOCKLPM5; //off//
    //Set LED output bit//
    P1DIR |= ~BIT0; //on, set P1.0 to output direction//

    //START WITH LED OFF//
    P1OUT &= ~BIT0; //P1.0 off//

    //P2.3 input switch//
    //all writes are 1 byte//
    P2DIR &= ~BIT3; //Set P2.3 as input bit (input default power-up)//
    P2OUT |= BIT3; //BIT3 on, set outbit to pull up//
    P2REN |= BIT3; //BIT3 on , Enable internal pull up register//
    P2IES |= BIT3; //One is falling edge//
    P2IE |= BIT3; //BIT3 on, P2.3 interrupt enabled//
    P2IFG &= ~BIT3; //BIT3 off, P2.3 IFG cleared//
    //LPM4 - shutdown - 0.49uA - OFF Section 6.3 SLASE59B//

    __bis_SR_register(LPM4_bits + GIE ); //LPM4 with interrupts enabled//
}

//Port 2 interrupt service routine//
#pragma vector=PORT2_VECTOR
__interrupt void Port2_(void)
{
  P1OUT ^= BIT0; //P1.0 = toggle (xor)//
  P2IFG &= ~BIT3; //P2.3 IFG off (cleared)//
}
