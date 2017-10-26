#ifndef __COMPLICATEDFIELD_H__
#define __COMPLICATEDFIELD_H__

class ComplicatedField : public RaceField
{
public:
	ComplicatedField();

	void	generateObstacle(); 
	int		getBufferBlockType(const Coordinate& coordinate)					const;
	void	clearBuffer();
	void	placeObstacle();
private:
	int buffer_[FIELD_WIDTH][4];

};

#endif