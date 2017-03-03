/*
*ƽ��ģ��
*ƽ�淽��Ϊ��ax + by + cz = d, (d > 0);
*a^2 + b^2 + c^2 = 1
*���зɣ�2015.12
*/

#ifndef plane_h
#define plane_h

#include "Model.h"
#include "../Luozf/Pointlzf.h"
#include "../Luozf/Matrix.h"

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

namespace td
{
	class Plane:public Model
	{
	public:
		Plane();
		Plane(double, double, double, double);
		~Plane();

		//����ƽ�����
		void setPara(double, double, double, double);
		
		//��ȡƽ�����A
		double getA()
		{
			return a;
		}

		//��ȡƽ�����B
		double getB()
		{
			return b;
		}

		//��ȡƽ�����C
		double getC()
		{
			return c;
		}

		//��ȡƽ�����D
		double getD()
		{
			return d;
		}

		//ͨ���㼯�������������ΪPCA
		void computeFromPoints(PointCloud& );

		//�㵽ƽ��ľ���
		double point2plane(Point&);

	private:
		double a;
		double b;
		double c;
		double d;
	};
}
#endif;
