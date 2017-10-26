#include "Includes.h"
#include "Car.h"
GameProcessor::GameProcessor(RaceField * field, Car * car, Timer * timer)
{
	raceField_ = field;
	car_ = car;
	timer_ = timer;
	gameTicksNo_ = 0;
	traveledDistance_ = 0;
}

GameProcessor::~GameProcessor()
{
	delete car_;
	car_ = nullptr;

	delete raceField_;
	raceField_ = nullptr;

	delete timer_;
	timer_ = nullptr;
}

bool 
GameProcessor::isCarCrushed(const int& direction) const
{
	vector<Coordinate> parts = car_->getCarPartsCoords();

	int topCarX = parts[Car::CAR_TOP].getX();
	int topCarY = parts[Car::CAR_TOP].getY();

	switch (direction)
	{
	case Car::DIRECTION_UP:
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType({ topCarX + i - 1, topCarY}) == RaceField::OBSTACLE)
				return true;
		break;
	case Car::DIRECTION_LEFT:
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType({ topCarX - 1, topCarY + i + 1 }) == RaceField::OBSTACLE)
				return true;
		break;
	case Car::DIRECTION_RIGHT:
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType({ topCarX + 1, topCarY + i + 1 }) == RaceField::OBSTACLE)
				return true;
		break;
	}		

	return false;
}

void
GameProcessor::placeCar(const vector<Coordinate>& oldPosition)
{
	raceField_->setBlockType(oldPosition[Car::LEFT_TOP_TIRE],		RaceField::EMPTY);
	raceField_->setBlockType(oldPosition[Car::LEFT_BOTTOM_TIRE],	RaceField::EMPTY);
	raceField_->setBlockType(oldPosition[Car::CAR_TOP],				RaceField::EMPTY);
	raceField_->setBlockType(oldPosition[Car::CAR_TORSO],			RaceField::EMPTY);
	raceField_->setBlockType(oldPosition[Car::RIGHT_TOP_TIRE],		RaceField::EMPTY);
	raceField_->setBlockType(oldPosition[Car::RIGHT_BOTTOM_TIRE],	RaceField::EMPTY);

	raceField_->drawBlock(oldPosition[Car::LEFT_TOP_TIRE]);
	raceField_->drawBlock(oldPosition[Car::LEFT_BOTTOM_TIRE]);
	raceField_->drawBlock(oldPosition[Car::CAR_TOP]);
	raceField_->drawBlock(oldPosition[Car::CAR_TORSO]);
	raceField_->drawBlock(oldPosition[Car::RIGHT_TOP_TIRE]);
	raceField_->drawBlock(oldPosition[Car::RIGHT_BOTTOM_TIRE]);

	vector<Coordinate> parts = car_->getCarPartsCoords();

	raceField_->setBlockType(parts[Car::LEFT_TOP_TIRE],		RaceField::CAR_TIRE);
	raceField_->setBlockType(parts[Car::LEFT_BOTTOM_TIRE],	RaceField::CAR_TIRE);
	raceField_->setBlockType(parts[Car::CAR_TOP],			RaceField::CAR_TOP);
	raceField_->setBlockType(parts[Car::CAR_TORSO],			RaceField::CAR_TORSO);
	raceField_->setBlockType(parts[Car::RIGHT_TOP_TIRE],	RaceField::CAR_TIRE);
	raceField_->setBlockType(parts[Car::RIGHT_BOTTOM_TIRE],	RaceField::CAR_TIRE);
}

void
GameProcessor::makeGameTick()
{
	int width = raceField_->getWidth();
	int height = raceField_->getHeight();


	for (int j = height-1; j > 0; j--)
	{
		for (int i = 0; i < width; i++)
		{

			int upperBlockType = raceField_->getBlockType({ i, j - 1 });
			int currentBlockType = raceField_->getBlockType({ i, j });

			bool isItCar = (upperBlockType == RaceField::CAR_TIRE);
			isItCar |= (upperBlockType == RaceField::CAR_TORSO);
			isItCar |= (upperBlockType == RaceField::CAR_TOP);
			isItCar |= (currentBlockType == RaceField::CAR_TIRE);
			isItCar |= (currentBlockType == RaceField::CAR_TORSO);
			isItCar |= (currentBlockType == RaceField::CAR_TOP);

			if (!isItCar)
				raceField_->setBlockType({ i, j }, upperBlockType);
		}
	}

	alternateBorders();

	bool isComplicated = (strcmp(typeid(*raceField_).name(), typeid(ComplicatedField).name()) == 0);
	bool isEasy = (strcmp(typeid(*raceField_).name(), typeid(EasyField).name()) == 0);

	if (gameTicksNo_ % 8 == 0)
	{
		if (isComplicated)
			raceField_->placeObstacle();
		else if (isEasy)
		{
			raceField_->placeObstacle();
			raceField_->placeObstacle();
		}
	}
	else
		for (int i = 1; i < width-1; i++)
			raceField_->setBlockType({ i, 0 }, RaceField::EMPTY);

	if (isCarCrushed(Car::DIRECTION_UP))
		gameOver();

	gameTicksNo_++;
	traveledDistance_ = gameTicksNo_;
	
	Sleep(1000/static_cast<int>(car_->getCurrentSpeed()));
}

void 
GameProcessor::gameOver() const
{
	ConsoleHelper::drawWindow({ 44, 9 }, { 75, 11 });
	ConsoleHelper::setCursorPosition({ 45, 10 });
	cout << "Sorry, your car has crushed...";
	ConsoleHelper::setCursorPosition({ 45, 13 });
	system("pause");
	exit(0);
}

void 
GameProcessor::processCarMove(const int& direction)
{
	vector<Coordinate> parts = car_->getCarPartsCoords();
	vector<Coordinate> oldParts(6);

	for (int i = 0; i < 6; i++)
	{
		oldParts[i].setX(parts[i].getX());
		oldParts[i].setY(parts[i].getY());
	}
	
	car_->moveCar(direction, raceField_->getWidth(), raceField_->getHeight());

	if (isCarCrushed(direction))
		gameOver();
	else
	{
		placeCar(oldParts); 

		drawCar(); 
	}
}

void 
GameProcessor::showTraveledDistance() const
{
	cout << "Traveled distance: " << traveledDistance_ << " m";
}

int 
GameProcessor::startingMode() const
{
	ConsoleHelper::drawWindow({ 24, 9 }, { 40, 14 });
	ConsoleHelper::setCursorPosition({ 25, 10 });
	cout << "Select the mode";
	ConsoleHelper::setCursorPosition({ 25, 11 });
	cout << "1. Obstacles";
	ConsoleHelper::setCursorPosition({ 25, 12 });
	cout << "2. Cars";
	ConsoleHelper::setCursorPosition({ 25, 13 });
	cout << "Answer: ";

	int answer;

	cin >> answer;

	while (answer < 1 || answer > 2)
	{
		ConsoleHelper::setCursorPosition({ 33, 13 });
		cin >> answer;
	}
	
	ConsoleHelper::clearWindow({ 24, 9 }, { 40, 14 });

	return answer;
}

void 
GameProcessor::setCar(Car * car)
{
	car_ = car;
}

void 
GameProcessor::setRaceField(RaceField * raceField)
{
	raceField_ = raceField;
}

void 
GameProcessor::setTimer(Timer * timer)
{
	timer_ = timer;
}

void 
GameProcessor::showStatistics() const
{
	ConsoleHelper::drawWindow({ 44, 4 }, { 70, 8 });
	ConsoleHelper::setCursorPosition({ 45, 5 });
	cout << "Time: ";
	timer_->showTime();
	ConsoleHelper::setCursorPosition({ 45, 6 });
	showTraveledDistance();
	ConsoleHelper::setCursorPosition({ 45, 7 });
	car_->showCarSpeed();
}

void 
GameProcessor::setPause() const
{
	ConsoleHelper::drawWindow({ 44, 9 }, { 50, 11 });
	ConsoleHelper::setCursorPosition({ 45, 10 });
	cout << "Pause";

	ConsoleHelper::setCursorPosition({ 45, 13 });
	system("pause");

	ConsoleHelper::clearWindow({ 44, 13 }, { 90, 13 });
	ConsoleHelper::clearWindow({ 44, 9 }, { 50, 11 });
}

void 
GameProcessor::leaveTheGame() const
{
	ConsoleHelper::drawWindow({ 44, 9 }, { 60, 14 });
	ConsoleHelper::setCursorPosition({ 45, 10 });
	cout << "Quit?";
	ConsoleHelper::setCursorPosition({ 45, 11 });
	cout << "1. Yes";
	ConsoleHelper::setCursorPosition({ 45, 12 });
	cout << "2. No";
	ConsoleHelper::setCursorPosition({ 45, 13 });
	cout << "Answer: ";

	int answer;

	cin >> answer;

	while (answer < 1 || answer > 2)
	{
		ConsoleHelper::setCursorPosition({ 53, 13 });
		cout << "  ";
		ConsoleHelper::setCursorPosition({ 53, 13 });
		cin >> answer;
	}

	if (answer == 1)
		exit(0);

	ConsoleHelper::clearWindow({ 44, 9 }, { 60, 14 });
}

vector<Coordinate> 
GameProcessor::getStartingPartsCoordinates() const
{
	vector<Coordinate> parts(6);

	int topX = raceField_->getWidth() / 2;
	int topY = raceField_->getHeight() - 5;

	parts[Car::LEFT_TOP_TIRE].setX(topX-1);
	parts[Car::LEFT_TOP_TIRE].setY(topY+1);
	parts[Car::LEFT_BOTTOM_TIRE].setX(topX - 1);
	parts[Car::LEFT_BOTTOM_TIRE].setY(topY + 3);

	parts[Car::CAR_TOP].setX(topX);
	parts[Car::CAR_TOP].setY(topY);
	parts[Car::CAR_TORSO].setX(topX);
	parts[Car::CAR_TORSO].setY(topY + 2);

	parts[Car::LEFT_TOP_TIRE].setX(topX + 1);
	parts[Car::LEFT_TOP_TIRE].setY(topY + 1);
	parts[Car::LEFT_BOTTOM_TIRE].setX(topX + 1);
	parts[Car::LEFT_BOTTOM_TIRE].setY(topY + 3);

	return parts;
}

void 
GameProcessor::alternateBorders() const
{
	int width = raceField_->getWidth();

	if (gameTicksNo_ % 2 == 0)
	{
		raceField_->setBlockType({ 0,0 }, RaceField::BORDER_TWO);
		raceField_->setBlockType({ width - 1, 0 }, RaceField::BORDER_TWO);
	}
	else
	{
		raceField_->setBlockType({ 0,0 }, RaceField::BORDER_ONE);
		raceField_->setBlockType({ width - 1, 0 }, RaceField::BORDER_ONE);
	}
}

void
GameProcessor::drawCar() const
{
	vector<Coordinate> parts = car_->getCarPartsCoords();

	raceField_->drawBlock(parts[Car::LEFT_TOP_TIRE]);
	raceField_->drawBlock(parts[Car::LEFT_BOTTOM_TIRE]);
	raceField_->drawBlock(parts[Car::CAR_TOP]);
	raceField_->drawBlock(parts[Car::CAR_TORSO]);
	raceField_->drawBlock(parts[Car::RIGHT_TOP_TIRE]);
	raceField_->drawBlock(parts[Car::RIGHT_BOTTOM_TIRE]);
}
