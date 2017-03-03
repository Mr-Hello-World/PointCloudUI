#include"Preprocess.h"
#include<iomanip>
#include<fstream>
#include<string>
#include<iostream>
using namespace std;
Preprocess::Preprocess()
{

}
Preprocess::~Preprocess()
{

}
void Preprocess::OutputCloud(vector<Point> &Cloud)
{
		string filename;
		std::cout << "输入点云路径:" << std::endl;
		cin >> filename;
		ofstream FileOut;
		FileOut.open(filename);
		for (int i = 0; i < Cloud.size(); ++i)
			FileOut << fixed << setprecision(3) << Cloud[i].x << ' ' << Cloud[i].y << ' ' << Cloud[i].z << endl;
		FileOut.close();
}
void Preprocess::InputCloud(vector<Point> &Cloud)
{
	string filename ;
	std::cout << "输入点云路径：" << std::endl;
	cin >> filename;
	ifstream FileIn;
	FileIn.open(filename);
	Point point;
	while (!FileIn.eof())
	{
		FileIn >> point.x >> point.y >> point.z;
		Cloud.push_back(point);
	}
	FileIn.close();
	std::cout << "读入点数：" << Cloud.size() << std::endl;
}
void Preprocess::GridCloud(vector<Point> &Cloud, map<Location, vector<Point>, ComLocation> &GridCloud, int &width, int &height)
{
	//格网化点云
	double Xmax(i_MIN), Xmin(i_MAX), Ymax(i_MIN), Ymin(i_MAX);
	double Zmin(i_MAX);
	for (int i = 0; i < Cloud.size(); ++i)
	{
		if (Xmax < Cloud[i].x)
			Xmax = Cloud[i].x;
		if (Xmin>Cloud[i].x)
			Xmin = Cloud[i].x;
		if (Ymax < Cloud[i].y)
			Ymax = Cloud[i].y;
		if (Ymin>Cloud[i].y)
			Ymin = Cloud[i].y;
		if (Zmin>Cloud[i].z)
			Zmin = Cloud[i].z;
	}
	double _side = 0.08;
	for (int i = 0; i < Cloud.size(); ++i)
		Cloud[i].z -= Zmin;
	//std::cout << Xmax << std::endl;
	//std::cout << Xmin << std::endl;
	//std::cout << Ymax << std::endl;
	//std::cout << Ymin << std::endl;
	width = ceil((Xmax - Xmin) / _side);
	height = ceil((Ymax - Ymin) / _side);
	std::cout << "width=" << width << std::endl;
	std::cout << "height=" << height << std::endl;
	for (int i = 0; i < Cloud.size(); ++i)
	{
		Location pos;
		pos.i = floor((Cloud[i].y - Ymin) / _side);
		pos.j = floor((Cloud[i].x - Xmin) / _side);
		GridCloud[pos].push_back(Cloud[i]);
	}
}
void Preprocess::process(map<Location, vector<Point>, ComLocation> &GridCloud, int &width, int &height, vector<Point> &SegCloud)
{
	map<Location, vector<Point>, ComLocation>::iterator CloudIt;
	//计算灰度图像
	int *gray = new int[width*height];
	for (int i = 0; i < width*height; ++i)
		gray[i] = 0;
	int num = 0;
	for (CloudIt = GridCloud.begin(); CloudIt != GridCloud.end(); CloudIt++)
	{
		int x = CloudIt->first.i;
		int y = CloudIt->first.j;
		gray[x*width + y] = CloudIt->second.size();
		num += CloudIt->second.size();
	}
	//std::cout << "num=" << num << std::endl;
	int GrayScale = -10;
	for (int i = 0; i<height; ++i)
	{
		for (int j = 0; j<width; ++j)
		{
			if (gray[i*width + j]>GrayScale)
				GrayScale = gray[i*width + j];//计算最大的灰度
		}
	}
	//std::cout << GrayScale << std::endl;

	int lineByte = (width * 24 / 8 + 3) / 4 * 4;
	img* orthoimage = new img[lineByte*height];//计算正射影像
	for (int i = 0; i<height; ++i)
	{
		for (int j = 0; j<width; ++j)
		{
			for (size_t k = 0; k<3; k++)
				orthoimage[i*lineByte + 3 * j + k] = img(255.0*(double)gray[i*width + j] / GrayScale);
		}
	}
	delete[]gray;
	//图像分割
	for (int i = 0; i<height; ++i)
	{
		for (int j = 0; j<width; ++j)
		{
			for (int k = 0; k<3; k++)
			{
				if (orthoimage[i*lineByte + 3 * j + k]>10)
					orthoimage[i*lineByte + 3 * j + k] = 255;
				else
					orthoimage[i*lineByte + 3 * j + k] = 0;
			}

		}
	}
	bmp ortho_seg;
	//cout << "Please Input the Ortho_seg Image File Path" << endl;
	string ortho_seg_imagepath = "1.bmp";
	//cin >> ortho_seg_imagepath;
	ortho_seg.saveimage(ortho_seg_imagepath.c_str(), orthoimage, width, height, 24, NULL);
	//得到分割之后的点云

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (orthoimage[i*lineByte + 3 * j + 0] == 255 && orthoimage[i*lineByte + 3 * j + 1] == 255 && orthoimage[i*lineByte + 3 * j + 2] == 255)
			{
				for (int k = 0; k < GridCloud[Location(i, j)].size(); ++k)
					SegCloud.push_back(GridCloud[Location(i, j)][k]);
			}
		}
	}
	std::cout <<"处理后剩余点数："<< SegCloud.size() << std::endl;

}