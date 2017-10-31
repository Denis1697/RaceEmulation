#ifndef __CONSOLENOTIFIER_H__
#define __CONSOLENOTIFIER_H__

class ConsoleNotifier : public IMessage
{
public:
	void        showStatistics(const int&, const string&, const double&) const;
	bool        leaveTheGame()                                           const;
	void        setPause()                                               const;
	int         startingMode()                                           const;
	static void gameOver();
private:	   
	const int  START_X_OFFSET = 44;
	const int  START_Y_OFFSET = 4;
};

#endif