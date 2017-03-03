#include <iostream>
#include "buildfootprint.h"
using namespace std;
/*
2015-03-08 by shizhenwei

Original data is ground mobile point clouds.

*/
void main_extractBuilding()
{
	cout << "ExtractBuilding..." << endl;
	BuildFootprint bdf;
	//bdf.reflectImage();
	bdf.featureImage();
}