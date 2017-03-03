#pragma once
#include "kdtree.h"
int KdTree::kNearestNeighbor(double &_x,double &_y,double &_z)
{
	pnts_.clear();
	nNearestNodes nNN(numberOfNeighbours_);
	nNN.setDistandIndx(radius_);
	nNN.setSearchPnt(_x,_y,_z);
	t_.locateNodes(&nNN,1);
	//cout<<"找到的点数："<<nNN.found<<endl;
	Point p;
	for(int i=1;i<=nNN.found;++i)
	{
		p.x=nNN.index[i]->pos[0];
		p.y=nNN.index[i]->pos[1];
		p.z=nNN.index[i]->pos[2];
		pnts_.push_back(p);
	}
	return pnts_.size();	//返回最临近点个数
}

list<Point> KdTree::kNearestNeighbor( Point &_point )
{
	pnts_.clear();
	nNearestNodes nNN(numberOfNeighbours_);
	nNN.setDistandIndx(radius_);
	nNN.setSearchPnt(_point.x,_point.y,_point.z);
	t_.locateNodes(&nNN,1);
	//cout<<"找到的点数："<<nNN.found<<endl;
	Point p;
	for(int i=1;i<=nNN.found;++i)
	{
		p.x=nNN.index[i]->pos[0];
		p.y=nNN.index[i]->pos[1];
		p.z=nNN.index[i]->pos[2];
		pnts_.push_back(p);
	}
	return pnts_;		//返回最临近点个数
}
