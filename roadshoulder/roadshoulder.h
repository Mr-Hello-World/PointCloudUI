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
	
	list<Point> concourPoints_;										//·��߽��
	list<Point> points_;											//ԭʼ����

	bool ifConcour(list<Point> &nei,Point &pnt,double dist);
	double point2point(Point &pnt1,Point &pnt2);
	double differenceOfElevation(Point &pnt1,Point &pnt2);			//�̲߳�

	void pointsNormal(KdTree &_tree,map<Point,Plane> &_normal);		//����ÿ����ķ�����

	double voxelMinz(map<Pos2D,list<Point>>::iterator &_voxelIt);	//դ���и߳���Сֵ
	double voxelMaxz(map<Pos2D,list<Point>>::iterator &_voxelIt);	//դ���и߳���Сֵ
	double voxelMeanZ(map<Pos2D,list<Point>>::iterator &_voxelIt);	//դ���е�ƽ���߳�

	double valueOfZ(list<Point> &nei,Point &pnt);
	double valueOfZLimitByDist(list<Point> &nei,Point &pnt,double limitDist);

	void findCurbVoxel(map<Pos2D,list<Point>> &voxel2DPoints,map<Point,bool> &label,double thr1,double thr2);	//������·����դ���ҳ��������еĵ���,>thr1=0.08;//·��߲���ֵ	<thr2=0.08;//ͬһ���͵��Ƹ߲�
	
	void finCurbPoints(KdTree &_tree,list<Point> &points,list<Point> &curbPoints);

	double getSlope(list<Point> _points);

	void findPos2D(map<Pos2D,list<Point>>::iterator &_begin,map<Pos2D,list<Point>>::iterator &_end,Pos2D &_pos2DBefore,Pos2D &_pos2Dback);			//����դ����Ѱͬ�л�ͬ�е�դ������·��դ�����ʼλ��

	void findRealCur(map<Pos2D,list<Point>>::iterator &_begin,map<Pos2D,list<Point>>::iterator &_end,map<Point,bool> &_label);

	bool judgeRealCur(map<Pos3D,list<Point>> &_voxel3D,Pos3D &_pos3D,int _n);

public:

	void test();
	
	void test3();

	void test5();

	void afterProgress();											//�����ѡ·��㣬���·���
	void afterProgress2();

	void test6();



	void chouxi();

	void cassRoad();

	void sortPointClouds();

	void shoulderInfor(int _ch);
	void extractCurbPoints(list<Point> &points, list<Point> &curbPoints);
	void afterProgress(list<Point> &points, list<Point> &curbPoints);//�����ѡ·��㣬���·���
	void afterProgress2(list<Point> &points, list<Point> &initialPoints , list<Point> &curbPoints);
	void chouxi(list<Point> &points, list<Point> &curbPoints);
	void sortPointClouds(list<Point> &points);
	void cassRoad(list<Point> &points, list<Point> &curbPoints);
	double l, m, h;
	double thr1, thr2;
};