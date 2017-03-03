#include <time.h>
#include<iomanip>
#include "surfacegrowing_2.h"
#include "label.h"
SurfaceGrowing_2::SurfaceGrowing_2()
{
	n_=10;//���������ٵ���
	rths_=0.3;	//��������ϰ뾶
	dths_=0.08;//���������������
	rthg_=0.3;//ƽ����չ�뾶
	dthg_=0.08;//��ƽ���������
	a_=3.0;//�ǶȲ���������cubeʱʹ��
	d_=0.1;//�������
	rm_=100;	//ͶƱ������ֵ
	vm_=30;//cube�в����ռ������ֵ
	lths_=lthl_=25;
	lthg_=35;
}
bool SurfaceGrowing_2::input()
{//���뺯��
	Point point;	
	point.input1(points_);//���ݶ��뵽list���͵�points_
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
//{//ƽ����չ
//	list<Point> seedRegion,regionPoint,candidatePoint,eligiblePoint,neighborPoints;
//	list<Point>::iterator seedRegionIt,regionPointIt,candidatePointIt,pointsIt;
//	double angle=0,dist=0;	//���ӵ�������ƽ��н�
//	Plane plane,seedPlane,growingPlane,normal;//���ƽ�����
//	int number=0,n=0;
//	Label lab;
//	int snum,rnum;
//	snum=100;
//	rnum=50;
//	//Step1:׼��k��������
//	KdTree tree(points_);//������
//	map<Point,bool> label;
//	//Step2:�����ķ�����
//	map<Point,Plane> pointNormal;	//�洢��ķ�����
//	tree.setNumberOfNeighbours(10);	//�ҳ��ٽ���
//	pointsNormal(tree,pointNormal);//����ÿ����ķ�����
//	/*cout<<"���normal:";
//	output(pointNormal);
//	cout<<"\nouver:"<<endl;
//	int aa;
//	cin>>aa;*/
//	int num=0;
//	for (pointsIt=points_.begin();pointsIt!=points_.end();++pointsIt)			//��������û��ǩ�ĵ�
//	{
//		if (label[*pointsIt])													//���˵㱻����Թ�
//		{
//			continue;
//		}
//		tree.setNumberOfNeighbours(snum);//snum=100
//		//tree.setNeighboursRadius(rths_);										//���Ӱ뾶
//		tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);            //������ǰ���snum�����
//		neighborPoints=tree.getNearestNeighbor();								//�����(���ڱ��&δ���)
//		//plane=houghTranform(neighborPoints);									//����任,����ƽ�����
//		if (!houghTranform(neighborPoints,plane))
//		{
//			continue;
//		}
//		number=countNum(plane,neighborPoints);									//����㵽���ƽ�����С��dths�ĵ���n1
//		dist=point2plane(*pointsIt,plane);
//		if (number>n_&&dist<dths_)												//�������ӵ㵽���ƽ��ľ���
//		{
//			seedPlane=plane;													//�������ҵ�
//		}else
//		{
//			continue;
//		}
//		regionPoint=neighborPoints;												//�洢��ƽ���(δ���)										
//		lab.removeLabeledPoints(label,regionPoint);								//���б�ǩ�������ȥ��
//		lab.labeling(label,regionPoint);										//��Ǵ������
//		//Step4:ƽ����չ
//		growingPlane=seedPlane;													//������������Ϊ��չƽ��
//		seedRegion=regionPoint;
//		tree.setNumberOfNeighbours(rnum);
//		//tree.setNeighboursRadius(rthg_);										//��չ�������뾶
//		n=0;
//		for (seedRegionIt=seedRegion.begin();seedRegionIt!=seedRegion.end();++seedRegionIt)
//		{
//			tree.kNearestNeighbor(seedRegionIt->x,seedRegionIt->y,seedRegionIt->z);
//			candidatePoint=tree.getNearestNeighbor();
//			lab.removeLabeledPoints(label,candidatePoint);						//����ѡ�����Ѿ���ǹ��ĵ�ȥ��
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
//				label[*candidatePointIt]=true;							//��Ǵ˵�
//				regionPoint.push_back(*candidatePointIt);				//���������
//				if (angle<10)
//				{
//					seedRegion.push_back(*candidatePointIt);			//�������ӵ�
//				}
//				if (n%50==0)
//				{
//					growingPlane=growingPlane.compute(seedRegion);		//����ƽ�����
//				}
//			}
//		}
//		if (regionPoint.size())													//ȷ������㲻����0
//		{
//			segments_.push_back(regionPoint);
//		}
//	}
//	//lab.getNoLabelPoints(label,points_,eligiblePoint);
//	//segments_.push_back(eligiblePoint);
//}
bool SurfaceGrowing_2::houghTranform( list<Point> &_pnt,Plane_2 &_plane )//_pnt��snum����㣬_plane��õ�ƽ��
{
	//��ȡ���������ߵĵ㣬����֮�������һ����ֵ��Χ�ڣ����������ȷ����һ��ƽ���ƽ�����
	vector<Point> vecPnt;
	vecPnt.resize(_pnt.size());
	list<Point>::iterator _pntIt;
	int n=0;
	for (_pntIt=_pnt.begin();_pntIt!=_pnt.end();++_pntIt)
	{//��vector�洢��ԭ���Ǳ������±����Ԫ��
		vecPnt[n++]=*_pntIt;
	}
	found_.clear();//����任ʱʹ�ã���֤ĳ�����ʱ���Ѿ�������map<Pos3D,bool> found_;
	srand((int)time(NULL));//�����srand()�ŵ�ѭ������,����ѭ����,ֻ������һ����������rand()��������������н���ͬ


	map<Point,int> vote;//��ʱPoint�д�Ų����ռ��еĲ�����int �Ǵ�cube�в����ĸ���
	int i=0;
	map<Pos3D,Vote> cube;
	int N=factorN(_pnt.size())/6;	//����ѭ������
	list<Point> points;
	while(i<rm_)//rm_ͶƱ������ֵ
	{
		//points=randPoints(vecPnt);
		if (!randPoints(vecPnt,points))	//�����ȡ�������ʵ�������
		{
			return false;
		}
		//����ҵ��������������ĵ㣬����ƽ�����
		_plane=_plane.compute(points);	//����ƽ�����
		if (productCube(_plane,cube))
		{
			return true;
		}
		++i;
	}
	//cout<<"����ѭ��������"<<i<<endl;
	//���������ռ����з����Ӧ�ۼ�����ѡ���ۼ�������Ǹ�С����Ĳ���
	foreachCube(cube,_plane);//��ͶƱ���Ĳ���
	return true;
}
int SurfaceGrowing_2::factorN( int _n )
{//����n�Ľ׳�n!
	int n=1,i;
	for (i=1;i<=_n;++i)
	{
		n=n*i;
	}
	return n;
}
bool SurfaceGrowing_2::randPoints( vector<Point> &_pnt,list<Point> &_point )
{
	_point.clear();	//��գ��洢������
	double dist1,dist2,dist3;	//��ű߳�
	int num[3]={};
	map<Pos3D,bool>::iterator foundIt;
	Pos3D pos;
	int i=0;//N=factorN(_pnt.size())/6;	//����ѭ������
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
		foundIt=found_.find(pos);//�����������±������Ƿ��Ѿ����ڹ�
		if (foundIt!=found_.end())	//˵��ѡ���������Ѿ���Ϲ�
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
		//cout<<"�����ʱѭ��������"<<i<<endl;
		return true;
	}
	return false;
}
bool SurfaceGrowing_2::productCube( Plane_2 &_plane,map<Pos3D,Vote> &cube )
{
	Pos3D key;
	double e_=0.5,pi=3.14159265;
	Point  para;
	para.x=acos(_plane.a)*180.0/pi;	//�����ռ�������Ȼ��Ƕ�
	para.y=acos(_plane.b)*180.0/pi;
	para.z=_plane.d;
	key.i=int((para.x+e_)/a_);//a_�ǶȲ���������cubeʱʹ��a_=3.0;//�ǶȲ���������cubeʱʹ��
	key.j=int((para.y+e_)/a_);
	key.k=int((para.z+e_)/d_);//d_�������d_=0.1;//�������
	cube[key].paraVote_=para;//paraVote_���������Ĳ���
	cube[key].vote_++;//vote_��¼cube�в����ĸ���
	if (cube[key].vote_>vm_)//vm_��cube�в����ռ������ֵ//cube�в����ռ������ֵ
	{
		return true;
	}
	return false;
}
void SurfaceGrowing_2::foreachCube( map<Pos3D,Vote> &_cube,Plane_2 &_plane )
{//��ͶƱ���Ĳ���
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
	//����䷨����,p1��p2����ֱ�ߵķ�������
	l=p2.x-p1.x;
	m=p2.y-p1.y;
	n=p2.z-p1.z;
	double a,b,c;//p3��p1����
	a=p3.x-p1.x;
	b=p3.y-p1.y;
	c=p3.z-p1.z;
	double e,f,g;//������˽��
	e=b*n-c*m;
	f=c*l-a*n;
	g=a*m-b*l;
	return sqrt(e*e+f*f+g*g)/sqrt(l*l+m*m+n*n);
}
void SurfaceGrowing_2::pointsNormal( KdTree &_tree,map<Point,Plane_2> &_normal )
{//����ÿ����ķ�����
	Plane_2 plane;
	list<Point> neighbor;
	list<Point>::iterator pointsIt;
	//_tree.setNumberOfNeighbours(20);//�ҳ��ٽ���
	for (pointsIt=points_.begin();pointsIt!=points_.end();++pointsIt)//points_��list<Point>����
	{
		_tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);
		neighbor=_tree.getNearestNeighbor();
		plane=plane.compute(neighbor);//����ƽ��Ĳ���������ֵ��Plane��
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
	//cout<<"���ӵ㣺"<<dist<<endl;
	return dist;
}
//bool SurfaceGrowing::output()
//{
//	string ofilePath;
//	cout<<"�������·��\n";
//	cin>>ofilePath;
//	ofstream ofile;
//	ofile.open(ofilePath);
//	if(!ofile)
//	{
//		cout<<"����ļ��޷��򿪣�"<<endl;
//		return false;
//	}
//	list<list<Point>>::iterator listIt;
//	list<Point>::iterator it;
//	int r=0,g=0,b=0;//��ɫֵ
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
void SurfaceGrowing_2::output( list<list<Point>> &_segments )//�������ɫֵ����
{
	string ofilePath;
	cout<<"�������·��\n";
	cin>>ofilePath;

	ofstream ofile;
	ofile.open(ofilePath);
	if(!ofile)
	{
		cout<<"����ļ��޷��򿪣�"<<endl;
		return ;
	}
	list<list<Point>>::iterator listIt;
	list<Point>::iterator it;
	int r=0,g=0,b=0;//��ɫֵ
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
	std::cout << "�ϲ���ƽ��ĸ�����" << allPlane.size() << std::endl;
}
void SurfaceGrowing_2::output( const map<Point,Plane_2> &_normal )//��������ߵĵ�
{
	string ofilePath;
	cout<<"�������·��\n";
	cin>>ofilePath;
	ofstream ofile;
	ofile.open(ofilePath);
	if(!ofile)
	{
		cout<<"����ļ��޷��򿪣�"<<endl;
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
//	for (it=segments_.begin();it!=segments_.end();++it)//�洢��Ƭ��
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
//	cout<<"ǽ��\n";
//	output(wall);
//	cout<<"��ǽ��\n";
//	output(noWall);
//}
void SurfaceGrowing_2::surfaceGrowing1(list<list<Point>> &segments_)
{
	list<Point> seedRegion,regionPoint,candidatePoint,eligiblePoint,neighborPoints,tempPonits;
	list<Point>::iterator seedRegionIt,regionPointIt,candidatePointIt,pointsIt;
	double angle=0,dist=0;	//���ӵ�������ƽ��н�
	Plane_2 plane,seedPlane,growingPlane,normal;//���ƽ�����
	int number=0,n=0,tempNum=0,tempNum1=0;
	Label lab;
	int snum,rnum;
	snum=30;
	n_=10;
	rnum=10;
	//Step1:׼��k��������
	KdTree tree(points_);//������
	map<Point,bool> label;
	////Step2:�����ķ�����
	//map<Point,Plane> pointNormal;	//�����ķ�����
	//pointsNormal(tree,pointNormal);
	//
	int num=0;
	for (pointsIt=points_.begin();pointsIt!=points_.end();++pointsIt)//��������û��ǩ�ĵ�
	{
		if (label[*pointsIt])	//���˵㱻����Թ�
		{
			continue;
		}
		tree.setNumberOfNeighbours(snum);//snum=30;
		//tree.setNeighboursRadius(rths_);	//���Ӱ뾶
		tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);
		neighborPoints=tree.getNearestNeighbor();//�����(���ڱ��&δ���)neighborPoints��list<Point>����
		//plane=houghTranform(neighborPoints);	//����任,����ƽ�����
		if (!houghTranform(neighborPoints,plane))
		{//�Ҳ���ƽ���continue��
			continue;
		}
		number=countNum(plane,neighborPoints);	//����㵽���ƽ�����С��dths�ĵ���number
		dist=point2plane(*pointsIt,plane);
		if (number>n_&&dist<dths_)//n_���������ٵĵ�����number����㵽����ƽ��ľ���С����ֵ�ĵ������������ӵ㵽���ƽ��ľ���
		{
			seedPlane=plane;//�������ҵ�
		}
		else
		{
			continue;
		}
		regionPoint=neighborPoints;	//�洢��ƽ���(δ���)	//list<Point> seedRegion,regionPoint
		//�����ǰ��regionPoint�еĵ��Ѿ���ǰ��ѭ���б���ǣ���ɾ���õ�
		lab.removeLabeledPoints(label,regionPoint);	//���б�ǩ�������ȥ��
		//��ʣ�µ�regionPoint�еĵ����Ѵ���
		lab.labeling(label,regionPoint);//��Ǵ������
		//Step4:ƽ����չ
		//����ĵ�ƽ�������Ϊ������
		growingPlane=seedPlane;	//������������Ϊ��չƽ��
		seedRegion=regionPoint;//list<Point> seedRegion,regionPoint
		tree.setNumberOfNeighbours(rnum);//rnum=10;
		//tree.setNeighboursRadius(0.1);//��չ�������뾶
		n=0;
		tempNum=0;
		for (regionPointIt=regionPoint.begin();regionPointIt!=regionPoint.end();++regionPointIt)
		{//�������������ڵĵ�
			tempNum1=tree.kNearestNeighbor(regionPointIt->x,regionPointIt->y,regionPointIt->z);//���������ڵĵ��rnum����//�������ٽ������
			candidatePoint=tree.getNearestNeighbor();////ȡ��ѡ��
			lab.removeLabeledPoints(label,candidatePoint);//����ѡ�����Ѿ���ǹ��ĵ�ȥ��
			for (candidatePointIt=candidatePoint.begin();candidatePointIt!=candidatePoint.end();++candidatePointIt)
			{//������ѡ��
				dist=point2plane(*candidatePointIt,growingPlane);//���ѡ�㵽������ľ���
				if (dist>dthg_)//���������ֵ������
				{
					continue;
				}
				++n;
				label[*candidatePointIt]=true;	//��Ǵ˵�
				regionPoint.push_back(*candidatePointIt);//���������
				if (n%30==0)//�������ӵ�һ�������󣬸���ƽ�����
				{//����ƽ�����
					growingPlane=growingPlane.compute(regionPoint);	
				}
			}
		}
		if (regionPoint.size())	//ȷ������㲻����0
		{
			segments_.push_back(regionPoint);
		}
	}
}
bool SurfaceGrowing_2::outputPlane(vector<Plane_2> &allPlane)
{
	string filename;
	std::cout << "ƽ�����·����" << std::endl;
	cin >> filename;
	ofstream FileOut;
	FileOut.open(filename);
	srand((int)time(NULL));
	int r = 0, g = 0, b = 0;//��ɫֵ
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
	std::cout << "�򻯺��ƽ�������" <<allPlane.size()<< std::endl;
}

void SurfaceGrowing_2::OutputLine(Plane_2 plane, list<Point> &Cloud)
{
	string filename;
	std::cout << "���ֱ�����·����" << std::endl;
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