#include "Includes.h"

ComplicatedField::ComplicatedField() {
	for (int j = 0; j < FIELD_HEIGHT; j++) {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			EnumHelper::eBlockType currentBorder = 
				(j % 2 == 0 ? EnumHelper::BORDER_ONE : EnumHelper::BORDER_TWO);

			if (i == 0 || i == FIELD_WIDTH - 1) {
				raceField_[j][i] = currentBorder;
			}
			else {
				raceField_[j][i] = EnumHelper::EMPTY;
			}
		}
	}
}

void
ComplicatedField::generateObstacle() {
	int firstRoadPart  = rand() % 2 + 1;
	int secondRoadPart = rand() % 2 + 1;

	generateCar(firstRoadPart, true);
	generateCar(secondRoadPart, false);
}

void
ComplicatedField::generateCar(int roadPart, bool isFirst) {
	const int LEFT_ROAD_PART  = 1;
	const int RIGHT_ROAD_PART = 2;

	int randomSeed, xOffset;
	int headX, headY;

	if (isFirst) {
		randomSeed = rand() % 4 - 2;
		xOffset = 4;
	}
	else {
		randomSeed = rand() % 6 - 3;
		xOffset = 11;
	}

	switch (roadPart) {
	    case LEFT_ROAD_PART:
	    	headX = xOffset + randomSeed;
	    	headY = EnumHelper::CAR_HEAD_BOTTOM;
	    
	    	buffer_[headY - 2][headX]     = EnumHelper::OBSTACLE;
	    	buffer_[headY - 1][headX - 1] = EnumHelper::OBSTACLE;
	    	buffer_[headY - 3][headX - 1] = EnumHelper::OBSTACLE;
	    	buffer_[headY - 1][headX + 1] = EnumHelper::OBSTACLE;
	    	buffer_[headY - 3][headX + 1] = EnumHelper::OBSTACLE;
	    	break;
	    case RIGHT_ROAD_PART:
	    	headX = FIELD_WIDTH - xOffset + randomSeed;
	    	headY = EnumHelper::CAR_HEAD_TOP;
	    
	    	buffer_[headY + 2][headX]     = EnumHelper::OBSTACLE;
	    	buffer_[headY + 1][headX - 1] = EnumHelper::OBSTACLE;
	    	buffer_[headY + 3][headX - 1] = EnumHelper::OBSTACLE;
	    	buffer_[headY + 1][headX + 1] = EnumHelper::OBSTACLE;
	    	buffer_[headY + 3][headX + 1] = EnumHelper::OBSTACLE;
	    	break;
		default:
			break;
	}

	buffer_[headY][headX] = EnumHelper::OBSTACLE;
}


int
ComplicatedField::getBufferBlockType(const Coordinate& coordinate) const {
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (isNotInField(coordinate) || y > BUFFER_HEIGHT - 1) {
		return BAD_BLOCKTYPE;
	}

	return buffer_[y][x];
}

void
ComplicatedField::clearBuffer() {
	for (int j = 0; j < BUFFER_HEIGHT; j++) {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			buffer_[j][i] = EnumHelper::EMPTY;
		}
	}
}

void
ComplicatedField::placeObstacle() {
	generateObstacle();

	for (int j = 0; j < BUFFER_HEIGHT; j++) {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			int bufferBlockType = getBufferBlockType({ i, j });

			if (bufferBlockType == EnumHelper::OBSTACLE) {
				setBlockType({ i, j }, bufferBlockType);
			}

		}
	}

	clearBuffer();
}