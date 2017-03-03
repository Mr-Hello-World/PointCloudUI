#ifndef POINT_H
#define POINT_H
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

using namespace std;
class Point															//点类用于存放点云数据
{
public:
	double x,y,z;

	friend bool operator<(const Point &_pnta,const Point &_pntb)	//可以用来sort和作为map的key;
	{
		if(_pnta.x<_pntb.x){
			return true;
		}else if(_pnta.x>_pntb.x){
			return false;
		}else if(_pnta.y<_pntb.y){
			return true;
		}else if(_pnta.y>_pntb.y){
			return false;
		}else if(_pnta.z<_pntb.z){
			return true;
		}else if(_pnta.z>_pntb.z){
			return false;
		}else{
			return false;
		}
	}
	bool operator==(const Point &_pnt);								//可以用来unique、remove等，排序后删除相邻相同值;
	void operator=(const Point &_pnt);
	Point();															//构造函数;

	void input1(list<Point> &_points);									//数据读入到list;
	void input2(vector<Point> &_points);								//数据读入到vector;

	void output1(list<Point> &_points);
	void output2(list<list<Point>> &_points);
	void output3(list<list<Point>> &_points);


	double point2point(Point &pnt1, Point &pnt2);
};

typedef list<Point> Points;

class PointRGB: public Point
{
public:
	int r_, g_, b_;
	PointRGB();
	void output1(list<PointRGB> &_points);
};

namespace Szw {
	//class Point: public PointClass 
	//{
	//public:
	//	void loadTxtPCL(const string &filePath, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud)
	//	{
	//		ifstream loadStream_;
	//		loadStream_.close();
	//		loadStream_.clear();
	//		loadStream_.open(filePath);

	//		if (!loadStream_)
	//		{
	//			cout<<"Open readFile fail..."<<endl;
	//			return;
	//		}
	//		
	//		pcl::PointXYZ pntXYZ;
	//		while(!loadStream_.eof()){
	//			loadStream_>>pntXYZ.x>>pntXYZ.y>>pntXYZ.z;
	//			cloud->points.push_back(pntXYZ);
	//		}
	//		cloud->points.pop_back();

	//		cout<<cloud->points.size()<<endl;
	//	}

	//	void loadPCDPCL(const string &filePath, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
	//	{
	//		 pcl::io::loadPCDFile(filePath,*cloud);
	//	}
	//};

	typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudXYZ;
	typedef boost::shared_ptr<pcl::visualization::PCLVisualizer> Viewer;
	typedef pcl::PointCloud<pcl::PointXYZRGBA>::Ptr CloudRGB;
} // namespace Ui

#endif
