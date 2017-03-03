#include "pclfilter.h"
//#include <pcl/filters/voxel_grid.h>
//#include <pcl/filters/extract_indices.h>
//
//#include <pcl/filters/passthrough.h>
//#include <pcl/filters/statistical_outlier_removal.h>
//#include <pcl/filters/radius_outlier_removal.h>
//#include <pcl/filters/conditional_removal.h>

PCLFilter::PCLFilter()
{
	passThroughUpLimit_=0;
	passThroughDownLimit_=1.0;
	passThroughFileName_="z";

	long_=width_=high_=0.1;

	statisticOutliersMeanK_=50;
	statisticOutliersStddevmulThresh_=1.0;

	conditionalRadius_=0.8;
	conditionalMinNeighbors_=2;
}
void PCLFilter::passThroughFilter( pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered )
{
	// Create the filtering object
	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud (cloud);
	pass.setFilterFieldName (passThroughFileName_);
	pass.setFilterLimits (passThroughDownLimit_, passThroughUpLimit_);
	//pass.setFilterLimitsNegative (true);
	pass.filter (*cloud_filtered);
}

void PCLFilter::downsamplingVoxelGridFilter( pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered )
{
	// Create the filtering object
	pcl::VoxelGrid<pcl::PointXYZ> sor;
	sor.setInputCloud (cloud);
	sor.setLeafSize (long_,width_,high_);
	sor.filter (*cloud_filtered);
}

void PCLFilter::statisticalOutlierRemovalFilter( pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered )
{
	// Create the filtering object
	pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
	sor.setInputCloud (cloud);
	sor.setMeanK (statisticOutliersMeanK_);
	sor.setStddevMulThresh (statisticOutliersStddevmulThresh_);
	sor.filter (*cloud_filtered);
}

void PCLFilter::radiusOutlierRemovalFilter( pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered )
{
		pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;		
		// build the filter
		outrem.setInputCloud(cloud);
		outrem.setRadiusSearch(conditionalRadius_);
		outrem.setMinNeighborsInRadius (conditionalMinNeighbors_);
		// apply filter
		outrem.filter (*cloud_filtered);
}
