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
	cout << "�������ݣ�\n";
	cout << "1 ·����ȡ.\n2 ·����ȡ����1.\n3 ·����ȡ����2.\n0 �˳�!\n";
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