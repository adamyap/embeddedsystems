#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <msp430.h>
#include <stdbool.h>

volatile int n; // Input character count
int Num[16] = {}; // Input number integer array

// Function for running luhn algorithm over input number
bool luhn_check (int number[]){
    int numDigit = 0;
    int numSum = 0;
    int i;
    for (i=15;i >= 0; i--){ // Runs a loop to iterate 16 times
        numDigit = number [i]; // Convert digit to integer
        if (i % 2 == 0){ // Double every other digit
            numDigit = numDigit * 2; // If doubled digit is ten or higher, sum its digits
            if (numDigit > 9){
                numDigit = (numDigit % 10) + 1; // Doubled digit will never be greater than 18, so modulo 10 plus one
            }
        }
        numSum = numSum + numDigit; // Update sum
    }
    return (numSum % 10 == 0); // Function output boolean
}

// Function for sending an output string back through UART to PC
void sendString(char *str){
    volatile int length = strlen(str); // Find the length of the input string
    unsigned int i;
    for (i=0; i <= length; i++){
        while (!(UCA0IFG & UCTXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = str[i];
        volatile int i;
        for(i=0;i<10000;i++); // Software delay to ensure correct sending
    }
}

// Main loop
int main(void)
{
    // UART Initialisation
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    // Configure LEDs
    P1DIR |= BIT0 | BIT1;
    P1OUT &= ~(BIT0 | BIT1);
    // Configure UART pins
    P1SEL0 |= BIT4 | BIT5; // set 2-UART pin as second function
    // Configure UART for Power UP default clock rate
    UCA0CTLW0 |= UCSWRST; // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK; // set equal to SMCLK
    // Baud Rate calculation 115200 baud
    UCA0BR0 = 8; // 1000000/115200 = 8.68
    UCA0MCTLW = 0xD600; // Remainder - 0.68  Table 21.4 & 21.
    UCA0CTLW0 &= ~UCSWRST; // Initialize eUSCI
    UCA0IE |= UCRXIE; // Enable USCI_A0 RX interrupt
    __bis_SR_register(LPM0_bits|GIE); // Enter LPM0 CPU off, SMCLK running
    __no_operation(); // For debugger
}

// Interrupt function when an input character is recieved
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    /* Variables */
    volatile int i;
    volatile int d;
    switch(UCA0IV){
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                while(!(UCA0IFG & UCTXIFG)); // Wait for TX buffer to be ready for new data
                UCA0TXBUF = UCA0RXBUF;
                char input = UCA0RXBUF;
                if (isdigit(input)){ // Check if received data is a numeric digit (ASCII)
                    Num[n] = input - '0'; // Converts ASCII input to integer value and stores in correct array position
                    n++;
                    if (n >= 16){ // If 16 digits have been input
                        n = 0;
                        if (luhn_check(Num)){ // If input number valid
                            P1OUT ^= BIT1; // Turn GREEN LED on
                            TA0CCR0 = 16384; // 0.5s
                            TA0CTL = MC_1 | ID_0 | TASSEL_1 |TACLR; // Timer on
                            for(;;){
                                while(!(TA0CTL & TAIFG)){}
                                TA0CTL = MC_0 | ID_0 | TASSEL_1 |TACLR; // Timer off
                                // Clear flags
                                TA0CTL &= ~TAIFG;
                                TA0CTL |= TACLR;
                                P1OUT ^=BIT1; // Turn GREEN LED off
                                break;
                            }
                            sendString("\n\rValid\n\r");
                        }
                        else{
                            P1OUT ^= BIT0; // Turn RED LED on
                            TA0CCR0 = 32768; // 1s
                            TA0CTL = MC_1 | ID_0 | TASSEL_1 |TACLR;
                            for(;;){
                                while(!(TA0CTL & TAIFG)){}
                                TA0CTL = MC_0 | ID_0 | TASSEL_1 |TACLR;
                                TA0CTL &= ~TAIFG;
                                TA0CTL |= TACLR;
                                P1OUT ^=BIT0; // Turn RED LED off
                                break;
                            }
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
