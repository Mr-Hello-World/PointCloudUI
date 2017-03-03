#pragma once
#include "../PointClass/point.h"
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
using std::map;

#define ROUNDEX(x) ((x)>=0? int((x)+0.5):int((x)-0.5))		//Àƒ…·ŒÂ»Î

class MaxMinValueofCoor
{
public:
	double maxx_, maxy_, maxz_;
	double minx_, miny_, minz_;
	MaxMinValueofCoor()
	{
		maxx_ = maxy_ = maxz_ = LONG_MIN;
		minx_ = miny_ = minz_ = LONG_MAX;
	}
	void getMaxMinValue(Points &_points)
	{
		maxx_ = maxy_ = maxz_ = LONG_MIN;
		minx_ = miny_ = minz_ = LONG_MAX;
		Points &points = _points;
		for (Points::iterator it = points.begin(); it != points.end(); ++it)
		{
			if (maxx_ < it->x)
			{
				maxx_ = it->x;
			}
			if (maxy_ < it->y)
			{
				maxy_ = it->y;
			}
			if (maxz_<it->z)
			{
				maxz_ = it->z;
			}
			if (minx_>it->x)
			{
				minx_ = it->x;
			}
			if (miny_ > it->y)
			{
				miny_ = it->y;
			}
			if (minz_ > it->z)
			{
				minz_ = it->z;
			}
		}
	}
	void getMaxMinX(Points &_points)
	{
		maxx_ = LONG_MIN;
		minx_ = LONG_MAX;
		Points &points = _points;
		for (Points::iterator it = points.begin(); it != points.end(); ++it)
		{
			if (maxx_<it->x)
			{
				maxx_ = it->x;
			}
			if (minx_>it->x)
			{
				minx_ = it->x;
			}
		}
	}
	void getMaxMinY(Points &_points)
	{
		maxy_ = LONG_MIN;
		miny_ = LONG_MAX;
		Points &points = _points;
		for (Points::iterator it = points.begin(); it != points.end(); ++it)
		{
			if (maxy_<it->y)
			{
				maxy_ = it->y;
			}
			if (miny_>it->y)
			{
				miny_ = it->y;
			}
		}
	}
	void getMaxMinZ(Points &_points)
	{
		maxz_ = LONG_MIN;
		minz_ = LONG_MAX;
		Points &points = _points;
		for (Points::iterator it = points.begin(); it != points.end(); ++it)
		{
			if (maxz_<it->z)
			{
				maxz_ = it->z;
			}
			if (minz_>it->z)
			{
				minz_ = it->z;
			}
		}
	}
};

class Pos2D;
//class Mat;
class BuildFootprint
{
	Points points_;
	
	MaxMinValueofCoor extream_;
public:
	double GSD_;
	double erfa_;
	double beta_;
	double gama_;
	int num_;

	BuildFootprint(double _GSD = 0.15, double _erfa = 0.1, double _beta = 0.9)
	{
		GSD_ = _GSD;
		erfa_ = _erfa;
		beta_ = _beta;
		gama_ = 1 - _erfa - _beta;
	}
	void parameter();

	void reflectImage();
	void featureImage();
	void featureImage(list<Point> &points, list<Points> &points_seg);
	void regionGrowing(cv::Mat &_src, cv::Mat &_seg, map<Pos2D, Points> &_voxel2D);
	void regionGrowing(cv::Mat &_src, cv::Mat &_seg, map<Pos2D, Points> &_voxel2D,list<Points> &points_seg);

	Point centerOfVoxel(const Pos2D &_pos2D);
	Point weightCenter(Points &_points);	

	double point2pointInXY(Point &pnt1, Point &pnt2)
	{
		return sqrt(pow(pnt1.x - pnt2.x, 2) + pow(pnt1.y - pnt2.y, 2));
	}
};