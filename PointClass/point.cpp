#pragma once
#include "point.h"

bool Point::operator==(const Point &_pnt) /*可以用来unique、remove等，排序后删除相邻相同值 */
{
	if(x==_pnt.x)
		if(y==_pnt.y)
			if(z==_pnt.z)
				return true;
	return false;
}

void Point::operator=(const Point &_pnt)
{
	x=_pnt.x;
	y=_pnt.y;
	z=_pnt.z;
}

Point::Point() /*构造函数 */
{
	x=y=z=0;
}

void Point::input1(list<Point> &_points) /*数据读入到list */
{
	string ifilePath;
	cout<<"Read Pointclouds：\n";
	cin>>ifilePath;
	ifstream ifile;
	ifile.open(ifilePath);
	if(!ifile)
	{
		cout<<"file data do not open ！"<<endl;
		return ;
	}
	Point tem;
	while(!ifile.eof())
	{
		ifile>>tem.x>>tem.y>>tem.z;
		_points.push_back(tem);
	}
	_points.pop_back();
	ifile.close();
}

void Point::input2(vector<Point> &_points) /*数据读入到vector */
{
	string ifilePath;
	cout<<"Read Pointclouds：\n";
	cin>>ifilePath;
	ifstream ifile;
	ifile.open(ifilePath);
	if(!ifile)
	{
		cout<<"file data do not open ！"<<endl;
		return ;
	}
	Point tem;
	while(!ifile.eof())
	{
		ifile>>tem.x>>tem.y>>tem.z;
		_points.push_back(tem);
	}
	_points.pop_back();
	ifile.close();
}

void Point::output1(list<Point> &_points)
{
	string ofilePath;
	cout<<"Write data:\n";
	cin>>ofilePath;

	ofstream ofile;
	ofile.open(ofilePath);
	if(!ofile)
	{
		cout<<"file data do not open ！"<<endl;
		return ;
	}
	list<Point>::iterator it;

	for (it=_points.begin();it!=_points.end();++it)
	{
		ofile<<it->x<<" "<<it->y<<" "<<it->z<<endl;
	}
	ofile.close();
}

void Point::output2(list<list<Point>> &_points)
{
	string ofilePath;
	cout << "Write data:\n";
	cin >> ofilePath;

	ofstream ofile;
	ofile.open(ofilePath);
	if (!ofile)
	{
		cout << "file data do not open ！" << endl;
		return;
	}
	list<list<Point>>::iterator it;
	int r, g, b;
	srand(unsigned(time(0)));
	for (it = _points.begin(); it != _points.end(); ++it)
	{
		//ofile << it->x << " " << it->y << " " << it->z << endl;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		for (list<Point>::iterator it1 = it->begin(); it1 != it->end(); ++it1)
		{
			ofile << it1->x << " " << it1->y << " " << it1->z << " " << r << " " << g << " " << b << endl;
		}
	}
	ofile.close();
}

void Point::output3(list<list<Point>> &_points)
{
	string ofilePath;
	cout << "Write data:\n";
	cin >> ofilePath;

	ofstream ofile;
	ofile.open(ofilePath);
	if (!ofile)
	{
		cout << "file data do not open ！" << endl;
		return;
	}
	list<list<Point>>::iterator it;

	for (it = _points.begin(); it != _points.end(); ++it)
	{			
		for (list<Point>::iterator it1 = it->begin(); it1 != it->end(); ++it1)
		{
			ofile << it1->x << " " << it1->y << " " << it1->z << endl;
		}
	}
	ofile.close();
}

double Point::point2point(Point &pnt1, Point &pnt2)
{
	return sqrt(pow(pnt1.x - pnt2.x, 2) + pow(pnt1.y - pnt2.y, 2) + pow(pnt1.z - pnt2.z, 2));
}

PointRGB::PointRGB() :Point()
{
	r_ = g_ = b_ = 0;
}

void PointRGB::output1(list<PointRGB> &_points)
{
	string ofilePath;
	cout << "Write data:\n";
	cin >> ofilePath;

	ofstream ofile;
	ofile.open(ofilePath);
	if (!ofile)
	{
		cout << "file data do not open ！" << endl;
		return;
	}
	list<PointRGB>::iterator it;

	for (it = _points.begin(); it != _points.end(); ++it)
	{
		ofile << it->x << " " << it->y << " " << it->z << " " << it->r_ << " " << it->g_ << " " << it->b_ << endl;
	}
	ofile.close();
}
