#include "polesextract.h"
#include "label.h"
#include "voxel.h"

bool PolesExtract::detectPole(map<Pos3D,list<Point>> &_voxel3DPoints, Pos3D &_pos3D, int &_voxelNum ,int _pitch)
{
	//throw std::exception("The method or operation is not implemented.");

	int i=0,j=0,k=0,ii,jj,upK;
	bool judge;
	i=_pos3D.i;												//此key的坐标
	j=_pos3D.j;
	k=_pos3D.k;
	judge=true;
	_voxelNum=0;
	upK=k+_pitch;

	map<Pos3D,list<Point>>::iterator tempIt;
	for(k=k-_pitch;k<=upK;++k)								//上下节数为4个。
	{
		Pos3D tempKey(i,j,k);
		tempIt=_voxel3DPoints.find(tempKey);
		if(tempIt==_voxel3DPoints.end())
			return false;
		//break;
		else
		{
			for(ii=i-2,jj=j-2;jj<=j+2;++jj)   
			{
				Pos3D tempkey(ii,jj,k);
				tempIt=_voxel3DPoints.find(tempkey);
				if(tempIt!=_voxel3DPoints.end())
				{
					break;
				}
				else
				{
					++_voxelNum;
				}
			}
			for(jj=j-2;jj<=j+2;jj+=4)
			{
				for(ii=i-1;ii<=i+1;++ii)
				{
					Pos3D tempkey(ii,jj,k);
					tempIt=_voxel3DPoints.find(tempkey);
					if(tempIt!=_voxel3DPoints.end())
					{
						judge=false;
						break;
					}
					else
					{
						++_voxelNum;
					}
				}
				if(judge==false)
					break;
			}
			for(ii=i+2,jj=j-2;jj<=j+2;++jj)
			{
				Pos3D  tempkey(ii,jj,k);
				tempIt=_voxel3DPoints.find(tempkey);
				if(tempIt!=_voxel3DPoints.end())
				{
					break;
				}
				else
				{
					++_voxelNum;
				}
			}
		}
	}

	return true;
}

int PolesExtract::detectTopK( map<Pos3D,list<Point>> &_voxel3DPoints, Pos3D &_pos3D)
{
	Pos3D tempPos3D;
	tempPos3D.k=_pos3D.k;
	map<Pos3D,list<Point>>::iterator findIt;
	int temp=0;
	while(true)
	{
		temp=0;
		for (int i=_pos3D.i-2;i<=_pos3D.i+2;++i)
		{
			for (int j=_pos3D.j-2;j<=_pos3D.j+2;++j)
			{
				tempPos3D.i=i;
				tempPos3D.j=j;
				if (tempPos3D.i==_pos3D.i&&tempPos3D.j==_pos3D.j)
				{
					continue;
				}
				findIt=_voxel3DPoints.find(tempPos3D);
				if (findIt!=_voxel3DPoints.end())
				{
					++temp;
				}
			}
		}
		//cout<<"k:"<<++tempPos3D.k<<" ";
		++tempPos3D.k;
		if (temp<8)
		{
			return --tempPos3D.k;
		}
	}
}

void PolesExtract::getCandidatePoles(map<Pos2D,list<Point>> &_voxel2DPoints, Pos3D &_pos3D,list<Point> &_candidate )
{
	int i=0,j=0;
	Pos2D pos2D;
	pos2D.i=_pos3D.i;
	pos2D.j=_pos3D.j;

	map<Pos2D,list<Point>>::iterator tempIt;

	for (i=_pos3D.i-1;i<=_pos3D.i+1;++i)
	{
		for (j=_pos3D.j-1;j<=_pos3D.j+1;++j)
		{
			pos2D.i=i;
			pos2D.j=j;

			tempIt=_voxel2DPoints.find(pos2D);
			if(tempIt!=_voxel2DPoints.end())
			{
				_candidate.insert(_candidate.end(),tempIt->second.begin(),tempIt->second.end());
			}
		}
	}
}

void PolesExtract::getCandidatePoles( map<Pos3D,list<Point>> &_voxel3DPoints,Pos3D &_topPos3D,map<Pos3D,bool> &_keyLabel,list<Point> &_candidate )
{
	Pos3D tempPos3D=_topPos3D;
	map<Pos3D,list<Point>>::iterator tempIt;
	for (int k=_topPos3D.k;k>=_topPos3D.k-300;--k)
	{
		tempPos3D.k=k;
		tempIt=_voxel3DPoints.find(tempPos3D);
		if (tempIt==_voxel3DPoints.end())
		{
			continue;
		}
		_keyLabel[tempIt->first]=true;
		_candidate.insert(_candidate.begin(),tempIt->second.begin(),tempIt->second.end());
	}
}

double PolesExtract::extreamOfz( list<Point> &_points,double &_minz,double &_maxz )
{
	list<Point>::iterator it;
	_minz=100000;
	_maxz=-100000;
	for (it=_points.begin();it!=_points.end();++it)
	{
		if (it->z>_maxz)
		{
			_maxz=it->z;
		}
		if (it->z<_minz)
		{
			_minz=it->z;
		}
	}
	return abs(_maxz-_minz);
}



void PolesExtract::statisticPolesNum()
{
	/*ofstream ofile;
	cout<<"输入分类后数据文件：\n";
	string ofilePath;
	cin>>ofilePath;
	ofile.open(ofilePath);
	if (!ofile)
	{
	cout<<"error!"<<endl;
	return;
	}*/

	Point pnt;
	cout<<"输poles数据：";
	pnt.input1(points_);
	
	double minz,maxz;
	Voxels voxel;
	voxel.setVoxel(0.3,0.3,0.25,0);
	voxel.getVoxel2D3DPoints(points_);
	Pos2D pos2D;
	map<Pos2D,list<Point>>::iterator voxel2DIt;
	list<Point> treePoints,ligntPoints,elecPoints,otherPoints,tempPoints,temp2Points;
	double H=0;
	int treeNum=0,lightNum=0,electNum=0,otherNum=0;
	map<Pos2D,bool> label2D;
	double weightX,weightY;
	for (map<Pos3D,list<Point>>::iterator voxel3DIt=voxel.voxel3DPoints_.begin();voxel3DIt!=voxel.voxel3DPoints_.end();++voxel3DIt)
	{
		pos2D.i=voxel3DIt->first.i;
		pos2D.j=voxel3DIt->first.j;
		if (label2D[pos2D])
		{
			continue;
		}
		tempPoints.clear();
		for (int i=voxel3DIt->first.i-1;i<=voxel3DIt->first.i+1;++i)
		{
			for (int j=voxel3DIt->first.j-1;j<=voxel3DIt->first.j+1;++j)
			{
				pos2D.i=i;
				pos2D.j=j;

				voxel2DIt=voxel.voxel2DPoints_.find(pos2D);
				if (voxel2DIt==voxel.voxel2DPoints_.end()||label2D[pos2D])
				{
					continue;
				}

				label2D[pos2D]=true;
				tempPoints.insert(tempPoints.end(),voxel2DIt->second.begin(),voxel2DIt->second.end());
			}
		}

		H=extreamOfz(tempPoints,minz,maxz);
		//computeWeightXY(tempPoints,weightX,weightY);
		//ofile<<weightX<<" "<<weightY<<" "<<tempPoints.front().z<<endl;
		/*if (H<1.0)
		{
			continue;
		}else if (H<2.5)
		{
			ofile<<"tree "<<weightX<<" "<<weightY<<endl;
			++treeNum;
		}else if(H<10)
		{
			ofile<<"light "<<weightX<<" "<<weightY<<endl;
			++lightNum;
		}else
		{
			ofile<<"elec "<<weightX<<" "<<weightY<<endl;
			++electNum;
		}*/

		/*if (2.0<H<3.0)
		{
			continue;
		}else if (H<6.0)
		{
			temp2Points.insert(temp2Points.begin(),tempPoints.begin(),tempPoints.end());
			++lightNum;
		}else
		{
			++electNum;
		}*/

		if (H<0.5)
		{
			++otherNum;
			otherPoints.insert(otherPoints.end(),tempPoints.begin(),tempPoints.end());
			continue;
		}else if (H>=0.5&&H<4)
		{			
			++treeNum;
			treePoints.insert(treePoints.end(),tempPoints.begin(),tempPoints.end());
		}else if(H>=4&&H<8)
		{
			++lightNum;
			ligntPoints.insert(ligntPoints.end(),tempPoints.begin(),tempPoints.end());
		}else if(H>=8)
		{
			++electNum;
			elecPoints.insert(elecPoints.end(),tempPoints.begin(),tempPoints.end());
		}
	}

	cout<<"treeNum："<<treeNum<<" lightNum:"<<lightNum<<" elecNum:"<<electNum<<" otherNum:"<<otherNum<<endl;
	cout<<"输出其他点：\n";
	pnt.output1(otherPoints);
	
	cout<<"输出树点：\n";
	pnt.output1(treePoints);

	cout<<"输出路灯点：\n";
	pnt.output1(ligntPoints);

	cout<<"输出电杆点：\n";
	pnt.output1(elecPoints);

	/*cout<<"输出满足高度条件的柱状点云:\n";
	pnt.output1(temp2Points);*/
}


bool PolesExtract::output()
{
	string ofilePath;
	cout<<"输出数据路径\n";
	cin>>ofilePath;

	ofstream ofile;
	ofile.open(ofilePath);
	if(!ofile)
	{
		cout<<"输出文件无法打开！"<<endl;
		return false;
	}
	list<list<Point>>::iterator listIt;
	list<Point>::iterator it;

	for (listIt=poles_.begin();listIt!=poles_.end();++listIt)
	{
		for (it=listIt->begin();it!=listIt->end();++it)
		{
			ofile<<it->x<<" "<<it->y<<" "<<it->z<<endl;
		}
	}
	ofile.close();
	return true;
}

void PolesExtract::test()
{
	Point pnt;
	cout<<"输入数据：";
	pnt.input1(points_);

	map<Point,bool> label;
	Label lab;

	Voxels voxel;
	cout<<"输入阈值(0.2 0.2 0.2)：\n";
	double a,b,c;
	cin>>a>>b>>c;
	voxel.setVoxel(a,b,c,0);		//voxel.setVoxel(0.3,0.3,0.25,0);
	voxel.getVoxel3DPoints(points_);

	Pos3D pos3D;
	int voxelNum=0;
	list<Point> candidate;
	double minz,maxz;

	int spacenumber=80;												//分段周围空间立方体个数
	int pitch=2;													//控制连续体素个数
	double deta_h=2;												//杆状地物高度阈值

	map<Pos3D,bool> keyLabel;

	cout<<voxel.voxel3DPoints_.size();
	for(map<Pos3D,list<Point>>::iterator voxel3DIt=voxel.voxel3DPoints_.begin();voxel3DIt!=voxel.voxel3DPoints_.end();++voxel3DIt)
	{
		pos3D=voxel3DIt->first;
		if (keyLabel[pos3D])
			continue;
		
		voxelNum=0;
		if (!detectPole(voxel.voxel3DPoints_,pos3D,voxelNum,pitch))
			continue;
		/*cout<<"topK:";
		cout<<detectTopK(voxel.voxel3DPoints_,pos3D)<<endl;*/
		Pos3D tempPos3D=pos3D;
		tempPos3D.k=detectTopK(voxel.voxel3DPoints_,pos3D);

		if(voxelNum>=spacenumber/*&&voxel3DIt->second.size()>3*/)	//此时spacenum=80. 可以使用
		{
			getCandidatePoles(voxel.voxel3DPoints_,tempPos3D,keyLabel,candidate);
		}
	}

	candidate.sort();
	candidate.unique();

	cout<<"poles点：\n";
	pnt.output1(candidate);
}

void PolesExtract::computeWeightXY( list<Point> &_points,double &_x,double &_y )
{
	double sumx=0,sumy=0;

	for (list<Point>::iterator it=_points.begin();it!=_points.end();++it)
	{
		sumx+=it->x;
		sumy+=it->y;
	}
	_x=sumx/_points.size();
	_y=sumy/_points.size();
}

void PolesExtract::outputKey()
{
	Point pnt;
	cout<<"输点云数据：";
	list<Point> points;
	pnt.input1(points);

	ofstream ofile;
	cout<<"输出key的存储路径：";
	string ofilePath;
	cin>>ofilePath;
	ofile.open(ofilePath);
	if (!ofile)
	{
		cout<<"key文件输出失败！\n";
		return;
	}
	int i=0;
	for(list<Point>::iterator it=points.begin();it!=points.end();++i)
	{
		if (i%10)
		{
			points.erase(it++);
		}else
		{
			++it;
		}
	}


	Voxels voxel;
	voxel.setVoxel(1,1,1,0);
	voxel.getVoxel2D3DPoints(points);


	for(map<Pos3D,list<Point>>::iterator voxel3DIt=voxel.voxel3DPoints_.begin();voxel3DIt!=voxel.voxel3DPoints_.end();++voxel3DIt)
	{
		ofile<<voxel3DIt->first.i<<" "<<voxel3DIt->first.j<<" "<<voxel3DIt->first.k<<endl;
	}
	ofile.close();
	
	cout<<"输出2Dkey：";
	string ofilePa;
	cin>>ofilePa;
	ofile.open(ofilePa);

	for(map<Pos2D,list<Point>>::iterator voxel2DIt=voxel.voxel2DPoints_.begin();voxel2DIt!=voxel.voxel2DPoints_.end();++voxel2DIt)
	{
		ofile<<voxel2DIt->first.i<<" "<<voxel2DIt->first.j<<endl;
	}
	ofile.close();

	cout<<"输出抽稀后点：\n";
	pnt.output1(points);
}

void PolesExtract::computeCoordofPoles()
{
	ofstream ofile;
	cout<<"输入分类后数据文件：\n";
	string ofilePath;
	cin>>ofilePath;
	ofile.open(ofilePath);
	if (!ofile)
	{
		cout<<"error!"<<endl;
		return;
	}

	Point pnt;
	cout<<"输poles数据：";
	pnt.input1(points_);

	list<Point> pointss;
	cout<<"输点数据：";
	pnt.input1(pointss);


	double minz,maxz;
	Voxels voxel;
	voxel.setVoxel(0.3,0.3,0.25,0);
	voxel.getVoxel2D3DPoints(points_);
	Pos2D pos2D;
	map<Pos2D,list<Point>>::iterator voxel2DIt;
	list<Point> treePoints,ligntPoints,elecPoints,otherPoints,tempPoints,temp2Points;
	double H=0;
	int treeNum=0,lightNum=0,electNum=0,otherNum=0;
	map<Pos2D,bool> label2D;
	double weightX,weightY;
	for (map<Pos3D,list<Point>>::iterator voxel3DIt=voxel.voxel3DPoints_.begin();voxel3DIt!=voxel.voxel3DPoints_.end();++voxel3DIt)
	{
		pos2D.i=voxel3DIt->first.i;
		pos2D.j=voxel3DIt->first.j;
		if (label2D[pos2D])
		{
			continue;
		}
		tempPoints.clear();
		for (int i=voxel3DIt->first.i-1;i<=voxel3DIt->first.i+1;++i)
		{
			for (int j=voxel3DIt->first.j-1;j<=voxel3DIt->first.j+1;++j)
			{
				pos2D.i=i;
				pos2D.j=j;

				voxel2DIt=voxel.voxel2DPoints_.find(pos2D);
				if (voxel2DIt==voxel.voxel2DPoints_.end()||label2D[pos2D])
				{
					continue;
				}

				label2D[pos2D]=true;
				tempPoints.insert(tempPoints.end(),voxel2DIt->second.begin(),voxel2DIt->second.end());
			}
		}

		H=extreamOfz(tempPoints,minz,maxz);
		computeWeightXY(tempPoints,weightX,weightY);
		
		if (H<0.5)
		{
			++otherNum;
			ofile<<"other\n"<<weightX<<" "<<weightY<<" "<<tempPoints.front().z<<endl;
		}else if (H>=0.5&&H<4)
		{			
			++treeNum;
			ofile<<"tree\n"<<weightX<<" "<<weightY<<" "<<tempPoints.front().z<<endl;
		}else if(H>=4&&H<8)
		{
			++lightNum;
			ofile<<"light\n"<<weightX<<" "<<weightY<<" "<<tempPoints.front().z<<endl;
		}else if(H>=8)
		{
			++electNum;
			ofile<<"elec\n"<<weightX<<" "<<weightY<<" "<<tempPoints.front().z<<endl;
		}
	}
	for (list<Point>::iterator it=pointss.begin();it!=pointss.end();++it)
	{
		ofile<<"point "<<it->x<<" "<<it->y<<" "<<it->z<<endl;
	}


	ofile.close();
}

void PolesExtract::polesEx(list<Point> &points_, list<Point> &candidate)
{
	Point pnt;
	/*cout << "输入数据：";
	pnt.input1(points_);*/

	map<Point, bool> label;
	Label lab;

	Voxels voxel;
	//cout << "输入阈值(0.2 0.2 0.2)：\n";
	//double a, b, c;
	//cin >> a >> b >> c;
	voxel.setVoxel(a, b, c, 0);		//voxel.setVoxel(0.3,0.3,0.25,0);
	voxel.getVoxel3DPoints(points_);

	Pos3D pos3D;
	int voxelNum = 0;
	//list<Point> candidate;
	double minz, maxz;

	//int spacenumber = 80;												//分段周围空间立方体个数
	//int pitch = 2;													//控制连续体素个数
	//double deta_h = 2;												//杆状地物高度阈值

	map<Pos3D, bool> keyLabel;

	cout << voxel.voxel3DPoints_.size();
	for (map<Pos3D, list<Point>>::iterator voxel3DIt = voxel.voxel3DPoints_.begin(); voxel3DIt != voxel.voxel3DPoints_.end(); ++voxel3DIt)
	{
		pos3D = voxel3DIt->first;
		if (keyLabel[pos3D])
			continue;

		voxelNum = 0;
		if (!detectPole(voxel.voxel3DPoints_, pos3D, voxelNum, pitch))
			continue;
		/*cout<<"topK:";
		cout<<detectTopK(voxel.voxel3DPoints_,pos3D)<<endl;*/
		Pos3D tempPos3D = pos3D;
		tempPos3D.k = detectTopK(voxel.voxel3DPoints_, pos3D);

		if (voxelNum >= spacenumber/*&&voxel3DIt->second.size()>3*/)	//此时spacenum=80. 可以使用
		{
			getCandidatePoles(voxel.voxel3DPoints_, tempPos3D, keyLabel, candidate);
		}
	}
	candidate.sort();
	candidate.unique();
	cout << "poles点：\n";
	//pnt.output1(candidate);
}

int PolesExtract::statisticPolesNumandClassify(list<Point> &points_, list<list<Point>> &polesclass)
{
	Point pnt;
	//cout << "输poles数据：";
	//pnt.input1(points_);

	double minz, maxz;
	Voxels voxel;
	voxel.setVoxel(a, b, c, 0);
	voxel.getVoxel2D3DPoints(points_);
	Pos2D pos2D;
	map<Pos2D, list<Point>>::iterator voxel2DIt;
	list<Point> treePoints, ligntPoints, elecPoints, otherPoints, tempPoints, temp2Points;
	double H = 0;
	int treeNum = 0, lightNum = 0, electNum = 0, otherNum = 0;
	map<Pos2D, bool> label2D;
	double weightX, weightY;
	for (map<Pos3D, list<Point>>::iterator voxel3DIt = voxel.voxel3DPoints_.begin(); voxel3DIt != voxel.voxel3DPoints_.end(); ++voxel3DIt)
	{
		pos2D.i = voxel3DIt->first.i;
		pos2D.j = voxel3DIt->first.j;
		if (label2D[pos2D])
		{
			continue;
		}
		tempPoints.clear();
		for (int i = voxel3DIt->first.i - 1; i <= voxel3DIt->first.i + 1; ++i)
		{
			for (int j = voxel3DIt->first.j - 1; j <= voxel3DIt->first.j + 1; ++j)
			{
				pos2D.i = i;
				pos2D.j = j;

				voxel2DIt = voxel.voxel2DPoints_.find(pos2D);
				if (voxel2DIt == voxel.voxel2DPoints_.end() || label2D[pos2D])
				{
					continue;
				}

				label2D[pos2D] = true;
				tempPoints.insert(tempPoints.end(), voxel2DIt->second.begin(), voxel2DIt->second.end());
			}
		}

		H = extreamOfz(tempPoints, minz, maxz);
		//computeWeightXY(tempPoints,weightX,weightY);
		//ofile<<weightX<<" "<<weightY<<" "<<tempPoints.front().z<<endl;
		/*if (H<1.0)
		{
		continue;
		}else if (H<2.5)
		{
		ofile<<"tree "<<weightX<<" "<<weightY<<endl;
		++treeNum;
		}else if(H<10)
		{
		ofile<<"light "<<weightX<<" "<<weightY<<endl;
		++lightNum;
		}else
		{
		ofile<<"elec "<<weightX<<" "<<weightY<<endl;
		++electNum;
		}*/

		/*if (2.0<H<3.0)
		{
		continue;
		}else if (H<6.0)
		{
		temp2Points.insert(temp2Points.begin(),tempPoints.begin(),tempPoints.end());
		++lightNum;
		}else
		{
		++electNum;
		}*/

		if (H<h1/*0.5*/)
		{
			++otherNum;
			otherPoints.insert(otherPoints.end(), tempPoints.begin(), tempPoints.end());
			continue;
		}
		else if (H >= h1&&H<h2)
		{
			++treeNum;
			treePoints.insert(treePoints.end(), tempPoints.begin(), tempPoints.end());
		}
		else if (H >= h2 && H<h3)
		{
			++lightNum;
			ligntPoints.insert(ligntPoints.end(), tempPoints.begin(), tempPoints.end());
		}
		else if (H >= h3)
		{
			++electNum;
			elecPoints.insert(elecPoints.end(), tempPoints.begin(), tempPoints.end());
		}
	}

	cout << "treeNum：" << treeNum << " lightNum:" << lightNum << " elecNum:" << electNum << " otherNum:" << otherNum << endl;
	//cout << "输出其他点：\n";
	//pnt.output1(otherPoints);

	//cout << "输出树点：\n";
	//pnt.output1(treePoints);

	//cout << "输出路灯点：\n";
	//pnt.output1(ligntPoints);

	//cout << "输出电杆点：\n";
	//pnt.output1(elecPoints);

	/*cout<<"输出满足高度条件的柱状点云:\n";
	pnt.output1(temp2Points);*/
	polesclass.push_back(otherPoints);
	polesclass.push_back(treePoints);
	polesclass.push_back(ligntPoints);
	polesclass.push_back(elecPoints);

	return treeNum + lightNum + electNum + otherNum;
}

void PolesExtract::computeCoordofPoles(list<Point> &points_, list<list<Point>> &centers_)
{
	//ofstream ofile;
	//cout << "输入分类后数据文件：\n";
	//string ofilePath;
	//cin >> ofilePath;
	//ofile.open(ofilePath);
	//if (!ofile)
	//{
	//	cout << "error!" << endl;
	//	return;
	//}

	Point pnt;
	//cout << "输poles数据：";
	//pnt.input1(points_);

	//list<Point> pointss;
	//cout << "输点数据：";
	//pnt.input1(pointss);


	double minz, maxz;
	Voxels voxel;
	voxel.setVoxel(a, b, c, 0);
	voxel.getVoxel2D3DPoints(points_);
	Pos2D pos2D;
	map<Pos2D, list<Point>>::iterator voxel2DIt;
	list<Point> treePoints, ligntPoints, elecPoints, otherPoints, tempPoints, temp2Points;
	double H = 0;
	int treeNum = 0, lightNum = 0, electNum = 0, otherNum = 0;
	map<Pos2D, bool> label2D;
	double weightX, weightY;
	for (map<Pos3D, list<Point>>::iterator voxel3DIt = voxel.voxel3DPoints_.begin(); voxel3DIt != voxel.voxel3DPoints_.end(); ++voxel3DIt)
	{
		pos2D.i = voxel3DIt->first.i;
		pos2D.j = voxel3DIt->first.j;
		if (label2D[pos2D])
		{
			continue;
		}
		tempPoints.clear();
		for (int i = voxel3DIt->first.i - 1; i <= voxel3DIt->first.i + 1; ++i)
		{
			for (int j = voxel3DIt->first.j - 1; j <= voxel3DIt->first.j + 1; ++j)
			{
				pos2D.i = i;
				pos2D.j = j;

				voxel2DIt = voxel.voxel2DPoints_.find(pos2D);
				if (voxel2DIt == voxel.voxel2DPoints_.end() || label2D[pos2D])
				{
					continue;
				}

				label2D[pos2D] = true;
				tempPoints.insert(tempPoints.end(), voxel2DIt->second.begin(), voxel2DIt->second.end());
			}
		}

		H = extreamOfz(tempPoints, minz, maxz);
		computeWeightXY(tempPoints, weightX, weightY);

		if (H < h1/*0.5*/)
		{
			++otherNum;
			//ofile << "other\n" << weightX << " " << weightY << " " << tempPoints.front().z << endl;
			pnt.x = weightX;
			pnt.y = weightY;
			pnt.z = tempPoints.front().z;
			otherPoints.push_back(pnt);
		}
		else if (H >= h1/*0.5*/&&H < h2/*4*/)
		{
			++treeNum;
			//ofile << "tree\n" << weightX << " " << weightY << " " << tempPoints.front().z << endl;
			pnt.x = weightX;
			pnt.y = weightY;
			pnt.z = tempPoints.front().z;
			treePoints.push_back(pnt);
		}
		else if (H >= h2/*4*/ && H < h3/*8*/)
		{
			++lightNum;
			//ofile << "light\n" << weightX << " " << weightY << " " << tempPoints.front().z << endl;
			pnt.x = weightX;
			pnt.y = weightY;
			pnt.z = tempPoints.front().z;
			ligntPoints.push_back(pnt);
		}
		else if (H >= h3/*8*/)
		{
			++electNum;
			//ofile << "elec\n" << weightX << " " << weightY << " " << tempPoints.front().z << endl;
			pnt.x = weightX;
			pnt.y = weightY;
			pnt.z = tempPoints.front().z;
			elecPoints.push_back(pnt);
		}
	}
	//for (list<Point>::iterator it = pointss.begin(); it != pointss.end(); ++it)
	//{
	//	ofile << "point " << it->x << " " << it->y << " " << it->z << endl;
	//}


	//ofile.close();

	centers_.push_back(otherPoints);
	centers_.push_back(treePoints);
	centers_.push_back(ligntPoints);
	centers_.push_back(elecPoints);
}
