int main(void)
{
	/*Include variables*/
	int Num = 0;
	int numDigit = 0;
	int numSum = 0;
	numCheck = -1;
	int numStep = 0;

	/*Get Num from UART*/
	Num = //idk how to do this yet

	/*Protection*/
	if Num > 9999999999999999 or Num < 000000000000000
		system_printf("ERROR - invalid number\n");

	else

		/*Carry out Luhn Algorithm*/
		
		for (int i = 0 ; i > 15 ; i++)
		{
			/*Get digit value*/
			numDigit = Num % 10;

			/*Double every other digit*/
			if (i % 2 == 0) 
			{
				numDigit = numDigit * 2;

				/*If doubled digit is ten or higher, sum it's digits*/
				if (numDigit > 9)
				{
					/*Doubled digit will never be greater than 18, so modulo 10 plus one*/
					numDigit = (numDigit % 10) + 1;
				}
			}

		/*Update sum*/
		numSum = numSum + numDigit;

		/*Loop through digits*/
		Num = (Num - numDigit) / 10;

		}

	/*Check if number is valid*/
	/*For valid number*/
	if (numCheck == 0)
	{
		system_printf("very nice borat voice\n");
	}
	/*For error state*/
	else if (numCheck < 0)
	{
		system_printf("ERROR - failure in checking number\n");
	/*For invalid number*/
	else
	{
		system_printf("Number is INVALID\n");