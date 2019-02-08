#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Critter.h"

class Doodlebug :
	public Critter
{
private:
	int fed;
public:
	Doodlebug(int row, int col, int rowSize, int colSize);
	~Doodlebug();
	void Move(Critter*** &board);
	bool Breed(Critter*** &board);
	bool Starve();
	Type GetType();
	bool validSpace(int nextRow, int nextCol);
};

#endif