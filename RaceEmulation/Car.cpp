#include "Includes.h"

Car::Car(const Coordinate& carTop) {
	carParts_ = new vector<Coordinate>(PARTS_COUNT);

	int x = carTop.getX();
	int y = carTop.getY();

	carParts_->at(CarPart::LEFT_TOP_TIRE).setX(x - 1);
	carParts_->at(CarPart::LEFT_TOP_TIRE).setY(y + 1);
	carParts_->at(CarPart::LEFT_BOTTOM_TIRE).setX(x - 1);
	carParts_->at(CarPart::LEFT_BOTTOM_TIRE).setY(y + 3);

	carParts_->at(CarPart::CAR_HEAD).setX(x);
	carParts_->at(CarPart::CAR_HEAD).setY(y);
	carParts_->at(CarPart::CAR_BODY).setX(x);
	carParts_->at(CarPart::CAR_BODY).setY(y + 2);

	carParts_->at(CarPart::RIGHT_TOP_TIRE).setX(x + 1);
	carParts_->at(CarPart::RIGHT_TOP_TIRE).setY(y + 1);
	carParts_->at(CarPart::RIGHT_BOTTOM_TIRE).setX(x + 1);
	carParts_->at(CarPart::RIGHT_BOTTOM_TIRE).setY(y + 3);

	speedStep_    = 0.1;
	minCarSpeed_  = 1.0;
	currentSpeed_ = 5.0;
}

void
Car::move(const int& direction, const int& fieldWidth, const int& fieldHeight) {
	int dX = 0;

	int leftBorder  = 1;
	int rightBorder = fieldWidth - 2;

	switch (direction) {
	case DIRECTION_LEFT:
		if (carParts_->at(LEFT_TOP_TIRE).getX() == leftBorder) {
			return;
		}
		dX = -1;
		break;
	case DIRECTION_RIGHT:
		if (carParts_->at(RIGHT_TOP_TIRE).getX() == rightBorder) {
			return;
		}
		dX = 1;
		break;
	case DIRECTION_UP:
		currentSpeed_ += speedStep_;
		break;
	case DIRECTION_DOWN:
		currentSpeed_ -= speedStep_;

		if (currentSpeed_ <= minCarSpeed_) {
			currentSpeed_ = minCarSpeed_;
		}

		break;
	}

	for (int i = 0; i < PARTS_COUNT; i++) {
		int oldX = carParts_->at(i).getX();

		carParts_->at(i).setX(oldX + dX);
	}
}

void
Car::showSpeed() const {
	cout << "Car speed: " << setw(5) << currentSpeed_ << " m/s";
}

double Car::getSpeedStep() const {
	return speedStep_;
}

double
Car::getCurrentSpeed() {
	return currentSpeed_;
}

void
Car::setPartsCoords(const vector<Coordinate>& parts) {
	*carParts_ = parts;
}

int
Car::getPartsCount() const {
	return PARTS_COUNT;
}

const vector<Coordinate>&
Car::getPartsCoords() const {
	return *carParts_;
}

double
Car::getMinSpeed() const {
	return minCarSpeed_;
}

