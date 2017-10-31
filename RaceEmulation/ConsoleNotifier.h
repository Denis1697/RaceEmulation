#ifndef __CONSOLENOTIFIER_H__
#define __CONSOLENOTIFIER_H__

class ConsoleNotifier : public IMessage
{
public:
	void        showStatistics(const int&, const string&, const double&) const;
	bool        leaveTheGame()                                           const;
	void        setPause()                                               const;
	int         startingMode()                                           const;
	//int         menu()                                                   const;
	static void gameOver();
};

#endif