#include "../Luozf/Segmentation.h"


td::Segmentation::Segmentation()
: radius(0)
, threshold(0)
, k(0)
, averageError(0)
{
}

td::Segmentation::Segmentation(PointCloud in)
{
	cloud = in;
}

td::Segmentation::~Segmentation()
{
}

void td::Segmentation::setInputCloud(PointCloud in)
{
	cloud = in;
}

//���������ָ�,RANSAC���
void td::Segmentation::regionGrow(METHOD method)
{																	//������
	
	
	//Step1:׼��k��������
	KdTree tree(cloud);
	//�����ռ���������
	/*std::map<Point, int> index_map;*/
	std::map<Point, bool> label;
	
	//��ǩ��ʼ��
	for (size_t index = 0; index < cloud.size(); ++index)
	{
		label[cloud[index]] = false;
		/*index_map[cloud[index]] = index;*/
	}

	//������ӵ�
	for (size_t index = 0; index < cloud.size();index++)
	{
		if (label[cloud[index]])
			continue;
		PointCloud neighbors;            //����㼯
		tree.setNumberOfNeighbours(k);
		//tree.setNeighboursRadius(radius);//����뾶
		tree.kNearestNeighbor(cloud[index].x, cloud[index].y, cloud[index].z);
		neighbors = tree.getNearestNeighbor();

		//��ʼ�������,�ҵ�������
		PlaneFitting fit;
		fit.setInputCloud(neighbors);
		bool state(false);
		state = selectMethod(fit, method);
		if (!state)
			continue;
		//��ȡƽ������������ڵ�
		Plane pl;
		pl = fit.getModel();
		PointCloud inliers;
		inliers = fit.getInliers();

		//���������б��
		for (size_t in_i = 0; in_i < inliers.size(); ++in_i)
		{
			label[inliers[in_i]] = true;
		}

		//�Ծ��ڵ������������
		int n = 0;
		//��ò�Ҫʹ�õ��������б���
		for (size_t i = 0; i < inliers.size(); ++i)
		{
			tree.kNearestNeighbor(inliers[i].x, inliers[i].y, inliers[i].z);
			PointCloud candidate = tree.getNearestNeighbor();
			for (PointCloud::iterator can_it = candidate.begin(); can_it != candidate.end(); ++can_it)
			{
				double dis = pl.point2plane(*can_it);
				if (dis > fit.getInlierThershold() || label[*can_it] == true)
				{
					continue;
				}
				++n;
				inliers.push_back(*can_it);								//������ڵ�
				label[*can_it] = true;
				if (n % 30 == 0)
				{
					fit.setInputCloud(inliers);
					state = selectMethod(fit, method);
					pl = fit.getModel();								//����ƽ�����
				}
			}
		}
		indices.push_back(inliers);
		double currentError = 0;
		for (size_t i = 0; i < inliers.size(); i++)
		{
			currentError += pow(pl.point2plane(inliers[i]), 2);
		}
		currentError /= inliers.size();
		currentError = sqrt(currentError);
		averageError += currentError;
	}
	averageError /= indices.size();
}

int td::Segmentation::getModelNum()
{
	return indices.size();
}


// �������������뾶
void td::Segmentation::setRadius(double r)
{
	this->radius = r;
}


// ���������ֵ����Ҫ���RANSAC��BAYSAC���
void td::Segmentation::setThreshold(double threshold)
{
	this->threshold = threshold;
}


bool td::Segmentation::selectMethod(PlaneFitting& fit, METHOD method)
{
	bool state;
	switch (method)
	{
	case RANSAC:
		state = fit.computeByRANSAC(threshold);
		break;
	case BAYSAC:
		state = fit.computeByBAYSAC(threshold);
		break;
	case BAYLMEDS:
		state = fit.computeByBayLMedS();
		break;
	default:
		break;
	}
	return state;
}


// ���Ʒָ���Ϻ����
void td::Segmentation::outPut(std::string path)
{
	std::ofstream outfile;
	outfile.open(path, std::ios::out);
	
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < indices.size(); i++)
	{
		//���������ɫ
		unsigned int r = (int)((double)rand() / ((RAND_MAX + 1.0) / (255 - 100 + 1.0)) + 100);
		unsigned int g = (int)((double)rand() / ((RAND_MAX + 1.0) / (255 - 100 + 1.0)) + 100);
		unsigned int b = (int)((double)rand() / ((RAND_MAX + 1.0) / (255 - 100 + 1.0)) + 100);
		for (size_t j = 0; j < indices.at(i).size(); j++)
		{
			outfile << std::setw(15);
			outfile << std::right;
			outfile << std::fixed;
			outfile << indices.at(i).at(j).x;
			outfile << std::setw(15);
			outfile << std::right;
			outfile << indices.at(i).at(j).y;
			outfile << std::setw(15);
			outfile << std::right;
			outfile << indices.at(i).at(j).z;
			outfile << std::setw(6);
			outfile << std::right;
			outfile << r;
			outfile << std::setw(6);
			outfile << std::right;
			outfile << g;
			outfile << std::setw(6);
			outfile << std::right;
			outfile << b;
			outfile << std::endl;
		}
	}
	outfile.close();
	
}


// ����k����ֵ
void td::Segmentation::setKNearest(int k)
{
	this->k = k;
}

double td::Segmentation::getAverageError()
{
	return averageError;
}

// //Multi-RANSAC���зָ�
void td::Segmentation::multiRansac()
{
	indices.clear();
	double pro = 1.0;
	PointCloud mcloud = cloud;
	while (pro>0.2)
	{
		PlaneFitting fit;
		fit.setInputCloud(mcloud);
		bool state(false);
		state = selectMethod(fit, RANSAC);
		if (!state)
			break;
		//��ȡƽ������������ڵ�
		Plane pl;
		pl = fit.getModel();
		PointCloud inliers;
		inliers = fit.getInliers();
		indices.push_back(inliers);
		mcloud = fit.getOutliers();
		pro = (double)mcloud.size() / cloud.size();
		double currentError = 0;
		for (size_t i = 0; i < inliers.size(); i++)
		{
			currentError += pow(pl.point2plane(inliers[i]), 2);
		}
		currentError /= inliers.size();
		currentError = sqrt(currentError);
		averageError += currentError;
	}
	averageError /= indices.size();
}
