#include "Includes.h"

void main()
{
	srand(static_cast<unsigned int>(time(0)));
	
	FileProcessor   fileProcessor;
	ConsoleNotifier consoleNotifier;
	Game* game = nullptr;
	bool isNewGame = true; 
	int gameResult;

	while (true) {
		if (isNewGame) {
			delete game;
			game = new Game();
			isNewGame = false;
		}

		int menuPoint = consoleNotifier.menu();
		int difficulty = EnumHelper::eDifficulty::EASY;

		switch (menuPoint) {
		    case EnumHelper::eMenuPoint::POINT_NEW_GAME:
				game->run();
				isNewGame = true;
		    	break;
		    case EnumHelper::eMenuPoint::POINT_RECORDS:
		    	consoleNotifier.recordsTable(fileProcessor.loadTable());
		    	break;
		    case EnumHelper::eMenuPoint::POINT_INFORMATION:
				consoleNotifier.information();
		    	break;
		    case EnumHelper::eMenuPoint::POINT_DIFFICULTY:
				difficulty = consoleNotifier.difficultyChoose();
				game->setDifficulty(difficulty);
		    	break;
		    case EnumHelper::eMenuPoint::POINT_EXIT:
				exit(0);
		    	break;
		    default:
		    	break;
		}
	}
}