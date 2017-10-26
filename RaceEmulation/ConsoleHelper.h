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
};

#endif