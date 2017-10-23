#ifndef __RACEFIELD_H__
#define __RACEFIELD_H__

class RaceField
{
public:
	virtual int		getHeight()															= 0;
	virtual int		getWidth()															= 0;
	virtual void	generateObstacle()													= 0;
	virtual void	placePlayerCar()													= 0;
	virtual int		getBlockType(const int& x, const int& y)							= 0;
	virtual void	setBlockType(const int& x, const int& y, const int& blockType)		= 0;
protected:
	int**			raceField_;
	int**			bufferRaceField_;

	static enum BlockType 
	{
		EMPTY,
		BORDER,
		OBSTACLE,
		PLAYER_CAR
	};

	static enum Obstacle
	{
		STONE,
		LOG,
		TREE,
		CAR
	};
};

#endif