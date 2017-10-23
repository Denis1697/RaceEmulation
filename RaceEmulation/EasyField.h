#ifndef __EASYFIELD_H__
#define __EASYFIELD_H__

class EasyField : public RaceField
{
public:
	EasyField();

	int		getHeight()									const;
	int		getWidth()									const;
	void	generateObstacle();
	void	placePlayerCar();
private:
	static const int	FIELD_HEIGHT = 13;
	static const int	FIELD_WIDTH = 8;
	static const int	OBSTACLES_NO = 3;
};

#endif