#pragma once
#include "Critter.h"

class Ant :
	public Critter
{
public:
	Ant();
	~Ant();

	void Move();
	void Breed();
	Type GetType();
};

