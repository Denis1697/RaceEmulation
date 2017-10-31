#include "Includes.h"

EasyField::EasyField() {
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
EasyField::generateObstacle() {
	int obstacleChoice = rand() % EnumHelper::OBSTACLES_NO;
	int obstacleLength = 0;

	switch (obstacleChoice) {
	    case EnumHelper::STONE: obstacleLength = 1;	break;
	    case EnumHelper::LOG:   obstacleLength = 3;	break;
	    case EnumHelper::TREE:  obstacleLength = 5;	break;
		default:                                    break;
	}

	int x;

	if (obstacleChoice == EnumHelper::TREE && FIELD_WIDTH < 10) {
		int choice = rand() % 2;

		switch (choice) {
		    case 0: x = 1;  break;
		    case 1: x = 4;  break;
		    default:        break;
		}
	}
	else {
		x = rand() % (FIELD_WIDTH - obstacleLength - 1) + 1;
	}

	for (int i = x; i < x + obstacleLength; i++) {
		buffer_[i] = EnumHelper::OBSTACLE;
	}
}

int
EasyField::getBufferBlockType(const Coordinate& coordinate) const
{
	int x = coordinate.getX();

	if (x < 0 || x > FIELD_WIDTH - 1) {
		return BAD_BLOCKTYPE;
	}

	return buffer_[x];
}

void
EasyField::clearBuffer() {
	for (int i = 1; i < FIELD_WIDTH - 1; i++) {
		buffer_[i] = EnumHelper::EMPTY;
	}
}

void
EasyField::placeObstacle() {
	generateObstacle();

	for (int i = 0; i < FIELD_WIDTH; i++) {
		int bufferBlockType = getBufferBlockType({ i, 0 });

		if (bufferBlockType == EnumHelper::eBlockType::OBSTACLE) {
			setBlockType({ i, 0 }, bufferBlockType);
		}
	}

	clearBuffer();
}
