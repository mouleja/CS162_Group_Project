/******************************************************************************
** Program name: Critter.cpp
** Authors: (Group 8) Thomas Armstrong, Jason Moule, Chetan Prasad,Timothy Withers
** Assignment: Group Project  -  CS162-400-W19
** Date: 2/8/19
** Description: Parent Abstract class representing simulated insects
******************************************************************************/

#include "Critter.h"

void Critter::setMoved(bool moved)
{
	this->moved = moved;
}

bool Critter::hasMoved()
{
	return moved;
}

bool Critter::Starve()
{
	return false;
}
