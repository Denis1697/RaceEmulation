#ifndef __COMPLICATEDFIELD_H__
#define __COMPLICATEDFIELD_H__

class ComplicatedField : public RaceField
{
public:
	ComplicatedField();

	void	generateObstacle(); 
	int		getBufferBlockType(const Coordinate& coordinate)	const;
	void	clearBuffer();
	void	placeObstacle();
private:
	static const int	BUFFER_HEIGHT = 4;
	int					buffer_[BUFFER_HEIGHT][FIELD_WIDTH];
};

#endif