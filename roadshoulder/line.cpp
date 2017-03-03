#include "line.h"

ThreeDLine ThreeDLine::computeMLS( Points &_points )
{
	double sxx,sx,sy,sz,sxz,syz,szz;
	sxx=sx=sy=sz=syz=sxz=szz=0;
	for (Points::iterator it=_points.begin();it!=_points.end();++it)
	{
		sx+=it->x;
		sy+=it->y;
		sz+=it->z;

		sxz+=it->x*it->z;
		szz+=it->z*it->z;
		syz+=it->y*it->z;
	}
	a_=(2*sxz-sx*sz)/(2*szz-sz*sz);
	b_=(sx-a_*sz)/2.0;
	c_=(2*syz-sy*sz)/(2*szz-sz*sz);
	d_=(sy-c_*sz)/2.0;
	ThreeDLine line;
	line.a_=a_;
	line.b_=b_;
	line.c_=c_;
	line.d_=d_;
	return line;
}



ThreeDLine ThreeDLine::computeTwoPoints( Point &_pnt1,Point &_pnt2 )
{
	point_=_pnt1;
	l_=_pnt2.x-_pnt1.x;
	m_=_pnt2.y-_pnt1.y;
	n_=_pnt2.z-_pnt1.z;
	double s=sqrt(l_*l_+m_*m_+n_*n_);
	l_=l_/s;
	m_=m_/s;
	n_=n_/s;
	Vecline v1,v2,v3;
	v1.x=l_;
	v1.y=m_;
	v1.z=n_;
	v2.x=point_.x;
	v2.y=point_.y;
	v2.z=point_.z;
	v3=cross(v1,v2);
	do_=sqrt(v3.x*v3.x+v3.y*v3.y+v3.z*v3.z);

	ThreeDLine line;
	line.l_=l_;
	line.m_=m_;
	line.n_=n_;
	return line;
}

ThreeDLine ThreeDLine::computeNew( Point &_pnt1,Point &_pnt2 )
{
	ThreeDLine line;

	computeTwoPoints(_pnt1,_pnt2);
	Vecline v1,v2,v3;
	v1.x=l_;
	v1.y=m_;
	v1.z=n_;

	line.l_=l_;
	line.m_=m_;
	line.n_=n_;
	line.point_=_pnt1;

	v2.x=_pnt2.x;
	v2.y=_pnt2.y;
	v2.z=0;

	v3.x=1;
	v3.y=0;
	v3.z=0;

	theta=angleofVec(v1,v2);
	double temp=Radian2Angle(theta);
	if (temp>90)
	{
		theta=Angle2Radian(180-temp);
	}
	line.theta=theta;
	line.fi=fi=angleofVec(v2,v3);

	double bx,by,bz;
	bx=cos(fi)*cos(theta);
	by=sin(fi)*cos(theta);
	bz=sin(theta);

	double x,y,z,t;
	t=(-_pnt1.x*l_-_pnt1.y*m_-_pnt1.x*n_)/sqrt(l_*l_+m_*m_+n_*n_);
	x=t*l_+_pnt1.x;
	y=t*m_+_pnt1.y;
	z=t*n_+_pnt1.z;

	double xt,yt;
	xt=(1+bx*bx/(1+bz))*x-bx*by*y/(1+bz)-bx*z;
	yt=(1+by*by/(1+bz))*y-bx*by*x/(1+bz)-by*z;
	
	line.ro=ro=sqrt(xt*xt+yt*yt);
	line.erfa=erfa=atan(yt/xt);

	return line;
}

double ThreeDLine::point2LineTwoPoints( Point &_point )
{
	Vecline v1,v2,v3;
	v1.x=l_;
	v1.y=m_;
	v1.z=n_;
	v2.x=point_.x-_point.x;
	v2.y=point_.y-_point.y;
	v2.z=point_.z-_point.z;
	v3=cross(v1,v2);
	return sqrt(v3.x*v3.x+v3.y*v3.y+v3.z*v3.z);
}


double ThreeDLine::point2LineMLS( Point &_point )
{
	return sqrt(pow(-_point.y+c_*_point.z+d_,2)+pow(_point.x-a_*_point.z-b_,2)+pow(-c_*_point.x+a_*_point.y+b_*c_-a_*d_,2))/sqrt(a_*a_+c_*c_+1);
}