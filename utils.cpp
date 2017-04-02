#include "utils.hpp"

/************************************************************************************
 * **Name: getInteger
 * **Description:  Reusable function to get and validate integer input. User parameters
 * **specify min and max values, and function validates input to be within that range
 * **before returning value. Function also takes a string message to prompt user for
 * **input.
 * *************************************************************************************/


int getInteger(std::string message, int minInt, int maxInt, int suggInt)
{
	int anInt;
	bool flag = false;

	/*Repeat until numeric value entered.  Code modified from stackoverflow suggestion*/
	do {

		std::cout << message << " Enter value between " << minInt << " and " << maxInt;
		if (suggInt != 0) {
			std::cout << " (suggested input is " << suggInt << ")." << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		std::cin >> anInt;

		if (std::cin.fail())
		{
			std::cout << "Inputted value in not a number.  Please try again." << std::endl;

			/*user didn't input a number*/
			std::cin.clear(); /*reset failbit*/

							  /* clear out the bad input from the stream*/
			std::cin.ignore(1000, '\n');
		}

		else if (std::cin)
		{
			/* clear out any additional input from the stream*/
			std::cin.ignore(1000, '\n');

			if (std::cin.gcount() > 1) {
				std::cout << "Input is mixed numeric and character." << std::endl;
				flag = false;
			}

			else if ((anInt < minInt) || (anInt > maxInt))
			{
				/*Inputted integer is not within defined limits*/
				std::cout << "Inputted value in not within range.  Please try again." << std::endl;
				flag = false;
			}
			else
			{
				/*Good input. Set flag and exit function*/
				flag = true;
			}

		};
	} while (flag == false);

	return anInt;

}


/************************************************************************************
 * **Name: getBoolean
 * **Description:  Reusable function to get and validate a boolean value. Includes a
 * **prompting string message to display to user
 * *************************************************************************************/

bool getBoolean(std::string message)
{
	bool boolAnswer = 0;
	bool loopFlag = false;

	do {
		std::cout << message << std::endl;
		char randomChoice;
		std::cin >> randomChoice;

		if ((randomChoice == 'y') || (randomChoice == 'Y')) {
			boolAnswer = 1;
			loopFlag = true;
		}
		else if ((randomChoice == 'n') || (randomChoice == 'N')) {
			boolAnswer = 0;
			loopFlag = true;
		}
	} while (loopFlag == false);

	return boolAnswer;
}


/************************************************************************************
 * **Name: getDouble
 * **Description:  Reusable function to get and validate a double value. Includes a
 * **prompting string message to display to user.
 * *************************************************************************************/

double getDouble(std::string doubleMessage, double minDouble, double maxDouble)
{
	double theDouble;

	bool flag = false;

	do {
		std::cout << doubleMessage << std::endl;
		std::cin >> theDouble;

		if (std::cin.fail())
		{
			std::cout << "Inputted value in not a number.  Please try again." << std::endl;

			/*user didn't input a number*/
			std::cin.clear(); /*reset failbit*/

							  /* clear out the bad input from the stream*/
			std::cin.ignore(1000, '\n');
		}

		else if (std::cin)
		{
			/* clear out any additional input from the stream*/
			std::cin.ignore(1000, '\n');

			if (std::cin.gcount() > 1) {
				std::cout << "Input is mixed numeric and character." << std::endl;
				flag = false;
			}

			else if ((theDouble < minDouble) || (theDouble > maxDouble))
			{
				/*Inputted integer is not within defined limits*/
				std::cout << "Inputted value in not within range.  Please try again." << std::endl;
				flag = false;
			}
			else
			{
				/*Good input. Set flag and exit function*/
				flag = true;
			}

		}
	} while (flag == false);


	return theDouble;
}


/************************************************************************************
 * **Name: getString
 * **Description:  Simple function to prompt user and get string.  Checks to see that
 * *input as actually entered and not blank.
 * *************************************************************************************/
std::string getString(std::string stringMessage)
{
	std::string aString;
	int size;

	/*Get string and validate that it is not empty*/
	do {
		std::cout << stringMessage << std::endl;

		getline(std::cin, aString);

		size = aString.length();

	} while (size == 0);

	return aString;
}


/************************************************************************************
 * *  *Name: getRandomInteger
 * *   *Description:  Reusable function to get and return random integer scaled between 0
 * *    *and maximum specified as parameter to function
 * *     ************************************************************************************/

int getRandomInteger(int maxValue)
{
	/*unsigned seed;*/
	/*seed = time(0);*/
	/*srand(seed);*/
	return rand() % maxValue;
}


