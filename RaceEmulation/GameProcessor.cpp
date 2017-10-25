#include "Includes.h"

GameProcessor::GameProcessor(RaceField * field)
{
	raceField_ = field;

	topCarX_ = raceField_->getWidth() / 2;
	topCarY_ = raceField_->getHeight() - 5;

	gameTicksNo_ = 0;

	speedStep_ = 0.1;
	minCarSpeed_ = 1;
	currentSpeed_ = 5;

	traveledDistance_ = 0;
}

bool 
GameProcessor::isCarCrushed(const int& direction) const
{
	switch (direction)
	{
	case DIRECTION_UP:
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType(topCarX_ + i - 1, topCarY_ ) == RaceField::OBSTACLE)
				return true;
		break;
	case DIRECTION_LEFT:
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType(topCarX_ - 2, topCarY_ + i + 1) == RaceField::OBSTACLE)
				return true;
		break;
	case DIRECTION_RIGHT:
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType(topCarX_ + 2, topCarY_ + i + 1) == RaceField::OBSTACLE)
				return true;
		break;
	}		

	return false;
}

int 
GameProcessor::getLeftTopCarX() const
{
	return topCarX_;
}

int 
GameProcessor::getLeftTopCarY() const
{
	return topCarY_;
}

void
GameProcessor::placePlayerCar(const int& x, const int& y)
{
	int height = raceField_->getHeight();
	int width = raceField_->getWidth();

	if (x < 2 || x > width - 2 || y < height / 2 || y > height - 2)
		return;

	raceField_->setBlockType(topCarX_ - 1,	topCarY_ + 1,	RaceField::EMPTY);
	raceField_->setBlockType(topCarX_ - 1,	topCarY_ + 3,	RaceField::EMPTY);
	raceField_->setBlockType(topCarX_,		topCarY_,		RaceField::EMPTY);
	raceField_->setBlockType(topCarX_,		topCarY_ + 2,	RaceField::EMPTY);
	raceField_->setBlockType(topCarX_ + 1,	topCarY_ + 1,	RaceField::EMPTY);
	raceField_->setBlockType(topCarX_ + 1,	topCarY_ + 3,	RaceField::EMPTY);

	raceField_->setBlockType(x - 1,			y + 1,			RaceField::CAR_TIRE);
	raceField_->setBlockType(x - 1,			y + 3,			RaceField::CAR_TIRE);
	raceField_->setBlockType(x,				y,				RaceField::CAR_TOP);
	raceField_->setBlockType(x,				y + 2,			RaceField::CAR_TORSO);
	raceField_->setBlockType(x + 1,			y + 1,			RaceField::CAR_TIRE);
	raceField_->setBlockType(x + 1,			y + 3,			RaceField::CAR_TIRE);


	topCarX_ = x;
	topCarY_ = y;
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
			
			int upperBlockType = raceField_->getBlockType(i, j - 1);
			int currentBlockType = raceField_->getBlockType(i, j);

			bool isItCar = (upperBlockType == RaceField::CAR_TIRE);
			isItCar |= (upperBlockType == RaceField::CAR_TORSO);
			isItCar |= (upperBlockType == RaceField::CAR_TOP);
			isItCar |= (currentBlockType == RaceField::CAR_TIRE);
			isItCar |= (currentBlockType == RaceField::CAR_TORSO);
			isItCar |= (currentBlockType == RaceField::CAR_TOP);

			if (!isItCar)
				raceField_->setBlockType(i, j, upperBlockType);
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
			raceField_->setBlockType(i, 0, RaceField::EMPTY);

	if (isCarCrushed(DIRECTION_UP))
		gameOver();

	gameTicksNo_++;
	traveledDistance_ = gameTicksNo_;
	
	Sleep(1000/static_cast<int>(currentSpeed_));
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
GameProcessor::moveCar(const int& direction)
{
	int dX = 0;

	switch (direction)
	{
	case DIRECTION_LEFT:
		if (topCarX_ - 1 == 1)
			return;

		dX = -1;
		break;
	case DIRECTION_RIGHT:
		if (topCarX_ + 1 == raceField_->getWidth() - 2)
			return;

		dX = 1;
		break;
	case DIRECTION_UP:
		currentSpeed_ += speedStep_;
		break;
	case DIRECTION_DOWN:
		currentSpeed_ -= speedStep_;

		if (currentSpeed_ <= minCarSpeed_)
			currentSpeed_ = minCarSpeed_;

		break;
	}

	if (isCarCrushed(direction))
		gameOver();
	else
		placePlayerCar(topCarX_ + dX, topCarY_);

	drawCar();
}

void 
GameProcessor::placeObstacle()
{
	int width = raceField_->getWidth();

	raceField_->generateObstacle();

	for (int i = 0; i < width; i++)
	{
		int bufferBlockType = raceField_->getBufferBlockType(i);

		if (bufferBlockType == RaceField::OBSTACLE)
			raceField_->setBlockType(i, 0, bufferBlockType);
	}

	raceField_->clearBuffer();
}

void 
GameProcessor::showTraveledDistance() const
{
	cout << "Traveled distance: " << traveledDistance_ << " m";
}

void 
GameProcessor::showCarSpeed() const
{
	cout << "Car speed: " << setw(3) <<  currentSpeed_ << " m/s";

}

void 
GameProcessor::alternateBorders() const
{
	int width = raceField_->getWidth();

	if (gameTicksNo_ % 2 == 0)
	{
		raceField_->setBlockType(0, 0, RaceField::BORDER_TWO);
		raceField_->setBlockType(width - 1, 0, RaceField::BORDER_TWO);
	}
	else
	{
		raceField_->setBlockType(0, 0, RaceField::BORDER_ONE);
		raceField_->setBlockType(width - 1, 0, RaceField::BORDER_ONE);
	}
}

void GameProcessor::drawCar() const
{
	raceField_->drawBlock(topCarX_ - 1, topCarY_ + 1);
	raceField_->drawBlock(topCarX_ - 1, topCarY_ + 3);

	raceField_->drawBlock(topCarX_, topCarY_);
	raceField_->drawBlock(topCarX_, topCarY_ + 2);

	raceField_->drawBlock(topCarX_ + 1, topCarY_ + 1);
	raceField_->drawBlock(topCarX_ + 1, topCarY_ + 3);
}
