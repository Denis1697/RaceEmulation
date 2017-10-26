#ifndef __CONSOLEHANDLER_H__
#define __CONSOLEHANDLER_H__

class ConsoleHelper
{
public:
	static void		setCursorPosition(const Coordinate& position);
	static void		setCursorState(const bool& active);
	static HANDLE	getStdHandle();
	static void		drawWindow(const Coordinate& leftTopCoord, const Coordinate& rightBottomCoord);
	static void		clearWindow(const Coordinate& leftTopCoord, const Coordinate& rightBottomCoord);
private:
	enum WindowParts
	{
		LEFT_TOP_CORNER		= 201,
		RIGHT_TOP_CORNER	= 187,
		RIGHT_BOTTOM_CORNER = 188,
		LEFT_BOTTOM_CORNER	= 200,
		HORIZONTAL_PART		= 205,
		VERTICAL_PART		= 186
	};
};

#endif