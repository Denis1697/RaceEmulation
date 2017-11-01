#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor();
	~GameProcessor();

	bool             isCarCrushed(const int& direction = 0)          const;
	int              computeGameTick();
	int              computeCarMove(const int& direction);
	int              getTraveledDistance()                           const;
	void             setRaceField(RaceField* raceField);		        
	Car&             getCar();
	void             setCar(const Car& car);
	void             drawCar()                                       const;
	void             placeCar(const vector<Coordinate>& oldPosition);
	const RaceField& getField()                                      const;
private:	            
	void         alternateBorders()                              const;

	RaceField*   raceField_;
	Car          car_;
	int          nGameTicks_;
};

#endif