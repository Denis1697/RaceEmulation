#include "Includes.h"

void main()
{
	ConsoleHandler::setCursorState(false);
	srand(static_cast<unsigned int>(time(0)));

	Timer timer;
	timer.start();


	RaceField * field = new EasyField();
	int width = field->getWidth();
	int height = field->getHeight();

	Coordinate top(width / 2, height - 5);
	Car * car = new Car(top);
	GameProcessor gameProcessor(field, car);
	
	gameProcessor.placeCar(car->getCarPartsCoords());

	while (true)
	{

		while (!_kbhit())
		{
			ConsoleHandler::setCursorPosition(45, 5);
			timer.showTime();
			ConsoleHandler::setCursorPosition(45, 6);
			gameProcessor.showTraveledDistance();
			ConsoleHandler::setCursorPosition(45, 7);
			car->showCarSpeed();

			gameProcessor.makeGameTick();
			field->draw();
		}

		int key = _getch();

		bool wasArrowPressed = (key == Car::DIRECTION_LEFT);
		wasArrowPressed |= (key == Car::DIRECTION_RIGHT);
		wasArrowPressed |= (key == Car::DIRECTION_UP);
		wasArrowPressed |= (key == Car::DIRECTION_DOWN);

		if (wasArrowPressed)
		{
			gameProcessor.processCarMove(key);
			gameProcessor.drawCar();
		}
	}
}