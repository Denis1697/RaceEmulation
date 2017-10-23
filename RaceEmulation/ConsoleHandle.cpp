#include "Includes.h"

void
ConsoleHandler::setCursorPosition(const HANDLE& handleStdOut, const int& x, const int& y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(handleStdOut, coord);
}