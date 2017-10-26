#include "Includes.h"

void
RaceField::draw() const
{
	for (int j = 0; j < FIELD_HEIGHT; j++)
		for (int i = 0; i < FIELD_WIDTH; i++)
			drawBlock({ i, j });
}

void
RaceField::drawBlock(const Coordinate& coordinate) const
{
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (x < 0 || x > FIELD_WIDTH - 1 || y < 0 || y > FIELD_HEIGHT - 1)
		return;

	ConsoleHelper::setCursorPosition({ x + 1, y + 1 });
	cout << static_cast<char>(raceField_[y][x]);
}

int
RaceField::getBlockType(const Coordinate& coordinate) const
{
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (x < 0 || x > FIELD_WIDTH - 1 || y < 0 || y > FIELD_HEIGHT - 1)
		return -1;

	return raceField_[y][x];
}

void
RaceField::setBlockType(const Coordinate& coordinate, const int& blockType)
{
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (x < 0 || x > FIELD_WIDTH - 1 || y < 0 || 
		y > FIELD_HEIGHT - 1 || blockType < 0 || blockType > 255)
		return;

	raceField_[y][x] = blockType;
}

int 
RaceField::getWidth() const
{
	return FIELD_WIDTH;
}

int
RaceField::getHeight() const
{
	return FIELD_HEIGHT;
}