#ifndef __RACEFIELD_H__
#define __RACEFIELD_H__

class RaceField
{
public:
	virtual int				getHeight()															const = 0;
	virtual int				getWidth()															const = 0;
	virtual void			generateObstacle()														  = 0;
	virtual void			placePlayerCar()														  = 0;
	virtual void			drawField()															const = 0;
protected:				
	enum BlockType 
	{
		EMPTY		= 32,
		BORDER		= 177,
		OBSTACLE	= 205,
		CAR_TOP		= 254,
		CAR_TIRE	= 111,
		CAR_TORSO	= 219
	};

	enum Obstacle
	{
		STONE,
		LOG,
		TREE,
		CAR
	};
};

#endif