#include "coordinate.h"
#include <sstream>
#include <time.h>
#include <iostream>      
#include <string>        
#include <fstream>       
#include <sstream>         

using namespace std;

void Coordinate::setFirstXYZ()
{
	inFile.open(inFilePath);
	/*while(!inFile.eof())
	{
		inFile>>firstX;
		inFile>>firstY;
		inFile>>firstZ;
		cout<<firstX<<" "<<firstY<<" "<<firstZ<<endl;
	}*/
	if (inFile)
	{
		inFile>>firstX;
		inFile>>firstY;
		inFile>>firstZ;

	}else
	{
		return ;
	}
	inFile.close();
	cout<<firstX<<" "<<firstY<<" "<<firstZ<<endl;

}

void Coordinate::translate(int w)
{
	setFirstXYZ();

	inFile.open(inFilePath);
	outFile.open(outFilePath);

	double tempX,tempY,tempZ;
	tempX=tempY=tempZ=0;
	while(!inFile.eof())
	{
		inFile>>tempX>>tempY>>tempZ;
		//cout<<"\nԭʼ��"<<setw(10)<<tempX<<" "<<setw(10)<<tempY<<" "<<setw(10)<<tempZ<<"\n";
		tempX-=firstX;
		tempY-=firstY;
		//tempZ-=firstZ;

		outFile << setw(w) << tempX << " " << setw(w) << tempY << " " << setw(w) << tempZ << "\n";
		//cout<<tempX<<" "<<tempY<<" "<<tempZ<<"\n";
		//cout<<firstX<<" "<<firstY<<" "<<firstZ<<endl;

		++num;
				
	}
	inFile.close();
	outFile.close();

	cout<<"������"<<num<<"\n";
}

//void Coordinate::translate()
//{
//	setFirstXYZ();
//
//	inFile.open(inFilePath);
//	outFile.open(outFilePath);
//
//	double temp;                     
//	string line;                  
//	stringstream stream;          
//	         
//	while(getline(inFile,line))    
//	{                             
//		stream<<line;
//		outFile<<line<<endl;
//		cout<<line<<endl;
//		          
//		while(stream>>temp)         
//		{                           
//			//image.push_back(temp); 
//			cout<<temp<<"d ";
//			
//		}
//		cout<<"hehe"<<endl;
//		stream.clear();             
//	}                             
//             
//
//	inFile.close();
//	outFile.close();
//
//	cout<<"������"<<num<<"\n";
//}

void Coordinate::setInOutFile()
{
	cout<<"�����ļ�:\n";
	cin>>inFilePath;
	cout<<"����ļ�:\n";
	cin>>outFilePath;
}

