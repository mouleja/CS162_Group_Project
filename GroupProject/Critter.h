/******************************************************************************
** Program name: Critter.h
** Author: Group8- Thomas Armstrong, Yidong Lin, Jason Moule, Chetan Prasad, Tim Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/8/19
** Description: Parent Abstract class representing simulated insects
******************************************************************************/

#ifndef CRITTER_H
#define CRITTER_H

class Critter
{
public:
	enum Type { Ant, Doodlebug };

protected:
	bool moved;		// Has critter moved this turn
	int row;		// Current row position on board
	int col;		// Current column position on board
	int rowSize;	// Number of rows on board
	int colSize;	// Number of coloumns on board
	int lastBred;	// Steps since critter last gave birth

public:
	Critter(int row, int col, int rowSize, int colSize)
	{ 
		this->row = row;
		this->col = col;
		this->rowSize = rowSize;
		this->colSize = colSize;
		this->moved = false;
		this->lastBred = 0;
	}

	// Setters and Getters
	void setMoved(bool moved); 
	bool hasMoved();

	// Virtual methods
	virtual bool Starve();

	virtual Type GetType() = 0;
	virtual void Move(Critter*** &board) = 0;
	virtual bool Breed(Critter*** &board) = 0;

	virtual ~Critter() {}
};

#endif