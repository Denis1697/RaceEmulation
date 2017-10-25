#include "Includes.h"

ComplicatedField::ComplicatedField()
{
	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			if (i == 0 || i == FIELD_HEIGHT - 1)
				raceField_[i][j] = 1; //1 for the border block

			raceField_[i][j] = 0; //0 for the empty block
		}
	}
}

int 
ComplicatedField::getHeight() const
{
	return FIELD_HEIGHT;
}

int 
ComplicatedField::getWidth() const
{
	return FIELD_WIDTH;
}

void 
ComplicatedField::generateObstacle()
{

}

void 
ComplicatedField::placePlayerCar()
{

}