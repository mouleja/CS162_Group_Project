#ifndef ANT_H
#define ANT_H

#include "Critter.h"
#include "randNum.hpp"

enum direction {UP, DOWN, LEFT, RIGHT};

class Ant :
	public Critter
{
private:
	int stepNum;

public:
	Ant(int row, int col, int rowSize, int colSize);
	~Ant();

	// Getters

	// Setters

	// Functions
	void Move(Critter*** &board);
	bool Breed(Critter*** &board);
	Type GetType();
};

#endif