#pragma once
#include "voxel.h"

class PolesExtract
{
	list<Point> points_;							//存储输入数据
	list<list<Point>> poles_;						//存储杆状点数据

	bool detectPole(map<Pos3D,list<Point>> &_voxel3DPoints, Pos3D &_pos3D, int &_voxelNum ,int _pitch);
	int detectTopK(map<Pos3D,list<Point>> &_voxel3DPoints, Pos3D &_pos3D);						//检测得到圆柱所在栅格最大k

	void getCandidatePoles(map<Pos2D,list<Point>> &_voxel2DPoints,Pos3D &_pos3D,list<Point> &_candidate);

	void getCandidatePoles(map<Pos3D,list<Point>> &_voxel3DPoints,Pos3D &_topPos3D,map<Pos3D,bool> &_keyLabel,list<Point> &_candidate);
	
	double extreamOfz(list<Point> &_points,double &_minz,double &_maxz);	//求z的最值,返回最值的差值

	void computeWeightXY(list<Point> &_points,double &_x,double &_y);

public:
	void statisticPolesNum();
	int statisticPolesNumandClassify(list<Point> &points_, list<list<Point>> &candidate);

	void computeCoordofPoles();
	void computeCoordofPoles(list<Point> &points_, list<list<Point>> &centers_);
	double h1, h2, h3, h4, h5;

	bool output();									//输出数据

	void test();
	void polesEx(list<Point> &points_,list<Point> &poles_);
	double a, b, c;
	int spacenumber;											//分段周围空间立方体个数
	int pitch;													//控制连续体素个数
	double deta_h;												//杆状地物高度阈值

	void outputKey();								//输出体素key
	
};