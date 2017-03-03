#pragma once
#include <vector>
#include "plane.h"
#include "eigenmatrix.h"

Plane Plane::compute(list<Point> &_pnt)
{
	Plane pla;
	list<Point>::iterator temIt;

	Matrix3d A;
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			A(i,j) = 0;
		}
	}
	
	double meanx,meany,meanz,sumx,sumy,sumz;	//x,y,z的均值
	double detax,detay,detaz;

	sumx=sumy=sumz=0;
	for(temIt=_pnt.begin();temIt!=_pnt.end();++temIt)
	{
		sumx+=temIt->x;
		sumy+=temIt->y;
		sumz+=temIt->z;
	}
	meanx=sumx/_pnt.size();
	meany=sumy/_pnt.size();
	meanz=sumz/_pnt.size();

	
	for(temIt=_pnt.begin();temIt!=_pnt.end();++temIt)
	{
		detax=temIt->x-meanx;				//detax[i];
		detay=temIt->y-meany;				//detay[i];
		detaz=temIt->z-meanz;				//detaz[i];
		A(0, 0) += detax*detax;				//deta_xi^2;
		A(0, 1) += detax*detay;				//deta_xi*deta_yi;
		A(0, 2) += detax*detaz;				//deta_xi*deta_zi;

		A(1, 0) += detax*detay;				//deta_xi*deta_yi;
		A(1, 1) += detay*detay;				//deta_yi^2;
		A(1, 2) += detay*detaz;				//deta_yi*deta_zi;

		A(2, 0) += detax*detaz;				//deta_xi*deta_zi;
		A(2, 1) += detay*detaz;				//deta_yi*deta_zi;
		A(2, 2) += detaz*detaz;				//deta_zi^2;
	}

	MatrixXd V(1, 3);
	minEigenvalueVector(A, V);

	a = pla.a = V(0, 0);
	b = pla.b = V(0, 1);
	c = pla.c = V(0, 2);
	d = pla.d = a * meanx + b * meany + c * meanz;
	
	//cout<<pla.a<<" "<<pla.b<<" "<<pla.c<<" "<<pla.d<<endl;

	return pla;
}

Plane Plane::compute(vector<Point> &_pnt)
{
	Plane pla;
	vector<Point>::iterator temIt;

	Matrix3d A;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			A(i, j) = 0;
		}
	}

	double meanx, meany, meanz, sumx, sumy, sumz;	//x,y,z的均值
	double detax, detay, detaz;

	sumx = sumy = sumz = 0;
	for (temIt = _pnt.begin(); temIt != _pnt.end(); ++temIt)
	{
		sumx += temIt->x;
		sumy += temIt->y;
		sumz += temIt->z;
	}
	meanx = sumx / _pnt.size();
	meany = sumy / _pnt.size();
	meanz = sumz / _pnt.size();


	for (temIt = _pnt.begin(); temIt != _pnt.end(); ++temIt)
	{
		detax = temIt->x - meanx;				//detax[i];
		detay = temIt->y - meany;				//detay[i];
		detaz = temIt->z - meanz;				//detaz[i];
		A(0, 0) += detax*detax;				//deta_xi^2;
		A(0, 1) += detax*detay;				//deta_xi*deta_yi;
		A(0, 2) += detax*detaz;				//deta_xi*deta_zi;

		A(1, 0) += detax*detay;				//deta_xi*deta_yi;
		A(1, 1) += detay*detay;				//deta_yi^2;
		A(1, 2) += detay*detaz;				//deta_yi*deta_zi;

		A(2, 0) += detax*detaz;				//deta_xi*deta_zi;
		A(2, 1) += detay*detaz;				//deta_yi*deta_zi;
		A(2, 2) += detaz*detaz;				//deta_zi^2;
	}

	MatrixXd V(1, 3);
	minEigenvalueVector(A, V);

	a = pla.a = V(0, 0);
	b = pla.b = V(0, 1);
	c = pla.c = V(0, 2);
	d = pla.d = a * meanx + b * meany + c * meanz;

	//cout<<pla.a<<" "<<pla.b<<" "<<pla.c<<" "<<pla.d<<endl;

	return pla;
}

double Plane::point2plane(Point &_point, Plane &_plane)
{
	double dist = 0;
	dist = abs(_point.x*_plane.a + _point.y*_plane.b + _point.z*_plane.c - _plane.d);
	return dist;
}
