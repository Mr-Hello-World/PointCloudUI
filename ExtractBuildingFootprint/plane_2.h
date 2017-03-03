#pragma once
#include <list>
#include "../PointClass/point.h"
using namespace std;
class Plane_2:public Point//面类，用与存放平面方程的参数，ax+by+cz=d(d>=0),a^2+b^2+c^2=1,di=|axi+byi+czi-d|为点pi到平面的距离
{
public:
	double a,b,c,d;
	double theta;
	double distance;
	list<Point> Pointlist;
	Plane_2():Point()
	{
		a=b=c=d=0;
		theta = 0;
		distance = 0;
		Pointlist.clear();
	}
	Plane_2 compute(list<Point> &_pnt);		//计算平面的参数
};