#include "Includes.h"

GameProcessor::GameProcessor(RaceField * field)
{
	raceField_ = field;
	leftTopCarX_ = 4;
	leftTopCarY_ = 8;
	gameTicksNo_ = 0;
}

const RaceField&
GameProcessor::getRaceField() const
{
	return *raceField_;
}

//-1 for the left, 1 for the right, 0 for up
bool 
GameProcessor::isCarCrushed(const int& xDirection) const 
{
	switch (xDirection)
	{
	case 0:		//up
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType(leftTopCarX_ + i, leftTopCarY_ + 1) == RaceField::OBSTACLE)
				return true;
		break;
	case -1:	//left
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType(leftTopCarX_, leftTopCarY_ + i - 1) == RaceField::OBSTACLE)
				return true;
		break;
	case 1:		//right
		for (int i = 0; i < 3; i++)
			if (raceField_->getBlockType(leftTopCarX_ + 3, leftTopCarY_ + i - 1) == RaceField::OBSTACLE)
				return true;
		break;
	}		

	return false;
}

int 
GameProcessor::getLeftTopCarX() const
{
	return leftTopCarX_;
}

int 
GameProcessor::getLeftTopCarY() const
{
	return leftTopCarY_;
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
	{
		raceField_->generateObstacle();

		for (int i = 0; i < width; i++)
		{
			int bufferBlockType = raceField_->getBufferBlockType(i);
			
			if (bufferBlockType == RaceField::OBSTACLE)
				raceField_->setBlockType(i, 0, bufferBlockType);
		}

		raceField_->clearBuffer();
	}
	else
	{
		for (int i = 1; i < width-1; i++)
			raceField_->setBlockType(i, 0, RaceField::EMPTY);
	}

	if (isCarCrushed(0))
		gameOver();

	system("cls");
	raceField_->drawField();

	gameTicksNo_++;
	
	Sleep(1000);
}

void GameProcessor::gameOver() const
{
	system("pause");
	system("cls");
	cout << "Sorry, you are dead!";
	exit(0);
}
