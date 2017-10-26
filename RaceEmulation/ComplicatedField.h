#ifndef __COMPLICATEDFIELD_H__
#define __COMPLICATEDFIELD_H__

class ComplicatedField : public RaceField
{
public:
	ComplicatedField();

	void	generateObstacle(); 
	void	clearBuffer();
	void	placeObstacle();
	int		getBufferBlockType(const Coordinate& coordinate)	const;

private:
	int buffer_[4][FIELD_WIDTH];

};

#endif