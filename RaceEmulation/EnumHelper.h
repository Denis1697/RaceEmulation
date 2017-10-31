#ifndef __ENUMHELPER_H__
#define __ENUMHELPER_H__

class EnumHelper 
{
public:

	//initialize static in .cpp
	static int  OBSTACLE_MODE;
	static int  CAR_MODE;
	static bool STATUS_ACTIVE;
	static bool STATUS_EXIT;
	static int  SECONDS_PER_MINUTE;
	static int  MINUTES_PER_SECONDS;
	static int  ONE_SECOND;
	static int  START_X_OFFSET;
	static int  START_Y_OFFSET;
	static int  PARTS_COUNT;
	static int  OBSTACLES_NO;
	static int  CAR_HEAD_TOP;
	static int  CAR_HEAD_BOTTOM;
	static int  DECIMAL;
	static int  OBSTACLE_ANSWER;
	static int  CAR_ANSWER;
	static int  ARRAY_OFFSET;

	enum eBlockType {
		EMPTY = 32,
		BORDER_ONE = 177,
		BORDER_TWO = 176,
		OBSTACLE = 220,
		CAR_TOP = 254,
		CAR_TIRE = 111,
		CAR_TORSO = 219
	};
	enum eObstacle {
		STONE,
		LOG,
		TREE,
		CAR
	};
	enum eDirection {
		DIRECTION_UP = 72,
		DIRECTION_LEFT = 75,
		DIRECTION_RIGHT = 77,
		DIRECTION_DOWN = 80
	};
	enum eCarPart {
		LEFT_TOP_TIRE,
		LEFT_BOTTOM_TIRE,
		CAR_HEAD,
		CAR_BODY,
		RIGHT_TOP_TIRE,
		RIGHT_BOTTOM_TIRE
	};

	enum eWindowPart {
		LEFT_TOP_CORNER = 201,
		RIGHT_TOP_CORNER = 187,
		RIGHT_BOTTOM_CORNER = 188,
		LEFT_BOTTOM_CORNER = 200,
		HORIZONTAL_PART = 205,
		VERTICAL_PART = 186
	};

	enum eServiceButton {
		ENTER = 13,
		ESCAPE = 27
	};
};

#endif