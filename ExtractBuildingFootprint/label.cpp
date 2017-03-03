#include "label.h"
void Label::removeLabel( map<Point,bool> &_label,list<Point> &_points )
{//默认没有标签,参数1是标签，2是要移除点的标签，给点初始标签为false
	list<Point>::iterator it;
	for (it=_points.begin();it!=_points.end();++it)//遍历所有点
	{
		_label[*it]=false;//_label是map类型
	}
}

void Label::labeling( map<Point,bool> &_label,list<Point> &_points )
{//将此点标记成true
	list<Point>::iterator it;
	for (it=_points.begin();it!=_points.end();++it)//遍历所有点，将点标签为true；
	{
		_label[*it]=true;
	}
}

void Label::getNoLabelPoints( map<Point,bool> &_label,list<Point> &_points1,list<Point> &_points2 )
{//未标记点，从_points1中将未标记点存入_points2
	list<Point>::iterator it;
	for (it=_points1.begin();it!=_points1.end();++it)
	{
		if (!_label[*it])
		{
			_points2.push_back(*it);
		}
	}
}

void Label::getLabeledPoints( map<Point,bool> &_label,list<Point> &_points1,list<Point> &_points2 )
{//已标记点,从_points1中将以标记点存入_points2
	list<Point>::iterator it;
	for (it=_points1.begin();it!=_points1.end();++it)
	{
		if (_label[*it])
		{
			_points2.push_back(*it);
		}
	}
}

int Label::labeledPointsNum( map<Point,bool> &_label,list<Point> &_points )
{//得到已标签点的个数
	int num=0;
	list<Point>::iterator pointsIt;

	for (pointsIt=_points.begin();pointsIt!=_points.end();++pointsIt)
	{
		if (_label[*pointsIt])
		{
			++num;
		}
	}
	--num;
	return num;
}

void Label::removeLabeledPoints( map<Point,bool> &_label,list<Point> &_points )
{//将已经标记点，从_points中去除
	list<Point>::iterator it;
	for (it=_points.begin();it!=_points.end();)
	{
		if (_label[*it])
		{
			it=_points.erase(it);
		}
		else
		{
			++it;
		}
	}
}
