#include "Includes.h"

void main()
{
	srand(static_cast<unsigned int>(0));

	RaceField * field = new EasyField();
	GameProcessor gameProcessor(field);

	HANDLE handleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Timer timer;
	timer.start();
	
	ConsoleHandler::setCursorState(false);

	gameProcessor.placePlayerCar();

	while (true)
	{
		while (!_kbhit()) 
		{
			timer.asyncTime();
			gameProcessor.makeGameTick();

			ConsoleHandler::setCursorPosition(handleStdOut, 45, 5);
			timer.showTime();
			ConsoleHandler::setCursorPosition(handleStdOut, 45, 6);
			gameProcessor.showTraveledDistance();

			ConsoleHandler::setCursorPosition(handleStdOut, 1, 1);
			field->draw();
		}

		std::flush(cout);
		int key = _getch();

		bool wasArrowPressed = (key == gameProcessor.DIRECTION_LEFT);
			wasArrowPressed |= (key == gameProcessor.DIRECTION_RIGHT);

		if (wasArrowPressed)
			gameProcessor.moveCar(key);
	}

}