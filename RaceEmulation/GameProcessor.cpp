#include "Includes.h"
GameProcessor::GameProcessor() : raceField_(nullptr), nGameTicks_(0) {}

GameProcessor::~GameProcessor() {
	delete raceField_;
	raceField_ = nullptr;
}

bool
GameProcessor::isCarCrushed(const int& direction) const {
	vector<Coordinate> parts = car_.getPartsCoords();

	int topCarX = parts[EnumHelper::eCarPart::CAR_HEAD].getX();
	int topCarY = parts[EnumHelper::eCarPart::CAR_HEAD].getY();

	int carWidth  = 3;
	int carHeight = 3;

	switch (direction) {
	    case EnumHelper::eDirection::DIRECTION_UP:
	    	for (int i = 0; i < carWidth; i++) {
	    		if (raceField_->getBlockType({ topCarX + i - 1,
	    			topCarY }) == EnumHelper::OBSTACLE) {
	    			return true;
	    		}
	    	}
	    	break;
	    case EnumHelper::eDirection::DIRECTION_LEFT:
	    	for (int i = 0; i < carHeight; i++) {
	    		if (raceField_->getBlockType({ topCarX - 1,
	    			topCarY + i + 1 }) == EnumHelper::OBSTACLE) {
	    			return true;
	    		}
	    	}
	    	break;
	    case EnumHelper::eDirection::DIRECTION_RIGHT:
	    	for (int i = 0; i < carHeight; i++) {
	    		if (raceField_->getBlockType({ topCarX + 1,
	    			topCarY + i + 1 }) == EnumHelper::OBSTACLE) {
	    			return true;
	    		}
	    	}
	    
	    	break;
	    default:
	    	break;
	}

	return false;
}

void
GameProcessor::placeCar(const vector<Coordinate>& oldPosition) {
	raceField_->setBlockType(oldPosition[EnumHelper::eCarPart::LEFT_TOP_TIRE],
		EnumHelper::eBlockType::EMPTY);
	raceField_->setBlockType(oldPosition[EnumHelper::eCarPart::LEFT_BOTTOM_TIRE],
		EnumHelper::eBlockType::EMPTY);
	raceField_->setBlockType(oldPosition[EnumHelper::eCarPart::CAR_HEAD],
		EnumHelper::eBlockType::EMPTY);
	raceField_->setBlockType(oldPosition[EnumHelper::eCarPart::CAR_BODY],
		EnumHelper::eBlockType::EMPTY);
	raceField_->setBlockType(oldPosition[EnumHelper::eCarPart::RIGHT_TOP_TIRE],
		EnumHelper::eBlockType::EMPTY);
	raceField_->setBlockType(oldPosition[EnumHelper::eCarPart::RIGHT_BOTTOM_TIRE],
		EnumHelper::eBlockType::EMPTY);

	raceField_->drawBlock(oldPosition[EnumHelper::eCarPart::LEFT_TOP_TIRE]);
	raceField_->drawBlock(oldPosition[EnumHelper::eCarPart::LEFT_BOTTOM_TIRE]);
	raceField_->drawBlock(oldPosition[EnumHelper::eCarPart::CAR_HEAD]);
	raceField_->drawBlock(oldPosition[EnumHelper::eCarPart::CAR_BODY]);
	raceField_->drawBlock(oldPosition[EnumHelper::eCarPart::RIGHT_TOP_TIRE]);
	raceField_->drawBlock(oldPosition[EnumHelper::eCarPart::RIGHT_BOTTOM_TIRE]);

	vector<Coordinate> parts = car_.getPartsCoords();

	raceField_->setBlockType(parts[EnumHelper::eCarPart::LEFT_TOP_TIRE],
		EnumHelper::eBlockType::CAR_TIRE);
	raceField_->setBlockType(parts[EnumHelper::eCarPart::LEFT_BOTTOM_TIRE],
		EnumHelper::eBlockType::CAR_TIRE);
	raceField_->setBlockType(parts[EnumHelper::eCarPart::CAR_HEAD],
		EnumHelper::eBlockType::CAR_TOP);
	raceField_->setBlockType(parts[EnumHelper::eCarPart::CAR_BODY],
		EnumHelper::eBlockType::CAR_TORSO);
	raceField_->setBlockType(parts[EnumHelper::eCarPart::RIGHT_TOP_TIRE],
		EnumHelper::eBlockType::CAR_TIRE);
	raceField_->setBlockType(parts[EnumHelper::eCarPart::RIGHT_BOTTOM_TIRE],
		EnumHelper::eBlockType::CAR_TIRE);
}

const RaceField& 
GameProcessor::getField() const {
	return *raceField_;
}

int
GameProcessor::computeGameTick() {
	int width = raceField_->getWidth();
	int height = raceField_->getHeight();

	for (int j = height - 1; j > 0; j--) {
		for (int i = 0; i < width; i++) {

			int upperBlockType   = raceField_->getBlockType({ i, j - 1 });
			int currentBlockType = raceField_->getBlockType({ i, j });

			bool isItCar  = (upperBlockType == EnumHelper::eBlockType::CAR_TIRE);
			     isItCar |= (upperBlockType == EnumHelper::eBlockType::CAR_TORSO);
			     isItCar |= (upperBlockType == EnumHelper::eBlockType::CAR_TOP);
			     isItCar |= (currentBlockType == EnumHelper::eBlockType::CAR_TIRE);
			     isItCar |= (currentBlockType == EnumHelper::eBlockType::CAR_TORSO);
			     isItCar |= (currentBlockType == EnumHelper::eBlockType::CAR_TOP);

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
			raceField_->setBlockType({ i, 0 }, EnumHelper::EMPTY);
		}
	}

	if (isCarCrushed(EnumHelper::eDirection::DIRECTION_UP)) {
		ConsoleNotifier::gameOver();
		return EnumHelper::eCarMoveResult::FAIL;
	}

	nGameTicks_++;
	
	int currentSpeed = car_.getCurrentSpeed();
	int drawSpeed = EnumHelper::ONE_SECOND / currentSpeed;

	Sleep(drawSpeed);
	return EnumHelper::eCarMoveResult::SUCCESS;
}

int
GameProcessor::computeCarMove(const int& direction) {
	int nParts = car_.getPartsCount();

	vector<Coordinate> parts = car_.getPartsCoords();
	vector<Coordinate> oldParts(nParts);

	for (int i = 0; i < nParts; i++) {
		oldParts[i].setX(parts[i].getX());
		oldParts[i].setY(parts[i].getY());
	}

	car_.move(direction, raceField_->getWidth(), raceField_->getHeight());

	if (isCarCrushed(direction)) {
		ConsoleNotifier::gameOver();
		return EnumHelper::FAIL;
	}
	else {
		placeCar(oldParts);
		drawCar();
	}
	return EnumHelper::SUCCESS;
}

void
GameProcessor::setCar(const Car& car) {
	car_ = car;
}

void
GameProcessor::setRaceField(RaceField* raceField) {
	raceField_ = raceField;
}

Car&
GameProcessor::getCar() {
	return car_;
}

int
GameProcessor::getTraveledDistance() const {
	return nGameTicks_;
}

void
GameProcessor::alternateBorders() const {
	int width = raceField_->getWidth();

	Coordinate leftBorder(0, 0);
	Coordinate rightBorder(width - 1, 0);

	bool isSecondTick = nGameTicks_ % 2 == 0;

	if (isSecondTick) {
		raceField_->setBlockType(leftBorder,  EnumHelper::BORDER_TWO);
		raceField_->setBlockType(rightBorder, EnumHelper::BORDER_TWO);
	}
	else {
		raceField_->setBlockType(leftBorder,  EnumHelper::BORDER_ONE);
		raceField_->setBlockType(rightBorder, EnumHelper::BORDER_ONE);
	}
}

void
GameProcessor::drawCar() const {
	vector<Coordinate> parts = car_.getPartsCoords();

	raceField_->drawBlock(parts[EnumHelper::eCarPart::LEFT_TOP_TIRE]);
	raceField_->drawBlock(parts[EnumHelper::eCarPart::LEFT_BOTTOM_TIRE]);
	raceField_->drawBlock(parts[EnumHelper::eCarPart::CAR_HEAD]);
	raceField_->drawBlock(parts[EnumHelper::eCarPart::CAR_BODY]);
	raceField_->drawBlock(parts[EnumHelper::eCarPart::RIGHT_TOP_TIRE]);
	raceField_->drawBlock(parts[EnumHelper::eCarPart::RIGHT_BOTTOM_TIRE]);
}
