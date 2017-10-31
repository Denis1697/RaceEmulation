#include "Includes.h"

void main()
{
	srand(static_cast<unsigned int>(time(0)));

	const int  OBSTACLE_MODE = 1;
	const int  CAR_MODE      = 2;
	const bool STATUS_ACTIVE = true;
	const bool STATUS_EXIT   = true;
	bool       gameStatus    = STATUS_ACTIVE;

	ConsoleNotifier consoleNotifier;
	GameProcessor   gameProcessor;
	RaceField*      field;

	int gameMode = consoleNotifier.startingMode() == 1;

	if (gameMode == OBSTACLE_MODE) {
		field = new EasyField();
	}
	else {
		field = new ComplicatedField();
	}

	int xOffset = field->getWidth() / 2;
	int yOffset = field->getHeight() - 5;
	Coordinate topCarCoord(xOffset, yOffset);

	Car   car(topCarCoord);
	Timer timer;

	gameProcessor.setRaceField(field);
	gameProcessor.setCar(car);
	gameProcessor.placeCar(car.getPartsCoords());

	timer.start();

	ConsoleHelper::setCursorState(false);

	while (gameStatus == STATUS_ACTIVE) {

		while (_kbhit() == 0) {
			timer.calculateTime();

			string time     = timer.getTime();
			double speed    = gameProcessor.getCar().getCurrentSpeed();
			int    distance = gameProcessor.getTraveledDistance();
			
			consoleNotifier.showStatistics(distance, time, speed);
			gameProcessor.computeGameTick();
			field->draw();
		}

		int key = _getch();

		bool wasArrowPressed  = (key == EnumHelper::Direction::DIRECTION_LEFT);
		     wasArrowPressed |= (key == EnumHelper::Direction::DIRECTION_RIGHT);
		     wasArrowPressed |= (key == EnumHelper::Direction::DIRECTION_UP);
		     wasArrowPressed |= (key == EnumHelper::Direction::DIRECTION_DOWN);

		if (wasArrowPressed) {
			gameProcessor.computeCarMove(key);
			gameProcessor.drawCar();
		}
		else {
			switch (key) {
			    case EnumHelper::ServiceButton::ENTER:
			        consoleNotifier.setPause();
			        break;
			    case EnumHelper::ServiceButton::ESCAPE:
					if (consoleNotifier.leaveTheGame() == true) {
						gameStatus = false;
					}
			}
		}
	}
}