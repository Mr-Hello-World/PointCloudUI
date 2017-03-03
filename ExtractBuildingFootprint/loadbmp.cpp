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
    //�����ƶ���ʽ��ָ����ͼ���ļ� 
    FILE *fp=fopen(path,"rb"); 
    if(fp==0) return 0;  
    fseek(fp, sizeof(BITMAPFILEHEADER),0); 
	
    BITMAPINFOHEADER head; 
    fread(&head, sizeof(BITMAPINFOHEADER), 1,fp);  

    width = head.biWidth; 
    height = head.biHeight; 
    biBitCount = head.biBitCount; 
    int lineByte=(width * biBitCount/8+3)/4*4; 

    if(biBitCount==8)   //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ� 
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
    //���λͼ����ָ��Ϊ0����û�����ݴ��룬�������� 
    if(!imge) 
        return 0; 
    

    int colorTablesize=0; 
    if(biBitCount==8) 
        colorTablesize=1024; 
    //���洢ͼ������ÿ���ֽ���Ϊ4�ı��� 
    
	int lineByte=(width * biBitCount/8+3)/4*4; 
    //�Զ�����д�ķ�ʽ���ļ� 
    FILE *fp=fopen(path,"wb"); 
    if(fp==0) return 0; 
    //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ 
    BITMAPFILEHEADER fileHead; 
    fileHead.bfType = 0x4D42;//bmp���� 
    
	//bfSize��ͼ���ļ�4����ɲ���֮�� 
    fileHead.bfSize= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) 
        + colorTablesize + lineByte*height; 
    fileHead.bfReserved1 = 0; 
    fileHead.bfReserved2 = 0; 
    //bfOffBits��ͼ���ļ�ǰ3����������ռ�֮�� 
    fileHead.bfOffBits=54+colorTablesize; 
    //д�ļ�ͷ���ļ� 
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp); 
    //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ 
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
    //дλͼ��Ϣͷ���ڴ� 
    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp); 
    //����Ҷ�ͼ������ɫ��д���ļ�  
    if(biBitCount==8) 
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp); 
    //дλͼ���ݽ��ļ� 
    fwrite(imge, height*lineByte, 1, fp); 
    //�ر��ļ� 
    fclose(fp); 
    return 1; 
          
}