#include "Includes.h"

EasyField::EasyField()
{
	for (int j = 0; j < FIELD_HEIGHT; j++)
	{
		for (int i = 0; i < FIELD_WIDTH; i++)
		{
			if (i == 0 || i == FIELD_WIDTH - 1)
				raceField_[j][i] = BORDER;
			else
				raceField_[j][i] = EMPTY;
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
		bufferField_[0][i] = OBSTACLE;
}

void 
EasyField::placePlayerCar()
{
	raceField_[9][2] = CAR_TIRE;
	raceField_[11][2] = CAR_TIRE;
	raceField_[8][3] = CAR_TOP;
	raceField_[10][3] = CAR_TORSO;
	raceField_[9][4] = CAR_TIRE;
	raceField_[11][4] = CAR_TIRE;
}

void 
EasyField::drawField() const
{
	for (int j = 0; j < FIELD_HEIGHT; j++)
	{
		for (int i = 0; i < FIELD_WIDTH; i++)
		{
			char c = static_cast<char>(raceField_[j][i]);
			//cout << raceField_[j][i] << " ";
			cout << c;			
		}
		cout << endl;
	}
}