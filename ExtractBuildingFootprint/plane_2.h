#pragma once
#include <list>
#include "../PointClass/point.h"
using namespace std;
class Plane_2:public Point//���࣬������ƽ�淽�̵Ĳ�����ax+by+cz=d(d>=0),a^2+b^2+c^2=1,di=|axi+byi+czi-d|Ϊ��pi��ƽ��ľ���
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
	Plane_2 compute(list<Point> &_pnt);		//����ƽ��Ĳ���
};