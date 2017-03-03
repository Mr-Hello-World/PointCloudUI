#include "algorithm.h"
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>

double Algorithm::computeCloudResolution(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
{
		double res = 0.0;
		int n_points = 0;
		int nres;
		std::vector<int> indices(2);
		std::vector<float> sqr_distances(2);
		pcl::search::KdTree<pcl::PointXYZ> tree;
		tree.setInputCloud(cloud);
	
		for (size_t i = 0; i < cloud->size(); ++i)
		{
			if (!pcl_isfinite((*cloud)[i].x))
			{
				continue;
			}
			//Considering the second neighbor since the first is the point itself.
			nres = tree.nearestKSearch(i, 2, indices, sqr_distances);
			if (nres == 2)
			{
				res += sqrt(sqr_distances[1]);
				++n_points;
			}
		}
		if (n_points != 0)
		{
			res /= n_points;
		}
		return res;
}

void Algorithm::estimatingTheNormals(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud, pcl::PointCloud<pcl::Normal>::Ptr &cloud_normals)
{
	// Create the normal estimation class, and pass the input dataset to it
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
	ne.setInputCloud(cloud);

	// Create an empty kdtree representation, and pass it to the normal estimation object.
	// Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
	ne.setSearchMethod(tree);

	// Output datasets
	//pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);

	// Use all neighbors in a sphere of radius 3cm
	ne.setRadiusSearch(radius);

	// Compute the features
	ne.compute(*cloud_normals);

	// cloud_normals->points.size () should have the same size as the input cloud->points.size ()*
}
