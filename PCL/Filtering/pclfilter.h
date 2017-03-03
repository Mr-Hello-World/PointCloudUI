#pragma once

#include <iostream>
#include <string>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>

#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>
class PCLFilter
{
public:
	double passThroughUpLimit_;
	double passThroughDownLimit_;
	std::string passThroughFileName_;

	float long_,width_,high_;

	int statisticOutliersMeanK_;
	double statisticOutliersStddevmulThresh_;

	double conditionalRadius_;
	int conditionalMinNeighbors_;
	PCLFilter();
	~PCLFilter(){}
	
	void passThroughFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered);
	void downsamplingVoxelGridFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered);
	void statisticalOutlierRemovalFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered);
	void radiusOutlierRemovalFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered);
};