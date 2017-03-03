#ifndef SURFACEGROWING_H
#define SURFACEGROWING_H
#include <map>
#include <vector>
#include "../PointClass/point.h"
#include "plane_2.h"
#include "../KDTree/kdtree.h"
#include "../Voxel/voxel.h"
const double pi = 3.141592654;
class Vote
{
public:
	Point paraVote_;	//���������Ĳ���
	int vote_;			//��¼cube�в����ĸ���
	Vote()
	{
		vote_=0;
	}
};

class SurfaceGrowing_2
{
public:
	SurfaceGrowing_2();												//���캯��
	bool input();													//���뺯��
	bool input(vector<Point> &Cloud);
	//bool output();													//�������������Ƭ�����						
	//void surfaceGrowing();											//ƽ����չ
	void surfaceGrowing1(list<list<Point>> &segments_);											//ƽ����չ
	//void postProcess(double _num);									//����ƬС��һ����������ֿ�
	void MergerPlane(list<list<Point>> &segments_, vector<Plane_2> &allPlane);
	bool outputPlane(vector<Plane_2> &allPlane);
	void output(list<list<Point>> &_segments);
	void DeletePlane(vector<Plane_2> &allPlane);
	void OutputLine(Plane_2 plane, list<Point> &Cloud);
private:
	int n_;															//���������ٵ���
	double rths_;													//��������ϰ뾶
	double dths_;													//���������������

	double rthg_;													//ƽ����չ�뾶
	double dthg_;													//��ƽ���������

	double a_;														//�ǶȲ���������cubeʱʹ��
	double d_;														//�������

	int rm_;														//ͶƱ������ֵ
	int vm_;														//cube�в����ռ������ֵ

	double lths_;
	double lthl_;
	double lthg_;

	list<Point> points_;//�洢���ݵ�
	//list<list<Point>> segments_;//�洢��Ƭ��
	map<Pos3D,bool> found_;	//����任ʱʹ�ã���֤ĳ�����ʱ���Ѿ�������
	
	void pointsNormal(KdTree &_tree,map<Point,Plane_2> &_normal);		//����ÿ����ķ�����
	bool houghTranform(list<Point> &_pnt,Plane_2 &_plane);			//3d����任����������Ƿ���Թ���ƽ��
	int factorN(int _n);											//����n�Ľ׳�n!
	bool randPoints(vector<Point> &_pnt,list<Point> &_point);		//���ѡ������һ��������������
	bool productCube(Plane_2 &_plane,map<Pos3D,Vote> &cube);			//���������ռ��cube,����vote���ʱ�Ĳ���
	void foreachCube(map<Pos3D,Vote> &_cube,Plane_2 &_plane);			//���������ռ�ѡ������ۼ�����Ӧ����Ƭ����
	double point2line(Point &p1,Point &p2,Point &p3);				//����p3�㵽�������㹹��ֱ�ߵľ���,�㵽ֱ�ߵľ���
	double point2plane(Point &_point,Plane_2 &_plane);				//�㵽��ľ���

	int countNum(Plane_2 &_plane,list<Point> &_neiPnt);

	

	void output(const map<Point,Plane_2> &_normal);					//�����Ӧ������ķ�����
};

#endif