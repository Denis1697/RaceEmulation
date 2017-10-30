#ifndef __RACEFIELD_H__
#define __RACEFIELD_H__

class RaceField
{
public:
	virtual ~RaceField() {};

	int           getHeight()                                      const;
	int           getWidth()                                       const;
	void          draw()                                           const;
	void          drawBlock(const Coordinate& coordinate)          const;
	bool          isNotInField(const Coordinate& coordinate)       const;
	int           getBlockType(const Coordinate& coordinate)       const;
	void          setBlockType(const Coordinate& coordinate,
		                       const int& blockType);
	virtual void  generateObstacle() = 0;
	virtual void  clearBuffer() = 0;
	virtual void  placeObstacle() = 0;
	virtual int   getBufferBlockType(const Coordinate& coordinate) const = 0;

protected:
	static const int  FIELD_HEIGHT  = 30;
	static const int  FIELD_WIDTH   = 30;
	const  int        BAD_BLOCKTYPE = -1;
	int               raceField_[FIELD_HEIGHT][FIELD_WIDTH];
};

#endif