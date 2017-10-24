#ifndef __RACEFIELD_H__
#define __RACEFIELD_H__

class RaceField
{
public:
	virtual int			getHeight()														const = 0;
	virtual int			getWidth()														const = 0;
	virtual void		draw()															const = 0;
	virtual void		generateObstacle()													  = 0;
	virtual void		setBlockType(const int& x, const int& y, const int& blockType)		  = 0;
	virtual int			getBlockType(const int& x, const int& y)						const = 0;
	virtual int			getBufferBlockType(const int& x)								const = 0;
	virtual void		clearBuffer()														  = 0;
	virtual void		placeObstacle()														  = 0;

	enum BlockType
	{
		EMPTY = 32,
		BORDER_ONE = 177,
		BORDER_TWO = 176,
		OBSTACLE = 205,
		CAR_TOP = 254,
		CAR_TIRE = 111,
		CAR_TORSO = 219
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