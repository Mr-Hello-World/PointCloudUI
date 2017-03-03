#include "clusterextract.h"

void ClusterExtract::euclideanClusterExtract(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, list<list<Point>> &clusters)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f(new pcl::PointCloud<pcl::PointXYZ>);
	
	// Create the segmentation object for the planar model and set all the parameters
	pcl::SACSegmentation<pcl::PointXYZ> seg;
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ>());
	pcl::PCDWriter writer;
	seg.setOptimizeCoefficients(true);
	seg.setModelType(pcl::SACMODEL_PLANE);
	seg.setMethodType(pcl::SAC_RANSAC);
	seg.setMaxIterations(maxIterations_);
	seg.setDistanceThreshold(distanceThreshold_);

	int i = 0, nr_points = (int)cloud->points.size();
	while (cloud->points.size() > percent_ * nr_points)
	{
		// Segment the largest planar component from the remaining cloud
		seg.setInputCloud(cloud);
		seg.segment(*inliers, *coefficients);
		if (inliers->indices.size() == 0)
		{
			std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
			break;
		}

		// Extract the planar inliers from the input cloud
		pcl::ExtractIndices<pcl::PointXYZ> extract;
		extract.setInputCloud(cloud);
		extract.setIndices(inliers);
		extract.setNegative(false);

		// Get the points associated with the planar surface
		extract.filter(*cloud_plane);
		std::cout << "PointCloud representing the planar component: " << cloud_plane->points.size() << " data points." << std::endl;

		// Remove the planar inliers, extract the rest
		extract.setNegative(true);
		extract.filter(*cloud_f);
		*cloud = *cloud_f;
	}

	// Creating the KdTree object for the search method of the extraction
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);

	std::vector<pcl::PointIndices> cluster_indices;
	pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
	ec.setClusterTolerance(clusterTolerance_); // 2cm
	ec.setMinClusterSize(minClusterSize_);
	ec.setMaxClusterSize(maxClusterSize_);
	ec.setSearchMethod(tree);
	ec.setInputCloud(cloud);
	ec.extract(cluster_indices);

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
	list<Point> points;
	Point pnt;
	for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
	{
		points.clear();
		for (std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); ++pit)
		{
			pnt.x = cloud->points[*pit].x;
			pnt.y = cloud->points[*pit].y;
			pnt.z = cloud->points[*pit].z;
			points.push_back(pnt);
		}
		clusters.push_back(points);		
	}
}

ClusterExtract::ClusterExtract()
{
	maxIterations_=100;
	distanceThreshold_=0.02;
	percent_=0.3;

	clusterTolerance_=0.02;
	minClusterSize_=100;
	maxClusterSize_=25000;
}
