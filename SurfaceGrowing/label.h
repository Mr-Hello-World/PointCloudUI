#ifndef LABEL_H
#define  LABEL_H

#include <map>
#include <list>
//#include "../Point/point_h.h"
#include "../PointClass/point.h"
class Label
{
public:
	void removeLabel(map<Point, bool> &_label, list<Point> &_points);									//Ĭ��û�б�ǩ,����1�Ǳ�ǩ��2��Ҫ�Ƴ���ı�ǩ�������ʼ��ǩΪfalse
	void labeling(map<Point, bool> &_label, list<Point> &_points);									//���˵��ǳ�true
	void getNoLabelPoints(map<Point, bool> &_label, list<Point> &_points1, list<Point> &_points2);		//δ��ǵ㣬�Ӳ���1�н�δ��ǵ�������2
	void getLabeledPoints(map<Point, bool> &_label, list<Point> &_points1, list<Point> &_points2);		//�ѱ�ǵ�,�Ӳ���1�н��Ա�ǵ�������2
	int labeledPointsNum(map<Point, bool> &_label, list<Point> &_points);
	void removeLabeledPoints(map<Point, bool> &_label, list<Point> &_points);							//���Ѿ���ǵ㣬�Ӳ���2��ȥ��
};

#endif