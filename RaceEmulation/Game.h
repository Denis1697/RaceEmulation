#ifndef __GAME_H__
#define __GAME_H__

class Game
{
public:

	int             run();
	void            setGameMode(const int& gameMode);
	void            setConsoleNotifier(const ConsoleNotifier& consoleNotifier);
	void            setGameProcessor(const GameProcessor& gameProcessor);
	void            setDifficulty(const int& difficulty);
	int             getDifficulty();
	bool            wasArrowPressed(const int& key) const;

private:
	GameProcessor   gameProcessor_;
	ConsoleNotifier consoleNotifier_;
	bool            gameLoopStatus_;
	int             gameMode_;
	int             difficulty_;
};

#endif