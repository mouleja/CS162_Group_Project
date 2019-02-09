/******************************************************************************
** Program name: Doodlebug.cpp
** Authors: (Group 8) Thomas Armstrong, Jason Moule, Chetan Prasad,Timothy Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/8/19
** Description: Class representing simulated ant (Child of Critter)
******************************************************************************/

#include "Ant.h"

#include <iostream>
using std::cout;
using std::endl;

Ant::Ant(int row, int col, int rowSize, int colSize) : Critter(row, col, rowSize, colSize)
{
}

Ant::~Ant()
{
}

void Ant::Move(Critter*** &board)
{
	// Set old position to nullptr (blank space)
	board[row][col] = nullptr;	

	// Get random number for moving up, down, left, or right
	// UP = 0, DOWN, = 1, LEFT = 2, RIGHT = 3
	int randDir = getRandInt(0, 3);

	/*
	// Printing out for debugging. TODO: Remove this or comment out.
	switch (randDir) {
		case UP:
			cout << "Move UP" << endl;
			break;
		case DOWN:
			cout << "Move DOWN" << endl;
			break;
		case LEFT:
			cout << "Move LEFT" << endl;
			break;
		case RIGHT:
			cout << "Move RIGHT" << endl;
			break;
		default:
			break;
	}*/

	// randDir = 3; TODO: For debug, delete this

	// Try and move ant with particular random direction
	if (randDir == UP) {
		if (row - 1 >= 0) {
			if (board[row - 1][col] == nullptr) {
				row -= 1;
			}
		}
	}
	else if (randDir == DOWN) {
		if (row + 1 <= rowSize - 1) {
			if (board[row + 1][col] == nullptr) {
				row += 1;
			}
		}

	}
	else if (randDir == LEFT) {
		if (col - 1 >= 0) {
			if (board[row][col - 1] == nullptr) {
				col -= 1;
			}
		}
	}
	else {
		if (col + 1 <= colSize - 1) {
			if (board[row][col + 1] == nullptr) {
				col += 1;
			}
		}
	}

	// Update new calculated position with ant
	board[row][col] = this;

	//cout << "New position: [" << row << "][" << col << "]" << endl; TODO: For debug, delete this

	// Finish move
	moved = true;			// So they can't move again if they moved right or down
	this->lastBred += 1;	// Age one step
}

// Ants can breed if they haven't bred in 3 turns and have an empty spot next to them
bool Ant::Breed(Critter*** &board)
{
	bool breed = false;

	if (lastBred >= 3 && hasEmpty(row, col, board)) {

		while (breed == false) {

			// Get random number for moving up, down, left, or right
			// UP = 0, DOWN, = 1, LEFT = 2, RIGHT = 3
			int randDir = getRandInt(0, 3);

			// Check if a random spot is empty
			if (randDir == 0) {	// UP
				if (row - 1 >= 0) {
					if (board[row - 1][col] == nullptr) {
						board[row - 1][col] = new Ant(row - 1, col, rowSize, colSize);
						breed = true;
						std::cout << "New Ant born at " << row - 1 << " : " << col << std::endl;
					}
				}
			}
			else if (randDir == 1) {	// DOWN
				if (row + 1 <= rowSize - 1) {
					if (board[row + 1][col] == nullptr) {
						board[row + 1][col] = new Ant(row + 1, col, rowSize, colSize);
						breed = true;
						std::cout << "New Ant born at " << row + 1 << " : " << col << std::endl;
					}
				}
			}
			else if (randDir == 2) {	// LEFT
				if (col - 1 >= 0) {
					if (board[row][col - 1] == nullptr) {
						board[row][col - 1] = new Ant(row, col - 1, rowSize, colSize);
						breed = true;
						std::cout << "New Ant born at " << row << " : " << col - 1 << std::endl;
					}
				}
			}
			else if (randDir == 3) {		// RIGHT
				if (col + 1 <= colSize - 1) {
					if (board[row][col + 1] == nullptr) {
						board[row][col + 1] = new Ant(row, col + 1, rowSize, colSize);
						breed = true;
						std::cout << "New Ant born at " << row << " : " << col + 1 << std::endl;
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

Critter::Type Ant::GetType()
{
	return Critter::Type::Ant;
}

// Checks the four adjacent squares and returns true if one is empty
bool Ant::hasEmpty(int row, int col, Critter*** &board)
{
	return ((validSpace(row - 1, col) && board[row - 1][col] == nullptr)
		|| (validSpace(row + 1, col) && board[row + 1][col] == nullptr)
		|| (validSpace(row, col - 1) && board[row][col - 1] == nullptr)
		|| (validSpace(row, col + 1) && board[row][col + 1] == nullptr));
}

bool Ant::validSpace(int nextRow, int nextCol)
{
	bool valid = true;
	if ((nextRow < 0 || nextRow >= rowSize) || (nextCol < 0 || nextCol >= colSize))
	{
		valid = false;
	}
	return valid;
}//end validSpace