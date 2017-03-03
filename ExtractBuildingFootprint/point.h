#ifndef POINT_H
#define POINT_H
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Point															//�������ڴ�ŵ�������
{
public:
	double x,y,z;

	friend bool operator<(const Point &_pnta,const Point &_pntb)	//��������sort����Ϊmap��key
	{
		if(_pnta.x<_pntb.x){
			return true;
		}else if(_pnta.x>_pntb.x){
			return false;
		}else if(_pnta.y<_pntb.y){
			return true;
		}else if(_pnta.y>_pntb.y){
			return false;
		}else if(_pnta.z<_pntb.z){
			return true;
		}else if(_pnta.z>_pntb.z){
			return false;
		}else{
			return false;
		}
	}
	bool operator==(const Point &_pnt)								//��������unique��remove�ȣ������ɾ��������ֵͬ
	{
		if(x==_pnt.x)
			if(y==_pnt.y)
				if(z==_pnt.z)
					return true;
		return false;
	}
	void operator=(const Point &_pnt)
	{
		x=_pnt.x;
		y=_pnt.y;
		z=_pnt.z;
	}
	Point()															//���캯��
	{
		x=y=z=0;
	}

	void input1(list<Point> &_points)								//���ݶ��뵽list
	{
		string ifilePath;
		cout<<"�������ݣ�\n";
		cin>>ifilePath;
		ifstream ifile;
		ifile.open(ifilePath);
		if(!ifile)
		{
			cout<<"�����ļ��޷��򿪣�"<<endl;
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
	void input2(vector<Point> &_points)								//���ݶ��뵽vector
	{
		string ifilePath;
		cout<<"�������ݣ�\n";
		cin>>ifilePath;
		ifstream ifile;
		ifile.open(ifilePath);
		if(!ifile)
		{
			cout<<"�����ļ��޷��򿪣�"<<endl;
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
	void output1(list<Point> &_points)
	{
		string ofilePath;
		cout<<"�������·��\n";
		cin>>ofilePath;

		ofstream ofile;
		ofile.open(ofilePath);
		if(!ofile)
		{
			cout<<"����ļ��޷��򿪣�"<<endl;
			return ;
		}
		list<Point>::iterator it;

		for (it=_points.begin();it!=_points.end();++it)
		{
			ofile<<it->x<<" "<<it->y<<" "<<it->z<<endl;
		}
		ofile.close();
	}

};

#endif