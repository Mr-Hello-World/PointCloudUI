#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <time.h>
#include "contour.h"
#include "../PlaneClass/plane.h"
#include "../KDTree/kdtree.h"
#include "../PCA/pca.h";
#include <numeric>
//using namespace std;

Contour::Contour()
{
	angleTre_=100.0;
	k_=30;
}
void Contour::setAngleTre( double _angleTre/*=100.0*/ )
{
	angleTre_=_angleTre;
}

bool Contour::schedue(list<Point> &_neighbour,Point &point,Plane &plane)
{
	if (_neighbour.size()<3)
	{
		return false;
	}
	double normy[3]={};											//存放y轴方向向量
	double normx[3]={};											//存放x轴方向向量，第一点与p点得到

	double dist,maxDist=0;
	Point pnt;
	list<Point>::iterator it;
	for (it=_neighbour.begin();it!=_neighbour.end();++it)
	{
		dist=pow(it->x-point.x,2)+pow(it->y-point.y,2)+pow(it->z-point.z,2);
		dist=sqrt(dist);
		if (dist>maxDist)
		{
			maxDist=dist;
			pnt=*it;
		}
	}

	normx[0]=pnt.x-point.x;			
	normx[1]=pnt.y-point.y;
	normx[2]=pnt.z-point.z;

	normy[0]=plane.b*normx[2]-plane.c*normx[1];
	normy[1]=plane.c*normx[0]-plane.a*normx[2];
	normy[2]=plane.a*normx[1]-plane.b*normx[0];

	list<double> theta;											//存放计算出来的角度
	double costheta,costhetb;
	double u,v,w,sqrta,sqrtb,sqrtc;
	u=v=w=0;

	for (it=_neighbour.begin();it!=_neighbour.end();++it)
	{
		u=it->x-point.x;
		v=it->y-point.y;
		w=it->z-point.z;
		sqrta=u*u+v*v+w*w;

		sqrtb=normx[0]*normx[0]+normx[1]*normx[1]+normx[2]*normx[2];
		costheta=(u*normx[0]+v*normx[1]+w*normx[2])/sqrt(sqrta*sqrtb);
		costheta=acos(costheta)*180.0/3.14159265;				//与x轴方向向量的夹角

		sqrtc=normy[0]*normy[0]+normy[1]*normy[1]+normy[2]*normy[2];
		costhetb=(u*normy[0]+v*normy[1]+w*normy[2])/sqrt(sqrta*sqrtc);
		costhetb=acos(costhetb)*180.0/3.14159265;				//与y轴方向向量的夹角

		if (costhetb<90.0)
		{
			theta.push_back(costheta);
		}else
		{
			costheta=360.0-costheta;
			theta.push_back(costheta);
		}
	}
	theta.sort();												//将角度从小到大排序
	list<double>::iterator thetaNext,thetaPre;
	list<double> intersectAngle;

	thetaNext=thetaPre=theta.begin();
	++thetaNext;
	double max=0,temd2;
	max=theta.front()+(360.0-theta.back());
	intersectAngle.push_back(max);
	for (;thetaNext!=theta.end();)
	{
		temd2=(*thetaNext)-(*thetaPre);
		intersectAngle.push_back(temd2);
		if (temd2>max)
		{
			max=temd2;
		}
		thetaPre=thetaNext;
		++thetaNext;
	}
	int size=360/k_+0.5;
	double AngleThr = 3 * peakAngle(intersectAngle, 3*size);
	//if (AngleThr > 170)
	//{
	//	AngleThr = 170;
	//}
	if (max > AngleThr)
	{
		return true;
	}
	//cout<<"最大角度："<<max<<endl;
	/*if (max > angleTre_)
	{
	return true;
	}*/
	return false;
}
bool Contour::schedue1(list<Point> &_neighbour,Point &point,Plane &plane)
{
	if (_neighbour.size()<3)
	{
		return false;
	}
	double normy[3]={};											//存放y轴方向向量
	double normx[3]={};											//存放x轴方向向量，第一点与p点得到

	double dist,maxDist=0;
	Point pnt;
	list<Point>::iterator it;
	for (it=_neighbour.begin();it!=_neighbour.end();++it)
	{
		dist=pow(it->x-point.x,2)+pow(it->y-point.y,2)+pow(it->z-point.z,2);
		dist=sqrt(dist);
		if (dist>maxDist)
		{
			maxDist=dist;
			pnt=*it;
		}
	}

	normx[0]=pnt.x-point.x;			
	normx[1]=pnt.y-point.y;
	normx[2]=pnt.z-point.z;

	normy[0]=plane.b*normx[2]-plane.c*normx[1];
	normy[1]=plane.c*normx[0]-plane.a*normx[2];
	normy[2]=plane.a*normx[1]-plane.b*normx[0];

	list<double> theta;											//存放计算出来的角度
	double costheta,costhetb;
	double u,v,w,sqrta,sqrtb,sqrtc;
	u=v=w=0;

	for (it=_neighbour.begin();it!=_neighbour.end();++it)
	{
		u=it->x-point.x;
		v=it->y-point.y;
		w=it->z-point.z;
		sqrta=u*u+v*v+w*w;

		sqrtb=normx[0]*normx[0]+normx[1]*normx[1]+normx[2]*normx[2];
		costheta=(u*normx[0]+v*normx[1]+w*normx[2])/sqrt(sqrta*sqrtb);
		costheta=acos(costheta)*180.0/3.14159265;				//与x轴方向向量的夹角

		sqrtc=normy[0]*normy[0]+normy[1]*normy[1]+normy[2]*normy[2];
		costhetb=(u*normy[0]+v*normy[1]+w*normy[2])/sqrt(sqrta*sqrtc);
		costhetb=acos(costhetb)*180.0/3.14159265;				//与y轴方向向量的夹角

		if (costhetb<90.0)
		{
			theta.push_back(costheta);
		}else
		{
			costheta=360.0-costheta;
			theta.push_back(costheta);
		}
	}
	theta.sort();												//将角度从小到大排序

	//for (list<double>::iterator it=theta.begin();it!=theta.end();++it)
	//{
	//	cout<<*it<<endl;

	//}
	
	list<double>::iterator thetaNext,thetaPre;
	list<double> intersectAngle;

	thetaNext=thetaPre=theta.begin();
	++thetaNext;
	double max=0,temd2;
	max=theta.front()+(360.0-theta.back());
	intersectAngle.push_back(max);
	for (;thetaNext!=theta.end();)
	{
		temd2=(*thetaNext)-(*thetaPre);
		//cout<<temd2<<endl;
		intersectAngle.push_back(temd2);
		if (temd2>max)
		{
			max=temd2;
		}
		thetaPre=thetaNext;
		++thetaNext;
	}
	for (list<double>::iterator it=intersectAngle.begin();it!=intersectAngle.end();++it)
	{
		cout<<*it<<endl;

	}
	int size=360/50.0+0.5;
	double AngleThr = 3 * peakAngle(intersectAngle, size);
	//ccumulate(intersectAngle.begin(),intersectAngle.end(),0.0);
	//cout<<accumulate(intersectAngle.begin(),intersectAngle.end(),0.0)/intersectAngle.size()<<endl;
	

	////if (AngleThr > 170)
	////{
	////	AngleThr = 170;
	////}
	//if (max > AngleThr)
	//{
	//	return true;
	//}
	//cout<<"最大角度："<<max<<endl;
	/*if (max > angleTre_)
	{
	return true;
	}*/
	return false;
}


void Contour::projection(list<Point> &pnt_,Plane pla_)
{
	double k=0;
	list<Point>::iterator points_it;
	for(points_it=pnt_.begin();points_it!=pnt_.end();++points_it)			//将点投影到平面
	{
		k=-(pla_.a*points_it->x+pla_.b*points_it->y+pla_.c*points_it->z-pla_.d)/(pow(pla_.a,2)+pow(pla_.b,2)+pow(pla_.c,2));
		points_it->x+=k*pla_.a;
		points_it->y+=k*pla_.b;
		points_it->z+=k*pla_.c;
	}
}

bool Contour::judgeContour( list<Point> &_points ,Point &_kPoint)
{
	Plane plane;
	plane.compute(_points);	
	_points.remove(_kPoint);											//删除中心点
	
	list<Point> centerPoint;
	centerPoint.push_back(_kPoint);

	projection(_points,plane);
	projection(centerPoint,plane);

	return schedue(_points,centerPoint.front(),plane);
}
bool Contour::judgeContour1( list<Point> &_points ,Point &_kPoint)
{
	Plane plane;
	plane.compute(_points);	
	_points.remove(_kPoint);											//删除中心点

	list<Point> centerPoint;
	centerPoint.push_back(_kPoint);

	projection(_points,plane);
	projection(centerPoint,plane);

	return schedue1(_points,centerPoint.front(),plane);
}
double Contour::peakAngle(list<double> &_angle, int _side/*=10*/)
{
	map<int, int> vote;
	map<int, double> angle;

	for (list<double>::iterator it = _angle.begin(); it != _angle.end();++it)
	{
		vote[(*it) / _side]++;
		if (angle[(*it) / _side]<*it)
		{
			angle[(*it) / _side] = *it;
		}
	}
	double maxV=0;
	int id;
	for (map<int, int>::iterator it = vote.begin(); it != vote.end();++it)
	{
		if (it->second>maxV)
		{
			maxV = it->second;
			id = it->first;
		}
	}
	//cout << "id:" << vote[id] << "angle:" << angle[id] << endl;

	return angle[id];
}

void Contour::contourPoints(int k)
{
	list<Point> points;
	Point pnt;
	pnt.input1(points);

	KdTree tree(points);
	tree.setNumberOfNeighbours(k);

	PCA pca;
	Contour con;
	con.setAngleTre(100);

	list<Point> neigh, featurePoints, nofeaturePoints, simplePoints;
	for (list<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		tree.kNearestNeighbor(it->x, it->y, it->z);
		neigh = tree.getNearestNeighbor();

		if (con.judgeContour(neigh, *it))
		{
			featurePoints.push_back(*it);
		}
	}
	pnt.output1(featurePoints);
}
