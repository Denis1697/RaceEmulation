#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor();
	~GameProcessor();

	bool         isCarCrushed(const int& direction = 0)          const;
	int          getTraveledDistance()                           const;
	void         computeGameTick();
	void         computeCarMove(const int& direction);
	void         setRaceField(RaceField* raceField);
	const Car&   getCar()                                        const;
	void         drawCar()                                       const;
	void         placeCar(const vector<Coordinate>& oldPosition);
	void         setCar(const Car& car);
private:	     
	void         alternateBorders()                              const;

	RaceField*  raceField_;
	Car         car_;
	int         nGameTicks_;
	const int   ONE_SECOND = 1000;
};

#endif