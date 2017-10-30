#ifndef __CAR_H__
#define __CAR_H__

class Car
{
public:
	Car();
	~Car();
	Car(const Coordinate& carTop);
	Car(const Car& car);
	Car & operator=(const Car& car); 

	const vector<Coordinate>& getPartsCoords()                           const;
	double              getMinSpeed()                                    const;
	double              getSpeedStep()                                   const;
	int                 getPartsCount()                                  const;
	double              getCurrentSpeed()                                const;
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