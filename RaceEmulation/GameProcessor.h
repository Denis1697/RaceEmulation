#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor();
	~GameProcessor();

	int   startingMode()                                  const;
	bool  isCarCrushed(const int& direction = 0)          const;
	void  drawCar()                                       const;
	void  setPause()                                      const;
	void  leaveTheGame()                                  const;
	void  showStatistics()                                const;
	void  showTraveledDistance()                          const;
	void  gameOver();
	bool  getGameStatus();
	void  computeGameTick();
	void  setCar(Car* car);
	void  setTimer(Timer* timer);
	void  setRaceField(RaceField* raceField);
	void  computeCarMove(const int& direction);
	void  placeCar(const vector<Coordinate>& oldPosition);
private:
	vector<Coordinate>  getStartingPartsCoordinates()     const;
	void                alternateBorders()                const;

	RaceField*  raceField_;
	Car*        car_;
	Timer*      timer_;

	int         nGameTicks_;
	int         traveledDistance_;
	bool        gameStatus_;

	const int   ONE_SECOND = 1000;
};

#endif