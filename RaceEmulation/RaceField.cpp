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

	const int ARRAY_OFFSET = 1;

	ConsoleHelper::setCursorPosition({ x + ARRAY_OFFSET, y + ARRAY_OFFSET });
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

	bool isPointNotInField  = x < LEFT_BORDER;
	     isPointNotInField |= x > RIGHT_BORDER;
	     isPointNotInField |= y < BOTTOM_BORDER;
	     isPointNotInField |= y > TOP_BORDER;

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