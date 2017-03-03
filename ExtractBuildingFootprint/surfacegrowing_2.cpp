#include <time.h>
#include<iomanip>
#include "surfacegrowing_2.h"
#include "label.h"
SurfaceGrowing_2::SurfaceGrowing_2()
{
	n_=10;//种子面最少点数
	rths_=0.3;	//种子面拟合半径
	dths_=0.08;//到种子面的最大距离
	rthg_=0.3;//平面拓展半径
	dthg_=0.08;//到平面的最大距离
	a_=3.0;//角度参数，建立cube时使用
	d_=0.1;//距离参数
	rm_=100;	//投票次数阈值
	vm_=30;//cube中参数空间个数阈值
	lths_=lthl_=25;
	lthg_=35;
}
bool SurfaceGrowing_2::input()
{//输入函数
	Point point;	
	point.input1(points_);//数据读入到list类型的points_
	return true;
}
bool SurfaceGrowing_2::input(vector<Point> &Cloud)
{
	for (int i = 0; i < Cloud.size(); ++i)
	{
		points_.push_back(Cloud[i]);
	}
	return true;
}
//void SurfaceGrowing::surfaceGrowing()
//{//平面拓展
//	list<Point> seedRegion,regionPoint,candidatePoint,eligiblePoint,neighborPoints;
//	list<Point>::iterator seedRegionIt,regionPointIt,candidatePointIt,pointsIt;
//	double angle=0,dist=0;	//种子点向量与平面夹角
//	Plane plane,seedPlane,growingPlane,normal;//存放平面参数
//	int number=0,n=0;
//	Label lab;
//	int snum,rnum;
//	snum=100;
//	rnum=50;
//	//Step1:准备k邻域数据
//	KdTree tree(points_);//建立树
//	map<Point,bool> label;
//	//Step2:计算点的法相量
//	map<Point,Plane> pointNormal;	//存储点的法相量
//	tree.setNumberOfNeighbours(10);	//找出临近点
//	pointsNormal(tree,pointNormal);//计算每个点的法相量
//	/*cout<<"输出normal:";
//	output(pointNormal);
//	cout<<"\nouver:"<<endl;
//	int aa;
//	cin>>aa;*/
//	int num=0;
//	for (pointsIt=points_.begin();pointsIt!=points_.end();++pointsIt)			//遍历所有没标签的点
//	{
//		if (label[*pointsIt])													//若此点被标记略过
//		{
//			continue;
//		}
//		tree.setNumberOfNeighbours(snum);//snum=100
//		//tree.setNeighboursRadius(rths_);										//种子半径
//		tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);            //搜索当前点的snum邻域点
//		neighborPoints=tree.getNearestNeighbor();								//邻域点(存在标记&未标记)
//		//plane=houghTranform(neighborPoints);									//霍夫变换,计算平面参数
//		if (!houghTranform(neighborPoints,plane))
//		{
//			continue;
//		}
//		number=countNum(plane,neighborPoints);									//邻域点到检测平面距离小于dths的点数n1
//		dist=point2plane(*pointsIt,plane);
//		if (number>n_&&dist<dths_)												//计算种子点到检测平面的距离
//		{
//			seedPlane=plane;													//种子面找到
//		}else
//		{
//			continue;
//		}
//		regionPoint=neighborPoints;												//存储着平面点(未标记)										
//		lab.removeLabeledPoints(label,regionPoint);								//将有标签的区域点去除
//		lab.labeling(label,regionPoint);										//标记此区域点
//		//Step4:平面拓展
//		growingPlane=seedPlane;													//设置种子面作为拓展平面
//		seedRegion=regionPoint;
//		tree.setNumberOfNeighbours(rnum);
//		//tree.setNeighboursRadius(rthg_);										//拓展面搜索半径
//		n=0;
//		for (seedRegionIt=seedRegion.begin();seedRegionIt!=seedRegion.end();++seedRegionIt)
//		{
//			tree.kNearestNeighbor(seedRegionIt->x,seedRegionIt->y,seedRegionIt->z);
//			candidatePoint=tree.getNearestNeighbor();
//			lab.removeLabeledPoints(label,candidatePoint);						//将候选点中已经标记过的点去除
//			for (candidatePointIt=candidatePoint.begin();candidatePointIt!=candidatePoint.end();++candidatePointIt)
//			{
//				dist=point2plane(*candidatePointIt,growingPlane);
//				if (dist>dthg_)
//				{
//					continue;
//				}
//				normal=pointNormal[*candidatePointIt];
//				angle=abs(normal.a*growingPlane.a+normal.b*growingPlane.b+normal.c*growingPlane.c);
//				angle=acos(angle)*180/3.14159265;
//				++n;
//				label[*candidatePointIt]=true;							//标记此点
//				regionPoint.push_back(*candidatePointIt);				//加入区域点
//				if (angle<10)
//				{
//					seedRegion.push_back(*candidatePointIt);			//加入种子点
//				}
//				if (n%50==0)
//				{
//					growingPlane=growingPlane.compute(seedRegion);		//更新平面参数
//				}
//			}
//		}
//		if (regionPoint.size())													//确保区域点不等于0
//		{
//			segments_.push_back(regionPoint);
//		}
//	}
//	//lab.getNoLabelPoints(label,points_,eligiblePoint);
//	//segments_.push_back(eligiblePoint);
//}
bool SurfaceGrowing_2::houghTranform( list<Point> &_pnt,Plane_2 &_plane )//_pnt是snum邻域点，_plane求得的平面
{
	//任取三个不共线的点，三点之间距离在一定阈值范围内，求出这三点确定的一个平面的平面参数
	vector<Point> vecPnt;
	vecPnt.resize(_pnt.size());
	list<Point>::iterator _pntIt;
	int n=0;
	for (_pntIt=_pnt.begin();_pntIt!=_pnt.end();++_pntIt)
	{//用vector存储的原因是便于用下标访问元素
		vecPnt[n++]=*_pntIt;
	}
	found_.clear();//霍夫变换时使用，验证某个组合时候已经搜索过map<Pos3D,bool> found_;
	srand((int)time(NULL));//如果把srand()放到循环外面,它在循环中,只设置了一次种子这样rand()产生的随机数序列将不同


	map<Point,int> vote;//此时Point中存放参数空间中的参数，int 是此cube中参数的个数
	int i=0;
	map<Pos3D,Vote> cube;
	int N=factorN(_pnt.size())/6;	//控制循环次数
	list<Point> points;
	while(i<rm_)//rm_投票次数阈值
	{
		//points=randPoints(vecPnt);
		if (!randPoints(vecPnt,points))	//随机抽取不到合适的三个点
		{
			return false;
		}
		//如果找到三个符合条件的点，计算平面参数
		_plane=_plane.compute(points);	//计算平面参数
		if (productCube(_plane,cube))
		{
			return true;
		}
		++i;
	}
	//cout<<"霍夫循环次数："<<i<<endl;
	//遍历参数空间所有方格对应累加器，选出累加器最大那个小方格的参数
	foreachCube(cube,_plane);//求投票最多的参数
	return true;
}
int SurfaceGrowing_2::factorN( int _n )
{//计算n的阶乘n!
	int n=1,i;
	for (i=1;i<=_n;++i)
	{
		n=n*i;
	}
	return n;
}
bool SurfaceGrowing_2::randPoints( vector<Point> &_pnt,list<Point> &_point )
{
	_point.clear();	//清空，存储三个点
	double dist1,dist2,dist3;	//存放边长
	int num[3]={};
	map<Pos3D,bool>::iterator foundIt;
	Pos3D pos;
	int i=0;//N=factorN(_pnt.size())/6;	//控制循环次数
	while(i<30)
	{
		++i;
		for (int i=0;i<3;++i)
		{
			num[i]=rand()%_pnt.size();
		}
		pos.i=num[0];
		pos.j=num[1];
		pos.k=num[2];
		foundIt=found_.find(pos);//查找这三个下标的组合是否已经存在过
		if (foundIt!=found_.end())	//说明选出的三点已经组合过
		{
			found_[pos]=true;
			continue;
		}
		dist1=pow(_pnt[num[0]].x-_pnt[num[1]].x,2)+pow(_pnt[num[0]].y-_pnt[num[1]].y,2)+pow(_pnt[num[0]].z-_pnt[num[1]].z,2);
		dist1=sqrt(dist1);
		if (dist1<0.15)
		{
			continue;
		}
		dist2=pow(_pnt[num[0]].x-_pnt[num[2]].x,2)+pow(_pnt[num[0]].y-_pnt[num[2]].y,2)+pow(_pnt[num[0]].z-_pnt[num[2]].z,2);
		dist2=sqrt(dist2);
		if (dist2<0.15)
		{
			continue;
		}
		dist3=point2line(_pnt[num[0]],_pnt[num[1]],_pnt[num[2]]);
		if (dist3<0.15)
		{
			continue;
		}
		_point.push_back(_pnt[num[0]]);
		_point.push_back(_pnt[num[1]]);
		_point.push_back(_pnt[num[2]]);
		//cout<<"随机点时循环次数："<<i<<endl;
		return true;
	}
	return false;
}
bool SurfaceGrowing_2::productCube( Plane_2 &_plane,map<Pos3D,Vote> &cube )
{
	Pos3D key;
	double e_=0.5,pi=3.14159265;
	Point  para;
	para.x=acos(_plane.a)*180.0/pi;	//参数空间参数弧度化角度
	para.y=acos(_plane.b)*180.0/pi;
	para.z=_plane.d;
	key.i=int((para.x+e_)/a_);//a_角度参数，建立cube时使用a_=3.0;//角度参数，建立cube时使用
	key.j=int((para.y+e_)/a_);
	key.k=int((para.z+e_)/d_);//d_距离参数d_=0.1;//距离参数
	cube[key].paraVote_=para;//paraVote_存放最后进入的参数
	cube[key].vote_++;//vote_记录cube中参数的个数
	if (cube[key].vote_>vm_)//vm_是cube中参数空间个数阈值//cube中参数空间个数阈值
	{
		return true;
	}
	return false;
}
void SurfaceGrowing_2::foreachCube( map<Pos3D,Vote> &_cube,Plane_2 &_plane )
{//求投票最多的参数
	map<Pos3D,Vote>::iterator _cubeIt;
	int max=0;
	for (_cubeIt=_cube.begin();_cubeIt!=_cube.end();++_cubeIt)
	{
		if (_cubeIt->second.vote_>max)
		{
			max=_cubeIt->second.vote_;
			//_plane=_cubeIt->second.paraVote_;
			_plane.a=cos(_cubeIt->second.paraVote_.x*3.14159265/180.0);
			_plane.b=cos(_cubeIt->second.paraVote_.y*3.14159265/180.0);
			_plane.c=sqrt(1-_plane.a*_plane.a-_plane.b*_plane.b);
			_plane.d=_cubeIt->second.paraVote_.z;
		}
	}
}
double SurfaceGrowing_2::point2line( Point &p1,Point &p2,Point &p3 )
{
	double l,m,n;
	//两点间法相量,p1，p2构成直线的方向向量
	l=p2.x-p1.x;
	m=p2.y-p1.y;
	n=p2.z-p1.z;
	double a,b,c;//p3，p1向量
	a=p3.x-p1.x;
	b=p3.y-p1.y;
	c=p3.z-p1.z;
	double e,f,g;//向量叉乘结果
	e=b*n-c*m;
	f=c*l-a*n;
	g=a*m-b*l;
	return sqrt(e*e+f*f+g*g)/sqrt(l*l+m*m+n*n);
}
void SurfaceGrowing_2::pointsNormal( KdTree &_tree,map<Point,Plane_2> &_normal )
{//计算每个点的法相量
	Plane_2 plane;
	list<Point> neighbor;
	list<Point>::iterator pointsIt;
	//_tree.setNumberOfNeighbours(20);//找出临近点
	for (pointsIt=points_.begin();pointsIt!=points_.end();++pointsIt)//points_是list<Point>类型
	{
		_tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);
		neighbor=_tree.getNearestNeighbor();
		plane=plane.compute(neighbor);//计算平面的参数，返回值是Plane类
		_normal[*pointsIt]=plane;
	}
}
int SurfaceGrowing_2::countNum( Plane_2 &_plane,list<Point> &_neiPnt )
{
	double dist=0.0;
	int num=0;
	list<Point>::iterator _neiPntIt;
	for (_neiPntIt=_neiPnt.begin();_neiPntIt!=_neiPnt.end();++_neiPntIt)
	{
		dist=abs(_neiPntIt->x*_plane.a+_neiPntIt->y*_plane.b+_neiPntIt->z*_plane.c-_plane.d);
		dist=dist/sqrt(pow(_plane.a,2)+pow(_plane.b,2)+pow(_plane.c,2));
		if (dist<dths_)
		{
			++num;
		}
	}
	return num;
}
double SurfaceGrowing_2::point2plane( Point &_point,Plane_2 &_plane )
{
	double dist=0;
	dist=abs(_point.x*_plane.a+_point.y*_plane.b+_point.z*_plane.c-_plane.d);
	//cout<<"种子点："<<dist<<endl;
	return dist;
}
//bool SurfaceGrowing::output()
//{
//	string ofilePath;
//	cout<<"输出数据路径\n";
//	cin>>ofilePath;
//	ofstream ofile;
//	ofile.open(ofilePath);
//	if(!ofile)
//	{
//		cout<<"输出文件无法打开！"<<endl;
//		return false;
//	}
//	list<list<Point>>::iterator listIt;
//	list<Point>::iterator it;
//	int r=0,g=0,b=0;//颜色值
//	int n=0;
//	srand((int)time(NULL));
//	int num = 0;
//	for (listIt=segments_.begin();listIt!=segments_.end();++listIt)
//	{
//		if (listIt->size() < 500)
//			continue;
//		std::cout << ++num << ":" << listIt->size() << std::endl;
//		r=rand()%255;
//		g=rand()%255;
//		b=rand()%255;
//		/*if (listIt->size()<50)
//		{
//		continue;
//		}*/
//		for (it=listIt->begin();it!=listIt->end();++it)
//		{
//			ofile<<n<<" "<<fixed <<setprecision(4)<<it->x<<" "<<it->y<<" "<<it->z<<" "<<r<<" "<<g<<" "<<b<<endl;
//		}
//		++n;
//	}
//	ofile.close();
//	return true;
//}
void SurfaceGrowing_2::output( list<list<Point>> &_segments )//输出带颜色值的面
{
	string ofilePath;
	cout<<"输出数据路径\n";
	cin>>ofilePath;

	ofstream ofile;
	ofile.open(ofilePath);
	if(!ofile)
	{
		cout<<"输出文件无法打开！"<<endl;
		return ;
	}
	list<list<Point>>::iterator listIt;
	list<Point>::iterator it;
	int r=0,g=0,b=0;//颜色值
	int n=0;
	srand((int)time(NULL));

	for (listIt=_segments.begin();listIt!=_segments.end();++listIt)
	{
		/*if (listIt->size() < 300)
			continue;*/
		r=rand()%255;
		g=rand()%255;
		b=rand()%255;
		for (it=listIt->begin();it!=listIt->end();++it)
		{
			ofile<<n<<" "<<fixed<<setprecision(4)<<it->x<<" "<<it->y<<" "<<it->z<<" "<<r<<" "<<g<<" "<<b<<endl;
		}
		++n;
	}
	ofile.close();
}
void SurfaceGrowing_2::MergerPlane(list<list<Point>> &segments_, vector<Plane_2> &allPlane)
{
	list<list<Point>>::iterator listIt;
	for (listIt = segments_.begin(); listIt != segments_.end(); ++listIt)
	{
		//if (listIt->size() < 300)
		//	continue;
		Plane_2 temp;
		temp = temp.compute(*listIt);
		double Normd = sqrt(temp.a*temp.a + temp.b*temp.b + temp.c*temp.c);
		temp.theta = 180.0*acos(temp.c / Normd) / pi;
		temp.distance = temp.d / Normd;
		temp.Pointlist.assign(listIt->begin(), listIt->end());
		allPlane.push_back(temp);
	}
	for (int i = 1; i<allPlane.size(); ++i)
	{
		for (int j = 0; j<i;)
		{
			if (i<allPlane.size())
			{
				if (fabs(allPlane[i].theta - allPlane[j].theta) <= 2.5&&fabs(allPlane[i].distance - allPlane[j].distance) <= 0.1)
				{
					allPlane[j] = allPlane[i];
					swap(allPlane[i], allPlane[allPlane.size() - 1]);
					allPlane.pop_back();
					j = -1;
				}
				j++;
			}
			else
				break;
		}
	}
	std::cout << "合并后平面的个数：" << allPlane.size() << std::endl;
}
void SurfaceGrowing_2::output( const map<Point,Plane_2> &_normal )//输出带法线的点
{
	string ofilePath;
	cout<<"输出数据路径\n";
	cin>>ofilePath;
	ofstream ofile;
	ofile.open(ofilePath);
	if(!ofile)
	{
		cout<<"输出文件无法打开！"<<endl;
		return ;
	}
	map<Point,Plane_2>::const_iterator it;
	for (it=_normal.begin();it!=_normal.end();++it)
	{
		ofile<<it->first.x<<" "<<it->first.y<<" "<<it->first.z<<" "<<-it->second.a<<" "<<-it->second.b<<" "<<-it->second.c<<endl;
	}

	ofile.close();
}
//void SurfaceGrowing::postProcess( double _num )
//{
//	list<list<Point>> wall;
//	list<list<Point>> noWall;
//	list<list<Point>>::iterator it;
//	for (it=segments_.begin();it!=segments_.end();++it)//存储面片点
//	{
//		if (it->size()>_num)
//		{
//			wall.push_back(*it);
//		}
//		else
//		{
//			noWall.push_back(*it);
//		}
//	}
//	cout<<"墙面\n";
//	output(wall);
//	cout<<"非墙面\n";
//	output(noWall);
//}
void SurfaceGrowing_2::surfaceGrowing1(list<list<Point>> &segments_)
{
	list<Point> seedRegion,regionPoint,candidatePoint,eligiblePoint,neighborPoints,tempPonits;
	list<Point>::iterator seedRegionIt,regionPointIt,candidatePointIt,pointsIt;
	double angle=0,dist=0;	//种子点向量与平面夹角
	Plane_2 plane,seedPlane,growingPlane,normal;//存放平面参数
	int number=0,n=0,tempNum=0,tempNum1=0;
	Label lab;
	int snum,rnum;
	snum=30;
	n_=10;
	rnum=10;
	//Step1:准备k邻域数据
	KdTree tree(points_);//建立树
	map<Point,bool> label;
	////Step2:计算点的法相量
	//map<Point,Plane> pointNormal;	//计算点的法相量
	//pointsNormal(tree,pointNormal);
	//
	int num=0;
	for (pointsIt=points_.begin();pointsIt!=points_.end();++pointsIt)//遍历所有没标签的点
	{
		if (label[*pointsIt])	//若此点被标记略过
		{
			continue;
		}
		tree.setNumberOfNeighbours(snum);//snum=30;
		//tree.setNeighboursRadius(rths_);	//种子半径
		tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);
		neighborPoints=tree.getNearestNeighbor();//邻域点(存在标记&未标记)neighborPoints是list<Point>类型
		//plane=houghTranform(neighborPoints);	//霍夫变换,计算平面参数
		if (!houghTranform(neighborPoints,plane))
		{//找不到平面就continue；
			continue;
		}
		number=countNum(plane,neighborPoints);	//邻域点到检测平面距离小于dths的点数number
		dist=point2plane(*pointsIt,plane);
		if (number>n_&&dist<dths_)//n_种子面最少的点数，number邻域点到所求平面的距离小于阈值的点数，计算种子点到检测平面的距离
		{
			seedPlane=plane;//种子面找到
		}
		else
		{
			continue;
		}
		regionPoint=neighborPoints;	//存储着平面点(未标记)	//list<Point> seedRegion,regionPoint
		//如果当前的regionPoint中的点已经在前边循环中被标记，就删掉该点
		lab.removeLabeledPoints(label,regionPoint);	//将有标签的区域点去除
		//将剩下的regionPoint中的点标记已处理
		lab.labeling(label,regionPoint);//标记此区域点
		//Step4:平面拓展
		//将求的的平面参数作为种子面
		growingPlane=seedPlane;	//设置种子面作为拓展平面
		seedRegion=regionPoint;//list<Point> seedRegion,regionPoint
		tree.setNumberOfNeighbours(rnum);//rnum=10;
		//tree.setNeighboursRadius(0.1);//拓展面搜索半径
		n=0;
		tempNum=0;
		for (regionPointIt=regionPoint.begin();regionPointIt!=regionPoint.end();++regionPointIt)
		{//遍历种子区域内的点
			tempNum1=tree.kNearestNeighbor(regionPointIt->x,regionPointIt->y,regionPointIt->z);//找种子面内的点的rnum邻域，//返回最临近点个数
			candidatePoint=tree.getNearestNeighbor();////取候选点
			lab.removeLabeledPoints(label,candidatePoint);//将候选点中已经标记过的点去除
			for (candidatePointIt=candidatePoint.begin();candidatePointIt!=candidatePoint.end();++candidatePointIt)
			{//遍历候选点
				dist=point2plane(*candidatePointIt,growingPlane);//求候选点到种子面的距离
				if (dist>dthg_)//如果大于阈值，舍弃
				{
					continue;
				}
				++n;
				label[*candidatePointIt]=true;	//标记此点
				regionPoint.push_back(*candidatePointIt);//加入区域点
				if (n%30==0)//当点增加到一定数量后，更新平面参数
				{//更新平面参数
					growingPlane=growingPlane.compute(regionPoint);	
				}
			}
		}
		if (regionPoint.size())	//确保区域点不等于0
		{
			segments_.push_back(regionPoint);
		}
	}
}
bool SurfaceGrowing_2::outputPlane(vector<Plane_2> &allPlane)
{
	string filename;
	std::cout << "平面输出路径：" << std::endl;
	cin >> filename;
	ofstream FileOut;
	FileOut.open(filename);
	srand((int)time(NULL));
	int r = 0, g = 0, b = 0;//颜色值
	for (vector<Plane_2>::iterator allPlaneIt = allPlane.begin(); allPlaneIt != allPlane.end(); ++allPlaneIt)
	{
		if (allPlaneIt->Pointlist.size() < 400)
			continue;
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
		std::cout << allPlaneIt->Pointlist.size() << std::endl;
		for (list<Point>::iterator liIt = allPlaneIt->Pointlist.begin(); liIt != allPlaneIt->Pointlist.end(); ++liIt)
		{
			//FileOut << fixed << setprecision(3) << liIt->x << ' ' << (allPlaneIt->d - allPlaneIt->a*liIt->x) / allPlaneIt->b << ' ' << 0 << endl;
			FileOut << fixed << setprecision(3) << liIt->x << ' ' << liIt->y << ' ' << liIt->z <<' ';
			FileOut << r << ' ' << g << ' ' << b << endl;
		}
		//FileOut << endl << endl << endl;
	}
	FileOut.close();
	return true;
}

void SurfaceGrowing_2::DeletePlane(vector<Plane_2> &allPlane)
{
	for (int i = 0; i < allPlane.size(); )
	{
		if (allPlane[i].Pointlist.size() < 400)
		{
			swap(allPlane[i], allPlane[allPlane.size() - 1]);
			allPlane.pop_back();
		}
		else
		{
			i++;
		}
	}
	std::cout << "简化后的平面个数：" <<allPlane.size()<< std::endl;
}

void SurfaceGrowing_2::OutputLine(Plane_2 plane, list<Point> &Cloud)
{
	string filename;
	std::cout << "拟合直线输出路径：" << std::endl;
	cin >> filename;
	ofstream FileOut;
	FileOut.open(filename);
	list<Point>::iterator CloudIt;
	for (CloudIt = Cloud.begin(); CloudIt != Cloud.end(); ++CloudIt)
	{
		FileOut << fixed << setprecision(3) << CloudIt->x << ' ' << (plane.d-plane.a*CloudIt->x)/plane.b << ' ' << 0<< endl;
	}
	FileOut.close();
}