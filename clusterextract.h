#pragma once
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include "PointClass/point.h"

class ClusterExtract
{
public:
	ClusterExtract();

	int maxIterations_;
	double distanceThreshold_;
	double percent_;
	double clusterTolerance_;
	int minClusterSize_;
	int maxClusterSize_;
	
	void euclideanClusterExtract(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, list<list<Point>> &clusters);
};

