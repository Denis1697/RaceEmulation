#include "Includes.h"

Car::Car() : carParts_(nullptr), speedStep_(0.1), 
             minCarSpeed_(1.0),  currentSpeed_(5.0) {}

Car::Car(const Coordinate& carTop) {
	carParts_ = new vector<Coordinate>(EnumHelper::PARTS_COUNT);

	int x = carTop.getX();
	int y = carTop.getY();

	carParts_->at(EnumHelper::eCarPart::LEFT_TOP_TIRE).setX(x - 1);
	carParts_->at(EnumHelper::eCarPart::LEFT_TOP_TIRE).setY(y + 1);
	carParts_->at(EnumHelper::eCarPart::LEFT_BOTTOM_TIRE).setX(x - 1);
	carParts_->at(EnumHelper::eCarPart::LEFT_BOTTOM_TIRE).setY(y + 3);
							  
	carParts_->at(EnumHelper::eCarPart::CAR_HEAD).setX(x);
	carParts_->at(EnumHelper::eCarPart::CAR_HEAD).setY(y);
	carParts_->at(EnumHelper::eCarPart::CAR_BODY).setX(x);
	carParts_->at(EnumHelper::eCarPart::CAR_BODY).setY(y + 2);
							  
	carParts_->at(EnumHelper::eCarPart::RIGHT_TOP_TIRE).setX(x + 1);
	carParts_->at(EnumHelper::eCarPart::RIGHT_TOP_TIRE).setY(y + 1);
	carParts_->at(EnumHelper::eCarPart::RIGHT_BOTTOM_TIRE).setX(x + 1);
	carParts_->at(EnumHelper::eCarPart::RIGHT_BOTTOM_TIRE).setY(y + 3);

	speedStep_    = 0.1;
	minCarSpeed_  = 1.0;
	currentSpeed_ = 5.0;
}

Car::Car(const Car& car) {
	carParts_ = new vector<Coordinate>(EnumHelper::PARTS_COUNT);
	vector<Coordinate> newPartsCoords = car.getPartsCoords();

	for (int i = 0; i < EnumHelper::PARTS_COUNT; i++) {
		carParts_->at(i) = newPartsCoords[i];
	}
}

Car::~Car() {
	delete carParts_;
}

Car& Car::operator=(const Car& car) {
	if (this != &car) {
		delete carParts_;
		carParts_ = new vector<Coordinate>(EnumHelper::PARTS_COUNT);
		vector<Coordinate> newPartsCoords = car.getPartsCoords();

		for (int i = 0; i < EnumHelper::PARTS_COUNT; i++) {
			carParts_->at(i) = newPartsCoords[i];
		}
	}
	return *this;
}

void
Car::move(const int& direction, const int& fieldWidth, const int& fieldHeight) {
	int dX = 0;

	int leftBorder  = 1;
	int rightBorder = fieldWidth - 2;

	switch (direction) {
	    case EnumHelper::DIRECTION_LEFT:
	    	if (carParts_->at(EnumHelper::LEFT_TOP_TIRE).getX() == leftBorder) {
	    		return;
	    	}
	    	dX = -1;
	    	break;
	    case EnumHelper::DIRECTION_RIGHT:
	    	if (carParts_->at(EnumHelper::RIGHT_TOP_TIRE).getX() == rightBorder) {
	    		return;
	    	}
	    	dX = 1;
	    	break;
	    case EnumHelper::DIRECTION_UP:
	    	currentSpeed_ += speedStep_;
	    	break;
	    case EnumHelper::DIRECTION_DOWN:
	    	currentSpeed_ -= speedStep_;
	    
	    	if (currentSpeed_ <= minCarSpeed_) {
	    		currentSpeed_ = minCarSpeed_;
	    	}
	    
	    	break;
		default:
			break;
	}

	for (int i = 0; i < EnumHelper::PARTS_COUNT; i++) {
		int oldX = carParts_->at(i).getX();

		carParts_->at(i).setX(oldX + dX);
	}
}

double 
Car::getSpeedStep() const {
	return speedStep_;
}

double
Car::getCurrentSpeed() const {
	return currentSpeed_;
}

void
Car::setPartsCoords(const vector<Coordinate>& parts) {
	*carParts_ = parts;
}

int
Car::getPartsCount() const {
	return EnumHelper::PARTS_COUNT;
}

const vector<Coordinate>&
Car::getPartsCoords() const {
	return *carParts_;
}

void 
Car::setMinSpeed(const double& minCarSpeed) {
	minCarSpeed_ = minCarSpeed;
}

void 
Car::setSpeedStep(const double& speedStep) {
	speedStep_ = speedStep;
}

void 
Car::setCurrentSpeed(const double& currentSpeed) {
	currentSpeed_ = currentSpeed;
}

double
Car::getMinSpeed() const {
	return minCarSpeed_;
}

