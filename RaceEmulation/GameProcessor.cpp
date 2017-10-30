#include "Includes.h"
#include "Car.h"
GameProcessor::GameProcessor() {
	raceField_ = nullptr;
	car_       = nullptr;
	timer_     = nullptr;

	gameStatus_       = true;
	nGameTicks_       = 0;
	traveledDistance_ = 0;
}

GameProcessor::~GameProcessor() {
	delete car_;
	delete raceField_;
	delete timer_;

	car_       = nullptr;
	raceField_ = nullptr;
	timer_     = nullptr;
}

bool
GameProcessor::isCarCrushed(const int& direction) const {
	vector<Coordinate> parts = car_->getPartsCoords();

	int topCarX = parts[CarPart::CAR_HEAD].getX();
	int topCarY = parts[CarPart::CAR_HEAD].getY();

	int carWidth  = 3;
	int carHeight = 3;

	switch (direction) {
	case Direction::DIRECTION_UP:
		for (int i = 0; i < carWidth; i++) {
			if (raceField_->getBlockType({ topCarX + i - 1,
				topCarY }) == BlockType::OBSTACLE) {
				return true;
			}
		}
		break;
	case Direction::DIRECTION_LEFT:
		for (int i = 0; i < carHeight; i++) {
			if (raceField_->getBlockType({ topCarX - 1,
				topCarY + i + 1 }) == BlockType::OBSTACLE) {
				return true;
			}
		}
		break;
	case Direction::DIRECTION_RIGHT:
		for (int i = 0; i < carHeight; i++) {
			if (raceField_->getBlockType({ topCarX + 1,
				topCarY + i + 1 }) == BlockType::OBSTACLE) {
				return true;
			}
		}

		break;
	}

	return false;
}

void
GameProcessor::placeCar(const vector<Coordinate>& oldPosition) {
	raceField_->setBlockType(oldPosition[CarPart::LEFT_TOP_TIRE],
		BlockType::EMPTY);
	raceField_->setBlockType(oldPosition[CarPart::LEFT_BOTTOM_TIRE],
		BlockType::EMPTY);
	raceField_->setBlockType(oldPosition[CarPart::CAR_HEAD],
		BlockType::EMPTY);
	raceField_->setBlockType(oldPosition[CarPart::CAR_BODY],
		BlockType::EMPTY);
	raceField_->setBlockType(oldPosition[CarPart::RIGHT_TOP_TIRE],
		BlockType::EMPTY);
	raceField_->setBlockType(oldPosition[CarPart::RIGHT_BOTTOM_TIRE],
		BlockType::EMPTY);

	raceField_->drawBlock(oldPosition[CarPart::LEFT_TOP_TIRE]);
	raceField_->drawBlock(oldPosition[CarPart::LEFT_BOTTOM_TIRE]);
	raceField_->drawBlock(oldPosition[CarPart::CAR_HEAD]);
	raceField_->drawBlock(oldPosition[CarPart::CAR_BODY]);
	raceField_->drawBlock(oldPosition[CarPart::RIGHT_TOP_TIRE]);
	raceField_->drawBlock(oldPosition[CarPart::RIGHT_BOTTOM_TIRE]);

	vector<Coordinate> parts = car_->getPartsCoords();

	raceField_->setBlockType(parts[CarPart::LEFT_TOP_TIRE],
		BlockType::CAR_TIRE);
	raceField_->setBlockType(parts[CarPart::LEFT_BOTTOM_TIRE],
		BlockType::CAR_TIRE);
	raceField_->setBlockType(parts[CarPart::CAR_HEAD],
		BlockType::CAR_TOP);
	raceField_->setBlockType(parts[CarPart::CAR_BODY],
		BlockType::CAR_TORSO);
	raceField_->setBlockType(parts[CarPart::RIGHT_TOP_TIRE],
		BlockType::CAR_TIRE);
	raceField_->setBlockType(parts[CarPart::RIGHT_BOTTOM_TIRE],
		BlockType::CAR_TIRE);
}

void
GameProcessor::computeGameTick() {
	int width = raceField_->getWidth();
	int height = raceField_->getHeight();

	for (int j = height - 1; j > 0; j--) {
		for (int i = 0; i < width; i++) {

			int upperBlockType   = raceField_->getBlockType({ i, j - 1 });
			int currentBlockType = raceField_->getBlockType({ i, j });

			bool isItCar  = (upperBlockType == BlockType::CAR_TIRE);
			     isItCar |= (upperBlockType == BlockType::CAR_TORSO);
			     isItCar |= (upperBlockType == BlockType::CAR_TOP);
			     isItCar |= (currentBlockType == BlockType::CAR_TIRE);
			     isItCar |= (currentBlockType == BlockType::CAR_TORSO);
			     isItCar |= (currentBlockType == BlockType::CAR_TOP);

			if (!isItCar) {
				raceField_->setBlockType({ i, j }, upperBlockType);
			}
		}
	}

	alternateBorders();

	bool isComplicated = (strcmp(typeid(*raceField_).name(),
		typeid(ComplicatedField).name()) == 0);

	bool isEasy = (strcmp(typeid(*raceField_).name(),
		typeid(EasyField).name()) == 0);

	bool isEighthTick = nGameTicks_ % 8 == 0;

	if (isEighthTick) {
		if (isComplicated) {
			raceField_->placeObstacle();
		}
		else if (isEasy) {
			raceField_->placeObstacle();
			raceField_->placeObstacle();
		}
	}
	else {
		for (int i = 1; i < width - 1; i++) {
			raceField_->setBlockType({ i, 0 }, BlockType::EMPTY);
		}
	}

	if (isCarCrushed(Direction::DIRECTION_UP)) {
		gameOver();
	}

	nGameTicks_++;
	traveledDistance_ = nGameTicks_;

	int drawSpeed = ONE_SECOND / static_cast<int>(car_->getCurrentSpeed());

	Sleep(drawSpeed);
}

void
GameProcessor::gameOver() {
	int leftTopX     = 44;
	int leftTopY     = 9;
	int windowWidth  = 31;
	int windowHeight = 2;

	Coordinate leftTop  = { leftTopX, leftTopY };
	Coordinate rightBot = { leftTopX + windowWidth, 
		                    leftTopY + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ leftTopX + 1, leftTopY + 1 });
	cout << "Sorry, your car has crushed...";

	gameStatus_ = false;
	ConsoleHelper::setCursorPosition({ leftTopX + 1, leftTopY + 4 });
	system("pause");
	exit(0);
}

void
GameProcessor::computeCarMove(const int& direction) {
	int nParts = car_->getPartsCount();

	vector<Coordinate> parts = car_->getPartsCoords();
	vector<Coordinate> oldParts(nParts);

	for (int i = 0; i < nParts; i++) {
		oldParts[i].setX(parts[i].getX());
		oldParts[i].setY(parts[i].getY());
	}

	car_->move(direction, raceField_->getWidth(), raceField_->getHeight());

	if (isCarCrushed(direction)) {
		gameOver();
	}
	else {
		placeCar(oldParts);
		drawCar();
	}
}

void
GameProcessor::showTraveledDistance() const {
	cout << "Traveled distance: " << traveledDistance_ << " m";
}

bool
GameProcessor::getGameStatus() {
	return gameStatus_;
}

int
GameProcessor::startingMode() const {
	const int OBSTACLE_ANSWER = 1;
	const int CAR_ANSWER      = 2;

	int leftTopX     = 24;
	int leftTopY     = 9;
	int windowWidth  = 16;
	int windowHeight = 5;
	int firstColumn  = leftTopX + 1;

	Coordinate answerPosition = { leftTopX + 9, leftTopY + 4 };
	Coordinate leftTop        = { leftTopX, leftTopY };
	Coordinate rightBot       = { leftTopX + windowWidth,
		                          leftTopY + windowHeight };

	string startingModeText[4] = {
		"Select the mode",
		"1. Obstacles",
		"2. Cars",
		"Answer: "
	};

	ConsoleHelper::drawWindow(leftTop, rightBot);

	for (int i = 1; i < windowHeight; i++) {
		ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + i });
		cout << startingModeText[i - 1];
	}

	int answer;
	cin >> answer;

	bool isAnswerIncorrect  = answer != OBSTACLE_ANSWER;
	     isAnswerIncorrect &= answer != CAR_ANSWER;

	while (isAnswerIncorrect) {
		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> answer;

		isAnswerIncorrect  = answer != OBSTACLE_ANSWER;
		isAnswerIncorrect &= answer != CAR_ANSWER;
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);

	return answer;
}

void
GameProcessor::setCar(Car* car) {
	car_ = car;
}

void
GameProcessor::setRaceField(RaceField* raceField) {
	raceField_ = raceField;
}

void
GameProcessor::setTimer(Timer* timer) {
	timer_ = timer;
}

void
GameProcessor::showStatistics() const {
	int leftTopX     = 44;
	int leftTopY     = 4;
	int windowWidth  = 26;
	int windowHeight = 4;
	int firstColumn  = leftTopX + 1;

	Coordinate leftTop  = { leftTopX, leftTopY };
	Coordinate rightBot = { leftTopX + windowWidth,
		                    leftTopY + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + 1 });
	cout << "Time: ";
	timer_->showTime();

	ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + 2 });
	showTraveledDistance();

	ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + 3 });
	car_->showSpeed();
}

void
GameProcessor::setPause() const {
	int leftTopX     = 44;
	int leftTopY     = 9;
	int windowWidth  = 6;
	int windowHeight = 2;
	int firstColumn  = leftTopX + 1;

	Coordinate leftTop  = { leftTopX, leftTopY };
	Coordinate rightBot = { leftTopX + windowWidth,
		                    leftTopY + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + 1 });
	cout << "Pause";

	ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + 4 });
	system("pause");

	ConsoleHelper::clearWindow(leftTop, rightBot);

	//clearing window from system message "Press any key to continue"
	ConsoleHelper::clearWindow({ leftTopX, leftTopY + 4 },
	{ leftTopX + 50, leftTopY + 4 });
}

void
GameProcessor::leaveTheGame() const {
	const int YES_ANSWER = 1;
	const int NO_ANSWER  = 2;

	int leftTopX     = 44;
	int leftTopY     = 9;
	int windowWidth  = 16;
	int windowHeight = 5;
	int firstColumn  = leftTopX + 1;

	Coordinate answerPosition = { leftTopX + 9, leftTopY + 4 };
	Coordinate leftTop        = { leftTopX, leftTopY };
	Coordinate rightBot       = { leftTopX + windowWidth,
		                          leftTopY + windowHeight };

	string leaveTheGameText[4] = {
		"Quit?",
		"1. Yes",
		"2. No",
		"Answer: "
	};

	ConsoleHelper::drawWindow(leftTop, rightBot);

	for (int i = 1; i < windowHeight; i++) {
		ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + i });
		cout << leaveTheGameText[i - 1];
	}

	int answer;
	cin >> answer;

	bool isAnswerIncorrect  = answer != YES_ANSWER;
	     isAnswerIncorrect &= answer != NO_ANSWER;

	while (isAnswerIncorrect) {
		ConsoleHelper::setCursorPosition(answerPosition);
		cout << "  ";
		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> answer;

		isAnswerIncorrect  = answer != YES_ANSWER;
		isAnswerIncorrect &= answer != NO_ANSWER;
	}

	if (answer == YES_ANSWER) {
		exit(0);
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);
}

vector<Coordinate>
GameProcessor::getStartingPartsCoordinates() const {
	int nParts = car_->getPartsCount();

	vector<Coordinate> parts(nParts);

	int topX = raceField_->getWidth() / 2;
	int topY = raceField_->getHeight() - 5;

	parts[CarPart::LEFT_TOP_TIRE].setX(topX - 1);
	parts[CarPart::LEFT_TOP_TIRE].setY(topY + 1);
	parts[CarPart::LEFT_BOTTOM_TIRE].setX(topX - 1);
	parts[CarPart::LEFT_BOTTOM_TIRE].setY(topY + 3);

	parts[CarPart::CAR_HEAD].setX(topX);
	parts[CarPart::CAR_HEAD].setY(topY);
	parts[CarPart::CAR_BODY].setX(topX);
	parts[CarPart::CAR_BODY].setY(topY + 2);

	parts[CarPart::RIGHT_TOP_TIRE].setX(topX + 1);
	parts[CarPart::RIGHT_TOP_TIRE].setY(topY + 1);
	parts[CarPart::RIGHT_BOTTOM_TIRE].setX(topX + 1);
	parts[CarPart::RIGHT_BOTTOM_TIRE].setY(topY + 3);

	return parts;
}

void
GameProcessor::alternateBorders() const {
	int width = raceField_->getWidth();

	Coordinate leftBorder(0, 0);
	Coordinate rightBorder(width - 1, 0);

	bool isSecondTick = nGameTicks_ % 2 == 0;

	if (isSecondTick) {
		raceField_->setBlockType(leftBorder,  BORDER_TWO);
		raceField_->setBlockType(rightBorder, BORDER_TWO);
	}
	else {
		raceField_->setBlockType(leftBorder,  BORDER_ONE);
		raceField_->setBlockType(rightBorder, BORDER_ONE);
	}
}

void
GameProcessor::drawCar() const {
	vector<Coordinate> parts = car_->getPartsCoords();

	raceField_->drawBlock(parts[CarPart::LEFT_TOP_TIRE]);
	raceField_->drawBlock(parts[CarPart::LEFT_BOTTOM_TIRE]);
	raceField_->drawBlock(parts[CarPart::CAR_HEAD]);
	raceField_->drawBlock(parts[CarPart::CAR_BODY]);
	raceField_->drawBlock(parts[CarPart::RIGHT_TOP_TIRE]);
	raceField_->drawBlock(parts[CarPart::RIGHT_BOTTOM_TIRE]);
}
