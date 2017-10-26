#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor(RaceField * field = nullptr, Car * car = nullptr, Timer * timer = nullptr);
	~GameProcessor();

	bool		isCarCrushed(const int& direction = 0)				const;
	void		placeCar(const vector<Coordinate>& oldPosition);	
	void		drawCar()											const;
	void		processCarMove(const int& direction);
	void		makeGameTick();
	void		gameOver()											const;
	void		showTraveledDistance()								const;
	int			startingMode()										const;
	void		setCar(Car * car);
	void		setRaceField(RaceField * raceField);
	void		setTimer(Timer * timer);
	void		showStatistics()									const;
	void		setPause()											const; 
	void		leaveTheGame()										const;
	
	enum ServiceButton
	{
		SPACE = 32,
		ESCAPE = 27
	};

private:
	vector<Coordinate>		getStartingPartsCoordinates()			const;
	void					alternateBorders()						const;

	RaceField*	raceField_;
	Car*		car_;
	Timer*		timer_;

	int gameTicksNo_;
	int traveledDistance_;

};

#endif