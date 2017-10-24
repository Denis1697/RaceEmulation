#include "Includes.h"

void
ConsoleHandler::setCursorPosition(const HANDLE& handleStdOut, const int& x, const int& y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(handleStdOut, coord);
}

void ConsoleHandler::setCursorState(bool active)
{
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), active };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
