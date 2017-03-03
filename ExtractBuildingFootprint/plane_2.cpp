#include <vector>
#include "matrix.h"
#include "matrix.cpp"
#include "plane_2.h"
Plane_2 Plane_2::compute(list<Point> &_pnt)//计算平面的参数利用特征值法求解平面参数
{
	Plane_2 pla;//要计算的平面
	list<Point>::iterator temIt;
	vector<vector<double>> A,V;		//系数矩阵和最小特征值对应的特征向量
	A.resize(3);
	V.resize(3);
	for(int i=0;i<3;++i)
	{
		A[i].resize(3);
		V[i].resize(1);
	}
	double meanx,meany,meanz,sumx,sumy,sumz;//x,y,z的均值
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
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
		{
			A[i][j]=0;
		}
	}
	for(temIt=_pnt.begin();temIt!=_pnt.end();++temIt)
	{
		detax=temIt->x-meanx;	//detax[i];
		detay=temIt->y-meany;	//detay[i];
		detaz=temIt->z-meanz;	//detaz[i];
		A[0][0]+=detax*detax;	//deta_xi^2;
		A[0][1]+=detax*detay;	//deta_xi*deta_yi;
		A[0][2]+=detax*detaz;	//deta_xi*deta_zi;

		A[1][0]+=detax*detay;	//deta_xi*deta_yi;
		A[1][1]+=detay*detay;	//deta_yi^2;
		A[1][2]+=detay*detaz;	//deta_yi*deta_zi;

		A[2][0]+=detax*detaz;	//deta_xi*deta_zi;
		A[2][1]+=detay*detaz;	//deta_yi*deta_zi;
		A[2][2]+=detaz*detaz;	//deta_zi^2;
	}
	Matrix<double> norm;
	norm.NormalVector(A,V);//特征值&特征向量法计算法向量
	pla.a=V[0][0];
	pla.b=V[1][0];
	pla.c=V[2][0];
	pla.d=V[0][0]*meanx+V[1][0]*meany+V[2][0]*meanz;
	pla.theta = 0;
	pla.distance = 0;
	pla.Pointlist.clear();
	//cout<<pla.a<<" "<<pla.b<<" "<<pla.c<<" "<<pla.d<<endl;
	return pla;
}