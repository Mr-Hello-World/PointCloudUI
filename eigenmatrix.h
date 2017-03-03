//#pragma once
#ifndef EIGENMATRIX_H
#define EIGENMATRIX_H

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <list>
using std::list;
using namespace Eigen;

void minEigenvalueVector(Matrix3d &_mat, MatrixXd &_vectors);		//min value and its vector;
void sortEigenvalue(Matrix3d &_mat, MatrixXd &_values);				//from min to max;

#endif
