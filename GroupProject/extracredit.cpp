/**********************************************************************************************
* Document:			Extra Credit File for Group Project
* Last Modified by:	Tommy Armstrong
* Group Members:	Tommy Armstrong, Jason Moule, Chetam Prasad, Timothy Winters, Yidong Lin
* Description:		File that contains implementation of extra credit for the group
					project program.
***********************************************************************************************/

#include "extracredit.hpp"
#include "Critter.h"
#include "Ant.h"
#include "Doodlebug.h"
#include <cstdlib>

/***********************************************************************************************
*						randomPlacing()
* This function randomly  places the ants and doodlebugs on the board grid. It takes in as args the 
* board by reference, the rows and columns of the board's dimension, the total number of ants to
* be placed and the total number of doodlebugs to be placed.
************************************************************************************************/
void randomPlacing(Critter*** &board, int rows, int cols, int ants, int dbugs)
{
	int totalSpaces = rows * cols;
	int* spaces = new int[totalSpaces];
	int totalBugs = ants + dbugs;
	int randIndex;
	int randSpace;
	int randRow;
	int randCol;
	int nullSpace;
	int nullRow;
	int nullCol;
	//set up an array containing values [0, rows*cols] that represents available spaces
	//on the board for a bug to be placed in.
	for (int i = 0; i < totalSpaces; i++)
	{
		spaces[i] = i;
	}

	for (int j = 0; j < totalBugs; j++)
	{
		randIndex = rand() % totalSpaces; //the random index that will give the random space in spaces[]
		randSpace = spaces[randIndex]; //the random space's value in row*col format.
		randRow = randSpace / cols; //calc the row of the random space
		randCol = randSpace % cols; //calc the column of the random space
		//populate board with ants first
		if (ants)
		{
			board[randRow][randCol] = new Ant(randRow, randCol, rows, cols);
			ants--;
		}
		//then populate board with doodlebugs
		else if (dbugs)
		{
			board[randRow][randCol] = new Doodlebug(randRow, randCol, rows, cols);
			dbugs--;
		}
		//remove the random space just used from the array of viable spaces
		for (int i = randIndex; i < totalSpaces - 1; i++)
		{
			spaces[i] = spaces[i + 1];
		}

		totalSpaces--;
	}//end for

	//not sure if following is redundant:
	//set remaining spaces not occupied by bugs to null pointers
	for (int i = 0; i < totalSpaces; i++)
	{
		nullSpace = spaces[i];
		nullRow = nullSpace / cols;
		nullCol = nullSpace % cols;
		board[nullRow][nullCol] = nullptr;
	}

	delete[] spaces;

}//end randomPlacing

	//i was going to make spaces an array of type int** containing every space as
	//an x and y coordinate (similar to doodlebug::move() ) but thought it might be simpler if I just used arithmetic
	//to determine the space x and y coordinate. let me know what's preferrable.
	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			spaces[i*j + j] = new int[2];
			spaces[i*j + j][0] = i; //x coordinate of space
			spaces[i*j + j][1] = j; //y coordinate of space
		}
	*/
