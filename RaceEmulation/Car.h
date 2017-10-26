#ifndef __CAR_H__
#define __CAR_H__

class Car
{
public:
	Car(const Coordinate& carTop);

	void						move(const int& direction, const int& fieldWidth, 
									 const int& fieldHeight);
	void						showSpeed()								const;
	const vector<Coordinate>&	getPartsCoords()							const;
	double						getMinSpeed()								const;
	double						getSpeedStep()								const;
	double						getCurrentSpeed();
	void						setPartsCoords(const vector<Coordinate>& parts);
	int							getPartsCount()							const;

	enum Direction
	{
		DIRECTION_UP = 72,
		DIRECTION_LEFT = 75,
		DIRECTION_RIGHT = 77,
		DIRECTION_DOWN = 80
	};
	enum CarPart
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

	const int PARTS_COUNT = 6;

	double minCarSpeed_;
	double speedStep_;
	double currentSpeed_;	
};

#endif