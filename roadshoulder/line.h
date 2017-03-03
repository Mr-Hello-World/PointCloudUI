#pragma once
#include "../PointClass/point.h"
#define PI 3.14159265
#define Angle2Radian(x) ((x)*PI/180.0)
#define Radian2Angle(x) ((x)*180/PI)

typedef list<Point> Points;
typedef Point Vecline;
class ThreeDLine
{
public:
	double a_,b_,c_,d_;							//四参数
	double l_,m_,n_,do_;						//点、方向向量
	double fi,theta,ro,erfa;					//一种新的直线方程参数

	Point point_;
	ThreeDLine()
	{
		a_=b_=c_=d_=l_=m_=n_=do_=0;
		fi=theta=ro=erfa=0;
	}
	ThreeDLine computeMLS(Points &_points);
	ThreeDLine computeTwoPoints(Point &_pnt1,Point &_pnt2);
	ThreeDLine computeNew(Point &_pnt1,Point &_pnt2);

	double point2LineMLS(Point &_point);
	double point2LineTwoPoints(Point &_point);

	void operator= (ThreeDLine &_threeDLine)
	{
		a_=_threeDLine.a_;
		b_=_threeDLine.b_;
		c_=_threeDLine.c_;
		d_=_threeDLine.d_;

		l_=_threeDLine.l_;
		m_=_threeDLine.m_;
		n_=_threeDLine.n_;
		do_=_threeDLine.do_;

		fi=_threeDLine.fi;
		theta=_threeDLine.theta;
		ro=_threeDLine.ro;
		erfa=_threeDLine.erfa;
	}
	Vecline cross(Vecline &_v1,Vecline &_v2)
	{
		Vecline v;
		v.x=_v1.y*_v2.z-_v1.z*_v2.y;
		v.y=_v1.z*_v2.x-_v1.x*_v2.z;
		v.z=_v1.x*_v2.y-_v1.y*_v2.x;

		return v;
	}


	double angleofVec(Vecline &a,Vecline &b)
	{
		double c, d;
		c = a.x*b.x + a.y*b.y + a.z*b.z;
		d = sqrt(a.x*a.x + a.y*a.y + a.z*a.z) * sqrt(b.x*b.x + b.y*b.y + b.z*b.z);
		return acos(c/d);
	}
};