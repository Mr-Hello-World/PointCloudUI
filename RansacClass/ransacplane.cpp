#include "ransacplane.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "../PlaneClass/plane.h"							//此头文件放置在第一个位置，原因还未知

void RansacSegPlane::parameter()
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
		if (i == 2)
		{
			/*while (strstream >> temp)
			{
			std::cout << temp << " ";
			}*/
			strstream >> randNum_>>distThr_;
		}
		strstream.clear();
		strstream.str("");
	}
	ifile.close();
}

void RansacSegPlane::parameter(int _num,double _dist)
{
	randNum_=_num;
	distThr_=_dist;
}

RansacSegPlane::RansacSegPlane()
{
//	parameter();
}

void RansacSegPlane::segment()
{
	list<Point> seg;
	list<Points> segments;

	vector<Point> points;
	Point pnt,tempPoint;
	pnt.input2(points);
	Plane plane;
	cout << points.size() << endl;

	while (points.size() > 10)
	{
		plane = detectPlane(points);
		//cout << plane.a << " " << plane.b << " " << plane.c << " "<<plane.d<<endl;
		seg.clear();
		for (int i = 0; i < points.size();)
		{
			if (plane.point2plane(points[i], plane) < distThr_)
			{
				seg.push_back(points[i]);
				points[i] = points.back();
				points.pop_back();
			}
			else
			{
				++i;
			}
		}

		if (seg.size())
		{
			segments.push_back(seg);
			//cout << seg.size() << endl;
		}
	}
	pnt.output2(segments);
}

void RansacSegPlane::segment(int _num,double _dist,vector<Point> &_points,list<Points> &segments)
{
	parameter(_num,_dist);
	segments.clear();

	list<Point> seg;

	vector<Point> &points=_points;
	Point pnt,tempPoint;
	
	Plane plane;
	cout << points.size() << endl;

	while (points.size() > 10)
	{
		plane = detectPlane(points);
		//cout << plane.a << " " << plane.b << " " << plane.c << " "<<plane.d<<endl;
		seg.clear();
		for (int i = 0; i < points.size();)
		{
			if (plane.point2plane(points[i], plane) < distThr_)
			{
				seg.push_back(points[i]);
				points[i] = points.back();
				points.pop_back();
			}
			else
			{
				++i;
			}
		}

		if (seg.size())
		{
			segments.push_back(seg);
		}
	}
}

void RansacSegPlane::randPoints(list<Point> &_pnt1, list<Point> &_pnt)
{
	_pnt.clear();
	vector<Point> points(_pnt1.begin(), _pnt1.end());
	srand((int)time(NULL));
	int id;
	while (true)
	{
		for (int i = 0; i < randNum_; ++i)
		{
			id = rand() % points.size();
			_pnt.push_back(points[id]);
		}
		_pnt.sort();
		_pnt.unique();
		if (_pnt.size() == randNum_)
		{
			break;
		}
		else
			_pnt.clear();
	}
}

Plane RansacSegPlane::detectPlane(Points &_points)
{
	Plane plane, tempPlane;
	int k = 100;
	Points randPnts;										//存放随机点
	int temInterPointsNum = 0, interiorPointsNum = 0, n = 0;

	while (n <= k)
	{
		randPnts.clear();
		randPoints(_points, randPnts);						//选取随机点
		tempPlane.compute(randPnts);						//计算直线参数

		temInterPointsNum = 0;
		for (list<Point>::iterator pointsIt = _points.begin(); pointsIt != _points.end(); ++pointsIt)
		{
			if (tempPlane.point2plane(*pointsIt, tempPlane)<distThr_)
			{
				++temInterPointsNum;
			}
		}//for
		if (temInterPointsNum>interiorPointsNum)			//临时局内点大于局内点个数
		{
			plane = tempPlane;									//更新直线参数
			interiorPointsNum = temInterPointsNum;			//将临时局内赋值到局内点
			cout << "局内点个数：" << interiorPointsNum << endl;
			//cout<<"k："<<k<<endl;
		}//if
		++n;
	}//while

	list<Point> planePoints;
	for (list<Point>::iterator pointsIt = _points.begin(); pointsIt != _points.end(); ++pointsIt)
	{
		if (tempPlane.point2plane(*pointsIt, tempPlane) < distThr_)
		{
			planePoints.push_back(*pointsIt);
		}
	}

	plane = plane.compute(planePoints);				//更新直线参数
	return plane;
}

Plane RansacSegPlane::detectPlane(vector<Point> &_points)
{
	Plane plane, tempPlane;
	int randNum = randNum_;
	//int k = 100;
	int k = int(ceil(log10(0.01) / log10(1.0 - (double)randNum / _points.size())));
	
	//int *randId = new int[randNum];
	
	vector<Point> randPoints(randNum);
	int temInterPointsNum = 0, interiorPointsNum = 0, n = 0;
	srand((int)time(NULL));
	while (n <= k)
	{
		for (int i = 0; i < randNum; ++i)
		{
			//randId[i] = rand() % _points.size();
			//cout << randId[i] << endl;
			randPoints[i] = _points[rand() % _points.size()];
		}

		tempPlane.compute(randPoints);

		temInterPointsNum = 0;
		for (vector<Point>::iterator pointsIt = _points.begin(); pointsIt != _points.end(); ++pointsIt)
		{
			if (tempPlane.point2plane(*pointsIt, tempPlane)<distThr_)
			{
				++temInterPointsNum;
			}
		}//for
		if (temInterPointsNum>interiorPointsNum)			//临时局内点大于局内点个数
		{
			plane = tempPlane;								//更新直线参数
			interiorPointsNum = temInterPointsNum;			//将临时局内赋值到局内点
			k = int(ceil(log10(0.01) / log10(1.0 - pow((double)temInterPointsNum / _points.size(), 3))));//更新K值
			n = 0;
			continue;
			//cout << "局内点个数：" << interiorPointsNum << endl;
			//cout<<"k："<<k<<endl;
		}//if
		++n;
	}
	
	//list<Point> planePoints;
	//for (list<Point>::iterator pointsIt = _points.begin(); pointsIt != _points.end(); ++pointsIt)
	//{
	//	if (tempPlane.point2plane(*pointsIt, tempPlane) < distThr_)
	//	{
	//		planePoints.push_back(*pointsIt);
	//	}
	//}

	//plane = plane.compute(planePoints);				//更新直线参数
	return plane;
}

