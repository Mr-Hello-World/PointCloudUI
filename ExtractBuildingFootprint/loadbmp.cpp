#include "loadbmp.h"

bmp::bmp()
{
imagedata=NULL;
width=0;
height=0;
pColorTable=NULL;
biBitCount=0;
}

bool bmp::readimage(const char* path)
{
    //二进制读方式打开指定的图像文件 
    FILE *fp=fopen(path,"rb"); 
    if(fp==0) return 0;  
    fseek(fp, sizeof(BITMAPFILEHEADER),0); 
	
    BITMAPINFOHEADER head; 
    fread(&head, sizeof(BITMAPINFOHEADER), 1,fp);  

    width = head.biWidth; 
    height = head.biHeight; 
    biBitCount = head.biBitCount; 
    int lineByte=(width * biBitCount/8+3)/4*4; 

    if(biBitCount==8)   //申请颜色表所需要的空间，读颜色表进内存 
    { 
        pColorTable=new RGBQUAD[256]; 
        fread(pColorTable,sizeof(RGBQUAD),256,fp); 
    } 

    imagedata=new img[lineByte * height]; 
    fread(imagedata,1,lineByte * height,fp); 

    fclose(fp); 
    return 1; 
}

bool bmp::saveimage(const char *path, img *imge,  
             int width, int height,  
             int biBitCount, RGBQUAD *pColorTable) 
{ 
    //如果位图数据指针为0，则没有数据传入，函数返回 
    if(!imge) 
        return 0; 
    

    int colorTablesize=0; 
    if(biBitCount==8) 
        colorTablesize=1024; 
    //待存储图像数据每行字节数为4的倍数 
    
	int lineByte=(width * biBitCount/8+3)/4*4; 
    //以二进制写的方式打开文件 
    FILE *fp=fopen(path,"wb"); 
    if(fp==0) return 0; 
    //申请位图文件头结构变量，填写文件头信息 
    BITMAPFILEHEADER fileHead; 
    fileHead.bfType = 0x4D42;//bmp类型 
    
	//bfSize是图像文件4个组成部分之和 
    fileHead.bfSize= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) 
        + colorTablesize + lineByte*height; 
    fileHead.bfReserved1 = 0; 
    fileHead.bfReserved2 = 0; 
    //bfOffBits是图像文件前3个部分所需空间之和 
    fileHead.bfOffBits=54+colorTablesize; 
    //写文件头进文件 
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp); 
    //申请位图信息头结构变量，填写信息头信息 
    BITMAPINFOHEADER head;  
    head.biBitCount=biBitCount; 
    head.biClrImportant=0; 
    head.biClrUsed=0; 
    head.biCompression=0; 
    head.biHeight=height; 
    head.biPlanes=1; 
    head.biSize=40; 
    head.biSizeImage=lineByte*height; 
    head.biWidth=width; 
    head.biXPelsPerMeter=0; 
    head.biYPelsPerMeter=0; 
    //写位图信息头进内存 
    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp); 
    //如果灰度图像，有颜色表，写入文件  
    if(biBitCount==8) 
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp); 
    //写位图数据进文件 
    fwrite(imge, height*lineByte, 1, fp); 
    //关闭文件 
    fclose(fp); 
    return 1; 
          
}