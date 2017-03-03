#ifndef GROUNDFILTER_H
#define GROUNDFILTER_H
#include<list>
#include "../PointClass/point.h"
#include "../KDTree/kdtree.h"
#include "../Voxel/voxel.h"
using std::list;

class GroundFilter
{
	list<Point> points_;												//存储原始数据
	list<Point> groudPoints_;											//存储地表点
	list<Point> roadPoints_;											//道路点

	void statistHistogram(list<Point> &_points);						//高程统计初次地面滤波,参数中存入高程最大区间最多点
	int round(const double &_value);									//四舍五入取整函数

	double voxelMinz(map<Pos2D,list<Point>>::iterator &_voxelIt);		//栅格中高程最小值
	void voxelLower(map<Pos2D,list<Point>>::iterator &_voxelIt,list<Point> &_points,double minz);	//第二个参数存储每个栅格中的较低点

	void voxelFilter(list<Point> &_points1,list<Point> &_points2,double _l,double _w,double _h,double _e);		//栅格滤波,参数1是待滤波点,2滤波后点，3，4，5，6，控制栅格参数
	
	void densityRoad(KdTree &_tree,int num, list<Point> &_points1,list<Point> &_points2);		//将满足一定密度的点归为道路点,参数1为邻域点个数，参数2候选点，3道路点

	void getGround(Points &_points1,double _detaH,Points &_points2);

public:
	GroundFilter()
	{
		
	}

	void test();
	void groundFilters(list<Point> &rawPoints, list<Point> &groundPoints, list<Point> &onGroundPoints);
	double h, l, w;
};

#endif	//GROUNDFILTER_H