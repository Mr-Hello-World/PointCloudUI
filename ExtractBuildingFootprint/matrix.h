#ifndef MATRIX1_H
#define MATRIX1_H

#include<vector>
using namespace std;
template <typename T>
class Matrix
{
public:
	vector<vector<T>> value_;	//存放数组数据

	Matrix(){}
	Matrix(vector<vector<T>> &_val)
	{
		value_=_val;
	}
	void operator=(Matrix<T> &mat)
	{
		value_=mat.value_;
	}
	Matrix<T> operator*(Matrix<T> &mat);			//矩阵乘法A(m*n),B(n*p),C(m,p) 
	Matrix<T> Inv();								//矩阵求逆
	Matrix<T> Tra();								//矩阵转置
	int MatEigValVec(vector<vector<T>> &_a,vector<vector<T>> &_v,double _eps=0.00000001,int _jt=500);		//求实对称矩阵的特征值及特征向量的雅格比法 
	int NormalVector(vector<vector<T>> &_a,vector<vector<T>> &_normvec,double _eps=0.00000001,int _jt=500);//特征值&特征向量法计算法相量
	void disp();
};


#endif