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
int luhn_string (char string[])
{
    int length;
    int numDigit = 0;
    int numSum = -10;
    //int numStep = 0;

    /* Get string length */
    length = strlen (string);

    /* If string is not 16 digits, return error */
    if (length != 16)
    {
        return LENGTH_ERROR;
    }

    else
    {

        /* First character is string[0] */
        /* Last character is string[length - 1] */

        /* Deal with each digit individually */
        volatile int i;
        for (i=length;i > 0; i--)
        {
            /* Is the digit a number? */
            if (isdigit (string [i]))
            {
                /* Convert digit to integer */
                numDigit = atoi (string [i]);

                /* Deal with the digit here */

                /* Double every other digit */
                if (i % 2 == 0)
                {
                    numDigit = numDigit * 2;

                    /* If doubled digit is ten or higher, sum it's digits */
                    if (numDigit > 9)
                    {
                        /* Doubled digit will never be greater than 18, so modulo 10 plus one */
                        numDigit = (numDigit % 10) + 1;
                    }
                }

            /* Update sum */
            numSum = numSum + numDigit;

            } // <-- this should close the if statement on line 27 but instead closes the for loop on line 24

            else
            {
                /* not a number */
                return NOT_A_NUMBER;
            }
        }

    /* Function output */
    return numSum;

    }
}

int main(void)
{
    /* Include variables */
    char Num[15] = "377669976736261"; //unsure if int64 will work, check compile
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
