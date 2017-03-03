#ifndef SURFACEGROWING_H
#define SURFACEGROWING_H
#include <map>
#include <vector>
#include "../PointClass/point.h"
#include "plane_2.h"
#include "../KDTree/kdtree.h"
#include "../Voxel/voxel.h"
const double pi = 3.141592654;
class Vote
{
public:
	Point paraVote_;	//存放最后进入的参数
	int vote_;			//记录cube中参数的个数
	Vote()
	{
		vote_=0;
	}
};

class SurfaceGrowing_2
{
public:
	SurfaceGrowing_2();												//构造函数
	bool input();													//输入函数
	bool input(vector<Point> &Cloud);
	//bool output();													//输出函数，将面片点输出						
	//void surfaceGrowing();											//平面拓展
	void surfaceGrowing1(list<list<Point>> &segments_);											//平面拓展
	//void postProcess(double _num);									//将面片小于一定点数的面分开
	void MergerPlane(list<list<Point>> &segments_, vector<Plane_2> &allPlane);
	bool outputPlane(vector<Plane_2> &allPlane);
	void output(list<list<Point>> &_segments);
	void DeletePlane(vector<Plane_2> &allPlane);
	void OutputLine(Plane_2 plane, list<Point> &Cloud);
private:
	int n_;															//种子面最少点数
	double rths_;													//种子面拟合半径
	double dths_;													//到种子面的最大距离

	double rthg_;													//平面拓展半径
	double dthg_;													//到平面的最大距离

	double a_;														//角度参数，建立cube时使用
	double d_;														//距离参数

	int rm_;														//投票次数阈值
	int vm_;														//cube中参数空间个数阈值

	double lths_;
	double lthl_;
	double lthg_;

	list<Point> points_;//存储数据点
	//list<list<Point>> segments_;//存储面片点
	map<Pos3D,bool> found_;	//霍夫变换时使用，验证某个组合时候已经搜索过
	
	void pointsNormal(KdTree &_tree,map<Point,Plane_2> &_normal);		//计算每个点的法相量
	bool houghTranform(list<Point> &_pnt,Plane_2 &_plane);			//3d霍夫变换，用来检测是否可以构成平面
	int factorN(int _n);											//计算n的阶乘n!
	bool randPoints(vector<Point> &_pnt,list<Point> &_point);		//随机选择满足一定条件的三个点
	bool productCube(Plane_2 &_plane,map<Pos3D,Vote> &cube);			//产生参数空间的cube,返回vote最大时的参数
	void foreachCube(map<Pos3D,Vote> &_cube,Plane_2 &_plane);			//遍历参数空间选出最大累加器对应的面片参数
	double point2line(Point &p1,Point &p2,Point &p3);				//计算p3点到其中两点构成直线的距离,点到直线的距离
	double point2plane(Point &_point,Plane_2 &_plane);				//点到面的距离

	int countNum(Plane_2 &_plane,list<Point> &_neiPnt);

	

	void output(const map<Point,Plane_2> &_normal);					//输出对应点和它的法向量
};

#endif