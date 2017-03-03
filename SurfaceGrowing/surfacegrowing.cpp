#include "surfacegrowing.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "../Voxel/voxel.h"
#include "../PlaneClass/plane.h"
#include "../KDTree/kdtree.h"
#include "label.h"


void SurfaceGrowing::parameter()
{
	std::cout << "parameters:\n";
	std::ifstream ifile;
	ifile.open("parameter.par");
	if (!ifile)
	{
		std::cout << "file data do not open ！" << std::endl;
		return;
	}

	std::string line;
	std::stringstream strstream;
	int i = 0;
	while (getline(ifile, line))
	{
		strstream << line;		
		++i;
		std::cout << strstream.str() << std::endl;
		if (i==2)
		{			
			/*while (strstream >> temp)
			{
			std::cout << temp << " ";
			}*/
			strstream >> n_ >> rths_ >> dths_ >> rthg_ >> dthg_ >> a_ >> d_ >> rm_ >> vm_;
		}
		strstream.clear();
		strstream.str("");
	}
	ifile.close();
}

void SurfaceGrowing::segment()
{
	parameter();
	Point pnt;
	pnt.input1(points_);

	list<Point> seedRegion, regionPoint, candidatePoint, eligiblePoint, neighborPoints, tempPonits;
	list<Point>::iterator seedRegionIt, regionPointIt, candidatePointIt, pointsIt;
	double angle = 0, dist = 0;														//种子点向量与平面夹角
	Plane plane, seedPlane, growingPlane, normal;									//存放平面参数

	int number = 0, n = 0, tempNum = 0, tempNum1 = 0;

	Label lab;

	int snum, rnum;
	snum = 30;
	n_ = 10;
	rnum = 10;
	points_.sort();
	points_.unique();
	//Step1:准备k邻域数据
	KdTree tree(points_);														//建立树
	map<Point, bool> label;

	////Step2:计算点的法相量
	tree.setNumberOfNeighbours(10);
	map<Point,Plane> pointNormal;												//计算点的法相量
	pointsNormal(tree,pointNormal);
	//
	int num = 0;
	for (pointsIt = points_.begin(); pointsIt != points_.end(); ++pointsIt)		//遍历所有没标签的点
	{
		if (label[*pointsIt])													//若此点被标记略过
		{
			continue;
		}
		//tree.setNumberOfNeighbours(snum);
		tree.setNeighboursRadius(rths_);										//种子半径
		tree.kNearestNeighbor(pointsIt->x, pointsIt->y, pointsIt->z);
		neighborPoints = tree.getNearestNeighbor();								//邻域点(存在标记&未标记)

		/*	clock_t start,finish;
		start=clock();*/
		//plane=houghTranform(neighborPoints);									//霍夫变换,计算平面参数
		if (!houghTranform(neighborPoints, plane))
		{
			continue;
		}
		/*	finish=clock();
		cout<<double(finish-start)/CLOCKS_PER_SEC<<endl;*/


		number = countNum(plane, neighborPoints);								//邻域点到检测平面距离小于dths的点数n1
		dist = point2plane(*pointsIt, plane);
		if (number>n_&&dist<dths_)												//计算种子点到检测平面的距离
		{
			seedPlane = plane;													//种子面找到
		}
		else
		{
			continue;
		}
		regionPoint = neighborPoints;											//存储着平面点(未标记)										
		lab.removeLabeledPoints(label, regionPoint);							//将有标签的区域点去除
		lab.labeling(label, regionPoint);										//标记此区域点

		//Step4:平面拓展
		growingPlane = seedPlane;												//设置种子面作为拓展平面

		seedRegion = regionPoint;
		//tree.setNumberOfNeighbours(rnum);
		tree.setNeighboursRadius(rthg_);										//拓展面搜索半径

		n = 0;
		tempNum = 0;

		for (seedRegionIt = seedRegion.begin(); seedRegionIt != seedRegion.end(); ++seedRegionIt)
		{
			tempNum1 = tree.kNearestNeighbor(seedRegionIt->x, seedRegionIt->y, seedRegionIt->z);
			candidatePoint = tree.getNearestNeighbor();

			lab.removeLabeledPoints(label, candidatePoint);						//将候选点中已经标记过的点去除
			for (candidatePointIt = candidatePoint.begin(); candidatePointIt != candidatePoint.end(); ++candidatePointIt)
			{
				dist = point2plane(*candidatePointIt, growingPlane);
				if (dist > dthg_)
				{
					continue;
				}

				normal = pointNormal[*candidatePointIt];
				angle = abs(normal.a*growingPlane.a + normal.b*growingPlane.b + normal.c*growingPlane.c);
				angle = acos(angle) * 180 / 3.14159265;

				if (angle>20)
				{
					continue;
				}

				++n;
				label[*candidatePointIt] = true;								//标记此点
				regionPoint.push_back(*candidatePointIt);						//加入区域点

				if (angle<10)
				{
					seedRegion.push_back(*candidatePointIt);			//加入种子点
				}

				if (n % 30 == 0)
				{
					growingPlane = growingPlane.compute(regionPoint);			//更新平面参数
				}
			}
		}

		if (regionPoint.size())													//确保区域点不等于0
		{
			segments_.push_back(regionPoint);
		}
	}

	pnt.output2(segments_);
}

void SurfaceGrowing::segment( list<Point> &points_,list<list<Point>> &segments_ )
{
	list<Point> seedRegion, regionPoint, candidatePoint, eligiblePoint, neighborPoints, tempPonits;
	list<Point>::iterator seedRegionIt, regionPointIt, candidatePointIt, pointsIt;
	double angle = 0, dist = 0;														//种子点向量与平面夹角
	Plane plane, seedPlane, growingPlane, normal;									//存放平面参数

	int number = 0, n = 0, tempNum = 0, tempNum1 = 0;

	Label lab;

	//Step1:准备k邻域数据
	KdTree tree(points_);														//建立树
	map<Point, bool> label;

	int num = 0;
	for (pointsIt = points_.begin(); pointsIt != points_.end(); ++pointsIt)		//遍历所有没标签的点
	{
		if (label[*pointsIt])													//若此点被标记略过
		{
			continue;
		}
		
		tree.setNeighboursRadius(rths_);										//种子半径
		tree.kNearestNeighbor(pointsIt->x, pointsIt->y, pointsIt->z);
		neighborPoints = tree.getNearestNeighbor();								//邻域点(存在标记&未标记)

		/*	clock_t start,finish;
		start=clock();*/
		//plane=houghTranform(neighborPoints);									//霍夫变换,计算平面参数
		if (!houghTranform(neighborPoints, plane))
		{
			continue;
		}
		/*	finish=clock();
		cout<<double(finish-start)/CLOCKS_PER_SEC<<endl;*/


		number = countNum(plane, neighborPoints);								//邻域点到检测平面距离小于dths的点数n1
		dist = point2plane(*pointsIt, plane);
		if (number>n_&&dist<dths_)												//计算种子点到检测平面的距离
		{
			seedPlane = plane;													//种子面找到
		}
		else
		{
			continue;
		}
		regionPoint = neighborPoints;											//存储着平面点(未标记)										
		lab.removeLabeledPoints(label, regionPoint);							//将有标签的区域点去除
		lab.labeling(label, regionPoint);										//标记此区域点

		//Step4:平面拓展
		growingPlane = seedPlane;												//设置种子面作为拓展平面

		seedRegion = regionPoint;
		//tree.setNumberOfNeighbours(rnum);
		tree.setNeighboursRadius(rthg_);										//拓展面搜索半径

		n = 0;
		tempNum = 0;

		for (seedRegionIt = seedRegion.begin(); seedRegionIt != seedRegion.end(); ++seedRegionIt)
		{
			tempNum1 = tree.kNearestNeighbor(seedRegionIt->x, seedRegionIt->y, seedRegionIt->z);
			candidatePoint = tree.getNearestNeighbor();

			lab.removeLabeledPoints(label, candidatePoint);						//将候选点中已经标记过的点去除
			for (candidatePointIt = candidatePoint.begin(); candidatePointIt != candidatePoint.end(); ++candidatePointIt)
			{
				dist = point2plane(*candidatePointIt, growingPlane);
				if (dist > dthg_)
				{
					continue;
				}
				++n;
				label[*candidatePointIt] = true;								//标记此点
				regionPoint.push_back(*candidatePointIt);						//加入区域点

				if (dist<dths_)
				{
					seedRegion.push_back(*candidatePointIt);					//加入种子点
				}


				if (n % 30 == 0)
				{
					growingPlane = growingPlane.compute(regionPoint);			//更新平面参数
				}
			}
		}

		if (regionPoint.size())													//确保区域点不等于0
		{
			segments_.push_back(regionPoint);
		}
	}
}

void SurfaceGrowing::segment1()
{
	parameter();
	Point pnt;
	pnt.input1(points_);

	list<Point> seedRegion, regionPoint, candidatePoint, eligiblePoint, neighborPoints, tempPonits;
	list<Point>::iterator seedRegionIt, regionPointIt, candidatePointIt, pointsIt;
	double angle = 0, dist = 0;														//种子点向量与平面夹角
	Plane plane, seedPlane, growingPlane, normal;									//存放平面参数

	int number = 0, n = 0, tempNum = 0, tempNum1 = 0;

	Label lab;

	int snum, rnum;
	snum = 30;
	n_ = 10;
	rnum = 10;
	points_.sort();
	points_.unique();
	//Step1:准备k邻域数据
	KdTree tree(points_);														//建立树
	map<Point, bool> label;

	////Step2:计算点的法相量
	//tree.setNumberOfNeighbours(10);
	//map<Point, Plane> pointNormal;												//计算点的法相量
	//pointsNormal(tree, pointNormal);
	//
	int num = 0;
	for (pointsIt = points_.begin(); pointsIt != points_.end(); ++pointsIt)		//遍历所有没标签的点
	{
		if (label[*pointsIt])													//若此点被标记略过
		{
			continue;
		}
		//tree.setNumberOfNeighbours(snum);
		tree.setNeighboursRadius(rths_);										//种子半径
		tree.kNearestNeighbor(pointsIt->x, pointsIt->y, pointsIt->z);
		neighborPoints = tree.getNearestNeighbor();								//邻域点(存在标记&未标记)

		/*	clock_t start,finish;
		start=clock();*/
		//plane=houghTranform(neighborPoints);									//霍夫变换,计算平面参数
		if (!houghTranform(neighborPoints, plane))
		{
			continue;
		}
		/*	finish=clock();
		cout<<double(finish-start)/CLOCKS_PER_SEC<<endl;*/


		number = countNum(plane, neighborPoints);								//邻域点到检测平面距离小于dths的点数n1
		dist = point2plane(*pointsIt, plane);
		if (number>n_&&dist<dths_)												//计算种子点到检测平面的距离
		{
			seedPlane = plane;													//种子面找到
		}
		else
		{
			continue;
		}
		regionPoint = neighborPoints;											//存储着平面点(未标记)										
		lab.removeLabeledPoints(label, regionPoint);							//将有标签的区域点去除
		lab.labeling(label, regionPoint);										//标记此区域点

		//Step4:平面拓展
		growingPlane = seedPlane;												//设置种子面作为拓展平面

		seedRegion = regionPoint;
		//tree.setNumberOfNeighbours(rnum);
		tree.setNeighboursRadius(rthg_);										//拓展面搜索半径

		n = 0;
		tempNum = 0;

		for (seedRegionIt = seedRegion.begin(); seedRegionIt != seedRegion.end(); ++seedRegionIt)
		{
			tempNum1 = tree.kNearestNeighbor(seedRegionIt->x, seedRegionIt->y, seedRegionIt->z);
			candidatePoint = tree.getNearestNeighbor();

			lab.removeLabeledPoints(label, candidatePoint);						//将候选点中已经标记过的点去除
			for (candidatePointIt = candidatePoint.begin(); candidatePointIt != candidatePoint.end(); ++candidatePointIt)
			{
				dist = point2plane(*candidatePointIt, growingPlane);
				if (dist > dthg_)
				{
					continue;
				}

				/*normal = pointNormal[*candidatePointIt];
				angle = abs(normal.a*growingPlane.a + normal.b*growingPlane.b + normal.c*growingPlane.c);
				angle = acos(angle) * 180 / 3.14159265;

				if (angle>20)
				{
					continue;
				}*/

				++n;
				label[*candidatePointIt] = true;								//标记此点
				regionPoint.push_back(*candidatePointIt);						//加入区域点

				//if (angle<10)
				//{
				//	seedRegion.push_back(*candidatePointIt);			//加入种子点
				//}
				if (dist<dths_)
				{
					seedRegion.push_back(*candidatePointIt);					//加入种子点
				}


				if (n % 30 == 0)
				{
					growingPlane = growingPlane.compute(regionPoint);			//更新平面参数
				}
			}
		}

		if (regionPoint.size())													//确保区域点不等于0
		{
			segments_.push_back(regionPoint);
		}
	}

	pnt.output2(segments_);
}

SurfaceGrowing::SurfaceGrowing()
{
	found_ = new map<Pos3D, bool>;
}

SurfaceGrowing::~SurfaceGrowing()
{
	delete found_;
}

bool SurfaceGrowing::houghTranform(list<Point> &_pnt, Plane &_plane)
{
	//任取三个不共线的点，三点之间距离在一定阈值范围内，求出这三点确定的一个平面的平面参
	list<Point> points;

	vector<Point> vecPnt;
	vecPnt.resize(_pnt.size());
	list<Point>::iterator _pntIt;
	int n = 0;
	for (_pntIt = _pnt.begin(); _pntIt != _pnt.end(); ++_pntIt)
	{
		vecPnt[n++] = *_pntIt;
	}

	map<Point, int> vote;														//此时Point中存放参数空间中的参数，int 是此cube中参数的个数
	int i = 0;
	srand((int)time(NULL));
	found_->clear();
	map<Pos3D, Vote> cube;

	int N = factorN(_pnt.size()) / 6;												//控制循环次数
	while (i < rm_)
	{
		//points=randPoints(vecPnt);
		if (!randPoints(vecPnt, points))											//随机抽取不到合适的三个点
		{
			return false;
		}
		_plane = _plane.compute(points);											//计算平面参数

		if (productCube(_plane, cube))
		{
			return true;
		}
		++i;
	}
	//cout<<"霍夫循环次数："<<i<<endl;
	//遍历参数空间所有方格对应累加器，选出累加器最大那个小方格的参数
	foreachCube(cube, _plane);
	return true;
}

int SurfaceGrowing::factorN(int _n)
{
	int n = 1, i;
	for (i = 1; i <= _n; ++i)
	{
		n = n*i;
	}
	return n;
}

bool SurfaceGrowing::randPoints(vector<Point> &_pnt, list<Point> &_point)
{
	_point.clear();																//清空，存储三个点
	double dist1, dist2, dist3;													//存放边长
	int num[3] = {};
	map<Pos3D, bool>::iterator foundIt;
	Pos3D pos;

	int i = 0;//N=factorN(_pnt.size())/6;											//控制循环次数
	while (i < 30)
	{
		++i;
		for (int i = 0; i < 3; ++i)
		{
			num[i] = rand() % _pnt.size();
		}
		pos.i = num[0];
		pos.j = num[1];
		pos.k = num[2];
		foundIt = found_->find(pos);
		if (foundIt != found_->end())												//说明选出的三点已经组合过
		{
			found_->at(pos) = true;
			continue;
		}
		dist1 = pow(_pnt[num[0]].x - _pnt[num[1]].x, 2) + pow(_pnt[num[0]].y - _pnt[num[1]].y, 2) + pow(_pnt[num[0]].z - _pnt[num[1]].z, 2);
		dist1 = sqrt(dist1);
		if (dist1 < 0.15)
		{
			continue;
		}
		dist2 = pow(_pnt[num[0]].x - _pnt[num[2]].x, 2) + pow(_pnt[num[0]].y - _pnt[num[2]].y, 2) + pow(_pnt[num[0]].z - _pnt[num[2]].z, 2);
		dist2 = sqrt(dist2);
		if (dist2 < 0.15)
		{
			continue;
		}
		dist3 = point2line(_pnt[num[0]], _pnt[num[1]], _pnt[num[2]]);
		if (dist3 < 0.15)
		{
			continue;
		}
		_point.push_back(_pnt[num[0]]);
		_point.push_back(_pnt[num[1]]);
		_point.push_back(_pnt[num[2]]);
		//cout<<"随机点时循环次数："<<i<<endl;
		return true;
	}
	return false;
}

bool SurfaceGrowing::productCube(Plane &_plane, map<Pos3D, Vote> &cube)
{
	Pos3D key;
	double e_ = 0.5, side = 0.5, pi = 3.14159265;
	Point  para;
	para.x = acos(_plane.a)*180.0 / pi;										//参数空间参数
	para.y = acos(_plane.b)*180.0 / pi;
	para.z = _plane.d;

	key.i = int((para.x + e_) / a_);
	key.j = int((para.y + e_) / a_);
	key.k = int((para.z + e_) / d_);

	cube[key].paraVote_ = para;
	cube[key].vote_++;
	if (cube[key].vote_ > vm_)
	{
		return true;
	}
	return false;
}

void SurfaceGrowing::foreachCube(map<Pos3D, Vote> &_cube, Plane &_plane)
{
	map<Pos3D, Vote>::iterator _cubeIt;
	int max = 0;
	for (_cubeIt = _cube.begin(); _cubeIt != _cube.end(); ++_cubeIt)
	{
		if (_cubeIt->second.vote_ > max)
		{
			max = _cubeIt->second.vote_;
			//_plane=_cubeIt->second.paraVote_;
			_plane.a = cos(_cubeIt->second.paraVote_.x*3.14159265 / 180.0);
			_plane.b = cos(_cubeIt->second.paraVote_.y*3.14159265 / 180.0);
			_plane.c = sqrt(1 - _plane.a*_plane.a - _plane.b*_plane.b);
			_plane.d = _cubeIt->second.paraVote_.z;
		}
	}
}

double SurfaceGrowing::point2line(Point &p1, Point &p2, Point &p3)
{
	double l, m, n;														//两点间法相量,p1，p2构成直线的方向向量
	l = p2.x - p1.x;
	m = p2.y - p1.y;
	n = p2.z - p1.z;

	double a, b, c;														//p3，p1向量
	a = p3.x - p1.x;
	b = p3.y - p1.y;
	c = p3.z - p1.z;

	double e, f, g;														//向量叉乘结果
	e = b*n - c*m;
	f = c*l - a*n;
	g = a*m - b*l;

	return sqrt(e*e + f*f + g*g) / sqrt(l*l + m*m + n*n);
}

double SurfaceGrowing::point2plane(Point &_point, Plane &_plane)
{
	double dist = 0;
	dist = abs(_point.x*_plane.a + _point.y*_plane.b + _point.z*_plane.c - _plane.d);
	//cout<<"种子点："<<dist<<endl;
	return dist;
}

int SurfaceGrowing::countNum(Plane &_plane, list<Point> &_neiPnt)
{
	double dist = 0.0;
	int num = 0;
	list<Point>::iterator _neiPntIt;
	for (_neiPntIt = _neiPnt.begin(); _neiPntIt != _neiPnt.end(); ++_neiPntIt)
	{
		dist = abs(_neiPntIt->x*_plane.a + _neiPntIt->y*_plane.b + _neiPntIt->z*_plane.c - _plane.d);
		dist = dist / sqrt(pow(_plane.a, 2) + pow(_plane.b, 2) + pow(_plane.c, 2));
		if (dist < dths_)
		{
			++num;
		}
	}
	return num;
}

void SurfaceGrowing::pointsNormal(KdTree &_tree, map<Point, Plane> &_normal)
{
	Plane plane;
	list<Point> neighbor;
	list<Point>::iterator pointsIt;
	//_tree.setNumberOfNeighbours(20);											//找出临近点
	for (pointsIt = points_.begin(); pointsIt != points_.end(); ++pointsIt)
	{
		_tree.kNearestNeighbor(pointsIt->x, pointsIt->y, pointsIt->z);
		neighbor = _tree.getNearestNeighbor();
		plane = plane.compute(neighbor);
		_normal[*pointsIt] = plane;
	}
}