#pragma once
#include "voxel.h"

class PolesExtract
{
	list<Point> points_;							//�洢��������
	list<list<Point>> poles_;						//�洢��״������

	bool detectPole(map<Pos3D,list<Point>> &_voxel3DPoints, Pos3D &_pos3D, int &_voxelNum ,int _pitch);
	int detectTopK(map<Pos3D,list<Point>> &_voxel3DPoints, Pos3D &_pos3D);						//���õ�Բ������դ�����k

	void getCandidatePoles(map<Pos2D,list<Point>> &_voxel2DPoints,Pos3D &_pos3D,list<Point> &_candidate);

	void getCandidatePoles(map<Pos3D,list<Point>> &_voxel3DPoints,Pos3D &_topPos3D,map<Pos3D,bool> &_keyLabel,list<Point> &_candidate);
	
	double extreamOfz(list<Point> &_points,double &_minz,double &_maxz);	//��z����ֵ,������ֵ�Ĳ�ֵ

	void computeWeightXY(list<Point> &_points,double &_x,double &_y);

public:
	void statisticPolesNum();
	int statisticPolesNumandClassify(list<Point> &points_, list<list<Point>> &candidate);

	void computeCoordofPoles();
	void computeCoordofPoles(list<Point> &points_, list<list<Point>> &centers_);
	double h1, h2, h3, h4, h5;

	bool output();									//�������

	void test();
	void polesEx(list<Point> &points_,list<Point> &poles_);
	double a, b, c;
	int spacenumber;											//�ֶ���Χ�ռ����������
	int pitch;													//�����������ظ���
	double deta_h;												//��״����߶���ֵ

	void outputKey();								//�������key
	
};