#include "Includes.h"

void main()
{
	srand(static_cast<unsigned int>(time(0)));

	RaceField * field = new EasyField();
	GameProcessor gameProcessor(field);

	HANDLE handleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Timer timer;
	timer.start();
	
	ConsoleHandler::setCursorState(false);

	gameProcessor.placePlayerCar(field->getWidth()/2, field->getHeight() - 5);

	while (true)
	{
		while (!_kbhit()) 
		{
			gameProcessor.makeGameTick();

			ConsoleHandler::setCursorPosition(45, 5);
			timer.showTime();
			ConsoleHandler::setCursorPosition(45, 6);
			gameProcessor.showTraveledDistance();
			ConsoleHandler::setCursorPosition(45, 7);
			gameProcessor.showCarSpeed();

			ConsoleHandler::setCursorPosition(1, 1);
			field->draw();
		}

		int key = _getch();

		bool wasArrowPressed = (key == gameProcessor.DIRECTION_LEFT);
			wasArrowPressed |= (key == gameProcessor.DIRECTION_RIGHT);
			wasArrowPressed |= (key == gameProcessor.DIRECTION_UP);
			wasArrowPressed |= (key == gameProcessor.DIRECTION_DOWN);

		if (wasArrowPressed)
			gameProcessor.moveCar(key);
	}

}