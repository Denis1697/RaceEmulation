#ifndef __CAR_H__
#define __CAR_H__

class Car
{
public:
	Car(const Coordinate& carTop);

	void					moveCar(const int& direction, const int& fieldWidth, const int& fieldHeight);
	void					showCarSpeed()									const;
	vector<Coordinate>&		getCarPartsCoords()								const;
	double					getMinCarSpeed()								const;
	double					getSpeedStep()									const;
	double					getCurrentSpeed();
	void					setCarPartsCoords(const vector<Coordinate>& parts);

	enum Direction
	{
		DIRECTION_UP = 72,
		DIRECTION_LEFT = 75,
		DIRECTION_RIGHT = 77,
		DIRECTION_DOWN = 80
	};
	enum CarParts
	{
		LEFT_TOP_TIRE,
		LEFT_BOTTOM_TIRE,
		CAR_TOP,
		CAR_TORSO,
		RIGHT_TOP_TIRE,
		RIGHT_BOTTOM_TIRE
	};

private:
	vector<Coordinate>* carParts_;

	double minCarSpeed_;
	double speedStep_;
	double currentSpeed_;	
};

#endif