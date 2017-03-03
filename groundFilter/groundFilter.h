#ifndef GROUNDFILTER_H
#define GROUNDFILTER_H
#include<list>
#include "../PointClass/point.h"
#include "../KDTree/kdtree.h"
#include "../Voxel/voxel.h"
using std::list;

class GroundFilter
{
	list<Point> points_;												//�洢ԭʼ����
	list<Point> groudPoints_;											//�洢�ر��
	list<Point> roadPoints_;											//��·��

	void statistHistogram(list<Point> &_points);						//�߳�ͳ�Ƴ��ε����˲�,�����д���߳������������
	int round(const double &_value);									//��������ȡ������

	double voxelMinz(map<Pos2D,list<Point>>::iterator &_voxelIt);		//դ���и߳���Сֵ
	void voxelLower(map<Pos2D,list<Point>>::iterator &_voxelIt,list<Point> &_points,double minz);	//�ڶ��������洢ÿ��դ���еĽϵ͵�

	void voxelFilter(list<Point> &_points1,list<Point> &_points2,double _l,double _w,double _h,double _e);		//դ���˲�,����1�Ǵ��˲���,2�˲���㣬3��4��5��6������դ�����
	
	void densityRoad(KdTree &_tree,int num, list<Point> &_points1,list<Point> &_points2);		//������һ���ܶȵĵ��Ϊ��·��,����1Ϊ��������������2��ѡ�㣬3��·��

	void getGround(Points &_points1,double _detaH,Points &_points2);

public:
	GroundFilter()
	{
		
	}

	void test();
	void groundFilters(list<Point> &rawPoints, list<Point> &groundPoints, list<Point> &onGroundPoints);
	double h, l, w;
};

#endif	//GROUNDFILTER_H