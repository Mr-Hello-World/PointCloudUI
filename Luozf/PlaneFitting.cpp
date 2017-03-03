#include "../Luozf/PlaneFitting.h"


td::PlaneFitting::PlaneFitting()
: inliers_threshold(0)
{

}

td::PlaneFitting::PlaneFitting(td::PointCloud pc)
{
	cloud = pc;
}

td::PlaneFitting::~PlaneFitting()
{

}

//�������
void td::PlaneFitting::setInputCloud(td::PointCloud pc)
{
	cloud = pc;
}


//RANSAC�������
bool td::PlaneFitting::computeByRANSAC(double threshold)
{
	srand((unsigned)time(NULL));
	if (cloud.size() <= 3)
		return false;
	//��ʼ��������
	int initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)model.needNum / cloud.size())));
	int iter(0);  //RANSACѭ������
	int inliers_l(0), inliers_n(0);//��һ��ѭ�����ڵ���Ŀ������ѭ�����ڵ���Ŀ 

	int randnum = model.needNum;
	int* nIndex=new int [randnum];    //���������

	while (iter < initial_iter)
	{
		
		//��ȡ�����
		for (int i = 0; i < randnum; i++)
		{
			nIndex[i] = rand() % cloud.size();
		}
		
		//�жϳ�ȡ������Ƿ��ظ�
		bool allsame(true);
		for (int i = 1; i < randnum; i++)
		{
			allsame = allsame&&nIndex[i] == nIndex[i - 1];
		}
		if (allsame)
			continue;

		Plane pl;
		PointCloud randcloud;
		for (int i = 0; i < randnum; i++)
		{
			randcloud.push_back(cloud[nIndex[i]]);
		}
		pl.computeFromPoints(randcloud);

		double d2plane(0);
		inliers_n = 0;
		for (size_t i = 0; i < cloud.size(); ++i)
		{
			d2plane = pl.point2plane(cloud[i]);
			if (d2plane <= threshold)
			{
				inliers_n++;
			}
		}


		if (inliers_n > inliers_l)
		{
			inliers_l = inliers_n;
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers_n / cloud.size(), 3))));//����ѭ������
			model.setPara(pl.getA(), pl.getB(), pl.getC(), pl.getD());
			iter = 0;
			continue;//������һ��ѭ��
		}
		iter++;
	}
	delete[]nIndex;
	inliers_threshold = threshold;
	return true;
	
}

//BAYSAC�������
bool td::PlaneFitting::computeByBAYSAC(double threshold)
{
	srand((unsigned)time(NULL));
	if (cloud.size() <= 3)
		return false;

	std::vector<double> pro(cloud.size(), 0);//����ֵ���������һһ��Ӧ
	
	//��ʼ��������
	int initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)model.needNum / cloud.size())));
	int iter(0);  //RANSACѭ������
	int inliers_l(0), inliers_n(0);//��һ��ѭ�����ڵ���Ŀ������ѭ�����ڵ���Ŀ 

	int randnum = model.needNum;
	int* nIndex = new int[randnum];    //���������

	int loop_times = 0; //���ѭ������

	double para_percent = 0;//���Ų���ռ�ܲ����ı���

	//���ڲ���ͳ��
	std::vector<double> ins, plnum; //��¼ƽ�����
	std::vector<Plane> planes;

	//rasac && baysacͬʱ����
	while (iter < initial_iter)
	{
		
		//��ȡ�����
		for (int i = 0; i < randnum; i++)
		{
			nIndex[i] = rand() % cloud.size();
		}

		//�жϳ�ȡ������Ƿ��ظ�
		bool allsame(true);
		for (int i = 1; i < randnum; i++)
		{
			allsame = allsame&&nIndex[i] == nIndex[i - 1];
		}
		if (allsame)
			continue;

		loop_times++;

		Plane pl;
		PointCloud randcloud;
		for (int i = 0; i < randnum; i++)
		{
			randcloud.push_back(cloud[nIndex[i]]);
		}
		pl.computeFromPoints(randcloud);

		double d2plane(0);
		inliers_n = 0;
		for (size_t i = 0; i < cloud.size(); ++i)
		{
			d2plane = pl.point2plane(cloud[i]);
			if (d2plane <= threshold)
			{
				inliers_n++;
			}
		}


		if (inliers_n > inliers_l)
		{
			inliers_l = inliers_n;
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers_n / cloud.size(), 3))));//����ѭ������
			model.setPara(pl.getA(), pl.getB(), pl.getC(), pl.getD());
			iter = 0;
			continue;//������һ��ѭ��
		}
		iter++;

		//ÿ�μ���Ĳ�������ͳ��������
		planes.push_back(pl);
		ins.push_back(inliers_n);//�ò����¾��ڵ�ĸ���
		plnum.push_back(1);


		//���Ų���ͳ��,��ǰ������ǰ��Ĳ������бȽ�,
		if (loop_times >= 1)
		{
			for (size_t i = 0; i < planes.size() - 1; ++i)
			{
				double para_dif = fabs(pl.getA() - planes[i].getA()) + fabs(pl.getB() - planes[i].getB())
					+ fabs(pl.getC() - planes[i].getC()) + fabs(pl.getD() - planes[i].getD());
				if (para_dif < 0.1)
				{
					plnum[i]++;//ͳ�Ƶ�i�ײ�������Ŀ
					if (inliers_n>ins[i])
					{
						planes[i].setPara(pl.getA(), pl.getB(), pl.getC(), pl.getD());
						ins[i] = inliers_n;
					}
					planes.pop_back();
					ins.pop_back();
					plnum.pop_back();
				}
			}
			para_percent = *max_element(plnum.begin(), plnum.end()) / (double)(loop_times);
		}

		//��Ҷ˹����
		if (loop_times >= 30 && para_percent > 0.4)
		{
			std::vector<double>::iterator it_f = plnum.begin();
			std::vector<double>::iterator it_s = max_element(plnum.begin(), plnum.end());
			size_t para_best_index = it_s - it_f;

			//ͨ������ͳ��Ϊ�㸳�������
			for (size_t i = 0; i < cloud.size(); i++)
			{
				double d2plane = planes[para_best_index].point2plane(cloud[i]);
				if (d2plane <= threshold)
				{
					pro[i] = 1 - d2plane / threshold;
				}
			}

			//���¿�ʼѭ��������ͳ�Ʋ����Ѿ�����
			iter = 0;
			inliers_l = 0;
			inliers_n = 0;
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)model.needNum / cloud.size())));

			while (iter < initial_iter)
			{
				//�ҳ�����ֵ��ߵ�������
				std::vector<double> temp = pro;
				for (int i = 0; i < randnum; i++)
				{
					std::vector<double>::iterator it;
					it = max_element(temp.begin(), temp.end());
					nIndex[i] = it - temp.begin();
					temp.erase(it);
				}
				temp.clear();

				Plane pl_;
				PointCloud randcloud_;
				for (int i = 0; i < randnum; i++)
				{
					randcloud_.push_back(cloud[nIndex[i]]);
				}
				pl_.computeFromPoints(randcloud_);


				inliers_n = 0;
				for (size_t i = 0; i < cloud.size(); ++i)
				{
					d2plane = pl_.point2plane(cloud[i]);
					if (d2plane <= threshold)
					{
						inliers_n++;
					}
				}

				//���¼���㼯�������
				for (int i = 0; i<randnum; i++)
				{
					pro[nIndex[i]] = pro[nIndex[i]] * inliers_n / cloud.size();
				}


				//Ѱ�Ҿ��ڵ�
				if (inliers_n > inliers_l)
				{
					inliers_l = inliers_n;
					initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers_n / cloud.size(), 3))));//����Kֵ
					iter = 0;
					model.setPara(pl_.getA(), pl_.getB(), pl_.getC(), pl_.getD());
					continue;//������һ��ѭ��
				}
				iter++;
			}
			break;
		}
	}
	delete[]nIndex;
	inliers_threshold = threshold;
	return true;
}

//BAYLMEDS�������
bool td::PlaneFitting::computeByBayLMedS()
{
	srand((unsigned)time(NULL));
	int loop_times = 0;//���ѭ������
	if (cloud.size() <= 3)
		return false;

	std::vector<double> pro(cloud.size(), 0);//����ֵ���������һһ��Ӧ
	int randnum = model.needNum;
	int initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)randnum / cloud.size())));
	int iter(0);  //RANSACѭ������
	double min_median(1000), mid_deviation(0);//��С��ֵ������ѭ�����ڵ���Ŀ 

	int* nIndex = new int[randnum];    //���������

	double para_percent = 0;//���Ų���ռ�ܲ����ı���

	//���ڲ���ͳ��
	std::vector<double> mid, plnum; //��¼ƽ�����
	std::vector<Plane> planes;


	//lmeds && baylmedsͬʱ����,�����벻��baysacʱֱ����lmeds��
	while (iter < initial_iter)
	{
		for (int i = 0; i < randnum; i++)
		{
			nIndex[i] = rand() % cloud.size();
		}

		//�жϳ�ȡ������Ƿ��ظ�
		bool allsame(true);
		for (int i = 1; i < randnum; i++)
		{
			allsame = allsame&&nIndex[i] == nIndex[i - 1];
		}
		if (allsame)
			continue;

		loop_times++;

		Plane pl;
		PointCloud randcloud;
		for (int i = 0; i < randnum; i++)
		{
			randcloud.push_back(cloud[nIndex[i]]);
		}
		pl.computeFromPoints(randcloud);

		std::vector<double> model_deviation(0);//ͳ��ƫ����ֵ
		mid_deviation = 0;
		for (size_t i = 0; i < cloud.size(); i++)
		{
			double d2plane = pl.point2plane(cloud[i]);
			model_deviation.push_back(d2plane);
		}

		sort(model_deviation.begin(), model_deviation.end());

		//��ȡ��ֵ
		if (model_deviation.size() % 2 == 0)
			mid_deviation = (model_deviation[model_deviation.size() / 2 - 1] +
			model_deviation[model_deviation.size() / 2]) / 2;
		else
			mid_deviation = model_deviation[model_deviation.size() / 2];

		//Ѱ����С��ֵ��������ģ�Ͳ���
		if (mid_deviation < min_median)
		{
			min_median = mid_deviation;

			int inliers = 0;
			for (size_t i = 0; i < cloud.size(); i++)
			{
				double d2plane = pl.point2plane(cloud[i]);
				if (d2plane <= 2 * min_median)
				{
					inliers++;
				}
			}
			model.setPara(pl.getA(), pl.getB(), pl.getC(), pl.getD());
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers / cloud.size(), 3))));
			iter = 0;
			continue;
		}
		iter++;

		//ƽ�����
		//ÿ�μ���Ĳ�������ͳ��������
		planes.push_back(pl);
		mid.push_back(mid_deviation);
		plnum.push_back(1);


		//���Ų���ͳ��,��ǰ������ǰ��Ĳ������бȽ�
		if (loop_times >= 1)
		{
			for (size_t i = 0; i < planes.size() - 1; ++i)
			{
				double para_dif = fabs(pl.getA() - planes[i].getA()) + fabs(pl.getB() - planes[i].getB())
					+ fabs(pl.getC() - planes[i].getC()) + fabs(pl.getD() - planes[i].getD());
				if (para_dif < 0.1/*&&fabs(distance-para_distance[i])<6.0*/)
				{
					plnum[i]++;//ͳ�Ƶ�i�ײ�������Ŀ
					if (mid_deviation < mid[i])
					{
						planes[i].setPara(pl.getA(), pl.getB(), pl.getC(), pl.getD());
						mid[i] = mid_deviation;
					}
					planes.pop_back();
					mid.pop_back();
					plnum.pop_back();
				}
			}
			para_percent = *max_element(plnum.begin(), plnum.end()) / (double)(loop_times);
		}

		//��Ҷ˹����
		if (loop_times >= 30 && para_percent > 0.4)
		{
			std::vector<double>::iterator it_f = plnum.begin();
			std::vector<double>::iterator it_s = max_element(plnum.begin(), plnum.end());
			size_t para_best_index = it_s - it_f;

			//ͨ������ͳ��Ϊ�㸳�������
			for (size_t i = 0; i < cloud.size(); i++)
			{
				double d2plane = planes[para_best_index].point2plane(cloud[i]); 
				if (d2plane <= 2 * mid[para_best_index])
				{
					pro[i] = 1 - d2plane / (2 * mid[para_best_index]);
				}
			}

			//���¿�ʼѭ��������ͳ�Ʋ����Ѿ�����
			iter = 0;
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)randnum / cloud.size())));
			min_median = 1000;

			//��ѭ�������͸��ʵĸ��»�����Ҫ��ֵ
			while (iter < /*initial_iter*/1000)
			{
				//�ҳ�����ֵ��ߵ�������
				std::vector<double> temp = pro;
				for (int i = 0; i < randnum; i++)
				{
					std::vector<double>::iterator it;
					it = max_element(temp.begin(), temp.end());
					nIndex[i] = it - temp.begin();
					temp.erase(it);
				}
				temp.clear();

				Plane pl_;
				PointCloud randcloud_;
				for (int i = 0; i < randnum; i++)
				{
					randcloud_.push_back(cloud[nIndex[i]]);
				}
				
				pl_.computeFromPoints(randcloud_);

				std::vector<double> model_deviation_p(0);//ͳ��ƫ����ֵ

				mid_deviation = 0;//��ֵ

				for (size_t i = 0; i < cloud.size(); ++i)
				{
					double d2plane = pl_.point2plane(cloud[i]);
					model_deviation_p.push_back(d2plane);
				}

				sort(model_deviation_p.begin(), model_deviation_p.end());
				if (model_deviation_p.size() % 2 == 0)
					mid_deviation = (model_deviation_p[model_deviation_p.size() / 2 - 1] +
					model_deviation_p[model_deviation_p.size() / 2]) / 2;
				else
					mid_deviation = model_deviation_p[model_deviation_p.size() / 2];

				//���¼���㼯�������
				double k = 0;     //kΪ��ǰ��ֵ�����ڵ�ĸ���
				for (size_t i = 0; i < cloud.size(); ++i)
				{
					double d2plane = pl_.point2plane(cloud[i]);
					if (d2plane <= 2 * mid_deviation)
					{
						k = k + 1.0;
					}
				}
				for (int i = 0; i < randnum; i++)
				{
					pro[i] = pro[i] * k / cloud.size();
				}

				//Ѱ����С��ֵ��������ģ�Ͳ���
				if (mid_deviation < min_median)
				{
					min_median = mid_deviation;
					int inliers = 0;

					for (size_t i = 0; i < cloud.size(); ++i)
					{
						double d2plane = pl_.point2plane(cloud[i]);
						if (d2plane <= 3 * min_median)
						{
							inliers++;
						}
					}
					model.setPara(pl_.getA(), pl_.getB(), pl_.getC(), pl_.getD());
					initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers / cloud.size(), 3))));
					//iter = 0;
					//continue;
				}
				iter++;
			}
			break;
		}
	}
	delete[]nIndex;
	inliers_threshold = 2.0 * min_median;
	return true;
}

// ����ƽ�����
td::Plane td::PlaneFitting::getModel()
{
	return model;
}


// ���ؾ��ڵ�
td::PointCloud td::PlaneFitting::getInliers()
{
	PointCloud inliers;
	for (size_t i = 0; i < cloud.size(); ++i)
	{
		double d2plane = model.point2plane(cloud[i]);
		if (d2plane <= inliers_threshold)
		{
			inliers.push_back(cloud[i]);
		}
	}
	return inliers;
}


// ����ģ�ͱ�׼��ֵ
double td::PlaneFitting::getInlierThershold()
{
	return inliers_threshold;
}


// ���ؾ����
td::PointCloud td::PlaneFitting::getOutliers()
{
	PointCloud outliers;
	for (size_t i = 0; i < cloud.size(); ++i)
	{
		double d2plane = model.point2plane(cloud[i]);
		if (d2plane > inliers_threshold)
		{
			outliers.push_back(cloud[i]);
		}
	}
	return outliers;
}
