#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <clocale>
#include <string>
using namespace std;

#include "Coordinate.h"
#include "Car.h"
#include "Timer.h"
#include "RaceField.h"
#include "ComplicatedField.h"
#include "EasyField.h"
#include "ConsoleHelper.h"
#include "GameProcessor.h"

enum BlockType {
	EMPTY = 32,
	BORDER_ONE = 177,
	BORDER_TWO = 176,
	OBSTACLE = 220,
	CAR_TOP = 254,
	CAR_TIRE = 111,
	CAR_TORSO = 219
};
enum Obstacle {
	STONE,
	LOG,
	TREE,
	CAR
};
enum Direction {
	DIRECTION_UP = 72,
	DIRECTION_LEFT = 75,
	DIRECTION_RIGHT = 77,
	DIRECTION_DOWN = 80
};
enum CarPart {
	LEFT_TOP_TIRE,
	LEFT_BOTTOM_TIRE,
	CAR_HEAD,
	CAR_BODY,
	RIGHT_TOP_TIRE,
	RIGHT_BOTTOM_TIRE
};

enum WindowPart {
	LEFT_TOP_CORNER = 201,
	RIGHT_TOP_CORNER = 187,
	RIGHT_BOTTOM_CORNER = 188,
	LEFT_BOTTOM_CORNER = 200,
	HORIZONTAL_PART = 205,
	VERTICAL_PART = 186
};

enum ServiceButton {
	ENTER = 13,
	ESCAPE = 27
};

#endif