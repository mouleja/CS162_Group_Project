/******************************************************************************
** Program name: Simulation.hpp
** Authors: (Group 8) Thomas Armstrong, Jason Moule, Chetan Prasad,Timothy Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/2/19
** Description: Parent Abstract class representing simulated insects
******************************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "Ant.h"
#include "Doodlebug.h"

// Globals
#define DEFAULT_ROWS 20
#define DEFAULT_COLS 20
#define DEFAULT_ANTS 100
#define DEFAULT_BUGS 5

class Simulation
{
private:
	int rows;			// Number of rows in grid
	int cols;			// Number of columns in grid
	int startingAnts;	// Initial ants on board
	int startingBugs;	// Initial bugs on board

	Critter*** board;	// The place where the critters live

	// All critters of (type) execute their Move method
	// Returns number of (type)
	int makeMoves(Critter::Type type);

	// All critters of (type) execute their Breed method
	// Returns number of new (type)
	int breed(Critter::Type type);
	
	// All Doodlebugs starve if they haven't eaten
	// Return number of doodlebugs starved
	int starve();

	void resetMoved();

	void printBoard();

	void randomPlacing();

public:
	Simulation();
	Simulation(int rows, int cols, int startingAnts, int startingBugs);
	~Simulation();

	void Run();
};

#endif