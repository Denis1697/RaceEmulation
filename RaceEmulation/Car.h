#ifndef __CAR_H__
#define __CAR_H__

class Car
{
public:
	Car(const Coordinate& carTop);

	const vector<Coordinate>& getPartsCoords()                           const;
	void                showSpeed()                                      const;
	double              getMinSpeed()                                    const;
	double              getSpeedStep()                                   const;
	int                 getPartsCount()                                  const;
	double              getCurrentSpeed();
	void                setPartsCoords(const vector<Coordinate>& parts);
	void                move(const int& direction, const int& fieldWidth,
		                     const int& fieldHeight);

private:
	vector<Coordinate>* carParts_;

	const int           PARTS_COUNT = 6;
	double              minCarSpeed_;
	double              speedStep_;
	double              currentSpeed_;
};

#endif