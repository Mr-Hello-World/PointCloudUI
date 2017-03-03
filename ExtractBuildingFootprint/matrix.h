#ifndef MATRIX1_H
#define MATRIX1_H

#include<vector>
using namespace std;
template <typename T>
class Matrix
{
public:
	vector<vector<T>> value_;	//�����������

	Matrix(){}
	Matrix(vector<vector<T>> &_val)
	{
		value_=_val;
	}
	void operator=(Matrix<T> &mat)
	{
		value_=mat.value_;
	}
	Matrix<T> operator*(Matrix<T> &mat);			//����˷�A(m*n),B(n*p),C(m,p) 
	Matrix<T> Inv();								//��������
	Matrix<T> Tra();								//����ת��
	int MatEigValVec(vector<vector<T>> &_a,vector<vector<T>> &_v,double _eps=0.00000001,int _jt=500);		//��ʵ�Գƾ��������ֵ�������������Ÿ�ȷ� 
	int NormalVector(vector<vector<T>> &_a,vector<vector<T>> &_normvec,double _eps=0.00000001,int _jt=500);//����ֵ&�������������㷨����
	void disp();
};


#endif