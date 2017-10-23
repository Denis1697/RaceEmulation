#include "Includes.h"

EasyField::EasyField()
{
	raceField_ = new int*[FIELD_WIDTH];

	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		raceField_[i] = new int[FIELD_HEIGHT];

		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			if (i == 0 || i == FIELD_HEIGHT - 1)
				raceField_[i][j] = BORDER;

			raceField_[i][j] = EMPTY; 
		}
	}

	bufferRaceField_ = new int*[FIELD_WIDTH];

	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		bufferRaceField_[i] = new int[FIELD_HEIGHT];

		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			if (i == 0 || i == FIELD_HEIGHT - 1)
				bufferRaceField_[i][j] = BORDER;

			bufferRaceField_[i][j] = EMPTY;
		}
	}
}

int
EasyField::getHeight() const
{
	return FIELD_HEIGHT;
}

int
EasyField::getWidth() const
{
	return FIELD_WIDTH;
}

void 
EasyField::generateObstacle()
{
	int obstacleChoice = rand() % OBSTACLES_NO + 1;
	int obstacleLength, x;

	switch (obstacleChoice)
	{
	case STONE:
		obstacleLength = 1;
		break;
	case LOG:
		obstacleLength = 3;
		break;
	case TREE:
		obstacleLength = 5;
		break;
	}
	
	if (obstacleChoice == TREE)
	{
		int choice = rand() % 2;

		switch (choice)
		{
		case 0:
			x = 0;
			break;
		case 1:
			x = 3;
		}
	} 
	else
		x = rand() % (FIELD_WIDTH - obstacleLength);

	for (int i = x; i < x + obstacleLength; i++)
	{
		bufferRaceField_[i][0] = OBSTACLE;
	}
}

void 
EasyField::placePlayerCar()
{

}