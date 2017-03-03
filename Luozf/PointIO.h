/*
*���ƵĶ�ȡ
*���зɣ�2015.12
*/

#ifndef pointio_h
#define pointio_h

#include "../Luozf/Pointlzf.h"
#include <string>
#include <fstream>
#include <iostream>

namespace td
{
	class PointIO
	{
	public:
		PointIO();
		PointIO(std::string );
		~PointIO();
	private:
		// ��������
		PointCloud cloud;
	public:
		PointCloud getPointCloud();
		// �����ļ�
		void open(std::string path);
		void save(std::string path);
	};
}
#endif

