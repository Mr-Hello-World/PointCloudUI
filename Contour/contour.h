#ifndef Contour_H
#define Contour_H
#include <list>
#include <map>
#include <string>
#include "../PointClass/point.h"
using namespace std;

class Plane;
class Contour
{
public:
	Contour();
	void setAngleTre(double _angleTre=100.0);
	bool judgeContour(list<Point> &_points,Point &_kPoint);
	bool judgeContour1(list<Point> &_points,Point &_kPoint);
	void contourPoints(int k);
	double k_;

protected:
	bool schedue(list<Point> &pnt_,Point &point,Plane &plane);
	bool schedue1(list<Point> &pnt_,Point &point,Plane &plane);

	void projection(list<Point> &pnt_,Plane pla_);
	double peakAngle(list<double> &_angle,int _side);

private:
	double angleTre_;								//¥Ê∑≈Ω«∂»„–÷µ
	
};

#endif