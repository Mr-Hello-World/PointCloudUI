//#pragma once
#include "simple.h"
#include "../Contour/contour.h"
#include "../PCA/pca.h"
#include "../KDTree/kdtree.h"
#include "../Voxel/voxel.h"
#include <iostream>
#include <Windows.h>

void SimplePointCloud::simple()
{
	double l, w, h, e;
	l = w = h = 0.05;
	e = 0.5;

	cout << "输入：邻域k=50,角度anlgle=170，平整度planar=0.5，体素边长s=0.05\n";
	cin >> k_ >> angle_ >> planarity_ >> h;
	l = w = h;

	list<Point> points;
	Point pnt;
	pnt.input1(points);

	KdTree tree(points);
	tree.setNumberOfNeighbours(k_);
	
	PCA pca;
	Contour con;
	con.k_=k_;
	con.setAngleTre(angle_);
	
	list<Point> neigh, featurePoints, nofeaturePoints, simplePoints;
	for (list<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		tree.kNearestNeighbor(it->x, it->y, it->z);
		neigh = tree.getNearestNeighbor();
		
		if (pca.planarity(neigh) < planarity_)
		{
			featurePoints.push_back(*it);
		}else if (con.judgeContour(neigh,*it))
		{
			featurePoints.push_back(*it);
		}
		else
		{
			nofeaturePoints.push_back(*it);
		}
	}
	simplePoints.insert(simplePoints.end(), featurePoints.begin(), featurePoints.end());
	//pnt.output1(simplePoints);
	pnt.output1(featurePoints);
	
	Voxels voxel;
	voxel.setVoxel(l, w, h, e);
	voxel.getVoxel3DPoints(nofeaturePoints);
	map<Pos3D, list<Point>> &voxel3DPoints = voxel.voxel3DPoints_;

	for (map<Pos3D, list<Point>>::iterator it = voxel3DPoints.begin(); it != voxel3DPoints.end(); ++it)
	{
		simplePoints.push_back(simplePoint(it->second));
	}
	pnt.output1(simplePoints);
}

Point SimplePointCloud::simplePoint(list<Point> &_points)
{
	Point wc, sp;
	weightCenter(_points, wc);
	double dist = 100000000000, temd = 0;
	for (list<Point>::iterator it = _points.begin(); it != _points.end(); ++it)
	{
		temd = wc.point2point(*it, wc);
		if (dist >= temd)
		{
			dist = temd;
			sp = *it;
		}
	}
	return sp;
}

void SimplePointCloud::weightCenter(list<Point> &_points, Point &_weightC)
{
	_weightC.x = _weightC.y = _weightC.z = 0;
	for (list<Point>::iterator it = _points.begin(); it != _points.end(); ++it)
	{
		_weightC.x += it->x;
		_weightC.y += it->y;
		_weightC.z += it->z;
	}
	_weightC.x /= (_points.size()*1.0);
	_weightC.y /= (_points.size()*1.0);
	_weightC.z /= (_points.size()*1.0);
}

void SimplePointCloud::test()
{
	vector<Point> points;
	Point pnt;
	pnt.input2(points);
	KdTree tree(points);
	tree.setNumberOfNeighbours(2);
	list<Point> ng;

	ofstream outfile;
	outfile.open("dist.txt");
	list<double> dist;
	for (int i=0;i<points.size();++i)
	{
		ng=tree.kNearestNeighbor(points.at(i));
		//outfile<<pnt.point2point(ng.front(),ng.back())<<endl;
		dist.push_back(pnt.point2point(ng.front(),ng.back()));

	}
	dist.sort();
	for (list<double>::iterator it=dist.begin();it!=dist.end();++it)
	{
		outfile<<*it<<endl;
	}
	outfile.close();


	system("pause");
}

void SimplePointCloud::contourPoints( list<Point> &_points,list<Point> &_contourPoints )
{
	list<Point> &points=_points;

	KdTree tree(points);
	tree.setNumberOfNeighbours(k_);

	PCA pca;
	Contour con;
	con.k_=k_;
	list<Point> neigh;
	for (list<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		tree.kNearestNeighbor(it->x, it->y, it->z);
		neigh = tree.getNearestNeighbor();

		if (con.judgeContour(neigh,*it))
		{
			_contourPoints.push_back(*it);
		}
	}
}

void SimplePointCloud::PCAPoints( list<Point> &_points,list<Point> &_PCAPoints )
{
	list<Point> &points=_points;
	
	KdTree tree(points);
	tree.setNumberOfNeighbours(k_);

	PCA pca;
	list<Point> neigh;
	for (list<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		tree.kNearestNeighbor(it->x, it->y, it->z);
		neigh = tree.getNearestNeighbor();

		if (pca.planarity(neigh) < planarity_)
		{
			_PCAPoints.push_back(*it);
		}
	}
}

void SimplePointCloud::featurePoints( list<Point> &_points,list<Point> &_featurePoints )
{
	list<Point> &points=_points;
	
	KdTree tree(points);
	tree.setNumberOfNeighbours(k_);

	PCA pca;
	Contour con;
	con.k_=k_;
	con.setAngleTre(angle_);

	list<Point> neigh, &featurePoints=_featurePoints;
	for (list<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		tree.kNearestNeighbor(it->x, it->y, it->z);
		neigh = tree.getNearestNeighbor();

		if (pca.planarity(neigh) < planarity_)
		{
			featurePoints.push_back(*it);
		}else if (con.judgeContour(neigh,*it))
		{
			featurePoints.push_back(*it);
		}
	}
}

void SimplePointCloud::simplePoints( list<Point> &_points,list<Point> &_simplePoints )
{
	double l, w, h, e;
	l = w = h = voxelSides_;
	e = 0.5;
	
	list<Point> &points=_points;
	
	KdTree tree(points);
	tree.setNumberOfNeighbours(k_);

	PCA pca;
	Contour con;
	con.k_=k_;
	con.setAngleTre(angle_);

	list<Point> neigh, featurePoints, nofeaturePoints, &simplePoints=_simplePoints;;
	for (list<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		tree.kNearestNeighbor(it->x, it->y, it->z);
		neigh = tree.getNearestNeighbor();

		if (pca.planarity(neigh) < planarity_)
		{
			featurePoints.push_back(*it);
		}else if (con.judgeContour(neigh,*it))
		{
			featurePoints.push_back(*it);
		}
		else
		{
			nofeaturePoints.push_back(*it);
		}
	}
	simplePoints.insert(simplePoints.end(), featurePoints.begin(), featurePoints.end());
	
	Voxels voxel;
	voxel.setVoxel(l, w, h, e);
	voxel.getVoxel3DPoints(nofeaturePoints);
	map<Pos3D, list<Point>> &voxel3DPoints = voxel.voxel3DPoints_;

	for (map<Pos3D, list<Point>>::iterator it = voxel3DPoints.begin(); it != voxel3DPoints.end(); ++it)
	{
		simplePoints.push_back(simplePoint(it->second));
	}
}

 