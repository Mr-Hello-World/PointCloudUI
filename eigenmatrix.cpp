#include "eigenmatrix.h"

void minEigenvalueVector( Matrix3d &_mat, MatrixXd &_vectors ) /*min value and its vector */
{
	EigenSolver<Matrix3d> es(_mat);
	Matrix3d D = es.pseudoEigenvalueMatrix();
	Matrix3d V = es.pseudoEigenvectors();
	int id = 0;
	double minv = LONG_MAX;
	for (int i = 0; i < _mat.rows(); ++i)
	{
		if (abs(D(i, i)) < minv)
		{
			minv = abs(D(i, i));
			id = i;
		}
	}
	_vectors << V(0, id), V(1, id), V(2, id);
}

void sortEigenvalue( Matrix3d &_mat, MatrixXd &_values ) /*from min to max */
{
	EigenSolver<Matrix3d> es(_mat);
	Matrix3d D = es.pseudoEigenvalueMatrix();

	list<double> sot;
	sot.push_back(D(0, 0));
	sot.push_back(D(1, 1));
	sot.push_back(D(2, 2));

	sot.sort();
	int i = 0;
	for (list<double>::iterator it = sot.begin(); it != sot.end(); ++it)
	{
		_values(0, i++) = *(it);
	}
}

