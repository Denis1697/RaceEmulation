#include "Includes.h"

ComplicatedField::ComplicatedField()
{
	for (int j = 0; j < FIELD_HEIGHT; j++) {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			BlockType currentBorder = (j % 2 == 0 ? BORDER_ONE : BORDER_TWO);

			if (i == 0 || i == FIELD_WIDTH - 1)
				raceField_[j][i] = currentBorder;
			else
				raceField_[j][i] = EMPTY;
		}
	}
}

void 
ComplicatedField::generateObstacle()
{
	int partOfRoad	= rand() % 2 + 1;
	int seed		= rand() % 4 - 2;

	int headX;
	int headY; 

	switch (partOfRoad) {
		case 1 :
			headX = 4 + seed;
			headY = 3;

			buffer_[headY - 2][headX]		= OBSTACLE;
			buffer_[headY - 1][headX - 1]	= OBSTACLE;
			buffer_[headY - 3][headX - 1]	= OBSTACLE;
			buffer_[headY - 1][headX + 1]	= OBSTACLE;
			buffer_[headY - 3][headX + 1]	= OBSTACLE;
			break;
		case 2 :
			headX = FIELD_WIDTH - 4 + seed;
			headY = 0; 

			buffer_[headY + 2][headX]		= OBSTACLE;
			buffer_[headY + 1][headX - 1]	= OBSTACLE;
			buffer_[headY + 3][headX - 1]	= OBSTACLE;
			buffer_[headY + 1][headX + 1]	= OBSTACLE;
			buffer_[headY + 3][headX + 1]	= OBSTACLE;
			break;
	}

	buffer_[headY][headX] = OBSTACLE;

	partOfRoad = rand() % 2 + 1;
	seed = rand() % 6 - 3;

	switch (partOfRoad) {
		case 1 :
			headX = 11 + seed;
			headY = 3;

			buffer_[headY - 2][headX]		= OBSTACLE;
			buffer_[headY - 1][headX - 1]	= OBSTACLE;
			buffer_[headY - 3][headX - 1]	= OBSTACLE;
			buffer_[headY - 1][headX + 1]	= OBSTACLE;
			buffer_[headY - 3][headX + 1]	= OBSTACLE;
			break;
		case 2 :
			headX = FIELD_WIDTH - 11 + seed;
			headY = 0;

			buffer_[headY + 2][headX]		= OBSTACLE;
			buffer_[headY + 1][headX - 1]	= OBSTACLE;
			buffer_[headY + 3][headX - 1]	= OBSTACLE;
			buffer_[headY + 1][headX + 1]	= OBSTACLE;
			buffer_[headY + 3][headX + 1]	= OBSTACLE;
			break;
	}

	buffer_[headY][headX] = OBSTACLE;
}

int 
ComplicatedField::getBufferBlockType(const Coordinate& coordinate) const
{
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (x < 0 || x > FIELD_WIDTH - 1 || y < 0 || y > BUFFER_HEIGHT - 1)
		return -1;

	return buffer_[y][x];
}

void 
ComplicatedField::clearBuffer()
{
	for (int j = 0; j < BUFFER_HEIGHT; j++)
		for (int i = 0; i < FIELD_WIDTH; i++)
			buffer_[j][i] = EMPTY;
}

void 
ComplicatedField::placeObstacle()
{
	generateObstacle();

	for(int j = 0; j < BUFFER_HEIGHT; j++) {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			int bufferBlockType = getBufferBlockType({ i, j });

			if (bufferBlockType == RaceField::OBSTACLE)
				setBlockType({ i, j }, bufferBlockType);

		}
	}

	clearBuffer();
}