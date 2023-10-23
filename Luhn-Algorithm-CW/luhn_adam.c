#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <msp430.h>
#include <stdbool.h>

volatile int n;
int Num[16] = {};

/* Error codes */
#define LENGTH_ERROR -3
#define NOT_A_NUMBER -4
#define NUMBER_OVERFLOW -5
#define ALGORITHM_FAILURE -6

bool luhn_check (int number[])
{
    int numDigit = 0;
    int numSum = 0;
;
    int i;
    for (i=15;i >= 0; i--)
    {
        /* Convert digit to integer */
        numDigit = number [i];

        /* Deal with the digit here */

        /* Double every other digit */
        if (i % 2 == 0)
        {
            numDigit = numDigit * 2;

            /* If doubled digit is ten or higher, sum its digits */
            if (numDigit > 9)
            {
                /* Doubled digit will never be greater than 18, so modulo 10 plus one */
                numDigit = (numDigit % 10) + 1;
            }
        }

        /* Update sum */
        numSum = numSum + numDigit;
    }

    /* Function output */
    return (numSum % 10 == 0);
}

void sendString(const char *str)
{
    volatile int length = strlen(str);
    volatile int i;
    for (i=0; i <= length; i++)
    {
        while (!(UCA0IFG & UCTXIFG))
            ; // Wait for TX buffer to be ready for new data
        UCA0TXBUF = str[i];
    }
}

int main(void)
{
    /* UART Initialisation */

    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0 | BIT1;
    P1OUT &= ~(BIT0 | BIT1);

    /*TA0CTL = MC_1 | ID_0 | TASSEL_1 |TACLR;
    TA0CCR0 = 32768;
    TA0CCR1 = 65536;*/

    // Configure UART pins
    P1SEL0 |= BIT4 | BIT5;                    // set 2-UART pin as second function

    // Configure UART for Power UP default clock rate
    UCA0CTLW0 |= UCSWRST;                     // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;               // set equal to SMCLK

    // Baud Rate calculation 115200 baud
    UCA0BR0 = 8;                           // 1000000/115200 = 8.68
    UCA0MCTLW = 0xD600;                    // Remainder - 0.68  Table 21.4 & 21.5

    UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

    __bis_SR_register(LPM0_bits|GIE);     // Enter LPM0 CPU off, SMCLK running
    __no_operation();                     // For debugger
}


#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    /* Variables */
    volatile int i;
    volatile int d;
    switch(UCA0IV)
        {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                while(!(UCA0IFG & UCTXIFG)); // Wait for TX buffer to be ready for new data
                UCA0TXBUF = UCA0RXBUF;
                char input = UCA0RXBUF;
                if (isdigit(input))
                {
                    Num[n] = input - '0';
                    n++;

                    if (n >= 16)
                    {
                        n = 0;
                        if (luhn_check(Num))
                        {
                            P1OUT |= BIT1;

                            P1OUT &= ~BIT0;
                            /*TA0CCTL0 |= CCIE;*/
                            sendString("\n\rValid\n\r");
                        }
                        else
                        {
                            P1OUT |= BIT0;
                            P1OUT &= ~BIT1;
                            /*TA0CCTL1 |= CCIE;*/
                            sendString("\n\rInvalid\n\r");
                        }
                    }
                }
                break;
            case USCI_UART_UCTXIFG: break;
            case USCI_UART_UCSTTIFG: break;
            case USCI_UART_UCTXCPTIFG: break;
        }

}

/* #pragma vector= TIMER0_A0_VECTOR
__interruptvoidISR_TA0_CCR0(void)
{
    P1OUT &= ~BIT0;
    TA0CCTL0 &= ~CCIFG;
    TA0CCTL0 &= ~CCIE;
}

#pragma vector= TIMER0_A1_VECTOR
__interruptvoidISR_TA1_CCR0(void)
{
    P1OUT &= ~BIT1;
    TA0CCTL1 &= ~CCIFG;
    TA0CCTL1 &= ~CCIE;
}*/

