#ifndef __EASYFIELD_H__
#define __EASYFIELD_H__

class EasyField : public RaceField
{
public:
	EasyField();

	int		getHeight()														const;
	int		getWidth()														const;
	void	generateObstacle();
	void	draw()															const;
	int		getBlockType(const int& x, const int& y)						const;
	void	setBlockType(const int& x, const int& y, const int& blockType);
	int		getBufferBlockType(const int& x)								const;
	void	clearBuffer();
	void	placeObstacle();
private:
	static const int	FIELD_HEIGHT = 13;
	static const int	FIELD_WIDTH = 35;
	static const int	OBSTACLES_NO = 3;

	int raceField_[FIELD_HEIGHT][FIELD_WIDTH];
	int buffer_[FIELD_WIDTH];
};

#endif