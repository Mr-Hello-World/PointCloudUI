#include <math.h>
#include "roadshoulder.h"
#include "label.h"
#include "line.h"
//湖南点云
void RoadShoulder::test()
{
	Point pnt;
	cout<<"输入路面边界点:";
	pnt.input1(concourPoints_);

	cout<<"输入原始点云:";
	pnt.input1(points_);

	KdTree tree(points_);
	tree.setNeighboursRadius(0.5);															//设置搜索半径
	list<Point> neighborPoints;
	list<Point> roadShoulderPoints;

	for (list<Point>::iterator it=concourPoints_.begin();it!=concourPoints_.end();++it)		//遍历边界点
	{
		tree.kNearestNeighbor(it->x,it->y,it->z);
		neighborPoints=tree.getNearestNeighbor();
		
		if (ifConcour(neighborPoints,*it,0.1))
		{
			roadShoulderPoints.push_back(*it);
		}else{
			continue;
		}
	}

	cout<<"输出路肩点:\n";
	pnt.output1(roadShoulderPoints);
}

bool RoadShoulder::ifConcour( list<Point> &nei,Point &pnt,double disThr )
{
	for (list<Point>::iterator it=nei.begin();it!=nei.end();++it)
	{
		if (differenceOfElevation(*it,pnt)>disThr)
		{
			return true;
		}
	}

	return false;
}

double RoadShoulder::point2point( Point &pnt1,Point &pnt2 )
{
	return sqrt(pow(pnt1.x-pnt2.x,2)+pow(pnt1.y-pnt2.y,2)+pow(pnt1.z-pnt2.z,2));
}

double RoadShoulder::differenceOfElevation( Point &pnt1,Point &pnt2 )
{
	return abs(pnt1.z-pnt2.z);
}


void RoadShoulder::pointsNormal( KdTree &_tree,map<Point,Plane> &_normal )
{
	Plane plane;
	list<Point> neighbor;
	list<Point>::iterator pointsIt;
	//_tree.setNumberOfNeighbours(20);											//找出临近点
	for (pointsIt=points_.begin();pointsIt!=points_.end();++pointsIt)
	{
		_tree.kNearestNeighbor(pointsIt->x,pointsIt->y,pointsIt->z);
		neighbor=_tree.getNearestNeighbor();
		plane=plane.compute(neighbor);
		_normal[*pointsIt]=plane;
	}
}


//浦石老师数据，效果很好
void RoadShoulder::test3()
{
	Point pnt;
	cout<<"输入地面点云:";
	pnt.input1(points_);

	Voxels voxel;
	double l,m,h,e;
	l=m=h=0.2;
	e=0;
	voxel.setVoxel(l,m,h,e);
	//voxel.getVoxel2DPoints(points_);
	voxel.getVoxel2DPointsInYX(points_);

	map<Pos2D,list<Point>> &voxel2DPoints=voxel.voxel2DPoints_;
	list<Point> roadShoulderPoints;
	map<Pos2D,list<Point>>::iterator beforeIt,afterIt;
	for (map<Pos2D,list<Point>>::iterator mapIt=voxel2DPoints.begin();mapIt!=voxel2DPoints.end();++mapIt)
	{
		//cout<<mapIt->first.i<<" "<<mapIt->first.j<<endl;

		voxelMinz(mapIt);
		voxelMaxz(mapIt);
		
		if (mapIt==voxel2DPoints.begin())
		{
			continue;
		}
		if (mapIt==--voxel2DPoints.end())
		{
			continue;
		}

		beforeIt=--mapIt;
		++mapIt;
		afterIt=++mapIt;
		--mapIt;
		//cout<<"hehe\n";


		if (voxel2DPoints.find(afterIt->first)==voxel2DPoints.end()||voxel2DPoints.find(beforeIt->first)==voxel2DPoints.end())
		{
			continue;
		}

		if (!(beforeIt->first.i==mapIt->first.i&&mapIt->first.i==afterIt->first.i))
		{
			continue;
		}

		if (abs(voxelMinz(mapIt)-voxelMaxz(mapIt))>0.1&&abs(voxelMinz(beforeIt)-voxelMaxz(beforeIt))<0.1&&abs(voxelMinz(afterIt)-voxelMaxz(afterIt))<0.1&&abs(voxelMaxz(beforeIt)-voxelMaxz(afterIt))>0.1)
		{
			roadShoulderPoints.insert(roadShoulderPoints.end(),mapIt->second.begin(),mapIt->second.end());
		}
	}

	/*cout<<"输出路肩点:\n";
	pnt.output1(roadShoulderPoints);*/

	list<Point> initialPoints;
	cout<<"输入原始点云:\n";
	pnt.input1(initialPoints);
	KdTree tree(initialPoints);
	tree.setNeighboursRadius(0.5);															//设置搜索半径
	list<Point> neig;

	list<Point> ros;
	for (list<Point>::iterator it=roadShoulderPoints.begin();it!=roadShoulderPoints.end();++it)
	{
		tree.kNearestNeighbor(it->x,it->y,it->z);
		neig=tree.getNearestNeighbor();
		if (!(valueOfZ(neig,*it)>0.2))
		{
			ros.push_back(*it);
		}

	}
	cout<<"输出路肩点:\n";
	pnt.output1(ros);

}

double RoadShoulder::voxelMinz( map<Pos2D,list<Point>>::iterator &_voxelIt )
{
	list<Point>::iterator it;
	double minZ=10000;
	for (it=_voxelIt->second.begin();it!=_voxelIt->second.end();++it)
	{
		if (minZ>it->z)
		{
			minZ=it->z;
		}
	}
	return minZ;
}

double RoadShoulder::voxelMaxz( map<Pos2D,list<Point>>::iterator &_voxelIt )
{
	list<Point>::iterator it;
	double maxZ=-10000;
	for (it=_voxelIt->second.begin();it!=_voxelIt->second.end();++it)
	{
		if (maxZ<it->z)
		{
			maxZ=it->z;
		}
	}
	return maxZ;
}

double RoadShoulder::voxelMeanZ( map<Pos2D,list<Point>>::iterator &_voxelIt )
{
	double sum=0;
	for (list<Point>::iterator it=_voxelIt->second.begin();it!=_voxelIt->second.end();++it)
	{
		sum+=it->z;
	}
	return sum/(_voxelIt->second.size()*1.0);
}



void RoadShoulder::findCurbVoxel( map<Pos2D,list<Point>> &voxel2DPoints,map<Point,bool> &label ,double thr1,double thr2)
{
	map<Pos2D,list<Point>>::iterator beforeIt1,afterIt1;
	//double before,after,now;

	Label lab;
	map<Pos2D,list<Point>>::iterator tempBegin,tempEnd;
	double slope1,slope2,slope3;
	
	for (map<Pos2D,list<Point>>::iterator mapIt=voxel2DPoints.begin();mapIt!=voxel2DPoints.end();++mapIt)
	{
		//cout<<mapIt->first.i<<" "<<mapIt->first.j<<endl;
		tempBegin=voxel2DPoints.begin();
		tempEnd=voxel2DPoints.end();
		if (mapIt==tempBegin)
		{
			continue;
		}
		if (mapIt==--tempEnd||mapIt==--tempEnd)
		{
			continue;
		}
		
		beforeIt1=--mapIt;
		++mapIt;
		afterIt1=++mapIt;
		--mapIt;

		if (beforeIt1->first.i!=mapIt->first.i||afterIt1->first.i!=mapIt->first.i)
		{
			continue;
		}
		if (abs(voxelMinz(mapIt)-voxelMaxz(mapIt))>thr1&&abs(voxelMinz(beforeIt1)-voxelMaxz(beforeIt1))<thr2&&abs(voxelMinz(afterIt1)-voxelMaxz(afterIt1))<thr2&&abs(voxelMeanZ(beforeIt1)-voxelMeanZ(afterIt1))>thr1)
		{
			slope1=getSlope(mapIt->second);
			slope2=getSlope(beforeIt1->second);
			slope3=getSlope(afterIt1->second);
			//cout<<"坡度："<<getSlope(mapIt->second)<<" "<<getSlope(beforeIt1->second)<<" "<<getSlope(afterIt1->second)<<endl;
			lab.labeling(label,mapIt->second);
			/*if (abs(slope1-slope2)>50&&abs(slope1-slope3)>50&&abs(slope3-slope2)<50)
			{
				lab.labeling(label,mapIt->second);
			}	*/		
		}
		
	}
}

void RoadShoulder::finCurbPoints( KdTree &_tree,list<Point> &points,list<Point> &curbPoints )
{
	list<Point> neig;

	for (list<Point>::iterator it=points.begin();it!=points.end();++it)
	{
		_tree.kNearestNeighbor(it->x,it->y,it->z);
		neig=_tree.getNearestNeighbor();
		
		if (valueOfZLimitByDist(neig,*it,0.2)>0.2)
		{
			curbPoints.insert(curbPoints.end(),curbPoints.begin(),curbPoints.end());
		}
	}
}
double RoadShoulder::valueOfZ( list<Point> &nei,Point &pnt )
{
	double h=-10000;
	double temp;
	for (list<Point>::iterator it=nei.begin();it!=nei.end();++it)
	{
		temp=abs(it->z-pnt.z);
		if (h<temp)
		{
			h=temp;
		}
	}
	//cout<<h<<endl;
	return h;
}
double RoadShoulder::valueOfZLimitByDist( list<Point> &nei,Point &pnt,double limitDist )
{
	double h=-10000;
	double temp;
	for (list<Point>::iterator it=nei.begin();it!=nei.end();++it)
	{
		if (sqrt(pow(it->x-pnt.x,2)+pow(it->y-pnt.y,2))>limitDist||it->z-pnt.z<0)
		{
			continue;
		}
		
		temp=abs(it->z-pnt.z);
		if (h<temp)
		{
			h=temp;
		}
	}
	//cout<<h<<endl;
	return h;
}

bool compete(Point &_pnt1,Point &_pnt2)
{
	return _pnt1.z<_pnt2.z;
}
bool sortX(Point &_pnt1,Point &_pnt2)
{
	return _pnt1.x<_pnt2.x;
}
bool sortY(Point &_pnt1,Point &_pnt2)
{
	return _pnt1.y<_pnt2.y;
}

double RoadShoulder::getSlope(list<Point> _points )
{
	_points.sort(compete);
	double sumErfa=0;
	list<Point>::iterator it=_points.begin(),tempIt;
	for (int i=0;i<_points.size()-1;++i)
	{
		tempIt=it;
		++tempIt;
		sumErfa+=atan((tempIt->z-it->z)/sqrt(pow(it->x-tempIt->x,2)+pow(it->y-tempIt->y,2)));
	}
	return sumErfa*180/3.14159265;
}


void RoadShoulder::findPos2D( map<Pos2D,list<Point>>::iterator &_begin,map<Pos2D,list<Point>>::iterator &_end,Pos2D &_pos2DBefore,Pos2D &_pos2Dback )
{
	_pos2DBefore=_begin->first;


	map<Pos2D,list<Point>>::iterator mapIt=_begin;
	while(mapIt!=_end)
	{
		++mapIt;
		if (mapIt==_end)
		{
			break;
		}

		if (mapIt->first.i!=_pos2DBefore.i)
		{
			break;
		}
	}

	_pos2Dback=(--mapIt)->first;
	_begin=++mapIt;
}


//浦石老师数据，效果最好
void RoadShoulder::test5()
{
	double l,m,h,e;
	l=m=h=0.08;
	e=0;
	cout<<"输入栅格边长(0.08)：\n";
	cin>>h;
	l=m=h;
	cout<<endl;

	cout<<"输入阈值1(0.08)，阈值2(0.08)：\n";
	double thr1,thr2;
	cin>>thr1>>thr2;
	cout<<endl;

	Point pnt;
	cout<<"输入地面点云:";
	pnt.input1(points_);

	Voxels voxel;
	
	voxel.setVoxel(l,m,h,e);

	voxel.getVoxel2DPoints(points_);
	voxel.getVoxel2DPointsInYX(points_);

	list<Point> roadShoulderPoints;

	map<Point,bool> label;
	/*findCurbVoxel(voxel.voxel2DPoints_,label,0.05,0.1);
	findCurbVoxel(voxel.voxel2DPointsYX_,label,0.05,0.1);*/

	findCurbVoxel(voxel.voxel2DPoints_,label,thr1,thr2);
	findCurbVoxel(voxel.voxel2DPointsYX_,label,thr1,thr2);

	list<Point> curbPoints;
	Label lab;
	lab.getLabeledPoints(label,points_,curbPoints);
	cout<<"输出路肩点:\n";
	pnt.output1(curbPoints);


	////begin
	//list<Point> initialPoints;
	//cout<<"输入原始点云:\n";
	//pnt.input1(initialPoints);
	//KdTree tree(initialPoints);
	//tree.setNeighboursRadius(0.5);															//设置搜索半径

	//list<Point> neig;

	//list<Point> ros;
	//for (list<Point>::iterator it=curbPoints.begin();it!=curbPoints.end();++it)
	//{
	//	tree.kNearestNeighbor(it->x,it->y,it->z);
	//	neig=tree.getNearestNeighbor();
	//	//if (!(valueOfZ(neig,*it)>0.2))
	//	if (valueOfZLimitByDist(neig,*it,0.2)<0.2)
	//	{
	//		ros.push_back(*it);
	//	}
	//}

	//KdTree tree2(ros);
	//tree2.setNeighboursRadius(0.5);
	//list<Point> cur;
	//for (list<Point>::iterator it=ros.begin();it!=ros.end();++it)
	//{
	//	if (tree2.kNearestNeighbor(it->x,it->y,it->z)>=3)
	//	{
	//		cur.push_back(*it);
	//	}
	//}
	//
	//cout<<"输出路肩点:\n";
	//pnt.output1(cur);

	////end


	/*voxel.getVoxel3DPoints(initialPoints);
	Pos3D pos3D,temp3D;
	map<Pos3D,list<Point>>::iterator mapIt;
	for (list<Point>::iterator it=curbPoints.begin();it!=curbPoints.end();++it)
	{
	pos3D.i=int((it->x+e)/l);
	pos3D.j=int((it->y+e)/m);
	pos3D.k=int((it->z+e)/h)+1;

	if (voxel.voxel3DPoints_.find(pos3D)==voxel.voxel3DPoints_.end())
	{
	ros.push_back(*it);
	}
	}
	*/
	//KdTree tree(ros);
	//tree.setNeighboursRadius(0.5);															//设置搜索半径
	//list<Point> cur;
	//for (list<Point>::iterator it=ros.begin();it!=ros.end();++it)
	//{
	//	if (tree.kNearestNeighbor(it->x,it->y,it->z)>5)
	//	{
	//		cur.push_back(*it);
	//	}
	//}

	/*cout<<"输出路肩点:\n";
	pnt.output1(ros);*/

}

void RoadShoulder::findRealCur( map<Pos2D,list<Point>>::iterator &_begin,map<Pos2D,list<Point>>::iterator &_end,map<Point,bool> &_label )
{
	map<Pos2D,list<Point>>::iterator _beforeIt,_afterIt,beforeIt,afterIt;

	_beforeIt=_afterIt=beforeIt=afterIt=_begin;
	double maxDist=0,tempDist=0;
	Label lab;
	for (map<Pos2D,list<Point>>::iterator mapIt=_begin;mapIt!=_end;)
	{
		_beforeIt=mapIt;
		_afterIt=++mapIt;
		if (mapIt==_end)
		{
			//_pos2Dback=(--mapIt)->first;
			break;
		}

		if (_beforeIt->first.i!=_afterIt->first.i)
		{
			--_afterIt;
			lab.labeling(_label,beforeIt->second);
			lab.labeling(_label,afterIt->second);

			continue;
		}
		
		tempDist=sqrt(pow(_beforeIt->second.front().x-_afterIt->second.front().x,2)+pow(_beforeIt->second.front().y-_afterIt->second.front().y,2));
		if (tempDist>maxDist)
		{
			maxDist=tempDist;
			cout<<maxDist<<endl;
			beforeIt=_beforeIt;
			afterIt=_afterIt;
		}
	}
}

void RoadShoulder::afterProgress()
{
	Point pnt;

	list<Point> initialCurPoints,groundPoints;
	cout<<"输入初选路肩数据:";
	pnt.input1(initialCurPoints);
	/*cout<<"输入地面数据:";
	pnt.input1(groundPoints);*/

	Voxels voxelCur1,voxelGround1,voxelCur2,voxelGround2;
	double l,m,h,e;
	l=m=h=0.2;
	e=0;
	voxelCur1.setVoxel(l,m,h,e);
	voxelCur1.getVoxel2DPoints(initialCurPoints);
	voxelCur2.setVoxel(l,m,h,e);
	voxelCur2.getVoxel2DPointsInYX(initialCurPoints);

	/*voxelGround1.setVoxel(l,m,h,e);
	voxelGround1.getVoxel2DPoints(groundPoints);
	voxelGround2.setVoxel(l,m,h,e);
	voxelGround2.getVoxel2DPointsInYX(groundPoints);*/
		
	map<Point,bool> label;
	
	findRealCur(voxelCur1.voxel2DPoints_.begin(),voxelCur1.voxel2DPoints_.end(),label);
	findRealCur(voxelCur2.voxel2DPointsYX_.begin(),voxelCur2.voxel2DPointsYX_.end(),label);

	list<Point> shoulderPoints;

	for (list<Point>::iterator it=initialCurPoints.begin();it!=initialCurPoints.end();++it)
	{
		if (label[*it])
		{
			shoulderPoints.push_back(*it);
		}
	}

	cout<<"输出路肩点数据:\n";
	pnt.output1(shoulderPoints);

}

void RoadShoulder::afterProgress2()
{
	Point pnt;

	list<Point> initialCurPoints,initialPoints;
	cout<<"输入初选路肩数据:";
	pnt.input1(initialCurPoints);
	cout<<"输入原始数据:";
	pnt.input1(initialPoints);

	Voxels voxelCur,voxelInitial;
	double l,m,h,e;
	l=m=h=0.08;
	e=0;
	voxelCur.setVoxel(l,m,h,e);
	voxelCur.getVoxel3DPoints(initialCurPoints);

	voxelInitial.setVoxel(l,m,h,e);
	voxelInitial.getVoxel3DPoints(initialPoints);
	Pos3D tempPos3D;
	Label lab;
	map<Point,bool> label;
	for (map<Pos3D,list<Point>>::iterator it=voxelCur.voxel3DPoints_.begin();it!=voxelCur.voxel3DPoints_.end();++it)
	{
		tempPos3D=it->first;
		
		if (judgeRealCur(voxelInitial.voxel3DPoints_,tempPos3D,2))
		{
			lab.labeling(label,it->second);
		}		
	}

	list<Point> shoulderPoints;

	for (list<Point>::iterator it=initialCurPoints.begin();it!=initialCurPoints.end();++it)
	{
		if (label[*it])
		{
			shoulderPoints.push_back(*it);
		}
	}

	cout<<"输出路肩点数据:\n";
	pnt.output1(shoulderPoints);
}



bool RoadShoulder::judgeRealCur( map<Pos3D,list<Point>> &_voxel3D,Pos3D &_pos3D,int _n )
{
	Pos3D pos3D;
	pos3D.k=_pos3D.k+_n;
	map<Pos3D,list<Point>>::iterator tempIt;
	int num=0;
	for (int i=_pos3D.i-1;i<=_pos3D.i+1;++i)
	{
		for (int j=_pos3D.j-1;j<=_pos3D.j+1;++j)
		{
			pos3D.i=i;
			pos3D.j=j;
			
			tempIt=_voxel3D.find(pos3D);
			if (tempIt!=_voxel3D.end())
			{
				num++;
				return false;
			}
		}
	}
	cout<<num<<endl;
	return true;
}

void RoadShoulder::test6()
{
	Point pnt;

	list<Point> initialCurPoints;
	cout<<"输入初选路肩数据:";
	pnt.input1(initialCurPoints);
	
	Voxels voxelCur,voxelInitial;
	double l,m,h,e;
	l=m=h=0.2;
	e=0;
	voxelCur.setVoxel(l,m,h,e);
	voxelCur.getVoxel3DPoints(initialCurPoints);

	cout<<"输出提取路肩长度：";
	cout<<voxelCur.voxel3DPoints_.size()*l<<"m"<<endl;

}


void RoadShoulder::chouxi()
{
	Point pnt;
	list<Point> roads,chouxihou,neig;
	cout<<"read roads:";
	pnt.input1(roads);

	KdTree tree(roads);
	tree.setNeighboursRadius(1);
	Label lab;
	map<Point,bool> label;

	for (list<Point>::iterator it=roads.begin();it!=roads.end();++it)
	{
		if (label[*it])
		{
			continue;
		}
		chouxihou.push_back(*it);

		tree.kNearestNeighbor(it->x,it->y,it->z);
		neig=tree.getNearestNeighbor();

		lab.labeling(label,neig);


	}

	cout<<"write roads:";
	//chouxihou.sort(sortX);
	pnt.output1(chouxihou);


	

}

void RoadShoulder::chouxi(list<Point> &roads, list<Point> &chouxihou)
{
	Point pnt;
	list<Point> neig;
	cout << "read roads:";
	//pnt.input1(roads);

	KdTree tree(roads);
	tree.setNeighboursRadius(1);
	Label lab;
	map<Point, bool> label;

	for (list<Point>::iterator it = roads.begin(); it != roads.end(); ++it)
	{
		if (label[*it])
		{
			continue;
		}
		chouxihou.push_back(*it);

		tree.kNearestNeighbor(it->x, it->y, it->z);
		neig = tree.getNearestNeighbor();

		lab.labeling(label, neig);


	}

	cout << "write roads:";
	//chouxihou.sort(sortX);
	//pnt.output1(chouxihou);
}

void RoadShoulder::cassRoad()
{
	Point pnt;
	list<Point> roads,neig,tempPoints;
	cout<<"read roads:";
	pnt.input1(roads);

	list<list<Point>> clusters,clusters2;
	list<Point> cluster;
	
	KdTree tree(roads);
	tree.setNeighboursRadius(3);
	Label lab;
	map<Point,bool> label;
	
	for (list<Point>::iterator it=roads.begin();it!=roads.end();++it)
	{
		cluster.clear();
		if (label[*it])
		{
			continue;
		}
		label[*it]=true;
		cluster.push_back(*it);
		for (list<Point>::iterator cIt=cluster.begin();cIt!=cluster.end();++cIt)
		{
			tree.kNearestNeighbor(it->x,it->y,it->z);
			neig=tree.getNearestNeighbor();
			tempPoints.clear();
			lab.getNoLabelPoints(label,neig,tempPoints);
			cluster.insert(cluster.end(),tempPoints.begin(),tempPoints.end());
			lab.labeling(label,tempPoints);
		}

		clusters.push_back(cluster);
	}

	cout<<clusters.size()<<endl;

	ThreeDLine line;
	double angx,angy;
	
	for (list<list<Point>>::iterator csIt=clusters.begin();csIt!=clusters.end();++csIt)
	{
		if (csIt->size()<3)
		{
			continue;
		}

		line.computeMLS(*csIt);
		Vecline vx,vy,vl;
		vx.x=1;
		vy.y=1;
		
		vl.x=line.a_;
		vl.y=line.b_;
		vl.z=line.c_;

		angx=line.angleofVec(vx,vl);
		angy=line.angleofVec(vy,vl);

		angx=Radian2Angle(angx);
		angy=Radian2Angle(angy);
		
		if (angx>90)
		{
			angx=180-angx;
		}
		if (angy>90)
		{
			angy=180-angy;
		}
		//cout<<angx<<" "<<angy<<endl;

		if (angx<angy)
		{
			csIt->sort(sortX);
		}else
		{
			csIt->sort(sortY);
		}
		clusters2.push_back(*csIt);
	}

	ofstream ofile;
	cout<<"write roads:";
	string filePath;
	cin>>filePath;

	ofile.open(filePath);

	if (!ofile)
	{
		cout<<"open error!\n";
		return;
	}
	for (list<list<Point>>::iterator csIt=clusters2.begin();csIt!=clusters2.end();++csIt)
	{
		ofile<<"road "<<csIt->size()<<endl;
		for (list<Point>::iterator it=csIt->begin();it!=csIt->end();++it)
		{
			ofile<<it->x<<" "<<it->y<<" "<<it->z<<endl;
		}
	}
}

void RoadShoulder::cassRoad(list<Point> &roads, list<Point> &_points)
{
	Point pnt;
	list<Point> neig, tempPoints;
	cout << "read roads:";
	//pnt.input1(roads);

	list<list<Point>> clusters, clusters2;
	list<Point> cluster;

	KdTree tree(roads);
	tree.setNeighboursRadius(3);
	Label lab;
	map<Point, bool> label;

	for (list<Point>::iterator it = roads.begin(); it != roads.end(); ++it)
	{
		cluster.clear();
		if (label[*it])
		{
			continue;
		}
		label[*it] = true;
		cluster.push_back(*it);
		for (list<Point>::iterator cIt = cluster.begin(); cIt != cluster.end(); ++cIt)
		{
			tree.kNearestNeighbor(it->x, it->y, it->z);
			neig = tree.getNearestNeighbor();
			tempPoints.clear();
			lab.getNoLabelPoints(label, neig, tempPoints);
			cluster.insert(cluster.end(), tempPoints.begin(), tempPoints.end());
			lab.labeling(label, tempPoints);
		}

		clusters.push_back(cluster);
	}

	cout << clusters.size() << endl;

	ThreeDLine line;
	double angx, angy;

	for (list<list<Point>>::iterator csIt = clusters.begin(); csIt != clusters.end(); ++csIt)
	{
		if (csIt->size() < 3)
		{
			continue;
		}

		line.computeMLS(*csIt);
		Vecline vx, vy, vl;
		vx.x = 1;
		vy.y = 1;

		vl.x = line.a_;
		vl.y = line.b_;
		vl.z = line.c_;

		angx = line.angleofVec(vx, vl);
		angy = line.angleofVec(vy, vl);

		angx = Radian2Angle(angx);
		angy = Radian2Angle(angy);

		if (angx > 90)
		{
			angx = 180 - angx;
		}
		if (angy > 90)
		{
			angy = 180 - angy;
		}
		//cout<<angx<<" "<<angy<<endl;

		if (angx < angy)
		{
			csIt->sort(sortX);
		}
		else
		{
			csIt->sort(sortY);
		}
		clusters2.push_back(*csIt);
	}

	/*ofstream ofile;
	cout << "write roads:";
	string filePath;
	cin >> filePath;

	ofile.open(filePath);

	if (!ofile)
	{
	cout << "open error!\n";
	return;
	}*/
	for (list<list<Point>>::iterator csIt = clusters2.begin(); csIt != clusters2.end(); ++csIt)
	{
		//ofile << "road " << csIt->size() << endl;
		for (list<Point>::iterator it = csIt->begin(); it != csIt->end(); ++it)
		{
			//ofile << it->x << " " << it->y << " " << it->z << endl;
			pnt.x = it->x;
			pnt.y = it->y;
			pnt.z = it->z;
			_points.push_back(pnt);
		}
	}
}

void RoadShoulder::sortPointClouds()		//根据x或者y进行排序
{
	Point pnt;
	list<Point> points;
	cout << "read data:";
	pnt.input1(points);

	points.sort(sortX);
	double detaX, detaY;
	detaX = abs(points.front().x - points.back().x);
	points.sort(sortY);
	detaY = abs(points.front().y - points.back().y);

	if (detaY>detaX)
	{
		pnt.output1(points);
	}
	else
	{
		points.sort(sortX);
		pnt.output1(points);
	}
}

void RoadShoulder::sortPointClouds(list<Point> &points)
{
	Point pnt;
	//list<Point> points;
	cout << "read data:";
	//pnt.input1(points);

	points.sort(sortX);
	double detaX, detaY;
	detaX = abs(points.front().x - points.back().x);
	points.sort(sortY);
	detaY = abs(points.front().y - points.back().y);

	if (detaY > detaX)
	{
		//pnt.output1(points);
	}
	else
	{
		points.sort(sortX);
		//pnt.output1(points);
	}
}

void RoadShoulder::shoulderInfor(int ch)
{
	switch (ch)
	{
	case 1:
		test5();
		break;
	//case 2:
	//	rs.afterProgress();
	//	break;
	//case 3:
	//	rs.afterProgress2();
	//	break;
	//case 0:
	//	break;
	default:
		break;
	}

	//sortPointClouds();
}

void RoadShoulder::extractCurbPoints(list<Point> &points_, list<Point> &curbPoints)
{
	double e;
	//l = m = h = 0.08;
	e = 0;
	/*cout << "输入栅格边长(0.08)：\n";
	cin >> h;
	l = m = h;
	cout << endl;*/

	/*cout << "输入阈值1(0.08)，阈值2(0.08)：\n";
	double thr1, thr2;
	cin >> thr1 >> thr2;
	cout << endl;*/

	Point pnt;
	/*cout << "输入地面点云:";
	pnt.input1(points_);*/

	Voxels voxel;

	voxel.setVoxel(l, m, h, e);

	voxel.getVoxel2DPoints(points_);
	voxel.getVoxel2DPointsInYX(points_);

	list<Point> roadShoulderPoints;

	map<Point, bool> label;
	/*findCurbVoxel(voxel.voxel2DPoints_,label,0.05,0.1);
	findCurbVoxel(voxel.voxel2DPointsYX_,label,0.05,0.1);*/

	findCurbVoxel(voxel.voxel2DPoints_, label, thr1, thr2);
	findCurbVoxel(voxel.voxel2DPointsYX_, label, thr1, thr2);

	//list<Point> curbPoints;
	Label lab;
	lab.getLabeledPoints(label, points_, curbPoints);
	//cout << "输出路肩点:\n";
	//pnt.output1(curbPoints);
}
void RoadShoulder::afterProgress(list<Point> &initialCurPoints, list<Point> &shoulderPoints)
{
	Point pnt;

	//list<Point> /*initialCurPoints,*/ groundPoints;
	//cout << "输入初选路肩数据:";
	//pnt.input1(initialCurPoints);
	/*cout<<"输入地面数据:";
	pnt.input1(groundPoints);*/

	Voxels voxelCur1, voxelGround1, voxelCur2, voxelGround2;
	double /*l, m, h, */e;
	//l = m = h = 0.2;
	e = 0;
	voxelCur1.setVoxel(l, m, h, e);
	voxelCur1.getVoxel2DPoints(initialCurPoints);
	voxelCur2.setVoxel(l, m, h, e);
	voxelCur2.getVoxel2DPointsInYX(initialCurPoints);

	/*voxelGround1.setVoxel(l,m,h,e);
	voxelGround1.getVoxel2DPoints(groundPoints);
	voxelGround2.setVoxel(l,m,h,e);
	voxelGround2.getVoxel2DPointsInYX(groundPoints);*/

	map<Point, bool> label;

	findRealCur(voxelCur1.voxel2DPoints_.begin(), voxelCur1.voxel2DPoints_.end(), label);
	findRealCur(voxelCur2.voxel2DPointsYX_.begin(), voxelCur2.voxel2DPointsYX_.end(), label);

	//list<Point> shoulderPoints;

	for (list<Point>::iterator it = initialCurPoints.begin(); it != initialCurPoints.end(); ++it)
	{
		if (label[*it])
		{
			shoulderPoints.push_back(*it);
		}
	}

	//cout << "输出路肩点数据:\n";
	//pnt.output1(shoulderPoints);
}

void RoadShoulder::afterProgress2(list<Point> &initialCurPoints, list<Point> &initialPoints, list<Point> &shoulderPoints)
{
	Point pnt;

	//list<Point> /*initialCurPoints,*/ initialPoints;
	/*cout << "输入初选路肩数据:";
	pnt.input1(initialCurPoints);*/
	//cout << "输入原始数据:";
	//pnt.input1(initialPoints);

	Voxels voxelCur, voxelInitial;
	double /*l, m, h,*/ e;
	//l = m = h = 0.08;
	e = 0;
	voxelCur.setVoxel(l, m, h, e);
	voxelCur.getVoxel3DPoints(initialCurPoints);

	voxelInitial.setVoxel(l, m, h, e);
	voxelInitial.getVoxel3DPoints(initialPoints);
	Pos3D tempPos3D;
	Label lab;
	map<Point, bool> label;
	for (map<Pos3D, list<Point>>::iterator it = voxelCur.voxel3DPoints_.begin(); it != voxelCur.voxel3DPoints_.end(); ++it)
	{
		tempPos3D = it->first;

		if (judgeRealCur(voxelInitial.voxel3DPoints_, tempPos3D, 2))
		{
			lab.labeling(label, it->second);
		}
	}

	//list<Point> shoulderPoints;

	for (list<Point>::iterator it = initialCurPoints.begin(); it != initialCurPoints.end(); ++it)
	{
		if (label[*it])
		{
			shoulderPoints.push_back(*it);
		}
	}

	//cout << "输出路肩点数据:\n";
	//pnt.output1(shoulderPoints);
}