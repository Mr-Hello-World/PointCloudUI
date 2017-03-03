#pragma once
#include <list>
#include <vector>
#include "../PointClass/point.h"
using namespace std;

class Plane:public Point					//���࣬������ƽ�淽�̵Ĳ�����ax+by+cz=d(d>=0),a^2+b^2+c^2=1,di=|axi+byi+czi-d|Ϊ��pi��ƽ��ľ���
{
public:
	double a,b,c,d;
	Plane():Point()
	{
		a=b=c=d=0;
	}
	Plane compute(list<Point> &_pnt);		//����ƽ��Ĳ���
	Plane compute(vector<Point> &_pnt);		//����ƽ��Ĳ���
	double point2plane(Point &_point, Plane &_plane);
};