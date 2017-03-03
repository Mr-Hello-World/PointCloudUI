#include <map>
#include "groundFilter.h"
#include "label.h"
using std::map;

void GroundFilter::statistHistogram(list<Point> &_primary)
{
	map<int,int> statistHist;												//first int 代表高程间隔，second int代表vote
	map<int,int>::iterator statisIt,maxIt;
	int key;
	
	list<Point>::iterator pointsIt;
	list<Point> &_points=points_;											//必须进行初始化

	for (pointsIt=_points.begin();pointsIt!=_points.end();++pointsIt)
	{
		key=round(pointsIt->z);
		statisIt=statistHist.find(key);
		if (statisIt==statistHist.end())
		{
			statistHist[key]=0;
			++statistHist[key];
		}else
		{
			++statistHist[key];
		}
	}

	int max=0;
	double groudHigh=0;
	for (statisIt=statistHist.begin();statisIt!=statistHist.end();++statisIt)
	{
		if (statisIt->second>max)
		{
			max=statisIt->second;
			maxIt=statisIt;
			groudHigh=statisIt->first;
		}
	}
	
	groudHigh+=1.5;
	
	for (pointsIt=_points.begin();pointsIt!=_points.end();++pointsIt)
	{
		if (pointsIt->z<groudHigh)
		{
			_primary.push_back(*pointsIt);
		}
	}

	/*ofstream ofile;
	string filePath;
	cout<<"输出高程直方图："<<endl;
	cin>>filePath;
	ofile.open(filePath);
	map<int,int>::iterator statistHistIt;
	for (statistHistIt=statistHist.begin();statistHistIt!=statistHist.end();++statistHistIt)
	{
		ofile<<statistHistIt->first<<" "<<statistHistIt->second<<endl;
	}*/

}

int GroundFilter::round( const double &_value )
{
	if (_value>0){
		return int(_value+0.5);
	}else{
		return int(_value-0.5);
	}
}


double GroundFilter::voxelMinz( map<Pos2D,list<Point>>::iterator &_voxelIt )
{
	list<Point>::iterator it;
	double minZ=10000;
	for (it=_voxelIt->second.begin();it!=_voxelIt->second.end();++it)
	{
		if (minZ>it->z)
		{
			minZ=it->z;
		}
	}
	return minZ;
}
void GroundFilter::voxelLower( map<Pos2D,list<Point>>::iterator &_voxelIt,list<Point> &_points,double minZ )
{
	list<Point>::iterator it;
	for (it=_voxelIt->second.begin();it!=_voxelIt->second.end();++it)
	{
		if (it->z-minZ<0.3)
		{
			_points.push_back(*it);
		}
	}
}
void GroundFilter::voxelFilter(list<Point> &_points1,list<Point> &_points2,double _l,double _w,double _h,double _e)
{
	Voxels voxel;
	voxel.setVoxel(_l,_w,_h,_e);
	voxel.getVoxel2DPoints(_points1);
	map<Pos2D,list<Point>> &voxel2DPoints=voxel.voxel2DPoints_;

	double minz=0;

	map<Pos2D,list<Point>>::iterator voxelsIt;
	for (voxelsIt=voxel2DPoints.begin();voxelsIt!=voxel2DPoints.end();++voxelsIt)
	{
		minz=voxelMinz(voxelsIt);
		voxelLower(voxelsIt,_points2,minz);
	}
	//output(primary);
}

void GroundFilter::densityRoad(KdTree &_tree,int num, list<Point> &_points1,list<Point> &_points2 )
{
	list<Point>::iterator pointsIt;
	int key;
	
	for (pointsIt=_points1.begin();pointsIt!=_points1.end();++pointsIt)
	{
		key=_tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);
		if (key>=num)
		{
			_points2.push_back(*pointsIt);
		}	
	}
}

void GroundFilter::test()
{
	double h,l,w;
	cout<<" 输入栅格参数 h l w (1,1,1)：";
	cin>>h>>l>>w;
	cout<<endl;

	Point pnt;
	cout<<"输入数据：";
	pnt.input1(points_);

	list<Point> primaryPoints;
	statistHistogram(primaryPoints);

	//cout<<"输出初选点数据：";											//输出初选点，高程滤波
	//pnt.output1(primaryPoints);
	
	list<Point> groundPoints;
	voxelFilter(primaryPoints,groundPoints,h,l,w,0.0);

	cout<<"输出地面点：";												//输出地面点
	pnt.output1(groundPoints);

	map<Point,bool> label;
	Label lab;
	lab.labeling(label,groundPoints);
	list<Point> onGroundPoints;
	lab.getNoLabelPoints(label,points_,onGroundPoints);
	
	cout<<"输出地上点:";												//输出地上点
	pnt.output1(onGroundPoints);

	//不好用
	//KdTree trees(points_);
	//trees.setNeighboursRadius(0.3);
	//list<Point> roadPoints;
	//densityRoad(trees,10,groundPoints,roadPoints);
	//cout<<"输出道路点：";
	//pnt.output1(roadPoints);
	
	
}

void GroundFilter::getGround( Points &_points1,double _detaH,Points &_points2 )
{

}

void GroundFilter::groundFilters(list<Point> &points_, list<Point> &groundPoints, list<Point> &onGroundPoints)
{	
	Point pnt;
	this->points_ = points_;
	list<Point> primaryPoints;
	statistHistogram(primaryPoints);

	//cout<<"输出初选点数据：";											//输出初选点，高程滤波
	//pnt.output1(primaryPoints);

	voxelFilter(primaryPoints, groundPoints, h, l, w, 0.0);

	//cout << "输出地面点：";												//输出地面点
	//pnt.output1(groundPoints);

	map<Point, bool> label;
	Label lab;
	lab.labeling(label, groundPoints);
	
	lab.getNoLabelPoints(label, this->points_, onGroundPoints);

	//cout << "输出地上点:";												//输出地上点
	//pnt.output1(onGroundPoints);
}
