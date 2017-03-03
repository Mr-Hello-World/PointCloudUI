#include <iostream>
#include "roadshoulder.h"
using std::cout;

void main_shoulder()
{
	cout<<"RoadShoulder...\n";

	RoadShoulder rs;
	//rs.test5();

	//rs.afterProgress();
	//rs.afterProgress2();

	//rs.test6();
	
	//rs.chouxi();
	rs.cassRoad();
	int ch;
	cout << "输入数据：\n";
	cout << "1 路肩提取.\n2 路肩提取后处理1.\n3 路肩提取后处理2.\n0 退出!\n";
	cin >> ch;
	switch (ch)
	{
	case 1:
		rs.test5();
		break;
	case 2:
		rs.afterProgress();
		break;
	case 3:
		rs.afterProgress2();
		break;
	case 0:
		break;
	default:
		break;
	}

	rs.sortPointClouds();
}