#include "libLAS180.h"

void LibLAS180::readLASCloud(std::string _filePath)
{
	points = &cloudManage->processCloudLXYZ;
	points->clear();	
	
	std::ifstream ifs;
	ifs.open(_filePath, std::ios::in | std::ios::binary);
	if (!ifs)
	{
		return ;
	}

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);

	Point pnt;
	while (reader.ReadNextPoint())
	{
		pnt.x = reader.GetPoint().GetX();
		pnt.y = reader.GetPoint().GetY();
		pnt.z = reader.GetPoint().GetZ();
		points->push_back(pnt);
	}

	cloudManage->cloudXYZData.push_back(cloudManage->processCloudLXYZ);
	cloudManage->cloud->points.clear();
	cloudManage->cloudL2cloud(cloudManage->processCloudLXYZ, cloudManage->cloud);
	cloudManage->viewer->updatePointCloud(cloudManage->cloud, "cloud");
	cloudManage->viewer->resetCamera();
}

