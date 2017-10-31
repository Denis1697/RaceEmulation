#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor();
	~GameProcessor();

	bool         isCarCrushed(const int& direction = 0)          const;
	void         computeGameTick();
	void         computeCarMove(const int& direction);
	int          getTraveledDistance()                           const;
	void         setRaceField(RaceField* raceField);		        
	const Car&   getCar()                                        const;
	void         setCar(const Car& car);
	void         drawCar()                                       const;
	void         placeCar(const vector<Coordinate>& oldPosition);
private:	            
	void         alternateBorders()                              const;

	RaceField*   raceField_;
	Car          car_;
	int          nGameTicks_;
};

#endif