/******************************************************************************
** Program name: Game.hpp
** Author: Group8 :
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/2/19
** Description: 2D Predator-Prey simulation program
**	Ants(prey) and Doodlebugs(predators) move, breed and starve in a 2D grid
******************************************************************************/

#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Simulation.h"
#include "iohelper.h"

// Default constructor
Simulation::Simulation() : 
	rows(DEFAULT_ROWS),		
	cols (DEFAULT_COLS), 
	startingAnts(DEFAULT_ANTS),
	startingBugs(DEFAULT_BUGS)
{
	board = new Critter**[rows];
	for (int i = 0; i < rows; i++)
	{
		board[i] = new Critter*[cols];
	}
}

// Custom simulation constructor
Simulation::Simulation(int rows, int cols, int startingAnts, int startingBugs) :
	rows(rows),
	cols(cols),
	startingAnts(startingAnts),
	startingBugs(startingBugs)
{
	board = new Critter**[rows];
	for (int i = 0; i < rows; i++)
	{
		board[i] = new Critter*[cols];
	}
}

Simulation::~Simulation()
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			delete board[r][c];
		}
		delete[] board[r];
	}
	delete[] board;
}

// Main program loop
void Simulation::Run()
{
	printString("\nWelcome to the Predator-Prey Simulation Program by <NAMES>!\n");

	int ants = startingAnts;
	int bugs = startingBugs;
	randomPlacing();
	
	/*
	// Populate board with predefined board for now (REPLACE WITH RANDOM)
	vector< vector<int> > sampleBoard {
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

	

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (sampleBoard[r][c] == 1)
			{
				board[r][c] = new Ant(r, c, rows, cols);
				ants++;
			}
			else if (sampleBoard[r][c] == 2)
			{
				board[r][c] = new Doodlebug(r, c, rows, cols);
				bugs++;
			}
			else
			{
				board[r][c] = nullptr;
			}
		}
	}
	*/

	bool endSimulation = false;
	int currentTurn = 0, turns = 0;

		printBoard();		// print board to console
		std::cout << "Starting Board: Ants - " << ants << ", Doodlebugs- " << bugs << std::endl;

	while (!endSimulation)
	{
		turns += getInt("\nHow many turns do you want to simulate?:");

		while (currentTurn < turns)
		{
			printString();

			// go thru board and do actions
			// doodlebugs moved first
			bugs = makeMoves(Critter::Type::Doodlebug);
			ants = makeMoves(Critter::Type::Ant);
			resetMoved();		// reset moved bool for next turn

			bugs += breed(Critter::Type::Doodlebug);
			ants += breed(Critter::Type::Ant);

			bugs -= starve();

			printBoard();		// print board to console
			currentTurn++;
			std::cout<< "Turn: " << currentTurn << ", Ants - " 
				<< ants << ", Doodlebugs - " << bugs << std::endl;
		}

		char doMoreTurns[] = { 'y', 'n' };
		char more = getChar("\nSimulate more turns? (y/n):", doMoreTurns, 2);
		if (more == 'n')
		{
			endSimulation = true;
		}
	}
	printString("\nThanks for running our simulation!");
}

int Simulation::makeMoves(Critter::Type type)
{
	int total = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			// Check spot is critter, the right type and hasn't moved already
			if (board[r][c] != nullptr &&
				board[r][c]->GetType() == type &&
				board[r][c]->hasMoved() == false)
			{
				board[r][c]->Move(board);	// Move should update moved bool
				++total;
			}
		}
	}
	return total;
}

int Simulation::breed(Critter::Type type)
{
	int total = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (board[r][c] && board[r][c]->GetType() == type)
			{
				if (board[r][c]->Breed(board))
				{
					++total;
				}
			}
		}
	}
	return total;
}

int Simulation::starve()
{
	int total = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (board[r][c] && board[r][c]->GetType() == Critter::Type::Doodlebug)
			{
				if (board[r][c]->Starve())
				{
					delete board[r][c];
					board[r][c] = nullptr;
					printString("Doodlebug starves at " + std::to_string(r) + " : " +
						std::to_string(c));
					++total;
				}//end if starve
			}
		}
	}
	return total;
}

void Simulation::resetMoved()
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (board[r][c])
			{
				board[r][c]->setMoved(false);
			}
		}
	}
}

void Simulation::printBoard()
{
	printString();
	for (int c = 0; c < cols + 2; c++)
	{
		printString("=", false);
	}
	printString();

	for (int r = 0; r < rows; r++)
	{
		printString("|", false);

		for (int c = 0; c < cols; c++)
		{
			if (!board[r][c])
			{
				printString("-", false);
			}
			else if (board[r][c]->GetType() == Critter::Type::Ant)
			{
				printString("O", false);
			}
			else if (board[r][c]->GetType() == Critter::Type::Doodlebug)
			{
				printString("X", false);
			}
			else
			{
				printString("!", false);
			}
		}

		printString("|");
	}

	for (int c = 0; c < cols + 2; c++)
	{
		printString("=", false);
	}
	printString();
}

/***********************************************************************************************
*						randomPlacing()
* This function randomly  places the ants and doodlebugs on the board grid. It takes in as args the
* board by reference, the rows and columns of the board's dimension, the total number of ants to
* be placed and the total number of doodlebugs to be placed.
************************************************************************************************/
void Simulation::randomPlacing()
{
	int totalSpaces = rows * cols;
	int* spaces = new int[totalSpaces];
	int ants = startingAnts;
	int dbugs = startingBugs;
	int totalBugs = ants + dbugs;
	int randIndex;
	int randSpace;
	int randRow;
	int randCol;
	int nullSpace;
	int nullRow;
	int nullCol;
	//set up an array containing values [0, rows*cols] that represents available spaces
	//on the board for a bug to be placed in.
	for (int i = 0; i < totalSpaces; i++)
	{
		spaces[i] = i;
	}

	for (int j = 0; j < totalBugs; j++)
	{
		randIndex = rand() % totalSpaces; //the random index that will give the random space in spaces[]
		randSpace = spaces[randIndex]; //the random space's value in row*col format.
		randRow = randSpace / cols; //calc the row of the random space
		randCol = randSpace % cols; //calc the column of the random space
		//populate board with ants first
		if (ants)
		{
			board[randRow][randCol] = new Ant(randRow, randCol, rows, cols);
			ants--;
		}
		//then populate board with doodlebugs
		else if (dbugs)
		{
			board[randRow][randCol] = new Doodlebug(randRow, randCol, rows, cols);
			dbugs--;
		}
		//remove the random space just used from the array of viable spaces
		for (int i = randIndex; i < totalSpaces - 1; i++)
		{
			spaces[i] = spaces[i + 1];
		}

		totalSpaces--; //decrement number of viable spaces

	}//end for

	//not sure if following is redundant:
	//set remaining spaces not occupied by bugs to null pointers
	for (int i = 0; i < totalSpaces; i++)
	{
		nullSpace = spaces[i];
		nullRow = nullSpace / cols;
		nullCol = nullSpace % cols;
		board[nullRow][nullCol] = nullptr;
	}

	delete[] spaces;

}//end randomPlacing

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));	// Seed Rand()

	Simulation* simulation = new Simulation();
	simulation->Run();
	delete simulation;
}