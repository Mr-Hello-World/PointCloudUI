/*
*����������
*���зɣ�2015.12
*/

#ifndef point_h
#define point_h

#include <vector>

namespace td
{
	class Point
	{
	public:
		Point();
		//���캯��:Point(x,y,z)
		Point(double, double, double);
		~Point();

		//��������sort����Ϊmap��key
		friend bool operator<(const Point &_pnta, const Point &_pntb);

		//���õ������
		void setPoint(double, double, double);
		

	public:
		double x;
		double y;
		double z;
		bool operator==(const Point& pnt);
	};

	typedef std::vector<td::Point> PointCloud;
}
#endif;
