#ifndef Segline_H
#define Segline_H
#include"../PointClass/point.h"
#include<list>
#include"plane_2.h"
using namespace std;
class  Segline
{
public:
	 Segline();
	~ Segline();
	Point vertex1, vertex2;//�߶εĶ˵�
	double a, b, d;
	list<Point> pointlist;
	Segline computeSegline(list<Point> &Cloud,Plane_2 &plane);
	Point PointProjectLine(Point &point, Plane_2 &plane);
	void OutputSegline(vector<Segline> &allSegline);
	double Length();
private:
	double Point2Point(const Point a,const Point b);
	
};



#endif