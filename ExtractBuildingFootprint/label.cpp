#include "label.h"
void Label::removeLabel( map<Point,bool> &_label,list<Point> &_points )
{//Ĭ��û�б�ǩ,����1�Ǳ�ǩ��2��Ҫ�Ƴ���ı�ǩ�������ʼ��ǩΪfalse
	list<Point>::iterator it;
	for (it=_points.begin();it!=_points.end();++it)//�������е�
	{
		_label[*it]=false;//_label��map����
	}
}

void Label::labeling( map<Point,bool> &_label,list<Point> &_points )
{//���˵��ǳ�true
	list<Point>::iterator it;
	for (it=_points.begin();it!=_points.end();++it)//�������е㣬�����ǩΪtrue��
	{
		_label[*it]=true;
	}
}

void Label::getNoLabelPoints( map<Point,bool> &_label,list<Point> &_points1,list<Point> &_points2 )
{//δ��ǵ㣬��_points1�н�δ��ǵ����_points2
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
{//�ѱ�ǵ�,��_points1�н��Ա�ǵ����_points2
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
{//�õ��ѱ�ǩ��ĸ���
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
{//���Ѿ���ǵ㣬��_points��ȥ��
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
