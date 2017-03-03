#ifndef Preprocess_H
#define Preprocess_H
#include<iostream>
#include<vector>
#include<map>
#include"plane_2.h"
#include"../PointClass/point.h"
#include"loadbmp.h"
#include"Location.h"
using namespace std;
#define i_MIN -1000000000
#define i_MAX 10000000000
class Preprocess
{
public:
	Preprocess();
	~Preprocess();
	void InputCloud(vector<Point> &Cloud);
	void GridCloud(vector<Point> &Cloud, map<Location, vector<Point>, ComLocation> &GridCloud, int &width, int &height);
	void process(map<Location, vector<Point>, ComLocation> &GridCloud, int &width, int &height, vector<Point> &SegCloud);
	void OutputCloud(vector<Point> &Cloud);
};



#endif