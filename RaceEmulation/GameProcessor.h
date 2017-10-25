#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor(RaceField * field = nullptr);

	bool					isCarCrushed(const int& direction = 0)			const; //-1 for the left, 1 for the right, 0 for up
	int						getLeftTopCarX()								const;
	int						getLeftTopCarY()								const;
	void					placePlayerCar(const int& x, const int& y);
	void					moveCar(const int& direction); 
	void					makeGameTick();
	void					gameOver()										const;
	void					placeObstacle();
	void					showTraveledDistance()							const;
	void					showCarSpeed()									const;
	
	enum Direction
	{
		DIRECTION_UP = 72,
		DIRECTION_LEFT = 75,
		DIRECTION_RIGHT = 77,
		DIRECTION_DOWN = 80
	};
private:
	void					alternateBorders()								const;
	void					drawCar()										const;

	RaceField * raceField_;

	int topCarX_;
	int topCarY_;

	int gameTicksNo_;

	int minCarSpeed_;
	double speedStep_;	
	double currentSpeed_;

	int traveledDistance_;

};

#endif