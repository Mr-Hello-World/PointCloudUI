#ifndef KDTREE_H
#define KDTREE_H


#include <vector>
#include <cmath>
#include "../KDTree/3dKDtree.h"
#include "../Luozf/Pointlzf.h"

namespace td
{
	class KdTree
	{
		kdTree t_;
		int numberOfNeighbours_;						//�����������������
		double radius_;									//���뾶����
		PointCloud pnts_;					//�����������
	public:
		KdTree(PointCloud &_p) :t_(_p.size())			//����Kdtree,����Ĳ�����list����,�̳���Point�࣬������xyzֵ
		{
			std::vector<td::Point>::iterator it;
			it = _p.begin();

			for (int i = 0; it != _p.end(); ++it, ++i)
			{
				t_.store(it->x, it->y, it->z, i);
			}
			t_.treeBalance();							//������
		}

		void setNumberOfNeighbours(int _num)			//��������������
		{
			numberOfNeighbours_ = _num;
			radius_ = 5.0;								//Ĭ��1.0��,����500+���㣬�����뾶̫��û����
		}

		void setNeighboursRadius(double _radius)		//���뾶����
		{
			radius_ = _radius;
			numberOfNeighbours_ = 1000;					//1ƽ�׵���Լ��700+��
		}
		int kNearestNeighbor(double &_x, double &_y, double &_z);	//�������n�������,�䱾��Ҳ����������&�������ٽ������

		std::vector<td::Point>& getNearestNeighbor()				//ȡ���ٽ�ֵ
		{
			return pnts_;
		}
	};
}
#endif