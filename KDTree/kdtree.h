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
	int numberOfNeighbours_;						//�����������������
	double radius_;									//���뾶����
	list<Point> pnts_;								//�����������
	int id;											//�洢�ĵ���,0~n
public:
	KdTree(list<Point> &_p):t_(_p.size())			//����Kdtree,����Ĳ�����list����,�̳���Point�࣬������xyzֵ
	{
		list<Point>::iterator it;
		
		id=0;
		for(it=_p.begin();it!=_p.end();++it)
		{
			t_.store(it->x,it->y,it->z,id);
			++id;
		}
		t_.treeBalance();							//������
	}
	KdTree(vector<Point> &_p):t_(_p.size())			//����Kdtree,����Ĳ�����list����,�̳���Point�࣬������xyzֵ
	{
		vector<Point>::iterator it;

		id=0;
		for(it=_p.begin();it!=_p.end();++it)
		{
			t_.store(it->x,it->y,it->z,id);
			++id;
		}
		t_.treeBalance();							//������
	}

	KdTree(list<Point> &_p,string c):t_(_p.size())			//����Kdtree,����Ĳ�����list����,�̳���Point�࣬������xyzֵ
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
			t_.treeBalance();							//������
		}else if (c=="y")
		{
			for(it=_p.begin();it!=_p.end();++it)
			{
				t_.store(it->x,0,it->z,id);
				++id;
			}
			t_.treeBalance();							//������
		}else if (c=="z")
		{
			for(it=_p.begin();it!=_p.end();++it)
			{
				t_.store(it->x,it->y,0,id);
				++id;
			}
			t_.treeBalance();							//������
		}else
		{
			cout<<"build tree error!";
		}

	}
	KdTree(list<Point> &_p,int _size):t_(_size)		//����Kdtree,����Ĳ�����list����,�̳���Point�࣬������xyzֵ
	{
		list<Point>::iterator it;

		id=0;
		for(it=_p.begin();it!=_p.end();++it)
		{
			t_.store(it->x,it->y,it->z,id);
			++id;
		}
		t_.treeBalance();							//������
	}

	void setNumberOfNeighbours(int _num)			//��������������
	{
		numberOfNeighbours_=_num;
		radius_=10.0;								//Ĭ��1.0��,����500+���㣬�����뾶̫��û����
	}
	void setNeighboursRadius(double _radius)		//���뾶����
	{
		radius_=_radius;
		numberOfNeighbours_=5000;					//1ƽ�׵���Լ��700+�㣻�������ݼ���ϴ�
	}
	int kNearestNeighbor(double &_x,double &_y,double &_z);	//�������n�������,�䱾��Ҳ����������&�������ٽ������
	list<Point> kNearestNeighbor(Point &_point);

	void pushBack(double &_x,double &_y,double &_z)//
	{
		t_.store(_x,_y,_z,id);
		++id;
		t_.treeBalance();							//������
	}

	list<Point>& getNearestNeighbor()				//ȡ���ٽ�ֵ
	{
		return pnts_;
	}
};

#endif