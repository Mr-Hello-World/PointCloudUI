#ifndef LABEL_H
#define  LABEL_H

#include <map>
#include <list>
#include "../PointClass/point.h"
#include "label.h"
class Label
{
public:
	void removeLabel(map<Point,bool> &_label,list<Point> &_points);									//默认没有标签,参数1是标签，2是要移除点的标签，给点初始标签为false
	void labeling(map<Point,bool> &_label,list<Point> &_points);									//将此点标记成true
	void getNoLabelPoints(map<Point,bool> &_label,list<Point> &_points1,list<Point> &_points2);		//未标记点，从参数1中将未标记点存入参数2
	void getLabeledPoints(map<Point,bool> &_label,list<Point> &_points1,list<Point> &_points2);		//已标记点,从参数1中将以标记点存入参数2
	int labeledPointsNum(map<Point,bool> &_label,list<Point> &_points);
};

#endif