#include "Includes.h"

void main()
{
	srand(static_cast<unsigned int>(time(0)));

	GameProcessor gameProcessor;

	RaceField * field;	
	if (gameProcessor.startingMode() == 1)
		field = new EasyField();
	else
		field = new ComplicatedField();

	int width = field->getWidth();
	int height = field->getHeight();
	Coordinate topCarCoord(width / 2, height - 5);


	Car * car = new Car(topCarCoord);
	Timer timer;

	gameProcessor.setRaceField(field);
	gameProcessor.setCar(car);
	gameProcessor.setTimer(&timer);	

	gameProcessor.placeCar(car->getCarPartsCoords());

	timer.start();

	ConsoleHelper::setCursorState(false);

	while (true)
	{

		while (_kbhit() == 0)
		{
			gameProcessor.showStatistics();
			gameProcessor.makeGameTick();
			field->draw();
		}

		int key = _getch();

		bool wasArrowPressed  = (key == Car::DIRECTION_LEFT);
			 wasArrowPressed |= (key == Car::DIRECTION_RIGHT);
			 wasArrowPressed |= (key == Car::DIRECTION_UP);
			 wasArrowPressed |= (key == Car::DIRECTION_DOWN);
			 
		if (wasArrowPressed)
		{
			gameProcessor.processCarMove(key);
			gameProcessor.drawCar();
		}
		else 
		{
			switch (key)
			{
			case GameProcessor::ENTER:
				gameProcessor.setPause();
				break;
			case GameProcessor::ESCAPE:
				gameProcessor.leaveTheGame();
			}
		}
	}

}