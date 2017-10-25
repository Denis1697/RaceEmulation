#include "Includes.h"
#include "Car.h"
GameProcessor::GameProcessor(RaceField * field, Car * car)
{
	raceField_ = field;

	if (car == nullptr)
		car->setCarPartsCoords(getStartingPartsCoordinates());

	car_ = car;

	gameTicksNo_ = 0;

	traveledDistance_ = 0;
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

	if (gameTicksNo_ % 5 == 0)
	{
		raceField_->placeObstacle();
		raceField_->placeObstacle();
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
	system("pause");
	system("cls");
	cout << "Sorry, you are dead!";
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
