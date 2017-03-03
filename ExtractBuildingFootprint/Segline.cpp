#include"Segline.h"
#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<iomanip>
#include<algorithm>
using namespace std;
Segline::Segline()
{
}

Segline::~Segline()
{
}
double Segline::Length()
{
	return Point2Point(vertex1, vertex2);
}


Segline Segline::computeSegline(list<Point> &Cloud, Plane_2 &plane)
{
	Segline temp;
	temp.a = plane.a; temp.b = plane.b; temp.d = plane.d;
	Point temp_point;
	for (list<Point>::iterator CloudIt = Cloud.begin(); CloudIt != Cloud.end(); ++CloudIt)
	{
		//将点投影到直线上
		CloudIt->z = 0.0;
		temp_point = PointProjectLine(*CloudIt, plane);
		
		temp.pointlist.push_back(temp_point);
	}
	
	temp.pointlist.sort();
	temp.vertex1 = *(temp.pointlist.begin());
	list<Point>::iterator CloudIt = temp.pointlist.end();
	CloudIt--;
	temp.vertex2 = (*CloudIt);
	return temp;
}
Point Segline::PointProjectLine(Point &point, Plane_2 &plane)
{
	Point temp;
	if (plane.a == 0)
	{
		temp.x = point.x;
		temp.y = plane.d / plane.b;
		temp.z = point.z;
	}
	else if (plane.b == 0)
	{
		temp.x = plane.d / plane.a;
		temp.y = point.y;
		temp.z = point.z;
	}
	else
	{
		temp.x = (plane.a*plane.d+plane.b*plane.b*point.x-plane.a*plane.b*point.y) / (plane.a*plane.a+plane.b*plane.b);
		temp.y = (plane.b*plane.d + plane.a*plane.a*point.y - plane.a*plane.b*point.x) / (plane.a*plane.a + plane.b*plane.b);
		temp.z = point.z;
	}
	return temp;
}
double Segline::Point2Point(const Point a, const Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
void Segline::OutputSegline(vector<Segline> &allSegline)
{
	string filename;
	std::cout << "输入线段路径：" << std::endl;
	cin >> filename;
	ofstream FileOut;
	FileOut.open(filename);
	vector<Segline>::iterator SeglineIt;
	for (SeglineIt = allSegline.begin(); SeglineIt != allSegline.end(); ++SeglineIt)
	{
		//FileOut << fixed << setprecision(3) << SeglineIt->center.x << ' ' << SeglineIt->center.y << ' ' << SeglineIt->center.z << endl;
		FileOut << fixed << setprecision(3) << SeglineIt->vertex1.x << ' ' << SeglineIt->vertex1.y << ' ' << SeglineIt->vertex1.z << endl;
		FileOut << fixed << setprecision(3) << SeglineIt->vertex2.x << ' ' << SeglineIt->vertex2.y << ' ' << SeglineIt->vertex2.z << endl;
	}
	FileOut.close();
}