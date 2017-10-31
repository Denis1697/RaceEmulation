#ifndef __EASYFIELD_H__
#define __EASYFIELD_H__

class EasyField : public RaceField
{
public:
	EasyField();

	void   generateObstacle();
	int    getBufferBlockType(const Coordinate& coordinate) const;
	void   clearBuffer();
	void   placeObstacle();
private:
	int    buffer_[FIELD_WIDTH];
};

#endif