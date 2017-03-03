#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include "../RansacClass/ransacplane.h"
#include "../SurfaceGrowing/surfacegrowing.h"
#include "../PointCloudSimple/simple.h"
#include "../PCL/Filtering/pclfilter.h"
#include "clusterextract.h"
#include "../PCL/Algorithm/algorithm.h"
#include "../Luozf/Pointlzf.h"
#include "../Luozf/Segmentation.h"
#include "../PolesExtract/polesextract.h"
#include "../groundFilter/groundFilter.h"
#include "../roadshoulder/roadshoulder.h"
#include "../ExtractBuilding/buildfootprint.h"

#define RANSAC_SEGMENT_PLANE 1
#define SURFAC_SEGMENT_PLANE 2
#define CONTOUR_POINTS 3
#define PCA_POINTS 4
#define FEATURE_POINTS 5
#define SIMPLE_POINTS 6
#define PASSTHROUGH_FILTER 7
#define STATISTIC_FILTER 8
#define RADIUS_FILTER 9
#define DOWNSAMPLINGVOXELGRID_FILTER 11
#define CLUSTER_EXTRACT_EUCLIDEAN 12
#define ClOUD_RESOLUTION 13
#define REGIONGROW_RANSAC 14
#define REGIONGROW_BAYSAC 15
#define REGIONGROW_BAYLMEDS 16
#define ESTIMAT_NORMALS 17
#define POLES_EXTRAT 18
#define STATISTIC_POLESNUM_CLASSIFY 19
#define COMPUTE_COORDOFPOLES 20
#define GET_GROUND_INFO 21
#define ROAD_SHOULDER 22
#define SHOULD_AFTER_PROCESS1 23
#define SHOULD_AFTER_PROCESS2 24
#define EXTRACT_BUILDING 25

class SetRansac
{
public:
	vector<Point> *points;
	list<Points> *segments;

	int num_;
	double dist_;
	SetRansac()
	{
		num_=0;
		dist_=0;
	}
};

class SetSurfaceGrow
{
public:
	list<Point> *points;
	list<Points> *segments;
	SurfaceGrowing surfaceGrow;
};

class SetContour
{
public:
	list<Point> *points;
	list<Point> *contourPoints;
	SimplePointCloud contour;
};

class SetPCA
{
public:
	list<Point> *points;
	list<Point> *PCAPoints;
	SimplePointCloud PCA;
};
class SetFeature
{
public:
	list<Point> *points;
	list<Point> *featurePoints;
	SimplePointCloud feature;
};
class SetSimple
{
public:
	list<Point> *points;
	list<Point> *simplePoints;
	SimplePointCloud simple;
};

class SetFilter
{
public:
	pcl::PointCloud<pcl::PointXYZ>::Ptr *cloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr *cloud_filtered;
	PCLFilter pclFilter;
};
class SetCluster
{
public:
	pcl::PointCloud<pcl::PointXYZ>::Ptr *cloud;
	list<Points> *clusters;
	ClusterExtract clusterExtract;
};

class SetComputeResolution
{
public:
	pcl::PointCloud<pcl::PointXYZ>::Ptr *cloud;
	double *res;
	Algorithm alg;
};

class SetRegionGrow
{
public:
	vector<td::Point> *points;
	vector<vector<td::Point>> *segments;
	td::Segmentation seg;	
};
class SetEstimateNormals
{
public:
	pcl::PointCloud<pcl::PointXYZ>::Ptr *cloud;
	pcl::PointCloud<pcl::Normal>::Ptr *cloud_normals;
	Algorithm alg;
};
class SetPolesExtract
{
public:
	list<Point> *points;
	list<Point> *polesPoints;
	PolesExtract polesExtract;
};
class SetStatisticPolesNumClassify
{
public:
	list<Point> *points;
	list<list<Point>> *polesPoints;
	PolesExtract polesStatisticClassify;
};
class SetComputeCenter
{
public:
	list<Point> *points;
	list<list<Point>> *polesPoints;
	PolesExtract polesComputeCenter;
};
class SetGroundFilter
{
public:
	list<Point> *points;
	list<Point> *groundPoints;
	list<Point> *onGroundPoints;
	GroundFilter groundfilter;
};
class SetRoadShoulder
{
public:
	list<Point> *points;
	list<Point> *shoulderPoints;
	RoadShoulder roadShoulder;
};
class SetShoulderAfterProcess1
{
public:
	list<Point> *points;
	list<Point> *shoulderPoints;
	RoadShoulder roadShoulder;
};
class SetShoulderAfterProcess2
{
public:
	list<Point> *points;
	list<Point> *shoulderPoints;
	list<Point> *initialPoints;
	RoadShoulder roadShoulder;
};
class SetExtractBuild
{
public:
	list<Point> *points;
	list<list<Point>> *buildPoints;
	BuildFootprint extractBuild;
};
class Process
{
public:
	SetRansac setRansac;
	SetSurfaceGrow setSurfaceGrow;
	SetContour setContour;
	SetPCA setPCA;
	SetFeature setFeature;
	SetSimple setSimple;
	SetFilter setFilter;
	SetCluster setCluster;
	SetComputeResolution setComResolution;
	SetRegionGrow setRegionGrow;
	SetEstimateNormals setEstimateNormals;
	SetPolesExtract setPolesExtract;
	SetStatisticPolesNumClassify setStatisticPolesNumClassify;
	SetComputeCenter setComputeCenter;
	SetGroundFilter setGroundFilter;
	SetRoadShoulder setRoadShoulder;
	SetShoulderAfterProcess1 setShoulderAfterProcess1;
	SetShoulderAfterProcess2 setShoulderAfterProcess2;
	SetExtractBuild setExtractBuild;
public:
	Process()
	{
		choice_=100;
	}
	int choice_;

	void apply()
	{
		switch (choice_) {
		case RANSAC_SEGMENT_PLANE:
			{
				RansacSegPlane rs;
				rs.segment(setRansac.num_,setRansac.dist_,*setRansac.points,*setRansac.segments);
				break;				
			}
		case SURFAC_SEGMENT_PLANE:
			{
				setSurfaceGrow.surfaceGrow.segment(*setSurfaceGrow.points,*setSurfaceGrow.segments);
				break;
			}
		case CONTOUR_POINTS:
			{
				setContour.contour.contourPoints(*setContour.points,*setContour.contourPoints);
				break;
			}
		case PCA_POINTS:
			{
				setPCA.PCA.PCAPoints(*setPCA.points,*setPCA.PCAPoints);
				break;
			}
		case FEATURE_POINTS:
			{
				setFeature.feature.featurePoints(*setFeature.points,*setFeature.featurePoints);
				break;
			}
		case SIMPLE_POINTS:
			{
				setSimple.simple.simplePoints(*setSimple.points,*setSimple.simplePoints);
				break;
			}
		case PASSTHROUGH_FILTER:
			{
				setFilter.pclFilter.passThroughFilter(*setFilter.cloud,*setFilter.cloud_filtered);
				break;
			}
		case STATISTIC_FILTER:
			{
				setFilter.pclFilter.statisticalOutlierRemovalFilter(*setFilter.cloud,*setFilter.cloud_filtered);
				break;
			}
		case RADIUS_FILTER:
			{
				setFilter.pclFilter.radiusOutlierRemovalFilter(*setFilter.cloud,*setFilter.cloud_filtered);
				break;
			}
		case DOWNSAMPLINGVOXELGRID_FILTER:
			{
				setFilter.pclFilter.downsamplingVoxelGridFilter(*setFilter.cloud,*setFilter.cloud_filtered);
				break;
			}
		case CLUSTER_EXTRACT_EUCLIDEAN:
			{
				setCluster.clusterExtract.euclideanClusterExtract(*setCluster.cloud,*setCluster.clusters);
				break;
			}
		case ClOUD_RESOLUTION:
			{
				*setComResolution.res=setComResolution.alg.computeCloudResolution(*setComResolution.cloud);
				break;
			}
		case REGIONGROW_RANSAC:
			{
				setRegionGrow.seg.regionGrow(td::Segmentation::RANSAC);
				break;
			}
		case REGIONGROW_BAYSAC:
			{
				setRegionGrow.seg.regionGrow(td::Segmentation::BAYSAC);
				break;
			}
		case REGIONGROW_BAYLMEDS:
			{
				setRegionGrow.seg.regionGrow(td::Segmentation::BAYLMEDS);
				break;
			}
		case ESTIMAT_NORMALS:
			{
				setEstimateNormals.alg.estimatingTheNormals(*setEstimateNormals.cloud, *setEstimateNormals.cloud_normals);
				break;
			}
		case POLES_EXTRAT:
			{
				setPolesExtract.polesExtract.polesEx(*setPolesExtract.points, *setPolesExtract.polesPoints);
				break;
			}
		case STATISTIC_POLESNUM_CLASSIFY:
			{
				setStatisticPolesNumClassify.polesStatisticClassify.statisticPolesNumandClassify(*setStatisticPolesNumClassify.points, *setStatisticPolesNumClassify.polesPoints);
				break;
			}
		case COMPUTE_COORDOFPOLES:
			{
				setComputeCenter.polesComputeCenter.computeCoordofPoles(*setComputeCenter.points,*setComputeCenter.polesPoints);
				break;
			}
		case GET_GROUND_INFO:
			{
				setGroundFilter.groundfilter.groundFilters(*setGroundFilter.points, *setGroundFilter.groundPoints, *setGroundFilter.onGroundPoints);
				break;
			}
		case ROAD_SHOULDER:
			{
				setRoadShoulder.roadShoulder.extractCurbPoints(*setRoadShoulder.points, *setRoadShoulder.shoulderPoints);
				break;
			}
		case SHOULD_AFTER_PROCESS1:
		{
			setShoulderAfterProcess1.roadShoulder.afterProgress(*setShoulderAfterProcess1.points, *setShoulderAfterProcess1.shoulderPoints);
			break;
		}
		case SHOULD_AFTER_PROCESS2:
		{
			setShoulderAfterProcess2.roadShoulder.afterProgress2(*setShoulderAfterProcess2.points, *setShoulderAfterProcess2.initialPoints, *setShoulderAfterProcess2.shoulderPoints);
			break;
		}
		case EXTRACT_BUILDING:
		{
			setExtractBuild.extractBuild.featureImage(*setExtractBuild.points, *setExtractBuild.buildPoints);
			break;
		}
		default:
			break;
		}
	}
};

class CloudThread : public QThread
{
	Q_OBJECT

public:
	CloudThread();
	Process process;
	void stop();
protected:
	void run();
	void test();
private:
	
signals:
	void setActionEnable(bool _bool);
};

#endif
