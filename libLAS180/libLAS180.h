#pragma once
#include <liblas/liblas.hpp>
#include <fstream>  // std::ifstream
#include <iostream> // std::cout
#include "../PointClass/point.h"
#include "../CloudData/cloudmanage.h"

class LibLAS180
{
public:
	list<Point> *points;
	CloudManage *cloudManage;
	void readLASCloud(std::string _filePath);

};