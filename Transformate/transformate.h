#pragma once
#include <string>
class Transformate
{
public:
	std::string fileName1, fileName2;

	void txt2las(std::string &_fileNameTxt, std::string &_fileNameLas);
	void txt2laz(std::string &_fileNameTxt, std::string &_fileNameLaz);
	void txt2pcd(std::string &_fileNameTxt, std::string &_fileNamePcd);
	void txt2txt(std::string &_fileNameTxt1, std::string &_fileNameTxt2);

	void las2txt(std::string &_fileNameLas, std::string &_fileNameTxt);
	void las2laz(std::string &_fileNameLas, std::string &_fileNameLaz);
	void las2pcd(std::string &_fileNameLas, std::string &_fileNamePcd);
	void las2las(std::string &_fileNameLas1, std::string &_fileNameLas2);

	void laz2txt(std::string &_fileNameLaz, std::string &_fileNameTxt);
	void laz2laz(std::string &_fileNameLaz1, std::string &_fileNameLaz2);
	void laz2pcd(std::string &_fileNameLaz, std::string &_fileNamePcd);
	void laz2las(std::string &_fileNameLaz, std::string &_fileNameLas);

	void pcd2txt(std::string &_fileNamePcd, std::string &_fileNameTxt);
	void pcd2laz(std::string &_fileNamePcd, std::string &_fileNameLaz);
	void pcd2pcd(std::string &_fileNamePcd1, std::string &_fileNamePcd2);
	void pcd2las(std::string &_fileNamePcd, std::string &_fileNameLas);
};