/******************************************************************************
** Program name: Ant.h
** Author: Group8- Thomas Armstrong, Yidong Lin, Jason Moule, Chetan Prasad, Tim Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/8/19
** Description: Class representing simulated ant (Child of Critter)
******************************************************************************/

#ifndef ANT_H
#define ANT_H

#include "Critter.h"
#include "randNum.hpp"

enum direction {UP, DOWN, LEFT, RIGHT};

class Ant :
	public Critter
{
public:
	Ant(int row, int col, int rowSize, int colSize);
	~Ant();

	// Getters
	Type GetType();

	// Functions
	void Move(Critter*** &board);
	bool Breed(Critter*** &board);

	bool hasEmpty(int row, int col, Critter ***& board);
	bool validSpace(int nextRow, int nextCol);
};

#endif