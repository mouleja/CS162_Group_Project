#ifndef CRITTER_H
#define CRITTER_H

class Critter
{
public:
	enum Type { Ant, Doodlebug };

protected:
	bool moved;
	bool canBreed;
	int row;
	int col;
	int rowSize;
	int colSize;
	int age;

public:
	Critter(int row, int col, int rowSize, int colSize)
	{ 
		this->row = row;
		this->col = col;
		this->rowSize = rowSize;
		this->colSize = colSize;
		this->moved = false;
		this->age = 0;
		this->canBreed = false;
	}
	// Getters
	int getAge() { return this->age; }
	bool getCanBreed() { return this->canBreed; }

	// Setters
	void setAge(int age) { this->age = age; }
	void setCanBreed(bool canBreed) { this->canBreed = canBreed; }

	// Functions
	void setMoved(bool moved) { this->moved = moved; }
	bool hasMoved() { return moved; }
	virtual Type GetType() = 0;
	virtual void Move(Critter*** &board) = 0;
	virtual bool Breed(Critter*** &board) = 0;
	virtual bool Starve() { return false; }
	virtual ~Critter() {}
};

#endif