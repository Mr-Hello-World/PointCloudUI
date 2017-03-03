#pragma once
#include <list>
#include <vector>
#include "../PointClass/point.h"
using namespace std;

class Plane:public Point					//面类，用与存放平面方程的参数，ax+by+cz=d(d>=0),a^2+b^2+c^2=1,di=|axi+byi+czi-d|为点pi到平面的距离
{
public:
	double a,b,c,d;
	Plane():Point()
	{
		a=b=c=d=0;
	}
	Plane compute(list<Point> &_pnt);		//计算平面的参数
	Plane compute(vector<Point> &_pnt);		//计算平面的参数
	double point2plane(Point &_point, Plane &_plane);
};