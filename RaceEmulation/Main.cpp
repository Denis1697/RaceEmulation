#include "Includes.h"

void main()
{
	srand(static_cast<unsigned int>(time(0)));

	const int OBSTACLE_MODE = 1;
	const int CAR_MODE      = 2;

	GameProcessor gameProcessor;
	RaceField*    field;

	int gameMode = gameProcessor.startingMode() == 1;

	if (gameMode == OBSTACLE_MODE) {
		field = new EasyField();
	}
	else {
		field = new ComplicatedField();
	}

	int xOffset = field->getWidth() / 2;
	int yOffset = field->getHeight() - 5;
	Coordinate topCarCoord(xOffset, yOffset);

	Car*  car = new Car(topCarCoord);

	Timer timer;

	gameProcessor.setRaceField(field);
	gameProcessor.setCar(car);
	gameProcessor.setTimer(&timer);
	gameProcessor.placeCar(car->getPartsCoords());

	timer.start();

	ConsoleHelper::setCursorState(false);

	while (gameProcessor.getGameStatus() == true) {

		while (_kbhit() == 0) {
			gameProcessor.showStatistics();
			gameProcessor.computeGameTick();
			field->draw();
		}

		int key = _getch();

		bool wasArrowPressed  = (key == Direction::DIRECTION_LEFT);
		     wasArrowPressed |= (key == Direction::DIRECTION_RIGHT);
		     wasArrowPressed |= (key == Direction::DIRECTION_UP);
		     wasArrowPressed |= (key == Direction::DIRECTION_DOWN);

		if (wasArrowPressed) {
			gameProcessor.computeCarMove(key);
			gameProcessor.drawCar();
		}
		else {
			switch (key) {
			    case ServiceButton::ENTER:
			        gameProcessor.setPause();
			        break;
			    case ServiceButton::ESCAPE:
			        gameProcessor.leaveTheGame();
			}
		}
	}
}