#include "Includes.h"

GameProcessor::GameProcessor(RaceField * field)
{
	raceField_ = field;

	topCarX_ = 4;
	topCarY_ = 8;

	gameTicksNo_ = 0;

	speedStep_ = 25;
	minCarSpeed_ = 500;
	currentSpeed_ = 400;

	traveledDistance_ = 0;
}

bool 
GameProcessor::isCarCrushed(const int& direction) const
{
	switch (direction)
	{
	case DIRECTION_UP:
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType(topCarX_ + i - 1, topCarY_) == RaceField::OBSTACLE)
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
GameProcessor::placePlayerCar()
{
	raceField_->setBlockType(3, 9, RaceField::CAR_TIRE);
	raceField_->setBlockType(3, 11, RaceField::CAR_TIRE);
	raceField_->setBlockType(4, 8, RaceField::CAR_TOP);
	raceField_->setBlockType(4, 10, RaceField::CAR_TORSO);
	raceField_->setBlockType(5, 9, RaceField::CAR_TIRE);
	raceField_->setBlockType(5, 11, RaceField::CAR_TIRE);
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

	if (gameTicksNo_ % 2 == 0)
	{
		raceField_->setBlockType(0, 0, RaceField::BORDER_TWO);
		raceField_->setBlockType(width-1, 0, RaceField::BORDER_TWO);
	}
	else
	{
		raceField_->setBlockType(0, 0, RaceField::BORDER_ONE);
		raceField_->setBlockType(width - 1, 0, RaceField::BORDER_ONE);
	}

	if (gameTicksNo_ % 5 == 0)
		raceField_->placeObstacle();
	else
		for (int i = 1; i < width-1; i++)
			raceField_->setBlockType(i, 0, RaceField::EMPTY);

	
	//system("cls");
	//raceField_->draw();

	if (isCarCrushed(DIRECTION_UP))
		gameOver();

	gameTicksNo_++;
	traveledDistance_ = gameTicksNo_;
	
	Sleep(currentSpeed_);
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
	switch (direction)
	{
	case DIRECTION_LEFT:
		if (topCarX_ == 2)
			return;
		if (isCarCrushed(DIRECTION_LEFT))
			gameOver();
		else
		{
			raceField_->setBlockType(topCarX_ - 1, 9, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ - 2, 9, RaceField::CAR_TIRE);
			raceField_->setBlockType(topCarX_ - 1, 11, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ - 2, 11, RaceField::CAR_TIRE);

			raceField_->setBlockType(topCarX_ + 1, 9, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_, 9, RaceField::CAR_TIRE);
			raceField_->setBlockType(topCarX_ + 1, 11, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_, 11, RaceField::CAR_TIRE);

			raceField_->setBlockType(topCarX_, 8, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ - 1, 8, RaceField::CAR_TOP);

			raceField_->setBlockType(topCarX_, 10, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ - 1, 10, RaceField::CAR_TORSO);

			topCarX_--;
		}
		break;
	case DIRECTION_RIGHT:
		if (topCarX_ == raceField_->getWidth() - 3)
			return;
		if (isCarCrushed(DIRECTION_RIGHT))
			gameOver(); 
		else
		{
			raceField_->setBlockType(topCarX_ - 1, 9, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_, 9, RaceField::CAR_TIRE);
			raceField_->setBlockType(topCarX_ - 1, 11, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_, 11, RaceField::CAR_TIRE);

			raceField_->setBlockType(topCarX_ + 1, 9, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ + 2, 9, RaceField::CAR_TIRE);
			raceField_->setBlockType(topCarX_ + 1, 11, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ + 2, 11, RaceField::CAR_TIRE);

			raceField_->setBlockType(topCarX_, 8, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ + 1, 8, RaceField::CAR_TOP);

			raceField_->setBlockType(topCarX_, 10, RaceField::EMPTY);
			raceField_->setBlockType(topCarX_ + 1, 10, RaceField::CAR_TORSO);

			topCarX_++;
		}
		break;
	case DIRECTION_UP:
		system("pause");
		currentSpeed_ -= speedStep_;
		break;
	case DIRECTION_DOWN:
		system("pause");
		if (currentSpeed_ <= minCarSpeed_)
			return;
		currentSpeed_ += speedStep_;
		break;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 1, 1 });
	raceField_->draw();
}

void GameProcessor::placeObstacle()
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
