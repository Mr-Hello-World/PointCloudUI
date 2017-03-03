#pragma once

#include "pca.h"
#include "eigenmatrix.h"
PCA::PCA()
{

}
double PCA::planarity( list<Point> &_points )
{
	Matrix3d coVariaceMatrix;											//covariance_matrix of xyz
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			coVariaceMatrix(i, j) = 0;
		}
	}

	double meanx_, meany_, meanz_;										//相应维数的均值
	meanx_ = meany_ = meanz_ = 0.0;
	list<Point>::iterator it;
	for (it = _points.begin(); it != _points.end(); ++it)
	{
		meanx_ += it->x;
		meany_ += it->y;
		meanz_ += it->z;
	}
	meanx_ /= _points.size();
	meany_ /= _points.size();
	meanz_ /= _points.size();


	for (list<Point>::iterator it = _points.begin(); it != _points.end(); ++it)
	{
		coVariaceMatrix(0, 0) += (it->x - meanx_)*(it->x - meanx_);		//cov(x,x)
		coVariaceMatrix(0, 1) += (it->x - meanx_)*(it->y - meany_);		//cov(x,y)
		coVariaceMatrix(0, 2) += (it->x - meanx_)*(it->z - meanz_);		//cov(x,z)

		coVariaceMatrix(1, 0) = coVariaceMatrix(0, 1);					//cov(y,x)
		coVariaceMatrix(1, 1) += (it->y - meany_)*(it->y - meany_);		//cov(y,y)
		coVariaceMatrix(1, 2) += (it->y - meany_)*(it->z - meanz_);		//cov(y,z)

		coVariaceMatrix(2, 0) = coVariaceMatrix(0, 2);					//cov(x,z)
		coVariaceMatrix(2, 1) = coVariaceMatrix(1, 2);					//cov(y,z)
		coVariaceMatrix(2, 2) += (it->z - meanz_)*(it->z - meanz_);		//cov(z,z)
	}

	coVariaceMatrix(0, 0) /= (_points.size() - 1);						//cov(x,x)
	coVariaceMatrix(0, 1) /= (_points.size() - 1);						//cov(x,y)
	coVariaceMatrix(0, 2) /= (_points.size() - 1);						//cov(x,z)

	coVariaceMatrix(1, 0) /= (_points.size() - 1);						//cov(y,x)
	coVariaceMatrix(1, 1) /= (_points.size() - 1);						//cov(y,y)
	coVariaceMatrix(1, 2) /= (_points.size() - 1);						//cov(y,z)

	coVariaceMatrix(2, 0) /= (_points.size() - 1);						//cov(x,z)
	coVariaceMatrix(2, 1) /= (_points.size() - 1);						//cov(y,z)
	coVariaceMatrix(2, 2) /= (_points.size() - 1);						//cov(z,z)
	
	MatrixXd eigvalue(1, 3);
	sortEigenvalue(coVariaceMatrix, eigvalue);
	
	return (eigvalue(0, 1) - eigvalue(0, 0)) / eigvalue(0, 2);
}
