#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
  
using namespace std;

class Coordinate
{
	int firstX,firstY,firstZ;

	ifstream inFile;
	ofstream outFile;
	
	int num;

public:
	string inFilePath;
	string outFilePath;

	Coordinate(double x=0,double y=0,double z=0)
	{
		firstX=x;
		firstY=y;
		firstZ=z;
		
		num=0;
	}
	void setInOutFile();

	void translate(int w=6);

	void setFirstXYZ();


};

#endif	//COORDINATE_H