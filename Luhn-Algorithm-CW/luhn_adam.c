#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Error codes */
#define LENGTH_ERROR -3
#define NOT_A_NUMBER -4
#define NUMBER_OVERFLOW -5
#define ALGORITHM_FAILURE -6

/* Luhn algorithm function if input is a string */
int luhn_string (int number[])
{
    int length;
    int numDigit = 0;
    int numSum = 0;
    //int numStep = 0;
    /* First character is string[0] */
    /* Last character is string[length - 1] */

    /* Deal with each digit individually */
    volatile int i;
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
    return numSum;
}

int main(void)
{
    /* Include variables */
    volatile int i;
    int Num[] = {5,5,2,7,3,0,5,9,1,9,4,7,9,3,2,5};
    int luhnResult = 0;
    int numCheck = 0;

    /* Get Num from UART */
    // Num[] = "377669976736261" //idk how to do this yet

        /* Carry out Luhn Algorithm */
        luhnResult = luhn_string (Num);

        /* Error check */
        if (luhnResult < 0)
        {
            numCheck = -10;
        }

        else
        {
            /* Find the modulus of the sum */
            numCheck = luhnResult % 10;
        }

    // }

    /* Check if number is valid */
    /* For valid number */
    if (!numCheck)
    {
        printf("very nice borat voice\n");
    }
    /* For error state */
    else if (numCheck < 0)
    {
        return ALGORITHM_FAILURE;
    }
    /* For invalid number */
    else
    {
        printf("Number is INVALID\n");
    }

}
