#pragma once
#include <pcl/features/normal_3d_omp.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>

class Algorithm
{
	
public:
	double radius;
	double computeCloudResolution(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud);
	void estimatingTheNormals(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud, pcl::PointCloud<pcl::Normal>::Ptr &cloud_normals);
};