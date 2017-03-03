#include <ctime>
#include "surfacegrowing_2.h"
#include"Preprocess.h"
#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<iomanip>
#include"Segline.h"
#include"../ExtractBuildingFootprint/BulidingsFootprint_2.h"
using namespace std;

int main_extractBuildingFootPrint()
{
	vector<Point> Cloud;
	map<Location, vector<Point>, ComLocation> GridCloud;
	vector<Point> SegCloud;
	int width, height;
	Preprocess pre;
	pre.InputCloud(Cloud);
	pre.GridCloud(Cloud, GridCloud, width, height);
	pre.process(GridCloud, width, height, SegCloud);
	list<list<Point>> segments_;
	SurfaceGrowing_2 sur;
	sur.input(SegCloud);
	sur.surfaceGrowing1(segments_);;
	//合并平面
	vector<Plane_2> allPlane;
	sur.MergerPlane(segments_, allPlane);
	sur.DeletePlane(allPlane);
	sur.outputPlane(allPlane);
	vector<Segline> allSegline;
	 for (vector<Plane_2>::iterator PlaneIt = allPlane.begin(); PlaneIt != allPlane.end(); ++PlaneIt)
	{
		Segline line;
		line = line.computeSegline(PlaneIt->Pointlist, *PlaneIt);
		if (line.Length() < 3)//线段的长度阈值
			continue;
		allSegline.push_back(line);
	}
	std::cout << "线段条数："<<allSegline.size() << std::endl;
	//allSegline[0].OutputSegline(allSegline);

	//建筑物脚点合并及求解
	BuildingsFootprint_2 building;
	building.MergerFootprint_2(allSegline);
	//allSegline[0].OutputSegline(allSegline);
	vector<Point> footprint;
	building.CalFootprint_2(allSegline, footprint);
	building.OutputFootprint_2(footprint);
	system("pause");
	return 0;
}