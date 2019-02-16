/******************************************************************************
** Program name: Doodlebug.h
** Author: Group8- Thomas Armstrong, Yidong Lin, Jason Moule, Chetan Prasad, Tim Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/8/19
** Description: Class representing simulated doodlebugs (Child of Critter)
******************************************************************************/

#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Critter.h"

class Doodlebug :
	public Critter
{
private:
	int fed;	// Turns since last feeding
public:
	Doodlebug(int row, int col, int rowSize, int colSize);
	~Doodlebug();

	Type GetType();

	void Move(Critter*** &board);
	bool Breed(Critter*** &board);
	bool Starve();

	bool validSpace(int nextRow, int nextCol);
	bool hasEmpty(int row, int col, Critter ***& board);
};

#endif