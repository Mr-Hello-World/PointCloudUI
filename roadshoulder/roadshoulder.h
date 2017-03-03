#pragma once
#include <list>
#include <map>
#include "../PointClass/point.h"
#include "../KDTree/kdtree.h"
#include "../PlaneClass/plane.h"
#include "../Voxel/voxel.h"
using std::list;
using std::map;

class RoadShoulder
{
	double distThr_;
	
	list<Point> concourPoints_;										//路面边界点
	list<Point> points_;											//原始点云

	bool ifConcour(list<Point> &nei,Point &pnt,double dist);
	double point2point(Point &pnt1,Point &pnt2);
	double differenceOfElevation(Point &pnt1,Point &pnt2);			//高程差

	void pointsNormal(KdTree &_tree,map<Point,Plane> &_normal);		//计算每个点的法相量

	double voxelMinz(map<Pos2D,list<Point>>::iterator &_voxelIt);	//栅格中高程最小值
	double voxelMaxz(map<Pos2D,list<Point>>::iterator &_voxelIt);	//栅格中高程最小值
	double voxelMeanZ(map<Pos2D,list<Point>>::iterator &_voxelIt);	//栅格中的平均高程

	double valueOfZ(list<Point> &nei,Point &pnt);
	double valueOfZLimitByDist(list<Point> &nei,Point &pnt,double limitDist);

	void findCurbVoxel(map<Pos2D,list<Point>> &voxel2DPoints,map<Point,bool> &label,double thr1,double thr2);	//将包含路肩点的栅格找出并将其中的点标记,>thr1=0.08;//路肩高差阈值	<thr2=0.08;//同一类型点云高差
	
	void finCurbPoints(KdTree &_tree,list<Point> &points,list<Point> &curbPoints);

	double getSlope(list<Point> _points);

	void findPos2D(map<Pos2D,list<Point>>::iterator &_begin,map<Pos2D,list<Point>>::iterator &_end,Pos2D &_pos2DBefore,Pos2D &_pos2Dback);			//传入栅格，找寻同行或同列的栅格属于路肩栅格的起始位置

	void findRealCur(map<Pos2D,list<Point>>::iterator &_begin,map<Pos2D,list<Point>>::iterator &_end,map<Point,bool> &_label);

	bool judgeRealCur(map<Pos3D,list<Point>> &_voxel3D,Pos3D &_pos3D,int _n);

public:

	void test();
	
	void test3();

	void test5();

	void afterProgress();											//输入初选路肩点，输出路肩点
	void afterProgress2();

	void test6();



	void chouxi();

	void cassRoad();

	void sortPointClouds();

	void shoulderInfor(int _ch);
	void extractCurbPoints(list<Point> &points, list<Point> &curbPoints);
	void afterProgress(list<Point> &points, list<Point> &curbPoints);//输入初选路肩点，输出路肩点
	void afterProgress2(list<Point> &points, list<Point> &initialPoints , list<Point> &curbPoints);
	void chouxi(list<Point> &points, list<Point> &curbPoints);
	void sortPointClouds(list<Point> &points);
	void cassRoad(list<Point> &points, list<Point> &curbPoints);
	double l, m, h;
	double thr1, thr2;
};