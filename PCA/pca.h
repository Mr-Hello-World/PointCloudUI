/****************************************************************************
** Copyright (C) 2013-2015 CUGB Shizhenwei. All rights reserved.
**
** This file is part of the PCAClass project.
**
** This class can be used to calculate planarity of point clouds.
**
** shizhenwei@cugb.edu.cn
**
**********************************************************************/
#ifndef PCA_H
#define PCA_H
#include "../PointClass/point.h"

class PCA												//主成份分析
{
public:
	PCA();
	double planarity(list<Point> &_points);
};

#endif