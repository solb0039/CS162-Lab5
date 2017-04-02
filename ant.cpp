#include "ant.hpp"

/*Constructor*/

ant::ant() 
{
	indicator = 'O';
	movedAleady = false;
}


/********************************************************************************  
 * ** Function: Move  
 * ** Description:  This is the Ant class implementation of the virtual function
 * 		move(). It attempt to move the Ant object randomly to an adjacent
 * 		cell. If no cells are available, no action is taken. The function 
 * 		also checks on each iteration if the ant is to breed. 
 * ** Parameters:  critter*** grid, pointer to an array of critter pointers
 * 		int iR, the reference row of the current ant
 * 		int jC, the reference column of the current ant
 * ** Pre-Conditions: None
 * ** Post-Conditions:  The boolean exitFlag must be true to exit do-whiel loop.
 * 		This occurs after an ant moves of after checking all adjacent cells
 * ** Return:  Void
 * ******************************************************************************/


void ant::move(critter*** grid, int iR, int jC)
{
		/*Have an ant..now make it move*/
		/*Generate a random number*/
	bool exitFlag = false;
	bool uFlag = false;
	bool dFlag = false;
	bool rFlag = false;
	bool lFlag = false;

	do {
		int randMove = (getRandomInteger(4) + 1);

		switch (randMove)
		{
		
		case 1: /*Up*/
		{
			uFlag = true;
			/*If adjacent space unoccupied and on the grid, move the ant*/
			if (((iR - 1) >= 0) && (grid[iR - 1][jC] == NULL))
			{
				grid[iR - 1][jC] = (grid[iR][jC]);
				grid[iR - 1][jC]->setMovedAlready();

				/*Set pointer back to null to make old space a critter class again*/
				grid[iR][jC] = dynamic_cast<critter *>(grid[iR][jC]);
				grid[iR][jC] = NULL;
				exitFlag = true;

				/*Breed if lives is 3*/
				if (grid[iR - 1][jC]->getLives() == 3)
				{
					static_cast<ant *>(grid[iR - 1][jC])->breed(grid, (iR - 1), jC);
					grid[iR - 1][jC]->resetLives();
				}
			}
		}
		break;
		
		case 2: /*Down*/
		{
			dFlag = true;
			/*If adjacent space is unoccupied and on the grid, move the ant*/
			if (((iR + 1) < 20) && (grid[iR + 1][jC] == NULL))
			{
				grid[iR + 1][jC] = (grid[iR][jC]);
				grid[iR + 1][jC]->setMovedAlready();

				/*Set pointer back to null and make old space a critter class again*/
				grid[iR][jC] = static_cast<critter *>(grid[iR][jC]);
				grid[iR][jC] = NULL;
				exitFlag = true;
				
				/*Breed is lives is 3*/
				if (grid[iR + 1][jC]->getLives() == 3)
				{
					static_cast<ant *>(grid[iR + 1][jC])->breed(grid, (iR + 1), jC);
					grid[iR + 1][jC]->resetLives();
				}
			}
		}
		break;
		
		case 3: /*Right*/
		{
			rFlag = true;
			if (((jC + 1) < 20) && (grid[iR][jC + 1] == NULL))
			{
				grid[iR][jC + 1] = (grid[iR][jC]);
				grid[iR][jC + 1]->setMovedAlready();

				grid[iR][jC] = static_cast<critter *>(grid[iR][jC]);
				grid[iR][jC] = NULL;
				exitFlag = true;

				if (grid[iR][jC + 1]->getLives() == 3)
				{
					static_cast<ant *>(grid[iR][jC + 1])->breed(grid, iR, (jC + 1));
					grid[iR][jC + 1]->resetLives();
				}
			}

		}
		break;
		
		case 4: /*Left*/
		{
			lFlag = true;
			if (((jC - 1) >= 0) && (grid[iR][jC - 1] == NULL))
			{
				grid[iR][jC - 1] = (grid[iR][jC]);
				grid[iR][jC - 1]->setMovedAlready();

				grid[iR][jC] = static_cast<critter *>(grid[iR][jC]);
				grid[iR][jC] = NULL;
				exitFlag = true;

				if (grid[iR][jC - 1]->getLives() == 3)
				{
					static_cast<ant *>(grid[iR][jC - 1])->breed(grid, iR, (jC - 1));
					grid[iR][jC - 1]->resetLives();
				}
			}
		}
			break;
		default: 
			break;
		}
		
		/*No options available. Exit loop*/
		if ((uFlag && dFlag) && (rFlag && lFlag) ) { exitFlag = true; }
	
	} while (!exitFlag);
}


/***************************************************************************************  
 * ** Function: Breed 
 * ** Description: This function attempts to create a new ant in an 
 * 		adjacent cell to the reference ant.
 * ** Parameters:  critter*** inGrid, the pointer to the array of pointers of critters
 * ** Pre-Conditions:  None
 * ** Post-Conditions:  bool exitFlag must be true.  This happens after breeding, or after
 * 		checking all possible cells and not breeding.
 * ** Return:  void
 * ************************************************************************************/


void ant::breed(critter*** inGrid, int row, int col) 
{
	/*Exit flag to control loop.*/
	bool exitFlag = false;

	/*Use flags to only test each direction once*/
	bool upFlag = false;
	bool downFlag = false;
	bool rightFlag = false;
	bool leftFlag = false;

	do {
		/*Randomly generate direction*/
		int randMove = (getRandomInteger(4) + 1);
		switch (randMove) 
		{
			case 1: 
			{			
				upFlag = true;
				/*Try to place an ant above*/
				/*Check if in bounds*/
				if ( (row-1) >= 0 )
				{
					/*Check if space is open*/
					if ( inGrid[row-1][col] == NULL )
					{
						/*Success! Add the ant*/
						inGrid[row-1][col] = new ant();
						inGrid[row - 1][col]->setMovedAlready();
						exitFlag = true;
					}
				}	
			}
			break;
			
			case 2: 
			{
				downFlag = true;
				/*Try to place an ant above*/
				/*Check if in bounds*/
				if ((row + 1) < 20)
				{
					/*Check if space is open*/
					if (inGrid[row+1][col] == NULL)
					{
						/*Success! Add the ant*/
						inGrid[row+1][col] = new ant();
						inGrid[row + 1][col]->setMovedAlready();
						exitFlag = true;
					}
				}
			}
			break;
			
			case 3: 
			{
				rightFlag = true;
				/*Try to place an ant above*/
				/*Check if in bounds*/
				if ((col + 1) < 20)
				{
					/*Check if space is open*/
					if (inGrid[row][col + 1] == NULL)
					{
						/*Success! Add the ant*/
						inGrid[row][col + 1] = new ant();
						inGrid[row][col + 1]->setMovedAlready();
						exitFlag = true;
					}
				}
			}
			break;

			case 4: 
			{
				leftFlag = true;
				/*Try to place an ant above*/
				/*Check if in bounds*/
				if ( (col - 1) >= 0)
				{
					/*Check if space is open*/
					if (inGrid[row][col - 1] == NULL)
					{
						/*Success! Add the ant*/
						inGrid[row][col - 1] = new ant();
						inGrid[row][col - 1]->setMovedAlready();
						exitFlag = true;
					}
				}
			}
			break;
			
			default:	
			break;
		}

		/*No options available. Exit loop*/
		if((upFlag && downFlag) && (rightFlag && leftFlag)) { exitFlag = true; }

	} while ( !exitFlag );
}
