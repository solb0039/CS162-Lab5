/******************************************************************************* * 
** Program Filename:  main.cpp
** Author: Sean Solberg   
** Date:  30-Octber-2016
** Description: Ants and Doodlebugs simulation. 
** Input:  Number of steps that represent lives of the ants and doodlebugs
** Output:  A 20*20 grid is outputted to display with ants represented by "O", 
**	doodblebugs by "X " and empty spaces by "E".
***********************************************************************************/

#include "ant.hpp"
#include "critter.hpp"
#include "doodlebug.hpp"
#include <iostream>
#include "utils.hpp"
#include <time.h>
#include <unistd.h>

const int ROWS = 20;
const int COLS = 20;

/*************************************************************************  
** Function:  printDisplay
** Description: Function takes pointer to an array of pointers to objects
**		and iterates through the array to display the contents. 
** Parameters:  ***grid
** Pre-Conditions: None. This is the main function. 
** Post-Conditions:  Bool finishFlag must be false 
** Return:  void
*************************************************************************/

void printDisplay(critter*** grid) 
{
	/*Display grid by stepping through it and call indicator variable.*/
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
		{
			if (grid[i][j] == NULL)
			{
				std::cout << "E";
			}
			else if (grid[i][j] != NULL) 
			{ 
				std::cout << grid[i][j]->getIndicator(); 
			}

		}
		std::cout << std::endl;
	}
}

		

int main()
{
	/*Initiate random number generator and get time steps*/
	unsigned seed;
	seed = time(0);
	srand(seed);
	int timeSteps;
	

	/*Flag to end program*/
	bool finishFlag = false;

	/*Create grid*/ 
	critter ***grid = new critter**[ROWS];
	for (int i = 0; i < ROWS; i++)
		grid[i] = new critter*[COLS];

	/*intialize grid to null*/
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			grid[i][j] = NULL;
		}
	}
	
	/*Initialize board with 100 ants*/
	for (int aR = 0; aR < 100; aR++)
	{
		/*Loop until succesfully place an ant*/
		bool successFlag = false;
		do {
			
			int randCol = getRandomInteger(20);
			int randRow = getRandomInteger(20);
			
			if (grid[randRow][randCol] == NULL)
			{
				grid[randRow][randCol] = new ant();
				successFlag = true;
			}
			else successFlag = false;

		} while (!successFlag);
	}

	/*Initialize board with 5 doodlebugs*/
	for (int dbR = 0; dbR < 55; dbR++)
	{
		/*Loop until succesfully placed a doodlebug*/
		bool successFlag = false;
		do {
			
			int randCol = getRandomInteger(20);
			int randRow = getRandomInteger(20);

			if (grid[randRow][randCol] == NULL)
			{
				grid[randRow][randCol] = new doodlebug();
				successFlag = true;
			}
			else successFlag = false;
		} while (!successFlag);
	}

	/*Main do-while loop to iterate over time steps and exits upon user request*/
	do {
		/*Get an integer for number of time steps.  Max value provided to avoid 
 * 			accidental input of large time steps*/		
		timeSteps = getInteger("Enter the number of time steps?", 0, 10000);

		for (int step = 0; step < timeSteps; step++)
		{
		   /*Loop through board*/
		   for (int iR = 0; iR < ROWS; iR++)
		   {
			for (int jC = 0; jC < COLS; jC++)
			{
			   if (grid[iR][jC] != NULL)
			   {
			      /*Move Doodlebugs by calling move virtual function*/
			      if ((grid[iR][jC]->getIndicator() == 'X') && (!grid[iR][jC]->getMovedAlready()))
			      {
			         static_cast<doodlebug *>(grid[iR][jC])->move(grid, iR, jC);
			      }
			   }
			}
		    }

		   /*Move Ants. Iterate through array to locate them*/
		   for (int iR = 0; iR < ROWS; iR++)
		   {
			for (int jC = 0; jC < COLS; jC++)
			{
			   if (grid[iR][jC] != NULL)
			   {
				/*Move ant by calling move virtual function*/
			      if ((grid[iR][jC]->getIndicator() == 'O') && (!grid[iR][jC]->getMovedAlready()))
			      {
			         static_cast<ant *>(grid[iR][jC])->move(grid, iR, jC);
			      }
			   }
			}
		   }

		   /*Increment lives & reset move flags*/
		   for (int iR = 0; iR < ROWS; iR++)
		   {
		      for (int jC = 0; jC < COLS; jC++)
		      {
		         if ((grid[iR][jC] != NULL))
		         {
			    grid[iR][jC]->incrementLives();
			    grid[iR][jC]->resetMovedAlready();
			 }
		       }
		   }

		   /*Display output.  Pause for a moment to allow visualization*/
		   printDisplay(grid);
		   usleep(100000);
		   std::cout << "\033[2J\033[1;1H" << std::endl;
	    }

		/*Prompt user if they would like to continue*/
		finishFlag = getBoolean("Program ended.  Would you like to continue (Y/N)? ");

	} while (finishFlag);

	/*Deallocate the existing Ants and doodlebugs*/
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS ; j++)
		{
			if (grid[i][j] != NULL) 
			{
				delete grid[i][j];
			}
		}
	}

	/*Deallocate the critters on the board*/
	for (int i = 0; i < ROWS; i++) 
	{
		for (int j = 0; j< COLS; j++) 
		{
			delete grid[i][j];
		}
		delete grid[i];
	}
	delete grid;

    return 0;
}



