#include "cloudmanage.h"

#include <limits>

#include <QFile>
#include <QTextStream>
#include <QProgressDialog>

CloudManage::CloudManage(void)
{
	cloud.reset (new pcl::PointCloud<pcl::PointXYZ>);
	cloud_filtered.reset(new pcl::PointCloud<pcl::PointXYZ>);
	cloudrgb.reset (new pcl::PointCloud<pcl::PointXYZRGBA>);
	
	viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
	//pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
	cloud_normals.reset(new pcl::PointCloud<pcl::Normal>);

	activateXYZNum=-1;
	activateRGBNum=-1;

	isItemLoadCloud=false;
}

CloudManage::~CloudManage(void)
{

}

void CloudManage::loadCloudXYZ( const QString &fileName ,const QString &splitStr )
{
	cloud->points.clear();

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		return ;
	}
	QTextStream infile(&file);

	pcl::PointXYZ pntXYZ;
	cloud->points.clear();

	QString linestr=infile.readLine();
	infile.seek(0);
	int lineSize/*=infile.readLine().size()*/;
	if (linestr.size()-6)
	{
		lineSize=linestr.size()-6;
	}else
		lineSize=linestr.size();

	int lineNum=file.size()/(lineSize+2);

	QString temQS;

	int tsize=file.size();

	QProgressDialog openProgress;
	openProgress.setLabelText(QObject::tr("Approximate number of points: ")+temQS.setNum(lineNum));
	openProgress.setWindowTitle(QObject::tr("Openning cloud"));

	openProgress.setRange(0,file.size());
	openProgress.setModal(true);
	openProgress.setCancelButtonText(QObject::tr("Cancel"));

	list<Point> points;
	Point pntxyz;

	cloud->points.reserve(lineNum);
	infile.seek(0);
	while(!infile.atEnd())
	{
		QString lineData=infile.readLine();
		QStringList lineDatas=lineData.split(splitStr);

		//infile>>pntXYZ.x>>pntXYZ.y>>pntXYZ.z;
		pntxyz.x=pntXYZ.x=lineDatas.at(0).toFloat();
		pntxyz.y=pntXYZ.y=lineDatas.at(1).toFloat();
		pntxyz.z=pntXYZ.z=lineDatas.at(2).toFloat();
		cloud->points.push_back(pntXYZ);
		points.push_back(pntxyz);

		if (file.pos()%10)
		{
			openProgress.setValue(file.pos());
		}
		if (openProgress.wasCanceled())
		{
			break;
		}
	}
	cloud->points.pop_back();
	points.pop_back();
		
	if (!isItemLoadCloud)
	{
		cloudXYZData.clear();
		cloudXYZData.push_back(points);
	}else
	{
		cloudXYZData.push_back(points);
	}
	isItemLoadCloud=false;
	
	activateCloudXYZ(0);
	activateXYZNum=-1;
	file.close();
}

void CloudManage::loadCloudRGB( const QString &fileName ,const QString &splitStr )
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		return ;
	}
	QTextStream infile(&file);

	cloudrgb.reset (new pcl::PointCloud<pcl::PointXYZRGBA>);
	pcl::PointXYZRGBA pntXYZRGB;
	cloudrgb->points.clear();

	infile.seek(0);

	QString linestr=infile.readLine();
	infile.seek(0);
	int lineSize/*=infile.readLine().size()*/;
	if (linestr.size()-6)
	{
		lineSize=linestr.size()-6;
	}else
		lineSize=linestr.size();

	int lineNum=file.size()/(lineSize+2);

	QString temQS;

	int tsize=file.size();

	QProgressDialog saveProgress;
	saveProgress.setLabelText(QObject::tr("Approximate number of points: ")+temQS.setNum(lineNum));
	saveProgress.setWindowTitle(QObject::tr("Openning cloud"));

	saveProgress.setRange(0,file.size());
	saveProgress.setModal(true);
	saveProgress.setCancelButtonText(QObject::tr("Cancel"));

	cloudrgb->points.reserve(lineNum);
	infile.seek(0);
	while(!infile.atEnd())
	{
		QString lineData=infile.readLine();
		QStringList lineDatas=lineData.split(splitStr);

		//infile>>pntXYZ.x>>pntXYZ.y>>pntXYZ.z;
		pntXYZRGB.x=lineDatas.at(0).toFloat();
		pntXYZRGB.y=lineDatas.at(1).toFloat();
		pntXYZRGB.z=lineDatas.at(2).toFloat();
		pntXYZRGB.r=lineDatas.at(3).toInt();
		pntXYZRGB.g=lineDatas.at(4).toInt();
		pntXYZRGB.b=lineDatas.at(5).toInt();
		cloudrgb->points.push_back(pntXYZRGB);

		if (file.pos()%10)
		{
			saveProgress.setValue(file.pos());
		}
		if (saveProgress.wasCanceled())
		{
			break;
		}
	}
	cloudrgb->points.pop_back();
	file.close();
}

void CloudManage::cloud2cloudV( Szw::CloudXYZ &cloud,vector<Point> &cloudV )
{
	cloudV.resize(cloud->points.size());
	for (int i=0; i<cloud->points.size();++i)
	{
		cloudV.at(i).x=cloud->points.at(i).x;
		cloudV.at(i).y=cloud->points.at(i).y;
		cloudV.at(i).z=cloud->points.at(i).z;
	}
}

void CloudManage::cloud2cloudL( Szw::CloudXYZ &cloud,list<Point> &cloudL )
{
	Point point;
	for (int i=0; i<cloud->points.size();++i)
	{
		point.x=cloud->points.at(i).x;
		point.y=cloud->points.at(i).y;
		point.z=cloud->points.at(i).z;
		cloudL.push_back(point);
	}
}

void CloudManage::cloud2cloudL(Szw::CloudRGB &cloud, list<Point> &cloudL)
{
	Point point;
	for (int i = 0; i < cloud->points.size(); ++i)
	{
		point.x = cloud->points.at(i).x;
		point.y = cloud->points.at(i).y;
		point.z = cloud->points.at(i).z;
		cloudL.push_back(point);
	}
}

void CloudManage::cloudV2cloud( vector<Point> &cloudV,Szw::CloudXYZ &cloud )
{

}

void CloudManage::cloudL2cloud( list<Point> &cloudL,Szw::CloudXYZ &cloud )
{
	pcl::PointXYZ pntXYZ;
	for (list<Point>::iterator it=cloudL.begin();it!=cloudL.end();++it)
	{
		pntXYZ.x=it->x;
		pntXYZ.y=it->y;
		pntXYZ.z=it->z;
		cloud->points.push_back(pntXYZ);
	}
}
void CloudManage::cloudL2cloudRGB( list<Point> &cloudL,Szw::CloudRGB &cloudrgb )
{
	pcl::PointXYZRGBA pntXYZRGB;
	for (list<Point>::iterator it=cloudL.begin();it!=cloudL.end();++it)
	{
		pntXYZRGB.x=it->x;
		pntXYZRGB.y=it->y;
		pntXYZRGB.z=it->z;
		cloudrgb->points.push_back(pntXYZRGB);
	}
}

void CloudManage::cloudL2cloudV( list<Point> &cloudL,vector<Point> &cloudV )
{
	cloudV.insert(cloudV.begin(),cloudL.begin(),cloudL.end());
}

void CloudManage::cloudsL2cloudRGB( list<list<Point>> &clouds,Szw::CloudRGB &cloudrgb )
{
	pcl::PointXYZRGBA pntXYZRGB;
	int r,g,b;
	srand((int)time(NULL));
	for(list<Points>::iterator it1=clouds.begin();it1!=clouds.end();++it1)
	{
		r=255 *(1024 * rand () / (RAND_MAX + 1.0f));
		g=255 *(1024 * rand () / (RAND_MAX + 1.0f));
		b=255 *(1024 * rand () / (RAND_MAX + 1.0f));
		for(list<Point>::iterator it2=it1->begin();it2!=it1->end();++it2)
		{
			pntXYZRGB.x=it2->x;
			pntXYZRGB.y=it2->y;
			pntXYZRGB.z=it2->z;
			pntXYZRGB.r=r;
			pntXYZRGB.g=g;
			pntXYZRGB.b=b;
			cloudrgb->points.push_back(pntXYZRGB);
		}
	}
}

void CloudManage::cloudsV2cloudRGB( vector<list<Point>> &clouds,Szw::CloudRGB &cloudrgb )
{
	pcl::PointXYZRGBA pntXYZRGB;
	int r,g,b;
	srand((int)time(NULL));
	for(vector<Points>::iterator it1=clouds.begin();it1!=clouds.end();++it1)
	{
		r=255 *(1024 * rand () / (RAND_MAX + 1.0f));
		g=255 *(1024 * rand () / (RAND_MAX + 1.0f));
		b=255 *(1024 * rand () / (RAND_MAX + 1.0f));
		for(list<Point>::iterator it2=it1->begin();it2!=it1->end();++it2)
		{
			pntXYZRGB.x=it2->x;
			pntXYZRGB.y=it2->y;
			pntXYZRGB.z=it2->z;
			pntXYZRGB.r=r;
			pntXYZRGB.g=g;
			pntXYZRGB.b=b;
			cloudrgb->points.push_back(pntXYZRGB);
		}
	}
}

void CloudManage::setPointColorInX()
{
	cloudProperty.getProperty(cloud);
	minX=cloudProperty.minX;
	minY=cloudProperty.minY;
	
	minZ=cloudProperty.minZ;
	maxX=cloudProperty.maxX;
	maxY=cloudProperty.maxY;
	maxZ=cloudProperty.maxZ;

	cloudrgb->resize(cloud->points.size());
	int r,g,b;
	for (int i=0;i<cloud->points.size();++i)
	{
		cloudrgb->points.at(i).x=cloud->points.at(i).x;
		cloudrgb->points.at(i).y=cloud->points.at(i).y;
		cloudrgb->points.at(i).z=cloud->points.at(i).z;
		setColorInX(cloud->points.at(i).x,r,g,b);
		cloudrgb->points.at(i).r=r;
		cloudrgb->points.at(i).g=g;
		cloudrgb->points.at(i).b=b;
	}
}

void CloudManage::setPointColorInY()
{
	cloudProperty.getProperty(cloud);
	minX=cloudProperty.minX;
	minY=cloudProperty.minY;

	minZ=cloudProperty.minZ;
	maxX=cloudProperty.maxX;
	maxY=cloudProperty.maxY;
	maxZ=cloudProperty.maxZ;

	cloudrgb->resize(cloud->points.size());
	int r,g,b;
	for (int i=0;i<cloud->points.size();++i)
	{
		cloudrgb->points.at(i).x=cloud->points.at(i).x;
		cloudrgb->points.at(i).y=cloud->points.at(i).y;
		cloudrgb->points.at(i).z=cloud->points.at(i).z;
		setColorInY(cloud->points.at(i).y,r,g,b);
		cloudrgb->points.at(i).r=r;
		cloudrgb->points.at(i).g=g;
		cloudrgb->points.at(i).b=b;
	}
}

void CloudManage::setPointColorInZ()
{
	cloudProperty.getProperty(cloud);
	minX=cloudProperty.minX;
	minY=cloudProperty.minY;

	minZ=cloudProperty.minZ;
	maxX=cloudProperty.maxX;
	maxY=cloudProperty.maxY;
	maxZ=cloudProperty.maxZ;

	cloudrgb->resize(cloud->points.size());
	int r,g,b;
	for (int i=0;i<cloud->points.size();++i)
	{
		cloudrgb->points.at(i).x=cloud->points.at(i).x;
		cloudrgb->points.at(i).y=cloud->points.at(i).y;
		cloudrgb->points.at(i).z=cloud->points.at(i).z;
		setColorInZ(cloud->points.at(i).z,r,g,b);
		cloudrgb->points.at(i).r=r;
		cloudrgb->points.at(i).g=g;
		cloudrgb->points.at(i).b=b;
	}
}

void CloudManage::setColorInX( float &x, int &r, int &g,int &b )
{
	//blue
	int r1=0;
	int g1=0;
	int b1=255;
	//green
	int r2=0;
	int g2=255;
	int b2=0;
	//red
	int r3=255;
	int g3=0;
	int b3=0;
		
	/*r=r1+(r2-r1)*(z-minZ)/(maxZ-minZ);
	g=g1+(g2-g1)*(z-minZ)/(maxZ-minZ);
	b=b1+(b2-b1)*(z-minZ)/(maxZ-minZ);*/
	double midX=(maxX-minX)/2.0+minX;
	if (x<midX)
	{
		r=r1+(r2-r1)*(x-minX)/(midX-minX);
		g=g1+(g2-g1)*(x-minX)/(midX-minX);
		b=b1+(b2-b1)*(x-minX)/(midX-minX);
	}else
	{
		r=r2+(r3-r2)*(x-midX)/(maxX-midX);
		g=g2+(g3-g2)*(x-midX)/(maxX-midX);
		b=b2+(b3-b2)*(x-midX)/(maxX-midX);
	}
}

void CloudManage::setColorInY( float &y, int &r, int &g,int &b )
{
	//blue
	int r1=0;
	int g1=0;
	int b1=255;
	//green
	int r2=0;
	int g2=255;
	int b2=0;
	//red
	int r3=255;
	int g3=0;
	int b3=0;
		
	/*r=r1+(r2-r1)*(z-minZ)/(maxZ-minZ);
	g=g1+(g2-g1)*(z-minZ)/(maxZ-minZ);
	b=b1+(b2-b1)*(z-minZ)/(maxZ-minZ);*/
	double midY=(maxY-minY)/2.0+minY;
	if (y<midY)
	{
		r=r1+(r2-r1)*(y-minY)/(midY-minY);
		g=g1+(g2-g1)*(y-minY)/(midY-minY);
		b=b1+(b2-b1)*(y-minY)/(midY-minY);
	}else
	{
		r=r2+(r3-r2)*(y-midY)/(maxY-midY);
		g=g2+(g3-g2)*(y-midY)/(maxY-midY);
		b=b2+(b3-b2)*(y-midY)/(maxY-midY);
	}
}

void CloudManage::setColorInZ( float &z, int &r, int &g,int &b )
{
	//blue
	int r1=0;
	int g1=0;
	int b1=255;
	//green
	int r2=0;
	int g2=255;
	int b2=0;
	//red
	int r3=255;
	int g3=0;
	int b3=0;
		
	/*r=r1+(r2-r1)*(z-minZ)/(maxZ-minZ);
	g=g1+(g2-g1)*(z-minZ)/(maxZ-minZ);
	b=b1+(b2-b1)*(z-minZ)/(maxZ-minZ);*/
	double midZ=(maxZ-minZ)/2.0+minZ;
	if (z<midZ)
	{
		r=r1+(r2-r1)*(z-minZ)/(midZ-minZ);
		g=g1+(g2-g1)*(z-minZ)/(midZ-minZ);
		b=b1+(b2-b1)*(z-minZ)/(midZ-minZ);
	}else
	{
		r=r2+(r3-r2)*(z-midZ)/(maxZ-midZ);
		g=g2+(g3-g2)*(z-midZ)/(maxZ-midZ);
		b=b2+(b3-b2)*(z-midZ)/(maxZ-midZ);
	}
}

void CloudManage::activateCloudXYZ(int activateNum)
{
	activateXYZNum=activateNum;
	awaitingProcessCloudLXYZ=&cloudXYZData.at(activateXYZNum);
	

}

void CloudManage::activateCloudRGB(int activateNum)
{
	activateRGBNum=activateNum;
	awaitingProcessCloudLRGB=&cloudsRGBData.at(activateNum);
}

void CloudManage::removeCloudXYZ( int currentItemNum )
{
	vector<list<Point>>::iterator it=cloudXYZData.begin();
	cloudXYZData.erase((it+currentItemNum));
}

void CloudManage::removeCloudRGB( int currentItemNum )
{

}

void CloudManage::cloudL2cloudlzf(list<Point> &cloudL, vector<td::Point> &cloudlzf)
{
	cloudlzf.resize(cloudL.size());
	vector<td::Point>::iterator itLzf = cloudlzf.begin();
	for (list<Point>::iterator it = cloudL.begin(); it != cloudL.end(); ++it, ++itLzf)
	{
		itLzf->x = it->x;
		itLzf->y = it->y;
		itLzf->z = it->z;		
	}
}

void CloudManage::cloudVRGB2cloudLRGB(vector<vector<td::Point>> &cloudVRGB, list<list<Point>> &cloudLRGB)
{
	cloudLRGB.resize(cloudVRGB.size());
	list<list<Point>>::iterator it_1 = cloudLRGB.begin();
	list<Point>::iterator it_2;
	for (vector<vector<td::Point>> ::iterator it1 = cloudVRGB.begin(); it1 != cloudVRGB.end();++it1,++it_1)
	{
		it_1->resize(it1->size());
		it_2 = it_1->begin();
		for (vector<td::Point>::iterator it2 = it1->begin(); it2 != it1->end();++it2,++it_2)
		{
			it_2->x = it2->x;
			it_2->y = it2->y;
			it_2->z = it2->z;
		}
	}
}

void CloudManage::clearAllData()
{
	cloud->points.clear();
	cloud_filtered->points.clear();
	cloudrgb->points.clear();
	cloud_normals->clear();

	//cloudXYZData.clear();	//黑白云数据集
	//cloudsRGBData.clear();
	//cloudLRGBData.clear();

	processCloudLXYZ.clear();				//存放处理后数据
	processCloudLXYZ2.clear();
	processCloudLRGB.clear();
	awaitingProcessCloudVXYZ.clear();

	awaitingProecssCloudlzf.clear();
	waitingProecssCloudlzfRGB.clear();

}

void CloudManage::cloudV2cloudL(vector<Point> &cloudV, list<Point> &cloudL)
{
	cloudL.resize(cloudV.size());
	list<Point>::iterator itL = cloudL.begin();
	for (vector<Point>::iterator it = cloudV.begin(); it != cloudV.end(); ++it,++itL)
	{
		it->x = itL->x;
		it->y = itL->y;
		it->z = itL->z;
	}
}

CloudProperty::CloudProperty()
{
	minX=minY=minZ=LONG_MAX;
	maxX=maxY=maxZ=LONG_MIN;
	pointsNum=0;
}

void CloudProperty::getProperty(list<Point> &points)
{
	minX=minY=minZ=LONG_MAX;
	maxX=maxY=maxZ=LONG_MIN;
	pointsNum=points.size();
	for (list<Point>::iterator it=points.begin();it!=points.end();++it)
	{
		if (minX>it->x)
		{
			minX=it->x;
		}
		if (maxX<it->x)
		{
			maxX=it->x;
		}

		if (minY>it->y)
		{
			minY=it->y;
		}
		if (maxY<it->y)
		{
			maxY=it->y;
		}

		if (minZ>it->z)
		{
			minZ=it->z;
		}
		if (maxZ<it->z)
		{
			maxZ=it->z;
		}
	}
}

void CloudProperty::getProperty( list<PointRGB> &points )
{
	minX=minY=minZ=LONG_MAX;
	maxX=maxY=maxZ=LONG_MIN;
	pointsNum=points.size();
	for (list<PointRGB>::iterator it=points.begin();it!=points.end();++it)
	{
		if (minX>it->x)
		{
			minX=it->x;
		}
		if (maxX<it->x)
		{
			maxX=it->x;
		}

		if (minY>it->y)
		{
			minY=it->y;
		}
		if (maxY<it->y)
		{
			maxY=it->y;
		}

		if (minZ>it->z)
		{
			minZ=it->z;
		}
		if (maxZ<it->z)
		{
			maxZ=it->z;
		}
	}
}
void CloudProperty::getProperty( Szw::CloudXYZ &cloud )
{
	minX=minY=minZ=LONG_MAX;
	maxX=maxY=maxZ=LONG_MIN;
	pointsNum=cloud->points.size();
	for (int i=0;i<cloud->points.size();++i)
	{
		if (minX>cloud->points.at(i).x)
		{
			minX=cloud->points.at(i).x;
		}
		if (maxX<cloud->points.at(i).x)
		{
			maxX=cloud->points.at(i).x;
		}

		if (minY>cloud->points.at(i).y)
		{
			minY=cloud->points.at(i).y;
		}
		if (maxY<cloud->points.at(i).y)
		{
			maxY=cloud->points.at(i).y;
		}

		if (minZ>cloud->points.at(i).z)
		{
			minZ=cloud->points.at(i).z;
		}
		if (maxZ<cloud->points.at(i).z)
		{
			maxZ=cloud->points.at(i).z;
		}
	}
}