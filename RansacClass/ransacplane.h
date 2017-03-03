#pragma once
#include "../PointClass/point.h"
#include <iostream>
#include <map>
using std::map;

class KdTree;
class Plane;
class RansacSegPlane
{
	int randNum_;
	double distThr_;

	void parameter();
	void parameter(int _num,double _dist);
	void randPoints(list<Point> &_pnt1, list<Point> &_pnt);
	Plane detectPlane(Points &_points);
	Plane detectPlane(vector<Point> &_points);
	
public:
	RansacSegPlane();

	void segment();
    void segment(int _num,double _dist,vector<Point> &_points,list<Points> &_segments);
};
