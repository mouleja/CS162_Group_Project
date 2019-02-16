/******************************************************************************
** Program name: Game.hpp
** Author: Group8- Thomas Armstrong, Yidong Lin, Jason Moule, Chetan Prasad, Tim Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/16/19
** Description: 2D Predator-Prey simulation program
**	Ants(prey) and Doodlebugs(predators) move, breed and starve in a 2D grid
** INCLUDES MAIN PROGRAM (at bottom)
******************************************************************************/

#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Simulation.h"
#include "iohelper.h"

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
	int ants = startingAnts;
	int bugs = startingBugs;

	// initial an empty board
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			board[r][c] = nullptr;
		}
	}

	// random place ants
	while (ants != 0)
	{
		int r = getRandInt(0, rows - 1);
		int c = getRandInt(0, cols - 1);

		if (board[r][c] == nullptr)
		{
			board[r][c] = new Ant(r, c, rows, cols);
		}
		else
		{
			continue;
		}
		ants--;
	}

	// random place bugs
	while (bugs != 0)
	{
		int r = getRandInt(0, rows - 1);
		int c = getRandInt(0, cols - 1);

		if (board[r][c] == nullptr)
		{
			board[r][c] = new Doodlebug(r, c, rows, cols);
		}
		else
		{
			continue;
		}
		bugs--;
	}

	bool endSimulation = false;
	int currentTurn = 0, turns = 0;

	printBoard();		// print board to console
	std::cout << "Starting Board: Ants - " << startingAnts << ", Doodlebugs- " << startingBugs << std::endl;

	while (!endSimulation)	// loop until user quits
	{
		turns += getInt("\nHow many turns do you want to simulate?:");

		while (currentTurn < turns)		// go thru board and do actions
		{
			printString();

			bugs = makeMoves(Critter::Type::Doodlebug);	// doodlebugs move first
			ants = makeMoves(Critter::Type::Ant);
			resetMoved();								// reset moved bool for next turn

			bugs += breed(Critter::Type::Doodlebug);	// check for breeding & add critters if so
			ants += breed(Critter::Type::Ant);

			bugs -= starve();							// check for starvation in bugs

			printBoard();								// print board to console

			currentTurn++;
			std::cout<< "Turn: " << currentTurn << ", Ants - " 
				<< ants << ", Doodlebugs - " << bugs << std::endl;
		}

		char doMoreTurns[] = { 'y', 'n' };	
		char more = getChar("\nSimulate more turns? (y/n):", doMoreTurns, 2);

		if (more == 'n')								// Do more loops?
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
				printString(" ", false);
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
				printString("!", false);	// Debugging catcher
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

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));	// Seed Rand()

	printString("\nWelcome to the Predator-Prey Simulation Program");
	printString("by Thomas Armstrong, Yidong Lin, Jason Moule, Chetan Prasad, Tim Withers!\n");

	printString("\nWe did the Extra Credit!\n");

	int rows = 20, cols = 20, antNumber = 100, bugNumber = 5;
	printString("The default simulation runs with 100 ants and 5 doodlebugs on a 20 x 20 board.");

	char yesNo[] = { 'y', 'n' };
	char customInput = getChar("Would you like to run a custom simulation instead?", yesNo, 2);

	if (customInput == 'y')
	{
		rows = getInt(2, 100, "\nPlease input the number of rows [2, 100] on the board:");
		cols = getInt(2, 100, "Please input the number of columns [2, 100] on the board:");
		int maxAnts = (rows * cols) - 1;
		antNumber = getInt(1, maxAnts, "Please input the number of initial ants:");
		int maxBugs = (rows * cols) - antNumber;
		bugNumber = getInt(1, maxBugs, "Please input the number of intital doodlebugs:");
	}

	Simulation* simulation = new Simulation(rows, cols, antNumber, bugNumber);
	simulation->Run();
	delete simulation;

	printString("\nThank you and good day!\n");
}
