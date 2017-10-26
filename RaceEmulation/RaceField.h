#ifndef __RACEFIELD_H__
#define __RACEFIELD_H__

class RaceField
{
public:
	int				getHeight()														const;
	int				getWidth()														const;
	void			draw()															const;
	void			drawBlock(const Coordinate& coordinate)							const;
	void			setBlockType(const Coordinate& coordinate, const int& blockType);
	int				getBlockType(const Coordinate& coordinate)						const;

	virtual void	generateObstacle()													  = 0;
	virtual int		getBufferBlockType(const Coordinate& coordinate)				const = 0;
	virtual void	clearBuffer()														  = 0;
	virtual void	placeObstacle()														  = 0;

	enum BlockType
	{
		EMPTY = 32,
		BORDER_ONE = 177,
		BORDER_TWO = 176,
		OBSTACLE = 220,
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

protected:
	static const int	FIELD_HEIGHT = 30;
	static const int	FIELD_WIDTH = 30;

	int raceField_[FIELD_HEIGHT][FIELD_WIDTH];
};

#endif