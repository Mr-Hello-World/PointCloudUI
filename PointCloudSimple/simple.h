/****************************************************************************
** Copyright (C) 2013-2015 CUGB Shizhenwei. All rights reserved.
**
** This file is part of the SimplePointCloudClass project.
**
** This class can be used to simplify point clouds.
** We can set up values of k, angle and planarity to adjust the proportion of simplification.
**
** shizhenwei@cugb.edu.cn
**
**********************************************************************/

#pragma once
#include "../PointClass/point.h"

class SimplePointCloud
{
public:
	int k_;
	double angle_;
	double planarity_;
	double voxelSides_;
	
	SimplePointCloud():k_(40),angle_(170),planarity_(0.5){}
	void setPargama(int _k=50,double _angle=170,double _planarity=0.5)
	{
		k_=_k;
		angle_=_angle;
		planarity_=_planarity;
	}
	list<Point> featurePoints_;
	list<Point> generalPoints_;

	Point simplePoint(list<Point> &_points);
	void weightCenter(list<Point> &_points, Point &_weightC);
	
	void simple();
	void contourPoints(list<Point> &_points,list<Point> &_contourPoints);
	void PCAPoints(list<Point> &_points,list<Point> &_PCAPoints);
	void featurePoints(list<Point> &_points,list<Point> &_featurePoints);
	void simplePoints(list<Point> &_points,list<Point> &_simplePoints);

	void test();
};