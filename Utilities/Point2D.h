#ifndef __POINT2D__
#define __POINT2D__

class Point2D
{
public:

	Point2D(void);

	Point2D(double _x,double _y);

	Point2D(const Point2D& p);

	Point2D& operator=(const Point2D& rhs);

	Point2D	operator*(const double& a);

	~Point2D(void);

public:

	double	x,y;
};

inline Point2D& Point2D::operator =(const Point2D &rhs)
{
	x = rhs.x;
	y = rhs.y;

	return (*this);
}

inline Point2D Point2D::operator *(const double& a)
{
	return Point2D(a * x,a * y);
}

#endif