#ifndef LOAD_BMP_H
#define LOAD_BMP_H
#include <windows.h>
#include <iostream>
typedef unsigned char img;
class bmp
{
public:
	bmp();
	bool readimage(const char *path);
	bool saveimage(const char *path, img *imge,int width, int height,  int biBitCount, RGBQUAD *pColorTable);
	img *imagedata;
	int width;
	int height;
	RGBQUAD* pColorTable;
	int biBitCount;
};

#endif;