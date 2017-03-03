#include "voxel.h"
void Voxels::getVoxel2DPoints(list<Point> &_points)
{
	Pos2D pos2D;
	list<Point>::iterator pointsIt;
	for(pointsIt=_points.begin();pointsIt!=_points.end();++pointsIt)
	{
		pos2D.i=int((pointsIt->x+e_)/l_);
		pos2D.j=int((pointsIt->y+e_)/w_);
		voxel2DPoints_[pos2D].push_back(*pointsIt);
	}
}

void Voxels::getVoxel3DPoints( list<Point> &_points )
{
	Pos3D pos3D;
	list<Point>::iterator pointsIt;
	for(pointsIt=_points.begin();pointsIt!=_points.end();++pointsIt)
	{
		pos3D.i=int((pointsIt->x+e_)/l_);
		pos3D.j=int((pointsIt->y+e_)/w_);
		pos3D.k=int((pointsIt->z+e_)/h_);

		voxel3DPoints_[pos3D].push_back(*pointsIt);
	}
}
void Voxels::getVoxel2D3DPoints( list<Point> &_points )
{
	Pos2D pos2D;
	Pos3D pos3D;
	list<Point>::iterator pointsIt;
	for(pointsIt=_points.begin();pointsIt!=_points.end();++pointsIt)
	{
		pos3D.i=pos2D.i=int((pointsIt->x+e_)/l_);
		pos3D.j=pos2D.j=int((pointsIt->y+e_)/w_);
		pos3D.k=int((pointsIt->z+e_)/h_);
		voxel2DPoints_[pos2D].push_back(*pointsIt);
		voxel3DPoints_[pos3D].push_back(*pointsIt);
	}
}
