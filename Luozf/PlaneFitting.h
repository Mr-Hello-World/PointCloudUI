/*
*��Ҫ���ڵ��Ƶ����
*LMS����С���˷�
*RANSAC���������һ����
*BaySAC�����ڱ�Ҷ˹������ʳ���һ����
*BayLMedS:���ڱ�Ҷ˹���������Сƽ����ֵ
*���зɣ�2015.12
*/



#ifndef fitting_h
#define fitting_h


#include "../Luozf/Pointlzf.h"
#include "../Luozf/Planelzf.h"

#include <vector>
#include <ctime>

namespace td
{
	
	class PlaneFitting
	{
	public:
		PlaneFitting();
		PlaneFitting(td::PointCloud pc);
		~PlaneFitting();

		//�������
		void setInputCloud(PointCloud pc);


		//RANSAC�������
		bool computeByRANSAC(double );

		//BAYSAC�������
		bool computeByBAYSAC(double );

		//BAYLMEDS�������
		bool computeByBayLMedS();

	private:
		PointCloud cloud;
		Plane model;
	public:
		// ����ƽ�����
		Plane getModel();
	private:
		// ���ڵ���ֵ
		double inliers_threshold;
	public:
		// ���ؾ��ڵ�
		PointCloud getInliers();
		// ����ģ�ͱ�׼��ֵ
		double getInlierThershold();
		// ���ؾ����
		td::PointCloud getOutliers();
	};
}

#endif;
