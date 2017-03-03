#pragma once
#include "../PointClass/point.h"
#include "../Luozf/Pointlzf.h"
class QString;

class CloudProperty
{
public:
	double minX,minY,minZ;
	double maxX,maxY,maxZ;
	int pointsNum;
	CloudProperty();
	void getProperty(list<Point> &points);
	void getProperty(list<PointRGB> &points);
	void getProperty(Szw::CloudXYZ &cloud);
};

class CloudManage
{
public:
	Szw::CloudXYZ cloud;				//窗口显示黑白云数据集
	Szw::CloudXYZ cloud_filtered;
	Szw::CloudRGB cloudrgb;				//窗口显示彩色云数据集
	Szw::Viewer viewer;
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals;

	vector<list<Point>> cloudXYZData;	//黑白云数据集
	//vector<list<PointRGB>> cloudRGBData;//彩色云数据集
	
	vector<list<list<Point>>> cloudsRGBData;
	list<list<Point>> cloudLRGBData;

	//vector<CloudProperty> cloudXYZProp;
	//vector<CloudProperty> cloudRGBProp;

	list<Point> *awaitingProcessCloudLXYZ;		//不可有删除操作
	list<Point> processCloudLXYZ;				//存放处理后数据
	list<Point> processCloudLXYZ2;				//存放处理后数据
	list<list<Point>> processCloudLRGB;

	vector<Point> awaitingProcessCloudVXYZ;
	vector<Point> awaitingProcessCloudVXYZ2;
	//list<PointRGB> *awaitingProcessCloudRGB;
	list<list<Point>> *awaitingProcessCloudLRGB;	//不可有删除操作

	vector<td::Point> awaitingProecssCloudlzf;
	vector<vector<td::Point>> waitingProecssCloudlzfRGB;

	int activateXYZNum;
	int activateRGBNum;
	int levels;
	double scales;
	CloudProperty cloudProperty;
	bool isItemLoadCloud;
public:
	CloudManage(void);
	~CloudManage(void);
	void activateCloudXYZ(int activateNum);
	void activateCloudRGB(int activateNum);

	void removeCloudXYZ(int currentItemNum);
	void removeCloudRGB(int currentItemNum);

	void loadCloudXYZ( const QString &fileName ,const QString &splitStr);
	void loadCloudRGB( const QString &fileName ,const QString &splitStr);

	void cloud2cloudV(Szw::CloudXYZ &cloud,vector<Point> &cloudV);
	void cloud2cloudL(Szw::CloudXYZ &cloud,list<Point> &cloudL);
	void cloud2cloudL(Szw::CloudRGB &cloud, list<Point> &cloudL);
	void cloudV2cloud(vector<Point> &cloudV,Szw::CloudXYZ &cloud);
	void cloudV2cloudL(vector<Point> &cloudV, list<Point> &cloudL);
	void cloudL2cloud(list<Point> &cloudL,Szw::CloudXYZ &cloud);
	void cloudL2cloudRGB(list<Point> &cloudL,Szw::CloudRGB &cloudrgb);
	void cloudL2cloudV(list<Point> &cloudL,vector<Point> &cloudV);
	void cloudsL2cloudRGB(list<list<Point>> &clouds,Szw::CloudRGB &cloudrgb);
	void cloudsV2cloudRGB(vector<list<Point>> &clouds,Szw::CloudRGB &cloudrgb);
	void cloudL2cloudlzf(list<Point> &cloudL, vector<td::Point> &cloudlzf);
	void cloudVRGB2cloudLRGB(vector<vector<td::Point>> &cloudVRGB, list<list<Point>> &cloudLRGB);
		
	void setPointColorInX();
	void setPointColorInY();
	void setPointColorInZ();
	void clearAllData();	
	
private:
	void setColorInX( float &x, int &r, int &g,int &b );
	void setColorInY( float &y, int &r, int &g,int &b );
	void setColorInZ( float &z, int &r, int &g,int &b );
	float minZ,maxZ,minX,maxX,minY,maxY;
	
};

