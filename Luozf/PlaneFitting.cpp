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

//输入点云
void td::PlaneFitting::setInputCloud(td::PointCloud pc)
{
	cloud = pc;
}


//RANSAC进行拟合
bool td::PlaneFitting::computeByRANSAC(double threshold)
{
	srand((unsigned)time(NULL));
	if (cloud.size() <= 3)
		return false;
	//初始迭代次数
	int initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)model.needNum / cloud.size())));
	int iter(0);  //RANSAC循环变量
	int inliers_l(0), inliers_n(0);//上一次循环局内点数目，本次循环局内点数目 

	int randnum = model.needNum;
	int* nIndex=new int [randnum];    //随机点索引

	while (iter < initial_iter)
	{
		
		//抽取随机点
		for (int i = 0; i < randnum; i++)
		{
			nIndex[i] = rand() % cloud.size();
		}
		
		//判断抽取随机点是否重复
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
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers_n / cloud.size(), 3))));//更新循环次数
			model.setPara(pl.getA(), pl.getB(), pl.getC(), pl.getD());
			iter = 0;
			continue;//进行下一次循环
		}
		iter++;
	}
	delete[]nIndex;
	inliers_threshold = threshold;
	return true;
	
}

//BAYSAC进行拟合
bool td::PlaneFitting::computeByBAYSAC(double threshold)
{
	srand((unsigned)time(NULL));
	if (cloud.size() <= 3)
		return false;

	std::vector<double> pro(cloud.size(), 0);//概率值，索引与点一一对应
	
	//初始迭代次数
	int initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)model.needNum / cloud.size())));
	int iter(0);  //RANSAC循环变量
	int inliers_l(0), inliers_n(0);//上一次循环局内点数目，本次循环局内点数目 

	int randnum = model.needNum;
	int* nIndex = new int[randnum];    //随机点索引

	int loop_times = 0; //外层循环次数

	double para_percent = 0;//最优参数占总参数的比例

	//用于参数统计
	std::vector<double> ins, plnum; //记录平面参数
	std::vector<Plane> planes;

	//rasac && baysac同时进行
	while (iter < initial_iter)
	{
		
		//抽取随机点
		for (int i = 0; i < randnum; i++)
		{
			nIndex[i] = rand() % cloud.size();
		}

		//判断抽取随机点是否重复
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
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers_n / cloud.size(), 3))));//更新循环次数
			model.setPara(pl.getA(), pl.getB(), pl.getC(), pl.getD());
			iter = 0;
			continue;//进行下一次循环
		}
		iter++;

		//每次计算的参数放入统计序列中
		planes.push_back(pl);
		ins.push_back(inliers_n);//该参数下局内点的个数
		plnum.push_back(1);


		//最优参数统计,当前参数和前面的参数进行比较,
		if (loop_times >= 1)
		{
			for (size_t i = 0; i < planes.size() - 1; ++i)
			{
				double para_dif = fabs(pl.getA() - planes[i].getA()) + fabs(pl.getB() - planes[i].getB())
					+ fabs(pl.getC() - planes[i].getC()) + fabs(pl.getD() - planes[i].getD());
				if (para_dif < 0.1)
				{
					plnum[i]++;//统计第i套参数的数目
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

		//贝叶斯过程
		if (loop_times >= 30 && para_percent > 0.4)
		{
			std::vector<double>::iterator it_f = plnum.begin();
			std::vector<double>::iterator it_s = max_element(plnum.begin(), plnum.end());
			size_t para_best_index = it_s - it_f;

			//通过参数统计为点赋先验概率
			for (size_t i = 0; i < cloud.size(); i++)
			{
				double d2plane = planes[para_best_index].point2plane(cloud[i]);
				if (d2plane <= threshold)
				{
					pro[i] = 1 - d2plane / threshold;
				}
			}

			//重新开始循环，参数统计步骤已经结束
			iter = 0;
			inliers_l = 0;
			inliers_n = 0;
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)model.needNum / cloud.size())));

			while (iter < initial_iter)
			{
				//找出概率值最高的三个点
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

				//更新假设点集先验概率
				for (int i = 0; i<randnum; i++)
				{
					pro[nIndex[i]] = pro[nIndex[i]] * inliers_n / cloud.size();
				}


				//寻找局内点
				if (inliers_n > inliers_l)
				{
					inliers_l = inliers_n;
					initial_iter = int(ceil(log10(0.01) / log10(1.0 - pow((double)inliers_n / cloud.size(), 3))));//更新K值
					iter = 0;
					model.setPara(pl_.getA(), pl_.getB(), pl_.getC(), pl_.getD());
					continue;//进行下一次循环
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

//BAYLMEDS进行拟合
bool td::PlaneFitting::computeByBayLMedS()
{
	srand((unsigned)time(NULL));
	int loop_times = 0;//外层循环次数
	if (cloud.size() <= 3)
		return false;

	std::vector<double> pro(cloud.size(), 0);//概率值，索引与点一一对应
	int randnum = model.needNum;
	int initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)randnum / cloud.size())));
	int iter(0);  //RANSAC循环变量
	double min_median(1000), mid_deviation(0);//最小中值，本次循环局内点数目 

	int* nIndex = new int[randnum];    //随机点索引

	double para_percent = 0;//最优参数占总参数的比例

	//用于参数统计
	std::vector<double> mid, plnum; //记录平面参数
	std::vector<Plane> planes;


	//lmeds && baylmeds同时进行,当进入不了baysac时直接用lmeds做
	while (iter < initial_iter)
	{
		for (int i = 0; i < randnum; i++)
		{
			nIndex[i] = rand() % cloud.size();
		}

		//判断抽取随机点是否重复
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

		std::vector<double> model_deviation(0);//统计偏差中值
		mid_deviation = 0;
		for (size_t i = 0; i < cloud.size(); i++)
		{
			double d2plane = pl.point2plane(cloud[i]);
			model_deviation.push_back(d2plane);
		}

		sort(model_deviation.begin(), model_deviation.end());

		//获取中值
		if (model_deviation.size() % 2 == 0)
			mid_deviation = (model_deviation[model_deviation.size() / 2 - 1] +
			model_deviation[model_deviation.size() / 2]) / 2;
		else
			mid_deviation = model_deviation[model_deviation.size() / 2];

		//寻找最小中值，并计算模型参数
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

		//平面参数
		//每次计算的参数放入统计序列中
		planes.push_back(pl);
		mid.push_back(mid_deviation);
		plnum.push_back(1);


		//最优参数统计,当前参数和前面的参数进行比较
		if (loop_times >= 1)
		{
			for (size_t i = 0; i < planes.size() - 1; ++i)
			{
				double para_dif = fabs(pl.getA() - planes[i].getA()) + fabs(pl.getB() - planes[i].getB())
					+ fabs(pl.getC() - planes[i].getC()) + fabs(pl.getD() - planes[i].getD());
				if (para_dif < 0.1/*&&fabs(distance-para_distance[i])<6.0*/)
				{
					plnum[i]++;//统计第i套参数的数目
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

		//贝叶斯过程
		if (loop_times >= 30 && para_percent > 0.4)
		{
			std::vector<double>::iterator it_f = plnum.begin();
			std::vector<double>::iterator it_s = max_element(plnum.begin(), plnum.end());
			size_t para_best_index = it_s - it_f;

			//通过参数统计为点赋先验概率
			for (size_t i = 0; i < cloud.size(); i++)
			{
				double d2plane = planes[para_best_index].point2plane(cloud[i]); 
				if (d2plane <= 2 * mid[para_best_index])
				{
					pro[i] = 1 - d2plane / (2 * mid[para_best_index]);
				}
			}

			//重新开始循环，参数统计步骤已经结束
			iter = 0;
			initial_iter = int(ceil(log10(0.01) / log10(1.0 - (double)randnum / cloud.size())));
			min_median = 1000;

			//？循环次数和概率的更新还是需要阈值
			while (iter < /*initial_iter*/1000)
			{
				//找出概率值最高的三个点
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

				std::vector<double> model_deviation_p(0);//统计偏差中值

				mid_deviation = 0;//中值

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

				//更新假设点集先验概率
				double k = 0;     //k为当前中值，局内点的个数
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

				//寻找最小中值，并计算模型参数
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

// 返回平面参数
td::Plane td::PlaneFitting::getModel()
{
	return model;
}


// 返回局内点
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


// 返回模型标准阈值
double td::PlaneFitting::getInlierThershold()
{
	return inliers_threshold;
}


// 返回局外点
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
