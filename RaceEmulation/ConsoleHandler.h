#ifndef __CONSOLEHANDLER_H__
#define __CONSOLEHANDLER_H__

class ConsoleHandler
{
public:
	static void setCursorPosition(const int& x, const int& y);
	static void setCursorState(bool active);
	static HANDLE getStdHandle();
};

#endif