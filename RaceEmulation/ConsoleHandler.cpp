#include "Includes.h"

void
ConsoleHandler::setCursorPosition(const int& x, const int& y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(getStdHandle(), coord);
}

void 
ConsoleHandler::setCursorState(bool active)
{
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), active };
	SetConsoleCursorInfo(getStdHandle(), &cci);
}

HANDLE ConsoleHandler::getStdHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}


