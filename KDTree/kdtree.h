/****************************************************************************
** Copyright (C) 2013-2015 CUGB Shizhenwei. All rights reserved.
**
** This file is part of the KDTreeClass project.
**
** This data structure uses 2 method to search neighbor points.
** The first one can set up radius of searching r.
** The second one can use KNN (k nearest neighbor) points.
**
** shizhenwei@cugb.edu.cn
**
**********************************************************************/

#ifndef KDTREE_H
#define KDTREE_H
#include <list>
#include <math.h>
#include "3dKDtree.h"
#include "../PointClass/point.h"
using namespace std;
class KdTree
{
	kdTree t_;
	int numberOfNeighbours_;						//按最近邻域点个数搜索
	double radius_;									//按半径搜索
	list<Point> pnts_;								//存放最近邻域点
	int id;											//存储的点数,0~n
public:
	KdTree(list<Point> &_p):t_(_p.size())			//建立Kdtree,传如的参数是list数据,继承自Point类，其中有xyz值
	{
		list<Point>::iterator it;
		
		id=0;
		for(it=_p.begin();it!=_p.end();++it)
		{
			t_.store(it->x,it->y,it->z,id);
			++id;
		}
		t_.treeBalance();							//调整树
	}
	KdTree(vector<Point> &_p):t_(_p.size())			//建立Kdtree,传如的参数是list数据,继承自Point类，其中有xyz值
	{
		vector<Point>::iterator it;

		id=0;
		for(it=_p.begin();it!=_p.end();++it)
		{
			t_.store(it->x,it->y,it->z,id);
			++id;
		}
		t_.treeBalance();							//调整树
	}

	KdTree(list<Point> &_p,string c):t_(_p.size())			//建立Kdtree,传如的参数是list数据,继承自Point类，其中有xyz值
	{
		list<Point>::iterator it;

		id=0;
		
		if (c=="x")
		{
			for(it=_p.begin();it!=_p.end();++it)
			{
				t_.store(0,it->y,it->z,id);
				++id;
			}
			t_.treeBalance();							//调整树
		}else if (c=="y")
		{
			for(it=_p.begin();it!=_p.end();++it)
			{
				t_.store(it->x,0,it->z,id);
				++id;
			}
			t_.treeBalance();							//调整树
		}else if (c=="z")
		{
			for(it=_p.begin();it!=_p.end();++it)
			{
				t_.store(it->x,it->y,0,id);
				++id;
			}
			t_.treeBalance();							//调整树
		}else
		{
			cout<<"build tree error!";
		}

	}
	KdTree(list<Point> &_p,int _size):t_(_size)		//建立Kdtree,传如的参数是list数据,继承自Point类，其中有xyz值
	{
		list<Point>::iterator it;

		id=0;
		for(it=_p.begin();it!=_p.end();++it)
		{
			t_.store(it->x,it->y,it->z,id);
			++id;
		}
		t_.treeBalance();							//调整树
	}

	void setNumberOfNeighbours(int _num)			//按最近邻域点搜索
	{
		numberOfNeighbours_=_num;
		radius_=10.0;								//默认1.0米,具有500+个点，搜索半径太大没意义
	}
	void setNeighboursRadius(double _radius)		//按半径搜索
	{
		radius_=_radius;
		numberOfNeighbours_=5000;					//1平米点数约有700+点；机载数据间隔较大
	}
	int kNearestNeighbor(double &_x,double &_y,double &_z);	//搜索最近n个邻域点,其本身也被包括在内&返回最临近点个数
	list<Point> kNearestNeighbor(Point &_point);

	void pushBack(double &_x,double &_y,double &_z)//
	{
		t_.store(_x,_y,_z,id);
		++id;
		t_.treeBalance();							//调整树
	}

	list<Point>& getNearestNeighbor()				//取最临近值
	{
		return pnts_;
	}
};

#endif