#include "Includes.h"

Car::Car(const Coordinate& carTop)
{
	carParts_ = new vector<Coordinate>(6);
	int x = carTop.getX();
	int y = carTop.getY();

	carParts_->at(Car::LEFT_TOP_TIRE).setX(x - 1);
	carParts_->at(Car::LEFT_TOP_TIRE).setY(y + 1);
	carParts_->at(Car::LEFT_BOTTOM_TIRE).setX(x - 1);
	carParts_->at(Car::LEFT_BOTTOM_TIRE).setY(y + 3);

	carParts_->at(Car::CAR_TOP).setX(x);
	carParts_->at(Car::CAR_TOP).setY(y);
	carParts_->at(Car::CAR_TORSO).setX(x);
	carParts_->at(Car::CAR_TORSO).setY(y + 2);

	carParts_->at(Car::RIGHT_TOP_TIRE).setX(x + 1);
	carParts_->at(Car::RIGHT_TOP_TIRE).setY(y + 1);
	carParts_->at(Car::RIGHT_BOTTOM_TIRE).setX(x + 1);
	carParts_->at(Car::RIGHT_BOTTOM_TIRE).setY(y + 3);

	speedStep_ = 0.1;
	minCarSpeed_ = 1;
	currentSpeed_ = 5;
}

void 
Car::moveCar(const int& direction, const int& fieldWidth, const int& fieldHeight)
{
	int dX = 0;

	switch (direction)
	{
	case DIRECTION_LEFT:
		if (carParts_->at(LEFT_TOP_TIRE).getX() == 1)
			return;

		dX = -1;
		break;
	case DIRECTION_RIGHT:
		if (carParts_->at(RIGHT_TOP_TIRE).getX() == fieldWidth - 2)
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

	for (int i = 0; i < 6; i++)
		carParts_->at(i).setX(carParts_->at(i).getX() + dX);
}

void 
Car::showCarSpeed() const
{
	cout << "Car speed: " << setw(5) << currentSpeed_ << " m/s";
}

double Car::getSpeedStep() const
{
	return speedStep_;
}

double
Car::getCurrentSpeed()
{
	return currentSpeed_;
}

void Car::setCarPartsCoords(const vector<Coordinate>& parts)
{
	*carParts_ = parts;
}

vector<Coordinate>&
Car::getCarPartsCoords() const
{
	return *carParts_;
}

double Car::getMinCarSpeed() const
{
	return minCarSpeed_;
}

