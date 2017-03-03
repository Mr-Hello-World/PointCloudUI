
#include "label.h"

void Label::removeLabel( map<Point,bool> &_label,list<Point> &_points )
{
	list<Point>::iterator it;
	for (it=_points.begin();it!=_points.end();++it)
	{
		_label[*it]=false;
	}
}

void Label::labeling( map<Point,bool> &_label,list<Point> &_points )
{
	list<Point>::iterator it;
	for (it=_points.begin();it!=_points.end();++it)
	{
		_label[*it]=true;
	}
}

void Label::getNoLabelPoints( map<Point,bool> &_label,list<Point> &_points1,list<Point> &_points2 )
{
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
{
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
{
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
