#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include "../PointClass/point.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"

using namespace std;

class Cass
{
	DL_Dxf* dxf;
	DL_Codes::version exportVersion;
	DL_WriterA* dw;
	
	list<Point> points;
	list<Point> elecPoints;
	list<Point> treePoints;
	list<Point> lightPoints;

	void drawPoint(double x,double y,double z);
	void drawElec(double x,double y,double z);
	void drawTree(double x,double y,double z);
	void drawLight(double x,double y,double z);
	void drawRoom(vector<Point> &_points);
	void drawRoad(vector<Point> &_points);
	void drawPoints(vector<Point> &_points);
	void drawElecs(vector<Point> &_points);
	void drawTrees(vector<Point> &_points);
	void drawLights(vector<Point> &_points);

public:
	string dxfFilePath;
	string txtFilePath;
	

	Cass();

	Cass(string _dxfFilePath);

	~Cass()
	{
		delete dw;
		delete dxf;
	}

	void close();
	void initialDxf();
	void draw();
	void txt2dxf();
	void cassPoint();
	void cassElecs();
	void cassTrees();
	void cassLights();
	
};