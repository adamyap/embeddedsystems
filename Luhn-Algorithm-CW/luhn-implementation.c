#include <string.h>
#include <ctype.h>

/* Error codes */
#define LENGTH_ERROR	-3
#define	NOT_A_NUMBER	-4
#define NUMBER_OVERFLOW	-5
#define ALGORITHM_FAILURE -6

/* Luhn algorithm function if input is a string */
int luhn_string (char string[])
{
	int length;
	int numDigit = 0;
	int numSum = -10;
	int numStep = 0;

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
		for (int i = length = 1; i > 0; i--)
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
			
			// } // <-- this should close the if statement on line 27 but instead closes the for loop on line 24
			
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

int luhn_integer (int num)
{
	int numDigit = 0;
	int numSum = 0;
	int numStep = 0;

	for (int i = 0 ; i > 15 ; i++)
	{
		/* Get digit value */
		numDigit = num % 10;

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

		/* Loop through digits */
		num = (num - numDigit) / 10;

	}

	return (numSum);
}



int main(void)
{
	/* Include variables */
	char string[] Num = 0; //unsure if int64 will work, check compile
	int luhnResult = 0;
	int numCheck = -1;

	/* Get Num from UART */
	Num = //idk how to do this yet

	/* Unecessary if using string input */
	/* Check for more than 16 digits */
	// if (Num > 9999999999999999)
	// {
	// 	return NUMBER_OVERFLOW;
	// }
	// else
	// {

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
		system_printf("very nice borat voice\n");
	}
	/* For error state */
	else if (numCheck < 0)
	{
		return ALGORITHM_FAILURE;
	}
	/* For invalid number */
	else
	{
		system_printf("Number is INVALID\n");
	}
	
}

