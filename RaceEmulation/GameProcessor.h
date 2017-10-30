#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor();
	~GameProcessor();

	bool  isCarCrushed(const int& direction = 0)          const;
	void  drawCar()                                       const;
	int   getTraveledDistance()							  const;
	void  computeGameTick();
	void  computeCarMove(const int& direction);
	void  setRaceField(RaceField* raceField);
	const Car& getCar()                                   const;
	void  placeCar(const vector<Coordinate>& oldPosition);
	void  setCar(const Car& car);
private:
	vector<Coordinate>  getStartingPartsCoordinates()     const;
	void                alternateBorders()                const;

	RaceField*  raceField_;
	Car         car_;

	int         nGameTicks_;
	int         traveledDistance_;

	const int   ONE_SECOND = 1000;
};

#endif