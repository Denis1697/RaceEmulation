#ifndef __EASYFIELD_H__
#define __EASYFIELD_H__

class EasyField : public RaceField
{
public:
	EasyField();

	int		getHeight()				const;
	int		getWidth()				const;
	void	generateObstacle();
	void	placePlayerCar();
	void	drawField()				const;
private:
	static const int	FIELD_HEIGHT = 13;
	static const int	FIELD_WIDTH = 10;
	static const int	OBSTACLES_NO = 3;
	int raceField_[FIELD_HEIGHT][FIELD_WIDTH];
	int bufferField_[4][FIELD_WIDTH];
};

#endif