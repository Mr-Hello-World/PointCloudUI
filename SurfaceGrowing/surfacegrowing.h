#ifndef SURFACEGROWING_H
#define SURFACEGROWING_H
#include <map>
#include <vector>
#include "../PointClass/point.h"
using std::map;
using std::vector;
//
class Vote
{
public:
	Point paraVote_;											//���������Ĳ���
	int vote_;													//��¼cube�в����ĸ���
	Vote()
	{
		vote_ = 0;
	}
};

class Pos3D;
class Plane;
class KdTree;
class SurfaceGrowing
{
private:
	map<Pos3D, bool> *found_;										//����任ʱʹ�ã���֤ĳ�����ʱ���Ѿ�������
	Points points_;
	list<list<Point>> segments_;									//�洢��Ƭ��

	void parameter();
	void pointsNormal(KdTree &_tree, map<Point, Plane> &_normal);	//����ÿ����ķ�����
	bool houghTranform(list<Point> &_pnt, Plane &_plane);			//3d����任����������Ƿ���Թ���ƽ��
	int factorN(int _n);											//����n�Ľ׳�n!
	bool randPoints(vector<Point> &_pnt, list<Point> &_point);		//���ѡ������һ��������������
	bool productCube(Plane &_plane, map<Pos3D, Vote> &cube);		//���������ռ��cube,����vote���ʱ�Ĳ���
	void foreachCube(map<Pos3D, Vote> &_cube, Plane &_plane);		//���������ռ�ѡ������ۼ�����Ӧ����Ƭ����
	double point2line(Point &p1, Point &p2, Point &p3);				//����p3�㵽�������㹹��ֱ�ߵľ���,�㵽ֱ�ߵľ���
	double point2plane(Point &_point, Plane &_plane);				//�㵽��ľ���
	int countNum(Plane &_plane, list<Point> &_neiPnt);

public:
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

	SurfaceGrowing();												//���캯��

	~SurfaceGrowing();
	void segment();													//ƽ����չ
	void segment(list<Point> &points,list<list<Point>> &segments);

	void segment1();
};

#endif