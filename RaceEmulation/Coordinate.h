#ifndef __COORDINATE_H__
#define __COORDINATE_H__

class Coordinate
{
public:
	Coordinate(const int& x = -1, const int& y = -1);

	int    getX()               const;
	int    getY()               const;
	void   setX(const int& x);
	void   setY(const int& y);
private:
	int    x_;
	int    y_;
};

#endif
