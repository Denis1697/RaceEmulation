#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor(RaceField* field = nullptr, Car* car = nullptr, 
				  Timer* timer = nullptr);
	~GameProcessor();

	int			startingMode()										const;
	bool		isCarCrushed(const int& direction = 0)				const;
	void		placeCar(const vector<Coordinate>& oldPosition);	
	void		drawCar()											const;
	void		computeCarMove(const int& direction);
	void		computeGameTick();
	void		gameOver()											const;
	void		showTraveledDistance()								const;
	void		setCar(Car* car);
	void		setRaceField(RaceField* raceField);
	void		setTimer(Timer* timer);
	void		showStatistics()									const;
	void		setPause()											const; 
	void		leaveTheGame()										const;
	
	enum ServiceButton
	{
		ENTER = 13,
		ESCAPE = 27
	};
private:
	vector<Coordinate>		getStartingPartsCoordinates()			const;
	void					alternateBorders()						const;

	RaceField*	raceField_;
	Car*		car_;
	Timer*		timer_;

	int nGameTicks_;
	int traveledDistance_;
	
	const int ONE_SECOND = 1000;
};

#endif