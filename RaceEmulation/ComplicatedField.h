#ifndef __COMPLICATEDFIELD_H__
#define __COMPLICATEDFIELD_H__

class ComplicatedField : public RaceField
{
public:
	ComplicatedField();

	int		getHeight()									const;
	int		getWidth()									const;
	void	generateObstacle();
	void	placePlayerCar();
private:
	static const int	FIELD_HEIGHT = 13;
	static const int	FIELD_WIDTH = 16;
	int raceField_[FIELD_WIDTH][FIELD_HEIGHT];
	int bufferRaceField_[FIELD_WIDTH][FIELD_HEIGHT + 8];
};

#endif