#include "buildfootprint.h"
#include "../Voxel/voxel.h"
#include <list>
#include <time.h>
//#include <opencv2/opencv.hpp>
//using cv::Mat;
using cv::Vec3b;
typedef unsigned char BYTE;

void BuildFootprint::parameter()
{
	ifstream ifile;
	ifile.open("parameter.par");
	if (!ifile)
	{
		cout << "file data do not open ！" << endl;
		return;
	}
	ifile >> GSD_ >> erfa_ >> beta_ >> num_;
	cout << "GSD:" << GSD_ << " erfa:" << erfa_ << " beta:" << beta_ << " num:" << num_ << endl;
	ifile.close();
}

Point BuildFootprint::centerOfVoxel(const Pos2D &_pos2D)
{
	Point centerP;
	centerP.x = (_pos2D.i + 2)*GSD_ / 2.0 + extream_.minx_;
	centerP.x = (_pos2D.j + 2)*GSD_ / 2.0 + extream_.miny_;
	return centerP;
}
Point BuildFootprint::weightCenter(Points &_points)
{
	Point weightCP;
	weightCP.x = weightCP.y = weightCP.z = 0;
	for (Points::iterator it = _points.begin(); it != _points.end(); ++it)
	{
		weightCP.x += it->x;
		weightCP.y += it->y;
		weightCP.z += it->z;
	}
	weightCP.x /= (_points.size()*1.0);
	weightCP.y /= (_points.size()*1.0);
	weightCP.z /= (_points.size()*1.0);

	return weightCP;
}

void BuildFootprint::reflectImage()
{
	//parameter();

	Point pnt;
	pnt.input1(points_);

	map<Pos2D, Points> voxel2D;
	map<Pos2D, double> F;

	extream_.getMaxMinValue(points_);
	Pos2D pos2D;
	for (Points::iterator it = points_.begin(); it != points_.end(); ++it)
	{
		pos2D.i = ROUNDEX((it->x - extream_.minx_) / GSD_);	//w
		pos2D.j = ROUNDEX((it->y - extream_.miny_) / GSD_);	//h
		voxel2D[pos2D].push_back(*it);
	}

	Point centerPoint;
	MaxMinValueofCoor voxelij;
	double WijXY = 0, WijH = 0, Hij = 0, Wij = 0;
	double sum1 = 0, sum2 = 0;

	/*voxelij.getMaxMinZ(points_);
	cout<<voxelij.maxz_<<" "<<voxelij.minz_<<endl;
	cout << extream_.maxz_ << " " << extream_.minz_ << endl;*/
	double tempMax = LONG_MIN, tempMin = LONG_MAX, temp;
	//cout <<"erfa::"<< erfa_ << " "<<endl;
	for (map<Pos2D, Points>::iterator it = voxel2D.begin(); it != voxel2D.end(); ++it)
	{
		//centerPoint = centerOfVoxel(it->first);
		centerPoint = weightCenter(it->second);
		voxelij.getMaxMinZ(it->second);

		sum1 = 0, sum2 = 0;
		
		for (Points::iterator pIt = it->second.begin(); pIt != it->second.end(); ++pIt)
		{
			WijXY = sqrt(2.0)*GSD_ / point2pointInXY(*pIt, centerPoint);
			Hij = pIt->z - extream_.minz_;
			WijH = Hij*(voxelij.minz_ - extream_.minz_) / (extream_.maxz_ - voxelij.maxz_);

			Wij = erfa_*WijXY + beta_*WijH;

			sum1 += (Wij*pIt->z);
			sum2 += Wij;
		}
		F[it->first] = temp = sum1 / sum2;// +it->second.size() / 30;
		if (temp > tempMax)
		{
			tempMax = temp;
		}
		if (temp < tempMin)
		{
			tempMin = temp;
		}
		//cout<<"F:"<<sum1/sum2<<endl;			
	}
	int W, H;
	W = ROUNDEX((extream_.maxx_ - extream_.minx_) / GSD_);
	H = ROUNDEX((extream_.maxy_ - extream_.miny_) / GSD_);
	++W;
	++H;
	cout << GSD_ << endl;
	cv::Mat src(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
	cout << H << " " << W << endl;
	for (map<Pos2D, double>::iterator it = F.begin(); it != F.end(); ++it)
	{
		BYTE temp = BYTE(ROUNDEX(255 / (tempMax - tempMin)*(it->second - tempMin)));
		src.at<Vec3b>(it->first.j, it->first.i) = Vec3b(temp, temp, temp);
		//cout << (int)temp << endl;
	}

	for (map<Pos2D, Points>::iterator it = voxel2D.begin(); it != voxel2D.end(); ++it)
	{
		if (it->second.size()>num_)
		{
			BYTE temp = 180;
			src.at<Vec3b>(it->first.j, it->first.i) = Vec3b(temp, temp, temp);
		}
	}


	cv::imshow("src", src);
	imwrite("C:\\Users\\shizhenwei\\Desktop\\Polydata0406.bmp", src);
	cv::waitKey();


	//const char *pstrWindowsSrcTitle = "原图";
	//const char *pstrWindowsToolBar = "Threshold";
	//
	////从文件中载入图像的灰度图CV_LOAD_IMAGE_GRAYSCALE - 灰度图
	//g_pSrcImage = src;
	//g_pCannyImg.create(g_pSrcImage.size(),g_pSrcImage.type());
	//		
	////创建窗口
	//cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	//cvNamedWindow(pstrWindowsCannyTitle, CV_WINDOW_AUTOSIZE);
	//
	////创建滑动条
	//int nThresholdEdge = 1;
	//createTrackbar(pstrWindowsToolBar, pstrWindowsCannyTitle, &nThresholdEdge, 100, on_trackbar);
	//
	////在指定窗口中显示图像
	//imshow(pstrWindowsSrcTitle, g_pSrcImage);
	//on_trackbar(0,0);
	//	
	////等待按键事件
	//waitKey();
	//cout<<g_pSrcImage.rows<<" "<<g_pSrcImage.cols<<endl;
	//cout<<g_pCannyImg.rows<<" "<<g_pCannyImg.cols<<endl;
	//imwrite("canny.bmp",g_pCannyImg);
	//Mat can;
	//can=imread("canny.bmp");
	//imshow("can",can);
	//waitKey();
	//
	//Points points;
	//Pos2D pos2D1;
	//map<Pos2D,Points>::iterator it;
	//for(int row = 0; row < can.rows; row++)  
	//{      
	//	const Vec3b * Mi = can.ptr<Vec3b>(row);   
	//	for (int col = 0; col < can.cols; col++)        
	//	{
	//		if (can.at<Vec3b>(row,col)==Vec3b(255,255,255))
	//		{
	//			//cout<<can.at<Vec3b>(row,col)<<endl;
	//			
	//			for (int ii=row-1;ii<=row+1;++ii)
	//			{
	//				for (int jj=col-1;jj<=col+1;++jj)
	//				{
	//					pos2D1.j=ii;
	//					pos2D1.i=jj;
	//					it=voxel2D_.find(pos2D1);
	//					if (it!=voxel2D_.end())
	//					{
	//						points.insert(points.end(),voxel2D_[pos2D1].begin(),voxel2D_[pos2D1].end());
	//					}
	//				}
	//			}

	//			
	//		}
	//	}
	//}
	//points.sort();
	//points.unique();
	//Point pnt;
	//pnt.output1(points);
}



void BuildFootprint::regionGrowing(cv::Mat &_src, cv::Mat &_seg, map<Pos2D, Points> &_voxel2D)
{
	//for (int i = 0; i < _src.rows; ++i)
	//{
	//	for (int j = 0; j < _src.cols; ++j)
	//	{
	//		if ((int)_src.at<Vec3b>(i, j)[1])
	//		{
	//			cout << (int)_src.at<Vec3b>(i, j)[1] << endl;
	//		}
	//	}
	//}

	int H = _src.rows;
	int W = _src.cols;
	cout << "H:"<<H << " W:" << W << endl;
	
	std::vector<std::vector<bool>> label;							//default false
	label.resize(H);
	for (int i = 0; i < H; ++i)
	{
		label[i].resize(W);
	}
	
	list<Pos2D> src;													//原始像元的坐标
	list<list<Pos2D>> segs;
	Pos2D pos2D;
	for (int i = 1; i < H - 1; ++i)
	{
		for (int j = 1; j < W - 1; ++j)
		{
			pos2D.i = i;
			pos2D.j = j;
			src.push_back(pos2D);
		}
	}
	//cout << src.size() << endl;
	//cout << (H - 2)*(W - 2) << endl;

	int ths = 30, thr = 40;												//选取种子和生长阈值

	list<Pos2D> seg;
	Pos2D seed,temPos;
	int t=0;
	for (list<Pos2D>::iterator it = src.begin(); it != src.end(); ++it)
	{
		//cout << it->i << "　" << it->j << endl;
		if (label[it->i][it->j])
		{
			continue;
		}

		//cout << it->i << "　" << it->j << endl;
		//判断是否为种子
		int ssum=0;
		for (int i = it->i-1; i <= it->i + 1; ++i)
		{
			for (int j = it->j-1; j <= it->j + 1; ++j)
			{
				ssum += (int)_src.at<Vec3b>(i, j)[1];
			}
		}
		ssum -= (int)_src.at<Vec3b>(it->i,it->j)[1];
		ssum /= 8;
		seg.clear();
		if (abs((int)_src.at<Vec3b>(it->i, it->j)[1] - ssum) < ths)
		{
			seg.push_back(*it);
			seed = *it;
			//cout << "seed" << endl;
		}
		//cout << "heheda\n";
		//生长
		for (list<Pos2D>::iterator it1 = seg.begin(); it1 != seg.end(); ++it1)
		{			
			if (it1->i<1||it1->i>H-1||it1->j<1||it1->j>W-1)
			{
				continue;
			}

			for (int i = it1->i - 1; i <= it1->i + 1; ++i)
			{
				for (int j = it1->j - 1; j <= it1->j + 1; ++j)
				{
					if (i<1 || i>H - 1 || j<1 || j>W - 1)
					{
						continue;
					}

					if (label[i][j])
					{
						continue;
					}
					
					if (abs((int)_src.at<Vec3b>(i, j)[1] - (int)_src.at<Vec3b>(seed.i, seed.j)[1]) < thr)
					{
						temPos.i = i;
 						temPos.j = j;
 						seg.push_back(temPos);
 						label[i][j] = true;
						//++t;
					}
				}
			}			
		}
		if (seg.size())
		{
			segs.push_back(seg);
			//t += seg.size();
		}
		seg.clear();
	}
	cout <<"面片数目：" <<segs.size() << endl;
	cout << (H - 2)*(W - 2) << endl;
	cout << "t:" << t << endl;

	//list<Points> points;
	Points points;
	list<Points> points_seg;
	int r, g, b;
	srand(unsigned(time(0)));
	for (list<list<Pos2D>>::iterator it = segs.begin(); it != segs.end(); ++it)
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		//cout << it->size() << endl;
		for (list<Pos2D>::iterator it1 = it->begin(); it1 != it->end(); ++it1)
		{
			_seg.at<Vec3b>(it1->i, it1->j) = Vec3b(BYTE(r), BYTE(g), BYTE(b));
		}

		if (it->size() > 100 && it->size() < 1000)
		{
			//cout << ++t << endl;
			points.clear();
			for (list<Pos2D>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
			{
				Pos2D pos;
				pos.i = it2->j;
				pos.j = it2->i;
				
				points.insert(points.end(), _voxel2D[pos].begin(), _voxel2D[pos].end());
				//points.push_back(_voxel2D[pos]);
				//cout << it->size()<<endl;
				
			}
			points_seg.push_back(points);
		}
	}
	Point pnt;
	//points.sort();
	//points.unique();
	//pnt.output1(points);
	pnt.output2(points_seg);	
}

void BuildFootprint::regionGrowing(cv::Mat &_src, cv::Mat &_seg, map<Pos2D, Points> &_voxel2D, list<Points> &points_seg)
{
	//for (int i = 0; i < _src.rows; ++i)
	//{
	//	for (int j = 0; j < _src.cols; ++j)
	//	{
	//		if ((int)_src.at<Vec3b>(i, j)[1])
	//		{
	//			cout << (int)_src.at<Vec3b>(i, j)[1] << endl;
	//		}
	//	}
	//}

	int H = _src.rows;
	int W = _src.cols;
	cout << "H:" << H << " W:" << W << endl;

	std::vector<std::vector<bool>> label;							//default false
	label.resize(H);
	for (int i = 0; i < H; ++i)
	{
		label[i].resize(W);
	}

	list<Pos2D> src;													//原始像元的坐标
	list<list<Pos2D>> segs;
	Pos2D pos2D;
	for (int i = 1; i < H - 1; ++i)
	{
		for (int j = 1; j < W - 1; ++j)
		{
			pos2D.i = i;
			pos2D.j = j;
			src.push_back(pos2D);
		}
	}
	//cout << src.size() << endl;
	//cout << (H - 2)*(W - 2) << endl;

	int ths = 30, thr = 40;												//选取种子和生长阈值

	list<Pos2D> seg;
	Pos2D seed, temPos;
	int t = 0;
	for (list<Pos2D>::iterator it = src.begin(); it != src.end(); ++it)
	{
		//cout << it->i << "　" << it->j << endl;
		if (label[it->i][it->j])
		{
			continue;
		}

		//cout << it->i << "　" << it->j << endl;
		//判断是否为种子
		int ssum = 0;
		for (int i = it->i - 1; i <= it->i + 1; ++i)
		{
			for (int j = it->j - 1; j <= it->j + 1; ++j)
			{
				ssum += (int)_src.at<Vec3b>(i, j)[1];
			}
		}
		ssum -= (int)_src.at<Vec3b>(it->i, it->j)[1];
		ssum /= 8;
		seg.clear();
		if (abs((int)_src.at<Vec3b>(it->i, it->j)[1] - ssum) < ths)
		{
			seg.push_back(*it);
			seed = *it;
			//cout << "seed" << endl;
		}
		//cout << "heheda\n";
		//生长
		for (list<Pos2D>::iterator it1 = seg.begin(); it1 != seg.end(); ++it1)
		{
			if (it1->i<1 || it1->i>H - 1 || it1->j<1 || it1->j>W - 1)
			{
				continue;
			}

			for (int i = it1->i - 1; i <= it1->i + 1; ++i)
			{
				for (int j = it1->j - 1; j <= it1->j + 1; ++j)
				{
					if (i<1 || i>H - 1 || j<1 || j>W - 1)
					{
						continue;
					}

					if (label[i][j])
					{
						continue;
					}

					if (abs((int)_src.at<Vec3b>(i, j)[1] - (int)_src.at<Vec3b>(seed.i, seed.j)[1]) < thr)
					{
						temPos.i = i;
						temPos.j = j;
						seg.push_back(temPos);
						label[i][j] = true;
						//++t;
					}
				}
			}
		}
		if (seg.size())
		{
			segs.push_back(seg);
			//t += seg.size();
		}
		seg.clear();
	}
	cout << "面片数目：" << segs.size() << endl;
	cout << (H - 2)*(W - 2) << endl;
	cout << "t:" << t << endl;

	//list<Points> points;
	Points points;
	
	int r, g, b;
	srand(unsigned(time(0)));
	for (list<list<Pos2D>>::iterator it = segs.begin(); it != segs.end(); ++it)
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		//cout << it->size() << endl;
		for (list<Pos2D>::iterator it1 = it->begin(); it1 != it->end(); ++it1)
		{
			_seg.at<Vec3b>(it1->i, it1->j) = Vec3b(BYTE(r), BYTE(g), BYTE(b));
		}

		if (it->size() > 100 && it->size() < 1000)
		{
			//cout << ++t << endl;
			points.clear();
			for (list<Pos2D>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
			{
				Pos2D pos;
				pos.i = it2->j;
				pos.j = it2->i;

				points.insert(points.end(), _voxel2D[pos].begin(), _voxel2D[pos].end());
				//points.push_back(_voxel2D[pos]);
				//cout << it->size()<<endl;

			}
			points_seg.push_back(points);
		}
	}
	//Point pnt;
	//points.sort();
	//points.unique();
	//pnt.output1(points);
	//pnt.output2(points_seg);
}

void BuildFootprint::featureImage()
{
	//parameter();

	Point pnt;
	pnt.input1(points_);

	map<Pos2D, Points> voxel2D;
	map<Pos2D, double> F;

	extream_.getMaxMinValue(points_);

	Pos2D pos2D;
	for (Points::iterator it = points_.begin(); it != points_.end(); ++it)
	{
		pos2D.i = ROUNDEX((it->x - extream_.minx_) / GSD_);	//w
		pos2D.j = ROUNDEX((it->y - extream_.miny_) / GSD_);	//h
		voxel2D[pos2D].push_back(*it);
	}

	int maxNum=LONG_MIN, minNum=LONG_MAX;			//+-2147483648
	//cout << LONG_MIN << " " << LONG_MAX << endl;
	for (map<Pos2D, Points>::iterator it = voxel2D.begin(); it != voxel2D.end();++it)
	{
		if ((int)it->second.size()>maxNum)
		{
			maxNum = it->second.size();
		}
		if ((int)it->second.size()<minNum)
		{
			minNum = it->second.size();
		}
	}
	//cout << maxNum << " " << minNum << endl;

	int W, H;
	W = ROUNDEX((extream_.maxx_ - extream_.minx_) / GSD_);
	H = ROUNDEX((extream_.maxy_ - extream_.miny_) / GSD_);
	++W;
	++H;
	cout << H << " " << W << endl;

	MaxMinValueofCoor extreamVoxel;
	cv::Mat src(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
	for (map<Pos2D, Points>::iterator it = voxel2D.begin(); it != voxel2D.end(); ++it)
	{
		//BYTE temp = BYTE(ROUNDEX(255 / (tempMax - tempMin)*(it->second - tempMin)));
		BYTE temp1 = BYTE(ROUNDEX(255 / (maxNum - minNum)*((int)it->second.size() - minNum)));
		extreamVoxel.getMaxMinZ(it->second);
		BYTE temp2 = BYTE(ROUNDEX(255 / (extream_.maxz_ - extream_.minz_)*(extreamVoxel.maxz_ - extream_.minz_)));

		BYTE temp = erfa_*temp1 + beta_*temp2;
		//cout << (int)temp << endl;

		src.at<Vec3b>(it->first.j, it->first.i) = Vec3b(temp, temp, temp);	
	}

	string featureImagePaht,segFeatureImagePath;
	cout << "Input save featureImage path:";
	cin >> featureImagePaht;
	cout << "Input save segImage path:";
	cin >> segFeatureImagePath;

	cv::imshow("src", src);
	//imwrite("C:\\Users\\shizhenwei\\Desktop\\Polydata0406.bmp", src);
	imwrite(featureImagePaht.c_str(), src);
	cv::waitKey();
	
	//cv::Mat src = cv::imread("C:\\Users\\shizhenwei\\Desktop\\Polydata04062.bmp");
	//cv::imshow("src", src);
	H = src.rows;
	W = src.cols;

	cv::Mat seg(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
	cout << "regionGrowing" << endl;
	regionGrowing(src, seg, voxel2D);
	//imwrite("C:\\Users\\shizhenwei\\Desktop\\seg04062.bmp", seg);
	imwrite(segFeatureImagePath.c_str(), seg);
	imshow("seg", seg);
	cv::waitKey();
}

void BuildFootprint::featureImage(list<Point> &points_, list<Points> &points_seg)
{
	gama_ = 1 - erfa_ - beta_;
	//parameter();

	Point pnt;
	//pnt.input1(points_);

	map<Pos2D, Points> voxel2D;
	map<Pos2D, double> F;

	extream_.getMaxMinValue(points_);

	Pos2D pos2D;
	for (Points::iterator it = points_.begin(); it != points_.end(); ++it)
	{
		pos2D.i = ROUNDEX((it->x - extream_.minx_) / GSD_);	//w
		pos2D.j = ROUNDEX((it->y - extream_.miny_) / GSD_);	//h
		voxel2D[pos2D].push_back(*it);
	}

	int maxNum = LONG_MIN, minNum = LONG_MAX;			//+-2147483648
	//cout << LONG_MIN << " " << LONG_MAX << endl;
	for (map<Pos2D, Points>::iterator it = voxel2D.begin(); it != voxel2D.end(); ++it)
	{
		if ((int)it->second.size() > maxNum)
		{
			maxNum = it->second.size();
		}
		if ((int)it->second.size() < minNum)
		{
			minNum = it->second.size();
		}
	}
	//cout << maxNum << " " << minNum << endl;

	int W, H;
	W = ROUNDEX((extream_.maxx_ - extream_.minx_) / GSD_);
	H = ROUNDEX((extream_.maxy_ - extream_.miny_) / GSD_);
	++W;
	++H;
	cout << H << " " << W << endl;

	MaxMinValueofCoor extreamVoxel;
	cv::Mat src(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
	for (map<Pos2D, Points>::iterator it = voxel2D.begin(); it != voxel2D.end(); ++it)
	{
		//BYTE temp = BYTE(ROUNDEX(255 / (tempMax - tempMin)*(it->second - tempMin)));
		BYTE temp1 = BYTE(ROUNDEX(255 / (maxNum - minNum)*((int)it->second.size() - minNum)));
		extreamVoxel.getMaxMinZ(it->second);
		BYTE temp2 = BYTE(ROUNDEX(255 / (extream_.maxz_ - extream_.minz_)*(extreamVoxel.maxz_ - extream_.minz_)));

		BYTE temp = erfa_*temp1 + beta_*temp2;
		//cout << (int)temp << endl;

		src.at<Vec3b>(it->first.j, it->first.i) = Vec3b(temp, temp, temp);
	}

	//string featureImagePaht, segFeatureImagePath;
	/*cout << "Input save featureImage path:";
	cin >> featureImagePaht;
	cout << "Input save segImage path:";
	cin >> segFeatureImagePath;*/

	//cv::imshow("src", src);
	//imwrite("C:\\Users\\shizhenwei\\Desktop\\Polydata0406.bmp", src);
	//imwrite(featureImagePaht.c_str(), src);
	//cv::waitKey();

	//cv::Mat src = cv::imread("C:\\Users\\shizhenwei\\Desktop\\Polydata04062.bmp");
	//cv::imshow("src", src);
	H = src.rows;
	W = src.cols;

	cv::Mat seg(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
	//cout << "regionGrowing" << endl;
	regionGrowing(src, seg, voxel2D, points_seg);
	//imwrite("C:\\Users\\shizhenwei\\Desktop\\seg04062.bmp", seg);
	//imwrite(segFeatureImagePath.c_str(), seg);
	//imshow("seg", seg);
	//cv::waitKey();
}



