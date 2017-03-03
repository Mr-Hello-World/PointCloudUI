#ifndef BuildingsFootprint_H
#define BuildingsFootprint_H
#include<iostream>
#include<vector>
#include"Segline.h"
#include"../PointClass/point.h"
#include<cmath>
using namespace std;
class BuildingsFootprint_2
{
public:
	BuildingsFootprint_2();
	~BuildingsFootprint_2();
	void MergerFootprint_2(vector<Segline> &allSegline);//合并在一定阈值范围内的点
	void CalFootprint_2(vector<Segline> &allSegline,vector<Point> &Footprint);//得到一定顺序的建筑物脚点
	void OutputFootprint_2(vector<Point> &Footprint);//格式输出建筑物脚点
private:
	Point CrossPoint_line_2(const Segline &line1, const Segline &line2);//求两条直线的脚点
	double Caldist_2(const Point &a, const Point &b);
	bool Noequeal_2(const Point &a, const Point &b);
};

BuildingsFootprint_2::BuildingsFootprint_2()
{
}
bool BuildingsFootprint_2::Noequeal_2(const Point &a, const Point &b)
{
	if (a.x == b.x&&a.y == b.y&&a.z == b.z)
		return false;
	return true;
}
BuildingsFootprint_2::~BuildingsFootprint_2()
{
}
double BuildingsFootprint_2::Caldist_2(const Point &a, const Point &b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
void BuildingsFootprint_2::MergerFootprint_2(vector<Segline> &allSegline)
{
	double threshold = 1.0;
	for (vector<Segline>::iterator SeglineIt_1 = allSegline.begin(); SeglineIt_1 != allSegline.end(); SeglineIt_1++)
	{
		//求当前线段的端点1与其他线段的所有线段端点的关系；
		bool flag = false;
		Point ver1 = SeglineIt_1->vertex1;//
		if (flag == false)
		{
			for (vector<Segline>::iterator SeglineIt_2 = allSegline.begin(); SeglineIt_2 != allSegline.end(); ++SeglineIt_2)
			{
				if (SeglineIt_1 == SeglineIt_2)//如果是同一条线段
					continue;
				if (SeglineIt_1->a*SeglineIt_2->a + SeglineIt_1->b*SeglineIt_2->b > 0.1)//两条直线近似平行
					continue;

				double dist_1 = Caldist_2(ver1, SeglineIt_2->vertex1);
				if (dist_1 < threshold)//如果两端点距离小于阈值，将这两点合并，求两条直线的交点作为新的线段的端点
				{
					Point crossPoint = CrossPoint_line_2(*SeglineIt_1, *SeglineIt_2);
					SeglineIt_1->vertex1 = crossPoint;
					SeglineIt_2->vertex1 = crossPoint;
					flag = true;
					break;
				}
				double dist_2 = Caldist_2(ver1, SeglineIt_2->vertex2);
				if (dist_2 < threshold)
				{
					Point crossPoint = CrossPoint_line_2(*SeglineIt_1, *SeglineIt_2);
					SeglineIt_1->vertex1 = crossPoint;
					SeglineIt_2->vertex2 = crossPoint;
					flag = true;
					break;
				}
			}
		}
		if (flag == false)
		{
			Point ver2 = SeglineIt_1->vertex2;
			for (vector<Segline>::iterator SeglineIt_2 = allSegline.begin(); SeglineIt_2 != allSegline.end(); ++SeglineIt_2)
			{
				if (SeglineIt_1 == SeglineIt_2)//如果是同一条线段
					continue;
				if (SeglineIt_1->a*SeglineIt_2->a + SeglineIt_1->b*SeglineIt_2->b > 0.1)//两条直线近似平行
					continue;
				double dist_1 = Caldist_2(ver2, SeglineIt_2->vertex1);
				if (dist_1 < threshold)
				{
					Point crossPoint = CrossPoint_line_2(*SeglineIt_1, *SeglineIt_2);
					SeglineIt_1->vertex2 = crossPoint;
					SeglineIt_2->vertex1 = crossPoint;
					flag = true;
					break;
				}
				double dist_2 = Caldist_2(ver2, SeglineIt_2->vertex2);
				if (dist_2 < threshold)
				{
					Point crossPoint = CrossPoint_line_2(*SeglineIt_1, *SeglineIt_2);
					SeglineIt_1->vertex2 = crossPoint;
					SeglineIt_2->vertex2 = crossPoint;
					flag = true;
					break;
				}
			}
		}
		//求当前线段的端点1与其他线段的所有线段端点的关系；
		
	}
}
void BuildingsFootprint_2::CalFootprint_2(vector<Segline> &allSegline, vector<Point> &Footprint)
{
	//只有一条线段
	if (allSegline.size() == 0)
	{
		Footprint.push_back(allSegline[0].vertex1);
		Footprint.push_back(allSegline[0].vertex2);
	}
	//如果有两条线段，则需要求出建筑物的另外一个脚点
	if (allSegline.size()==2)
	{
		vector<Segline>::iterator SeglineIt1, SeglineIt2;
		SeglineIt1 = allSegline.begin();
		SeglineIt2 = allSegline.end() - 1;
		Point point1, point2, point3,point4;
		point1.z = point2.z = point3.z = point4.z = 0.0;
		point1 = SeglineIt1->vertex1;
		point2 = SeglineIt1->vertex2;
		if (Noequeal_2(SeglineIt2->vertex1, point1) && Noequeal_2(SeglineIt2->vertex1, point2))
		{
			point3 = SeglineIt2->vertex1;
		}
		else
		{
			point3 = SeglineIt2->vertex2;
		}
		//求角p1p2p3,
		double distP1P2, distP1P3, distP2P3;
		distP1P2 = Caldist_2(point1, point2);
		distP1P3 = Caldist_2(point1, point3);
		distP2P3 = Caldist_2(point2, point3);
		double angle = acos((distP1P2*distP1P2 + distP2P3*distP2P3 - distP1P3*distP1P3) / (2 * distP1P2*distP2P3));
		angle = angle * 180 / 3.14159265;
		if (angle > 80 && angle < 100)
		{
			point4.x = point1.x + point3.x - point2.x;
			point4.y = point1.y + point3.y - point2.y;
		}
		else
		{
			//交换point1和point2
			Point tmp = point1;
			point1 = point2;
			point2 = tmp;
			point4.x = point1.x + point3.x - point2.x;
			point4.y = point1.y + point3.y - point2.y;
		}
		Footprint.push_back(point1);
		Footprint.push_back(point2);
		Footprint.push_back(point3);
		Footprint.push_back(point4);
	}
	//如果有三条线段，则按一定顺序输出建筑物的脚点
	if (allSegline.size() == 3)
	{
		Footprint.resize(4);
		bool flag = false;
		for (vector<Segline>::iterator SeglineIt1 = allSegline.begin(); SeglineIt1 != allSegline.end(); ++SeglineIt1)
		{
			flag = false;
			//判断顶点1
			if (flag == false)
			{
				vector<Segline>::iterator SeglineIt2;
				for (SeglineIt2 = allSegline.begin(); SeglineIt2 != allSegline.end(); ++SeglineIt2)
				{
					if (SeglineIt1 == SeglineIt2)
						continue;
					if (Noequeal_2(SeglineIt1->vertex1, SeglineIt2->vertex1) == false || Noequeal_2(SeglineIt1->vertex1, SeglineIt2->vertex2) == false)
						break;
				}
				if (SeglineIt2 == allSegline.end())
				{
					flag = true;
					Footprint[0] = SeglineIt1->vertex1;
					Footprint[1] = SeglineIt1->vertex2;
				}
					
			}
			//判断顶点2
			if (flag == false)
			{
				vector<Segline>::iterator SeglineIt2;
				for (SeglineIt2 = allSegline.begin(); SeglineIt2 != allSegline.end(); ++SeglineIt2)
				{
					if (SeglineIt1 == SeglineIt2)
						continue;
					if (Noequeal_2(SeglineIt1->vertex2, SeglineIt2->vertex1) == false || Noequeal_2(SeglineIt1->vertex2, SeglineIt2->vertex2) == false)
						break;
				}
				if (SeglineIt2 == allSegline.end())
				{
					flag = true;
					Footprint[0] = SeglineIt1->vertex2;
					Footprint[1] = SeglineIt1->vertex1;
				}
					
			}
			if (flag == true)
				break;
		}


		//求footprint3;
		for (vector<Segline>::iterator SeglineIt1 = allSegline.begin(); SeglineIt1 != allSegline.end(); ++SeglineIt1)
		{
			if (Noequeal_2(SeglineIt1->vertex1, Footprint[1]) == false && Noequeal_2(SeglineIt1->vertex2, Footprint[0]) == true)
			{
				Footprint[2] = SeglineIt1->vertex2;
			}
			else if (Noequeal_2(SeglineIt1->vertex2, Footprint[1]) == false && Noequeal_2(SeglineIt1->vertex1, Footprint[0]) == true)
			{
				Footprint[2] = SeglineIt1->vertex1;
			}
		}
		////求footprint4;
		for (vector<Segline>::iterator SeglineIt1 = allSegline.begin(); SeglineIt1 != allSegline.end(); ++SeglineIt1)
		{
			if (Noequeal_2(SeglineIt1->vertex1, Footprint[2]) == false && Noequeal_2(SeglineIt1->vertex2, Footprint[1]) == true)
			{
				Footprint[3] = SeglineIt1->vertex2;
			}
			else if (Noequeal_2(SeglineIt1->vertex2, Footprint[2]) == false && Noequeal_2(SeglineIt1->vertex1, Footprint[1]) == true)
			{
				Footprint[3] = SeglineIt1->vertex1;
			}
		}
	}

}
Point BuildingsFootprint_2::CrossPoint_line_2(const Segline &line1, const Segline &line2)
{
	Point crossPoint;
	crossPoint.z = 0.0;
	if (line1.a == 0)
	{
		crossPoint.y = line1.d / line1.b;
		crossPoint.x = (line2.d - line2.b*crossPoint.y) / line2.a;
	}
	else if (line1.b==0)
	{
		crossPoint.x = line1.d / line1.a;
		crossPoint.y = (line2.d - line2.a*crossPoint.x) / line2.b;
	}
	else if (line2.a == 0)
	{
		crossPoint.y = line2.d / line2.b;
		crossPoint.x = (line1.d - line1.b*crossPoint.y) / line1.a;
	}
	else if (line1.b == 0)
	{
		crossPoint.x = line2.d / line2.a;
		crossPoint.y = (line1.d - line1.a*crossPoint.x) / line1.b;
	}
	else
	{
		crossPoint.y = (line1.a*line2.d-line2.a*line1.d) / (line1.a*line2.b-line2.a*line1.b);
		crossPoint.x = (line1.d - line1.b*crossPoint.y) / line1.a;
	}
	return crossPoint;
}
void BuildingsFootprint_2::OutputFootprint_2(vector<Point> &Footprint)
{
	string filename;
	std::cout << "建筑物脚点输出路径：" << std::endl;
	cin >> filename;
	ofstream FileOut;
	FileOut.open(filename);
	for (int i = 0; i < Footprint.size(); ++i)
	{
		if (i == 0)
		{
			FileOut << "Begin_Point:";
			FileOut << fixed << setprecision(3) << Footprint[i].x << ' ' << Footprint[i].y << ' ' << Footprint[i].z << endl;
		}
		else if (i == Footprint.size() - 1)
		{
			FileOut << "End_Point:";
			FileOut << fixed << setprecision(3) << Footprint[i].x << ' ' << Footprint[i].y << ' ' << Footprint[i].z << endl;
		}
		else
		{
			FileOut <<"Inter_Point:";
			FileOut << fixed << setprecision(3) << Footprint[i].x << ' ' << Footprint[i].y << ' ' << Footprint[i].z << endl;
		}
		
	}
	FileOut.close();
}
#endif