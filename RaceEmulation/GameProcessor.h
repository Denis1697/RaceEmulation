#ifndef __GAMEPROCESSOR_H__
#define __GAMEPROCESSOR_H__

class GameProcessor
{
public:
	GameProcessor(RaceField * field = nullptr);

	const	RaceField&		getRaceField()								const;

	bool					isCarCrushed(const int& xDirection = 0)		const; //-1 for the left, 1 for the right, 0 for up
	int						getLeftTopCarX()							const;
	int						getLeftTopCarY()							const;
	void					placePlayerCar();
	void					makeGameTick();
	void					gameOver()									const;
private:
	RaceField * raceField_;
	int leftTopCarX_;
	int leftTopCarY_;
	int gameTicksNo_;
};

#endif