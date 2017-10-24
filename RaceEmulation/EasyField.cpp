#include "Includes.h"

EasyField::EasyField()
{
	for (int j = 0; j < FIELD_HEIGHT; j++)
	{
		for (int i = 0; i < FIELD_WIDTH; i++)
		{
			BlockType currentBorder = (j % 2 == 0 ? BORDER_ONE : BORDER_TWO);

			if (i == 0 || i == FIELD_WIDTH - 1)
				raceField_[j][i] = currentBorder;
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
	int obstacleChoice = rand() % OBSTACLES_NO;
	int x, obstacleLength = 0;

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
	
	if (obstacleChoice == TREE && FIELD_WIDTH < 10)
	{
		int choice = rand() % 2;

		switch (choice)
		{
		case 0:
			x = 1;
			break;
		case 1:
			x = 4;
		}
	} 
	else
		x = rand() % (FIELD_WIDTH - obstacleLength);

	for (int i = x; i < x + obstacleLength; i++)
		buffer_[i] = OBSTACLE;
}

void 
EasyField::draw() const
{
	cout << endl;
	for (int j = 0; j < FIELD_HEIGHT; j++)
	{
		cout << " ";
		for (int i = 0; i < FIELD_WIDTH; i++)
		{
			char c = static_cast<char>(raceField_[j][i]);
			cout << c;
		}
		cout << endl;
	}
}

int 
EasyField::getBlockType(const int& x, const int& y) const
{
	if (x < 0 || x > FIELD_WIDTH - 1 || y < 0 || y > FIELD_HEIGHT - 1)
		return -1;

	return raceField_[y][x];
}

void 
EasyField::setBlockType(const int& x, const int& y, const int& blockType)
{
	if (x < 0 || x > FIELD_WIDTH - 1 || y < 0 || y > FIELD_HEIGHT - 1 || blockType < 0 || blockType > 255)
		return;

	raceField_[y][x] = blockType;
}

int 
EasyField::getBufferBlockType(const int & x) const
{
	if (x < 0 || x > FIELD_WIDTH - 1)
		return -1;

	return buffer_[x];
}

void
EasyField::clearBuffer()
{
	for (int i = 1; i < FIELD_WIDTH - 1; i++)
		buffer_[i] = EMPTY;
}

void EasyField::placeObstacle()
{
	generateObstacle();

	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		int bufferBlockType = getBufferBlockType(i);

		if (bufferBlockType == RaceField::OBSTACLE)
			setBlockType(i, 0, bufferBlockType);
	}

	clearBuffer();
}
