/******************************************************************************
** Program name: Doodlebug.cpp
** Authors: (Group 8) Thomas Armstrong, Jason Moule, Chetan Prasad,Timothy Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/8/19
** Description: Class representing simulated doodlebugs (Child of Critter)
******************************************************************************/

#include <cstdlib>
#include <iostream>	// FOR DE'BUG'GING (Get it?)

#include "Doodlebug.h"
#include "randNum.hpp"

Doodlebug::Doodlebug(int row, int col, int rowSize, int colSize) : Critter(row, col, rowSize, colSize)
{
	fed = 3;	// Days left before starving
}

Doodlebug::~Doodlebug()
{
}

void Doodlebug::Move(Critter*** &board)
{
	//stores row and col coordinates of valid spaces in the 4 different possible directions
	int** validSpaces = new int*[4];
	//stores row and col coordinates of ant objects in the 4 different possible directions
	int** ants = new int*[4];
	int numSpaces = 0; //number of adjacent spaces that are empty
	int numAnts = 0; //stores the number of ants in adjacent spaces
	int randNum;
	int nextRow;
	int nextCol;

	//looks into the spaces above, to the right, below and to the left of the doodlebug
	//and assesses whether there are available spaces or ants.
	//check upwards direction first
	if (validSpace(row - 1, col))
	{
		if (board[row - 1][col] == nullptr)
		{
			validSpaces[numSpaces] = new int[2];
			validSpaces[numSpaces][0] = row - 1;
			validSpaces[numSpaces][1] = col;
			numSpaces++;
			
		}
		else if (board[row - 1][col]->GetType() == Critter::Type::Ant)
		{
			ants[numAnts] = new int[2];
			ants[numAnts][0] = row - 1;
			ants[numAnts][1] = col;
			numAnts++;
		}
	}
	//check in the right direction second
	if (validSpace(row, col+1))
	{
		if (board[row][col+1] == nullptr)
		{
			validSpaces[numSpaces] = new int[2];
			validSpaces[numSpaces][0] = row;
			validSpaces[numSpaces][1] = col + 1;
			numSpaces++;

		}
		else if (board[row][col + 1]->GetType() == Critter::Type::Ant)
		{
			ants[numAnts] = new int[2];
			ants[numAnts][0] = row;
			ants[numAnts][1] = col + 1;
			numAnts++;
		}
	}//end right direction

	//check in the downward direction
	if (validSpace(row + 1, col))
	{
		if (board[row + 1][col] == nullptr)
		{
			validSpaces[numSpaces] = new int[2];
			validSpaces[numSpaces][0] = row + 1;
			validSpaces[numSpaces][1] = col;
			numSpaces++;

		}
		else if (board[row + 1][col]->GetType() == Critter::Type::Ant)
		{
			ants[numAnts] = new int[2];
			ants[numAnts][0] = row + 1;
			ants[numAnts][1] = col;
			numAnts++;
		}
	}//end check down direction

	//check in the left direction
	if (validSpace(row, col - 1))
	{
		if (board[row][col - 1] == nullptr)
		{
			validSpaces[numSpaces] = new int[2];
			validSpaces[numSpaces][0] = row;
			validSpaces[numSpaces][1] = col - 1;
			numSpaces++;

		}
		else if (board[row][col - 1]->GetType() == Critter::Type::Ant)
		{
			ants[numAnts] = new int[2];
			ants[numAnts][0] = row;
			ants[numAnts][1] = col - 1;
			numAnts++;
		}
	}//end left direction

	//if there are ants to in adjacent spaces to be eaten
	if (numAnts)
	{
		//srand(time(NULL));
		randNum = rand() % numAnts; //get a random neighboring ant
		nextRow = ants[randNum][0]; //get the ant's row coordinate
		nextCol = ants[randNum][1]; //get the ant's col coordinate
		delete board[nextRow][nextCol]; //'eat' the ant
		board[row][col] = nullptr;// leave current space empty
		row = nextRow; //update row
		col = nextCol; //update col
		board[row][col] = this; //move to space ant occuppied.
		std::cout << "Doodlebug eats ant at " << row << " : " << col << std::endl; // DEBUG
		fed = 3; //update fed status of doodlebug 
	}
	//if there aren't any ants but there are empty adjacent spaces to move into
	else if(numSpaces)
	{
		//srand(time(NULL));
		randNum = rand() % numSpaces; //randomly get an adjacent empty space
		nextRow = validSpaces[randNum][0]; //get row coordinate of empty space
		nextCol = validSpaces[randNum][1]; //get col coordinate of empty space
		board[row][col] = nullptr; //'leave' current space
		row = nextRow; //update bug's row coord
		col = nextCol; //update bug's col coord
		board[row][col] = this; //'move' into the previously empty space. 
		fed--; //update fed status of doodlebug.
	}
	//the doodlebug remains in it's current position for the turn and fed is updated.
	else
	{
		fed--;
	}

	lastBred++;
	moved = true;

	//deallocate array data:
	for (int i = 0; i < numSpaces; i++)
	{
		delete validSpaces[i];
	}
	delete[] validSpaces;

	for (int j = 0; j < numAnts; j++)
	{
		delete ants[j];
	}
	delete[] ants;

}//end move

	// Doodlebugs can breed if they haven't bred in 8 turns and have an empty spot next to them
bool Doodlebug::Breed(Critter*** &board)
{
    bool breed = false;

    if ( lastBred >= 8 && hasEmpty(row, col, board) ) {
        
		while (breed == false) {

			// Get random number for moving up, down, left, or right
			// UP = 0, DOWN, = 1, LEFT = 2, RIGHT = 3
			int randDir = getRandInt(0, 3);

			// Check if a random spot is empty
			if (randDir == 0) {	// UP
				if (row - 1 >= 0) {
					if (board[row - 1][col] == nullptr) {
						board[row - 1][col] = new Doodlebug(row - 1, col, rowSize, colSize);
						breed = true;
						std::cout << "New Doodlebug born at " << row - 1 << " : " << col << std::endl;
					}
				}
			}
			else if (randDir == 1) {	// DOWN
				if (row + 1 <= rowSize - 1) {
					if (board[row + 1][col] == nullptr) {
						board[row + 1][col] = new Doodlebug(row + 1, col, rowSize, colSize);
						breed = true;
						std::cout << "New Doodlebug born at " << row + 1 << " : " << col << std::endl;
					}
				}
			}
			else if (randDir == 2) {	// LEFT
				if (col - 1 >= 0) {
					if (board[row][col - 1] == nullptr) {
						board[row][col - 1] = new Doodlebug(row, col - 1, rowSize, colSize);
						breed = true;
						std::cout << "New Doodlebug born at " << row << " : " << col - 1 << std::endl;
					}
				}
			}
			else if (randDir == 3) {		// RIGHT
				if (col + 1 <= colSize - 1) {
					if (board[row][col + 1] == nullptr) {
						board[row][col + 1] = new Doodlebug(row, col + 1, rowSize, colSize);
						breed = true;
						std::cout << "New Doodlebug born at " << row << " : " << col + 1 << std::endl;
					}
				}
			}
		}	// Keep trying until an empty spot is found
    }	// If no adjacent squares empty, no breeding happens, will check again next turn

	if (breed)
	{
		lastBred = 0;
	}

    return breed;
}

bool Doodlebug::Starve()
{
	bool starved = false;
	if (fed < 0)
	{
		starved = true; //change doodlebug's current space to empty
	}
	return starved;
}

Critter::Type Doodlebug::GetType()
{
	return Critter::Type::Doodlebug;
}

bool Doodlebug::validSpace(int nextRow, int nextCol)
{
	bool valid = true;
	if ((nextRow < 0 || nextRow >= rowSize) || (nextCol < 0 || nextCol >= colSize))
	{
		valid = false;
	}
	return valid;
}//end validSpace

// Checks the four adjacent squares and returns true if one is empty
bool Doodlebug::hasEmpty(int row, int col, Critter*** &board)
{
	return ((validSpace(row - 1, col) && board[row - 1][col] == nullptr)
		|| (validSpace(row + 1, col) && board[row + 1][col] == nullptr)
		|| (validSpace(row, col - 1) && board[row][col - 1] == nullptr)
		|| (validSpace(row, col + 1) && board[row][col + 1] == nullptr));
}
