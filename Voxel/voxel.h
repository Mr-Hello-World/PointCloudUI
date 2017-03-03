#ifndef VOXEL_H
#define VOXEL_H
#include <list>
#include <map>
#include "../PointClass/point.h"
class Pos2D
{
public:
	int i,j;												//分别为x方向，y方向
	Pos2D(int a,int b)
	{
		i=a;
		j=b;
	}
	Pos2D()
	{
		i=0;
		j=0;
	}
	friend bool operator < (const Pos2D &a,const Pos2D &b)
	{
		if(a.i<b.i){
			return true;
		}else if(a.i>b.i){
			return false;
		}else if(a.j<b.j){
			return true;
		}else if(a.j>b.j){
			return false;
		}else{
			return false;
		}
	}
};

class Pos3D:public Pos2D
{
public:
	int k;													//z方向

	Pos3D(int a,int b,int c):Pos2D(a,b)
	{
		k=c;
	}
	Pos3D():Pos2D()
	{
		k=0;
	}
	friend bool operator<(const Pos3D &a,const Pos3D &b)
	{
		if(a.i<b.i){
			return true;
		}else if(a.i>b.i){
			return false;
		}else if(a.j<b.j){
			return true;
		}else if(a.j>b.j){
			return false;
		}else if(a.k<b.k){
			return true;
		}else if(a.k>b.k){
			return false;
		}else{
			return false;
		}
	}
};

class Voxels
{
	double l_,w_,h_,e_;
public:
	map<Pos3D,list<Point>> voxel3DPoints_;
	map<Pos2D,list<Point>> voxel2DPoints_;
	map<Pos2D,list<Point>> voxel2DPointsYX_;
	Voxels()
	{
		l_=w_=h_=0.5;														//控制方格边长
		e_=0.5;																//控制方格偏移量
	}
	void setVoxel(const double _l,const double _w,const double _h,double _e)
	{
		l_=_l;
		w_=_w;
		h_=_h;
		e_=_e;
	}

	void getVoxel3DPoints(list<Point> &_points);
	void getVoxel2DPoints(list<Point> &_points);
	void getVoxel2DPointsInYX(list<Point> &_points);
	void getVoxel2D3DPoints(list<Point> &_points);
};
#endif