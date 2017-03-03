#ifndef MATRIX1_CPP
#define MATRIX1_CPP
#include"matrix.h"

template<typename T>
Matrix<T> Matrix<T>::Inv()//矩阵求逆
{
	int i,j,k;
	Matrix<T> B,C;  //存入value_的逆矩阵
	//给B分配空间。
	int m=value_.size();
	B.value_.resize(m);
	C.value_.resize(m);
	for(i=0;i<m;++i)
	{
		C.value_[i].resize(m);
		B.value_[i].resize(2*m);
	}
	double t,x,y=1.0;
	for(i=0;i<m;i++)  
		for(j=0;j<(2*m);j++)  
		{
			if (j<m)   
				B.value_[i][j]=value_[i][j];  
			else 
				if (j==m+i) 
					B.value_[i][j]=1.0;  
				else  
					B.value_[i][j]=0.0;  
		} 
		for(i=0;i<m;i++) 
		{ 
			for(k=0;k<m;k++) 
			{	
				if(k!=i) 
				{	
					t=B.value_[k][i]/B.value_[i][i]; 
					for(j=0;j<(2*m);j++) 
					{	
						x=B.value_[i][j]*t; 
						B.value_[k][j]=B.value_[k][j]-x; 
					} 
				} 
			} 
		} 
		for(i=0;i<m;i++) 
		{	
			t=B.value_[i][i]; 
			for(j=0;j<(2*m);j++) 
				B.value_[i][j]=B.value_[i][j]/t; 
		} 
		for(i=0;i<m;i++)  
			y=y*B.value_[i][i]; 
		if(y==0)
		{
			cout<<"对不起，您输入的矩阵没有逆矩阵，请重新输入。\n"; 
			exit(0);
		}
		else    
			for(i=0;i<m;i++)  
				for(j=0;j<m;j++) 
					C.value_[i][j]=B.value_[i][j+m]; 
		return C;
}
template<typename T>
Matrix<T> Matrix<T>::Tra()//矩阵转置
{
	int m,n;
	m=value_.size();		//行
	n=value_[0].size();		//列
	Matrix<T> B;			//value_矩阵转置后(n*m)
	B.value_.resize(n);
	for(int i=0;i<n;i++)
		B.value_[i].resize(m);

	for(int i=0;i<m;++i)
	{
		for(int j=0;j<n;++j)
		{
			B.value_[j][i]=value_[i][j];
		}
	}
	return B;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &mat)//乘法运算符重载
{
	int m,p,n;
	m=value_.size();
	n=value_[0].size();
	p=mat.value_[0].size();
	Matrix<T> C;
	C.value_.resize(m);
	int i,j,k;
	for(i=0;i<m;++i)
		C.value_[i].resize(p);

	for(i=0;i<m;++i)
	{
		for(j=0;j<p;++j)
			C.value_[i][j]=0.0;
	}

	for(i=0;i<m;++i)
		for(j=0;j<p;++j)
			for(k=0;k<n;++k)
			{
				C.value_[i][j]+=value_[i][k]*mat.value_[k][j];
			}
			return C;
}
template<typename T>
void Matrix<T>::disp()//矩阵输出
{
	int m,n;
	m=value_.size();
	n=value_[0].size();
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<n;j++)
		{
			cout<<value_[i][j]<<" ";
		}
		cout<<endl;
	}
}

template<typename T>
int Matrix<T>::MatEigValVec(vector<vector<T>> &_a,vector<vector<T>> &_v,double _eps=0.00000001,int _jt=500)
{//求实对称矩阵的特征值及特征向量的雅格比法 
	int i,j,p,q,u,w,t,s,l,cj;
	double fm,cn,sn,omega,x,y,d;
	int n=_a.size();
	l=1; 
	for (i=0; i<=n-1; i++) 
	{ 
		_v[i][i]=1.0; 
		for (j=0; j<=n-1; j++) 
		{ 
			if (i!=j) 
			{ 
				_v[i][j]=0.0; 
			} 
		} 
	}
	while (1==1) 
	{ 
		fm=0.0; 
		for (i=0; i<=n-1; i++) 
		{ 
			for (j=0; j<=n-1; j++) 
			{ 
				d=fabs(_a[i][j]); 
				if ((i!=j)&&(d>fm)) 
				{ 
					fm=d; 
					p=i; 
					q=j; 
				} 
			} 
		} 
		if (fm<_eps) 
		{ 
			return(1); 
		} 
		if (l>_jt) 
		{ 
			return(-1); 
		} 
		l=l+1; 
		u=p*n+q; 
		w=p*n+p; 
		t=q*n+p; 
		s=q*n+q; 
		x=-_a[p][q]; 
		y=(_a[q][q]-_a[p][p])/2.0; 
		omega=x/sqrt(x*x+y*y); 
		if (y<0.0) 
		{ 
			omega=-omega; 
		} 
		sn=1.0+sqrt(1.0-omega*omega); 
		sn=omega/sqrt(2.0*sn); 
		cn=sqrt(1.0-sn*sn); 
		fm=_a[p][p]; 
		_a[p][p]=fm*cn*cn+_a[q][q]*sn*sn+_a[p][q]*omega; 
		_a[q][q]=fm*sn*sn+_a[q][q]*cn*cn-_a[p][q]*omega; 
		_a[p][q]=0.0; 
		_a[q][p]=0.0; 

		for (j=0; j<=n-1; j++) 
		{ 
			if ((j!=p)&&(j!=q)) 
			{ 
				cj=j;
				u=p*n+j; 
				w=q*n+j; 
				fm=_a[p][cj]; 
				_a[p][cj]=fm*cn+_a[q][cj]*sn; 
				_a[q][cj]=-fm*sn+_a[q][cj]*cn; 
			} 
		} 


		for (i=0; i<=n-1; i++) 
		{ 
			if ((i!=p)&&(i!=q)) 
			{ 
				u=i*n+p; 
				w=i*n+q; 
				fm=_a[i][p]; 
				_a[i][p]=fm*cn+_a[i][q]*sn; 
				_a[i][q]=-fm*sn+_a[i][q]*cn; 
			} 
		} 

		for (i=0; i<=n-1; i++) 
		{ 
			u=i*n+p; 
			w=i*n+q; 
			fm=_v[i][p]; 
			_v[i][p]=fm*cn+_v[i][q]*sn; 
			_v[i][q]=-fm*sn+_v[i][q]*cn; 
		} 
	} 
	return(1); 
}

template<typename T>
int Matrix<T>::NormalVector(vector<vector<T>> &_a,vector<vector<T>> &_normalvector,double _eps=0.00000001,int _jt=500)
{//特征值&特征向量法计算法相量
	vector<vector<T>> a,v;
	a=v=_a;
	int i,j,p,q,u,w,t,s,l,cj;
	double fm,cn,sn,omega,x,y,d;
	int n=a.size();
	l=1; 
	for (i=0; i<=n-1; i++) 
	{ 
		v[i][i]=1.0; 
		for (j=0; j<=n-1; j++) 
		{ 
			if (i!=j) 
			{ 
				v[i][j]=0.0; 
			} 
		} 
	}
	while (1==1) 
	{ 
		fm=0.0; 
		for (i=0; i<=n-1; i++) 
		{ 
			for (j=0; j<=n-1; j++) 
			{ 
				d=fabs(a[i][j]); 
				if ((i!=j)&&(d>fm)) 
				{ 
					fm=d; 
					p=i; 
					q=j; 
				} 
			} 
		} 
		if (fm<_eps) 
		{ 
			return(1); 
		} 
		if (l>_jt) 
		{ 
			return(-1); 
		} 
		l=l+1; 
		u=p*n+q; 
		w=p*n+p; 
		t=q*n+p; 
		s=q*n+q; 
		x=-a[p][q]; 
		y=(a[q][q]-a[p][p])/2.0; 
		omega=x/sqrt(x*x+y*y); 
		if (y<0.0) 
		{ 
			omega=-omega; 
		} 
		sn=1.0+sqrt(1.0-omega*omega); 
		sn=omega/sqrt(2.0*sn); 
		cn=sqrt(1.0-sn*sn); 
		fm=a[p][p]; 
		a[p][p]=fm*cn*cn+a[q][q]*sn*sn+a[p][q]*omega; 
		a[q][q]=fm*sn*sn+a[q][q]*cn*cn-a[p][q]*omega; 
		a[p][q]=0.0; 
		a[q][p]=0.0; 

		for (j=0; j<=n-1; j++) 
		{ 
			if ((j!=p)&&(j!=q)) 
			{ 
				cj=j;
				u=p*n+j; 
				w=q*n+j; 
				fm=a[p][cj]; 
				a[p][cj]=fm*cn+a[q][cj]*sn; 
				a[q][cj]=-fm*sn+a[q][cj]*cn; 
			} 
		} 

		for (i=0; i<=n-1; i++) 
		{ 
			if ((i!=p)&&(i!=q)) 
			{ 
				u=i*n+p; 
				w=i*n+q; 
				fm=a[i][p]; 
				a[i][p]=fm*cn+a[i][q]*sn; 
				a[i][q]=-fm*sn+a[i][q]*cn; 
			} 
		} 

		for (i=0; i<=n-1; i++) 
		{ 
			u=i*n+p; 
			w=i*n+q; 
			fm=v[i][p]; 
			v[i][p]=fm*cn+v[i][q]*sn; 
			v[i][q]=-fm*sn+v[i][q]*cn; 
		}

		//找到最小特征值对应的特征向量
		double min=a[0][0];
		int min_id=0;
		for(int i=1;i<n;++i)
		{
			if(min>a[i][i])
			{
				min=a[i][i];
				min_id=i;
			}
		}
		for(int i=0;i<n;++i)
		{
			_normalvector[i][0]=v[i][min_id];
		}
		//找出
	} 
	return(1); 
}

#endif