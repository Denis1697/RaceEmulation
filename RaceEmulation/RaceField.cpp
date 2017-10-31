#include "Includes.h"

void
RaceField::draw() const {
	for (int j = 0; j < FIELD_HEIGHT; j++) {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			drawBlock({ i, j });
		}
	}
}

void
RaceField::drawBlock(const Coordinate& coordinate) const {
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (isNotInField(coordinate)) {
		return;
	}

	ConsoleHelper::setCursorPosition({ x + EnumHelper::ARRAY_OFFSET, 
		                               y + EnumHelper::ARRAY_OFFSET });
	cout << static_cast<char>(raceField_[y][x]);
}

int
RaceField::getBlockType(const Coordinate& coordinate) const {
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (isNotInField(coordinate)) {
		return BAD_BLOCKTYPE;
	}

	return raceField_[y][x];
}

void
RaceField::setBlockType(const Coordinate& coordinate, const int& blockType) {
	int x = coordinate.getX();
	int y = coordinate.getY();

	bool isNotValidBlockType  = blockType < 0;
	     isNotValidBlockType |= blockType > 255;

	if (isNotInField(coordinate) || isNotValidBlockType) {
		return;
	}

	raceField_[y][x] = blockType;
}

bool
RaceField::isNotInField(const Coordinate& coordinate) const {
	int x = coordinate.getX();
	int y = coordinate.getY();

	int  leftBorder   = 0;
	int  bottomBorder = 0;
	int  rightBorder  = FIELD_WIDTH - 1;
	int  topBorder    = FIELD_HEIGHT - 1;

	bool isPointNotInField  = x < leftBorder;
	     isPointNotInField |= x > rightBorder;
	     isPointNotInField |= y < bottomBorder;
	     isPointNotInField |= y > topBorder;

	return isPointNotInField;
}

 int
RaceField::getWidth() const {
	return FIELD_WIDTH;
}

 int
RaceField::getHeight() const {
	return FIELD_HEIGHT;
}