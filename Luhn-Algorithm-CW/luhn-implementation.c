#include <string.h>
#include <ctype.h>

#define LENGTH_ERROR	-3
#define	NOT_A_NUMBER	-4

int luhn_2 (char string[])
{
	int length;

	/* Get string length */
	length = strlen (string);

	/* If string is not 16 digits, return error */
	if (length != 16)
		return LENGTH_ERROR;

	/* first character is string[0] */	
	/* last character is string[length - 1] */	

	for (int i = length = 1; i > 0; i--)
		{
			if (isdigit (string [i])
			{
				numDigit = atoi (string [i]);
				/* Deal with the digit here */
			}
			else
				/* not a number */
				return NOT_A_NUMBER;

			
		}

}

int luhn (int num)
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
	unsigned int64 Num = 0; //unsure if int64 will work, check compile
	int result = 0;
	int numCheck = -1;

	/* Get Num from UART */
	Num = //idk how to do this yet

	/* Check for more than 16 digits */
	if (Num > 9999999999999999)
	{
		system_printf("ERROR - invalid number\n");
	}
	else
	{

		/* Carry out Luhn Algorithm */
		result = luhn (Num);

		/* Find the modulus of the sum */
		numCheck = result % 10;

	}

	/* Check if number is valid */
	/* For valid number */
	if (!numCheck)
	{
		system_printf("very nice borat voice\n");
	}
	/* For error state */
	else if (numCheck < 0)
	{
		system_printf("ERROR - failure in checking number\n");
	}
	/* For invalid number */
	else
	{
		system_printf("Number is INVALID\n");
	}
	
}

