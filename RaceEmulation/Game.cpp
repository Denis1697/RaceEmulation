#include "Includes.h"

int 
Game::run() {
	RaceField*      field;
	FileProcessor   fileProcessor; 
	gameLoopStatus_ = EnumHelper::STATUS_ACTIVE;

	ConsoleNotifier consoleNotifier;
	setConsoleNotifier(consoleNotifier_);
	setGameMode(consoleNotifier_.startingMode());

	if (gameMode_ == EnumHelper::OBSTACLE_MODE) {
		field = new EasyField();
	}
	else {
		field = new ComplicatedField();
	}

	Coordinate    topCarCoord(field->getWidth() / 2,
		                      field->getHeight() - 5);
	Car           car(topCarCoord);	

	gameProcessor_.setCar(car);

	vector<Coordinate> parts(EnumHelper::PARTS_COUNT);
	parts = gameProcessor_.getCar().getPartsCoords();

	switch (difficulty_) {
	    default:
	    case EnumHelper::EASY:
	    	gameProcessor_.getCar().setCurrentSpeed(5.0);
	    	gameProcessor_.getCar().setMinSpeed(1.0);
	    	gameProcessor_.getCar().setSpeedStep(0.1);
	    	break;
	    case EnumHelper::MEDIUM:
			gameProcessor_.getCar().setCurrentSpeed(12.0);
			gameProcessor_.getCar().setMinSpeed(10.0);
			gameProcessor_.getCar().setSpeedStep(0.5);
	    	break;
	    case EnumHelper::HARD:
			gameProcessor_.getCar().setCurrentSpeed(25.0);
			gameProcessor_.getCar().setMinSpeed(25.0);
			gameProcessor_.getCar().setSpeedStep(1.0);
	    	break;
	}

	gameProcessor_.setRaceField(field);
	gameProcessor_.placeCar(parts);

	GameProcessor gameProcessor;
	setGameProcessor(gameProcessor_);

	ConsoleHelper::setCursorState(false);

	Timer timer;
	timer.start();

    int carMoveResult = -1;

	while (gameLoopStatus_ == EnumHelper::STATUS_ACTIVE) {

		while (_kbhit() == 0) {
			timer.calculateTime();

			string time     = timer.getTime();
			double speed    = gameProcessor_.getCar().getCurrentSpeed();
			int    distance = gameProcessor_.getTraveledDistance();

			consoleNotifier_.showStatistics(distance, time, speed);

			carMoveResult = gameProcessor_.computeGameTick();

			if (carMoveResult == EnumHelper::FAIL) {
				break;
			}

			field->draw();
		}

		int key = _getch();

		if (wasArrowPressed(key)) {
			carMoveResult = gameProcessor_.computeCarMove(key);
			gameProcessor_.drawCar();
		}
		else {
			switch (key) {
			case EnumHelper::eServiceButton::ENTER:
				consoleNotifier_.setPause();
				break;
			case EnumHelper::eServiceButton::ESCAPE:
				if (consoleNotifier.leaveTheGame() == true) {
					system("cls");
					gameLoopStatus_ = false;
				}
			default:
				break;
			}
		}
		if (carMoveResult == EnumHelper::FAIL) {
			system("cls");
			gameLoopStatus_ = EnumHelper::STATUS_EXIT;

			char buffer[5];
			_itoa_s(gameProcessor_.getTraveledDistance(),
				buffer, EnumHelper::DECIMAL);

			vector<string> tableNote(EnumHelper::NOTE_DATA_COUNT);
			tableNote.push_back(consoleNotifier.inputNickname());
			tableNote.push_back(buffer);
			tableNote.push_back(timer.getTime());

			fileProcessor.addTableNote(tableNote);
		}
	}
}

void 
Game::setGameMode(const int& gameMode) {
	gameMode_ = gameMode;
}

void 
Game::setConsoleNotifier(const ConsoleNotifier& consoleNotifier) {
	consoleNotifier_ = consoleNotifier;
}

void 
Game::setGameProcessor(const GameProcessor & gameProcessor) {
	gameProcessor_ = gameProcessor;
}

void 
Game::setDifficulty(const int& difficulty) {
	difficulty_ = difficulty;
} 

int 
Game::getDifficulty() {
	return difficulty_;
}

bool 
Game::wasArrowPressed(const int& key) const {
	bool isArrow  = (key == EnumHelper::eDirection::DIRECTION_LEFT);
	     isArrow |= (key == EnumHelper::eDirection::DIRECTION_RIGHT);
	     isArrow |= (key == EnumHelper::eDirection::DIRECTION_UP);
	     isArrow |= (key == EnumHelper::eDirection::DIRECTION_DOWN);

    return isArrow;
}