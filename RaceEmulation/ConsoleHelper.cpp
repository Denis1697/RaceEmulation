#include "Includes.h"

void
ConsoleHelper::setCursorPosition(const Coordinate& position)
{
	int x = position.getX();
	int y = position.getY();

	COORD coord = { x, y };
	SetConsoleCursorPosition(getStdHandle(), coord);
}

void 
ConsoleHelper::setCursorState(const bool& active)
{
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), active };
	SetConsoleCursorInfo(getStdHandle(), &cci);
}

HANDLE 
ConsoleHelper::getStdHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

void 
ConsoleHelper::drawWindow(const Coordinate & leftTopCoord, const Coordinate & rightBottomCoord)
{
	int x1 = leftTopCoord.getX();
	int x2 = rightBottomCoord.getX();
	int y1 = leftTopCoord.getY();
	int y2 = rightBottomCoord.getY();

	int dX = x2 - x1;
	int dY = y2 - y1;

	setCursorPosition(leftTopCoord);
	cout << static_cast<char>(201);
	setCursorPosition({ x2, y1 });
	cout << static_cast<char>(187);
	setCursorPosition(rightBottomCoord);
	cout << static_cast<char>(188);
	setCursorPosition({ x1, y2 });
	cout << static_cast<char>(200);


	for (int i = 0; i < dX-1; i++)
	{
		setCursorPosition({ x1 + i + 1, y1 });
		cout << static_cast<char>(205);
		setCursorPosition({ x1 + i + 1, y2 });
		cout << static_cast<char>(205);
	}

	for (int i = 0; i < dY-1; i++)
	{
		setCursorPosition({ x1, y1 + i + 1 });
		cout << static_cast<char>(186);
		setCursorPosition({ x2, y1 + i + 1 });
		cout << static_cast<char>(186);
	}
}

void 
ConsoleHelper::clearWindow(const Coordinate & leftTopCoord, const Coordinate & rightBottomCoord)
{
	int x1 = leftTopCoord.getX();
	int x2 = rightBottomCoord.getX();
	int y1 = leftTopCoord.getY();
	int y2 = rightBottomCoord.getY();

	setCursorPosition(leftTopCoord);

	for (int i = y1; i <= y2; i++)
	{
		for (int j = x1; j <= x2; j++)
		{
			cout << " ";
		}
		setCursorPosition({ x1, i + 1 });
	}
}