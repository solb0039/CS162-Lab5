
#include "doodlebug.hpp"
#include "utils.hpp"

/**************************************************************************************  
 * ** Function:  Move
 * ** Description:  This is a very long function that tries to move the 
 * 	doodlebug on the board by checking all the adjacent cells for 
 * 	an Ant. If an ant is found, the DB eats the ant and returns.  If
 * 	no Ant class is found, then the DB tries to move to an adajcent
 * 	cell. If no cell is available, no action is taken. For each iteration
 * 	the DB also checks the condition to breed and starve.
 * ** Parameters:  critter*** grid, the pointer to the array of critter objects
 * 		int row, the reference row where the current DB is
 * 		int col, the reference col where the current DB is
 * ** Pre-Conditions: None 
 * ** Post-Conditions: There are two bool exit flags that control the two do-while
 * 		loops. Exiting the do-while loop(s) will complete function call and 
 * 		return to main. 
 * ** Return:  Void
 * **********************************************************************************/


void doodlebug::move(critter*** grid, int row, int col)
{	
	/*Flag variables to control loop execution*/
	bool exitDBFlag = false;
	bool noEatFlag = false;
	bool eatFlag = false;
	bool upFlag = false;
	bool downFlag = false;
	bool rightFlag = false;
	bool leftFlag = false;

	/*Check to see if adjacent cell is ant. Randomly try all 4 locations
 	if no ant after checking all, then move doodlebug without eating*/
 	
	/*First, check for ant*/
	do {
		/*Get random integer to represent direction*/
		int randDBMove = (getRandomInteger(4) + 1);

		switch (randDBMove)
		{
		   case 1: /*Up*/
		   {
			upFlag = true;

			/*Check if adjacent cell is in bounds and is not NULL*/
			if (((row - 1) >= 0) && (grid[row - 1][col] != NULL))
			{
				if ((grid[row - 1][col]->getIndicator() == 'O') && (!grid[row - 1][col]->getMovedAlready()) )
				{
					/*Found an ant. Eat it and set exit flag*/
					eatAnt(grid, (row - 1), col);
					exitDBFlag = true;
					eatFlag = true;

					/*Move DB to that position*/
					grid[row - 1][col] = grid[row][col];
					grid[row - 1][col]->setMovedAlready();

					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;

					/*Reset eat counter*/
					grid[row - 1][col]->resetEatCounter();

					/*If lives = 8, then breed*/
					if (grid[row - 1][col]->getLives() == 8)
					{
						/*Breed*/
						breed(grid, (row - 1), col);
						grid[row - 1][col]->resetLives();
					}

				}
			}
		   }
		   	break;
		
		   case 2: /*Down*/
		   {
			downFlag = true;
			
			/*Check if ant and in bounds*/
			if (((row + 1) <20) && (grid[row + 1][col] != NULL))
			{
				if ((grid[row + 1][col]->getIndicator() == 'O') && (!grid[row + 1][col]->getMovedAlready()))
				{
					/*If ant then eat and set exit flag*/
					exitDBFlag = true;
					eatAnt(grid, (row + 1), col);
					eatFlag = true;

					/*move DB to that position*/
					grid[row + 1][col] = grid[row][col];
					grid[row + 1][col]->setMovedAlready();

					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;

					/*Reset eat counter*/
					grid[row + 1][col]->resetEatCounter();

					/*If lives = 8, then breed*/
					if (grid[row + 1][col]->getLives() == 8)
					{
						/*Breed*/
						breed(grid, (row + 1), col);
						grid[row + 1][col]->resetLives();
					}
				}
			}
		    }
			break;
		
		case 3: /*Right*/
		{
			rightFlag = true;
			
			/*Check if ant and in bounds*/
			if (((col + 1) < 20) && (grid[row][col+1] != NULL))
			{
				if ( (grid[row][col+1]->getIndicator() == 'O') && (!grid[row][col + 1]->getMovedAlready()) )
				{
					/*If ant then eat and set exit flag*/
					exitDBFlag = true;
					eatAnt(grid, (row), (col+1));
					eatFlag = true;

					/*move DB to that position*/
					grid[row][col + 1] = grid[row][col];
					grid[row][col + 1]->setMovedAlready();

					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;

					/*Reset eat counter*/
					grid[row][col+1]->resetEatCounter();

					/*If lives = 8, then breed*/
					if (grid[row ][col+1]->getLives() == 8)
					{
						/*breed*/
						breed(grid, (row), (col+1));
						grid[row][col+1]->resetLives();
					}

				}
			  }
		   }
			break;
		
		case 4: /*Left*/
		{
			leftFlag = true;
			
			/*Check if ant and in bounds*/
			if (((col - 1) >= 0) && (grid[row][col - 1] != NULL))
			{
				if ((grid[row][col - 1]->getIndicator() == 'O') && (!grid[row][col - 1]->getMovedAlready()) )
				{
					/*If ant then eat and set exit flag*/
					exitDBFlag = true;
					eatAnt(grid, (row), (col - 1));
					eatFlag = true;

					/*move DB to that position*/
					grid[row][col - 1] = grid[row][col];
					grid[row][col - 1]->setMovedAlready();

					//grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;

					/*Reset eat counter*/
					grid[row][col-1]->resetEatCounter();

					/*If lives = 8, then breed*/
					if (grid[row][col - 1]->getLives() == 8)
					{
						/*breed*/
						breed(grid, (row), (col - 1));
						grid[row][col-1]->resetLives();
					}

				}
			 }
		  }
			break;
		
		  default:
			break;
		}

		/*If all directions have been checked and the DB did not eat*/
		if ( ( (upFlag && downFlag) && (rightFlag && leftFlag) ) && !eatFlag )
		{ 
			noEatFlag = true;
			grid[row][col]->incrementEatCounter();
			exitDBFlag = true; 
		}
		
	} while (!exitDBFlag);

	/*Then, if no ant was eaten, move cell using same logic as Ant*/
	bool upFlag2 = false;
	bool downFlag2 = false;
	bool rightFlag2 = false;
	bool leftFlag2 = false;

	if (noEatFlag == true) {

		bool exitDBMoveFlag = false;
		bool moveFlag = false;

		do {
			int randDBMove2 = (getRandomInteger(4) + 1);

			switch (randDBMove2)
			{
			case 1: /*Up*/
			{
				upFlag2 = true;

				/*If adjacent space unoccupied and on the grid, move*/
				if (((row - 1) >= 0) && (grid[row - 1][col] == NULL))
				{
					/*Move to that space*/
					grid[row - 1][col] = (grid[row][col]);
					grid[row - 1][col]->setMovedAlready();

					/*Set pointer back to null to make old space a critter class again*/
					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;
					exitDBMoveFlag = true;
					moveFlag = true;

					/*If lives = 8, then breed*/
					if (grid[row - 1][col]->getLives() == 8)
					{
						/*breed*/
						breed(grid, (row - 1), col);
						grid[row - 1][col]->resetLives();
					}
					
					/*Check if havent eaten*/
					if (grid[row-1][col]->getEatCounter() == 3)
					{
						/*Starve.  Delete the doodlebug*/
						delete grid[row-1][col];

						grid[row-1][col] = static_cast<critter *>(grid[row-1][col]);
						grid[row - 1][col] = NULL;
					}
				}
			}
				break;

			case 2: /*Down*/
			{
				downFlag2 = true;

				/*If adjacent space unoccupied and on the grid, move the ant*/
				if (((row + 1) < 20) && (grid[row + 1][col] == NULL))
				{
					/*Move to that space*/
					grid[row + 1][col] = (grid[row][col]);
					grid[row + 1][col]->setMovedAlready();
					
					/*Set pointer back to null to make old space a critter class again*/
					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;
					exitDBMoveFlag = true;
					moveFlag = true;

					/*If lives = 8, then breed*/
					if (grid[row + 1][col]->getLives() == 8)
					{
						/*breed*/
						breed(grid, (row + 1), col);
						grid[row + 1][col]->resetLives();
					}
					
					/*Check if havent eaten*/
					if (grid[row+1][col]->getEatCounter() == 3)
					{
						/*Starve.  Delete the doodlebug*/
						delete grid[row+1][col];

						grid[row+1][col] = static_cast<critter *>(grid[row+1][col]);
						grid[row + 1][col] = NULL;
					}

				}
			}
				break;

			case 3: /*Right*/
			{
				rightFlag2 = true;
				/*If adjacent space unoccupied and on the grid, move the ant*/
				if (((col + 1) < 20) && (grid[row][col + 1] == NULL))
				{
					/*Move to that space*/
					grid[row][col + 1] = (grid[row][col]);
					grid[row][col + 1]->setMovedAlready();

					/*Set pointer back to null to make old space a critter class again*/
					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;
					exitDBMoveFlag = true;
					moveFlag = true;

					/*If lives = 8, then breed*/
					if (grid[row][col + 1]->getLives() == 8)
					{
						/*breed*/
						breed(grid, (row), (col + 1));
						grid[row][col+1]->resetLives();
					}

					/*Check if havent eaten*/
					if (grid[row][col +1]->getEatCounter() == 3)
					{
						/*Starve. Delete the doodlebug*/
						delete grid[row][col + 1];
						grid[row][col + 1] = static_cast<critter *>(grid[row][col + 1]);
						grid[row][col + 1] = NULL;
					}

				}
			}
				break;

			case 4: /*Left*/
			{
				leftFlag2 = true;

				/*If adjacent space unoccupied and on the grid, move the ant*/
				if (((col - 1) >= 0) && (grid[row][col - 1] == NULL))
				{
					/*Move to that space*/
					grid[row][col - 1] = (grid[row][col]);
					grid[row][col - 1]->setMovedAlready();

					/*Set pointer back to null to make old space a critter class again*/
					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;
					exitDBMoveFlag = true;
					moveFlag = true;

					/*If lives = 8, then breed*/
					if (grid[row][col - 1]->getLives() == 8)
					{
						/*breed*/
						breed(grid, (row), (col - 1));
						grid[row][col-1]->resetLives();
					}

					/*Check if havent eaten*/
					if (grid[row][col - 1]->getEatCounter() == 3)
					{
						/*Starve. Delete the doodlebug*/
						delete grid[row][col - 1];
						grid[row][col - 1] = static_cast<critter *>(grid[row][col - 1]);
						grid[row][col - 1] = NULL;
					}

				}
			}
				break;

			default:
				break;
			}
			
			/*If doodlebug has checked all options and cannot move*/
			if (((upFlag2 && downFlag2) && (rightFlag2 && leftFlag2)) && (!moveFlag) ) 
			{ 
				/*Couldnt move.*/
				if (grid[row][col]->getLives() == 8) 
				{
					grid[row][col]->resetLives();
				}

				/*Check if havent eaten*/
				if (grid[row][col]->getEatCounter() == 3)
				{
					/*Starve.  Delete the doodlebug*/
					delete grid[row][col];
					grid[row][col] = static_cast<critter *>(grid[row][col]);
					grid[row][col] = NULL;
				}

				exitDBMoveFlag = true; 
			}
		} while (!exitDBMoveFlag);
	}
}


/*********************************************************************************  
 * ** Function: eatAnt  
 * ** Description: Deletes the ant class on the grid.  
 * ** Parameters:  critter*** grid, a pointer to the array
 * 		int row, the reference row where the ant pointer is located
 * 		int col, the reference column where the ant pointer is located
 * ** Pre-Conditions:  None
 * ** Post-Conditions:  None
 * ** Return:  Void
 * *****************************************************************************/	


void doodlebug::eatAnt(critter*** grid, int row, int col) 
{
	/*Delete Ant*/
	delete grid[row][col];
	grid[row][col]=NULL;
	
	/*Cast back to critter*/
	grid[row][col] = static_cast<critter *>(grid[row][col]);
}


/*****************************************************************************  
 * ** Function:  Breed
 * ** Description:  Function randomly checks all adjacent cells to test if open
 * 		if the cell is open, a doodlebug is created. If no cells are 
 * 		open, then function terminates with no action. 
 * ** Parameters:  critter*** grid, a pointer to the grid array
 * 		int row, the reference row in the grid where the DB is
 * 		int col, the reference columnin the grid where the DB is
 * ** Pre-Conditions:  None
 * ** Post-Conditions:  Bool exitFlag must be true.  This is accomplished by
 * 		either placing a DB, or after checking all adjacent cells
 * 		without breeding a new DB. 
 * ** Return:  Void
 * ***************************************************************************/


void doodlebug::breed(critter*** grid, int row, int col) 
{
	/*Breed by adding 1 DB to grid*/
	bool exitFlag = false;

	/*Use flags to only test each direction once*/
	bool upFlag = false;
	bool downFlag = false;
	bool rightFlag = false;
	bool leftFlag = false;

	do {
		/*Randomly generate direction*/
		int randDBMove = (getRandomInteger(4) + 1);

		switch (randDBMove)
		{
		case 1:
		{
			if (!upFlag)
			{
				upFlag = true;
				/*Try to place an ant above*/
				/*Check if in bounds*/
				if ((row - 1) >= 0)
				{
					/*Check if space is open*/
					if (grid[row - 1][col] == NULL)
					{
						/*Success! Add the DB*/
						grid[row - 1][col] = new doodlebug();

						exitFlag = true;
					}
				}
			}
		}
		break;
		
		case 2:
		{
			if (!downFlag)
			{
				downFlag = true;

				/*Try to place an ant below*/
				/*Check if in bounds*/
				if ((row + 1) < 20)
				{
					/*Check if space is open*/
					if (grid[row + 1][col] == NULL)
					{
						/*Success! Add the ant*/
						grid[row + 1][col] = new doodlebug();

						exitFlag = true;
					}
				}
			}
		}
		break;
		
		case 3:
		{
			if (!rightFlag)
			{
				rightFlag = true;

				/*Try to place an ant to the right*/
				/*Check if in bounds*/
				if ((col + 1) < 20)
				{
					/*Check if space is open*/
					if (grid[row][col + 1] == NULL)
					{
						/*Success! Add the ant*/
						grid[row][col + 1] = new doodlebug();

						exitFlag = true;
					}
				}
			}
		}
		break;
		
		case 4:
		{
			if (!leftFlag)
			{
				leftFlag = true;

				/*Try to place an ant on the row above*/
				/*First, check if in bounds*/
				if ((col - 1) >= 0)
				{
					/*Check if space is open*/
					if (grid[row][col - 1] == NULL)
					{
						/*Success! Add the DB*/
						grid[row][col - 1] = new doodlebug();

						exitFlag = true;
					}
				}
			}
		}
		break;
		
		default:
		{
			exitFlag = true;
		}
			break;
		}

		/*No empty space available to breed*/
		if ((upFlag && downFlag) && (rightFlag && leftFlag)) 
		{ 
			exitFlag = true; 
		}

	} while (exitFlag == false);
}


/*********************************************************************  
 * ** Function: doodlebug
 * ** Description: Class constructor 
 * ** Parameters: None 
 * ** Pre-Conditions: None 
 * ** Post-Conditions:  None
 * ** Return:  Void
 * *********************************************************************/


doodlebug::doodlebug()
{
	indicator = 'X';
	eatCounter = 0;
	movedAleady = false;
}



