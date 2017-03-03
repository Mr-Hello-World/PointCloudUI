#include <algorithm>
#include "cass.h"
using namespace std;
Cass::Cass()
{

}

Cass::Cass( string _dxfFilePath )
{

}

void Cass::close()
{
	dw->sectionEnd();
	dxf->writeObjects(*dw);
	dxf->writeObjectsEnd(*dw);
	dw->dxfEOF();
	dw->close();
}
//black = 250,
//green = 3,
//red = 1,
//brown = 15,
//yellow = 2,
//cyan = 4,
//magenta = 6,
//gray = 8,
//blue = 5,
//l_blue = 163,
//l_green = 121,
//l_cyan = 131,
//l_red = 23,
//l_magenta = 221,
//l_gray = 252,
//white = 7,
//bylayer = 256,
//byblock = 0

void Cass::drawPoint(double x,double y,double z)
{
	/*cout<<"points\n";
	Point pnt;
	pnt.input1(points);

	for (list<Point>::iterator it=points.begin();it!=points.end();++it)
	{
	dxf->writePoint(*dw,DL_PointData(it->x,it->y,it->z),DL_Attributes("mainlayer", 256, -1, "BYLAYER"));
	}*/

	dxf->writePoint(*dw,DL_PointData(x,y,z),DL_Attributes("mainlayer", 7, -1, "BYLAYER"));
	
}

void Cass::drawElec(double x,double y,double z)
{
	//_dxffile.Point(x,y);
	//_dxffile.Circle(x+0,y+0,0.5);
	int col=2;
	dxf->writePoint(*dw,DL_PointData(x,y,z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));

	dxf->writeCircle(*dw,DL_CircleData(x,y,z,0.5),DL_Attributes("mainlayer",col, -1, "BYLAYER"));
}

void Cass::drawTree(double x,double y,double z)
{
	//_dxffile.Point(x,y);
	//_dxffile.Circle(x+0,y+0,0.8);
	int col = 3;
	dxf->writePoint(*dw,DL_PointData(x,y,z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));

	dxf->writeCircle(*dw,DL_CircleData(x,y,z,0.8),DL_Attributes("mainlayer", col, -1, "BYLAYER"));

}

void Cass::drawLight(double x,double y,double z)
{
	//_dxffile.Point(x,y);

	//_dxffile.Circle(x+0,y+0,0.5);
	//_dxffile.Circle(x-1.0,y+2.39999999999999,0.5);
	//_dxffile.Circle(x+1.0,y+2.39999999999999,0.5);

	//_dxffile.Line(x+0,y+0.5,x+0,y+3.5);
	//_dxffile.Line(x-1.0,y+2.9,x-1.0,y+3.5);
	//_dxffile.Line(x-1.0,y+3.5,x+1.0,y+3.5);
	//_dxffile.Line(x+1.0,y+3.5,x+1.0,y+2.9);
	int col=2;
	dxf->writePoint(*dw,DL_PointData(x,y,z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));

	//dw->sectionEntities();
	//dw->sectionBlockEntry();
	dxf->writeCircle(*dw,DL_CircleData(x-0.0,y-0.00000000000000,z,0.5),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	dxf->writeCircle(*dw,DL_CircleData(x-1.0,y+2.39999999999999,z,0.5),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	dxf->writeCircle(*dw,DL_CircleData(x+1.0,y+2.39999999999999,z,0.5),DL_Attributes("mainlayer", col, -1, "BYLAYER"));

	dxf->writeLine(*dw,DL_LineData(x+0.0,y+0.5,z,x+0.0,y+3.5,z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	dxf->writeLine(*dw,DL_LineData(x-1.0,y+2.9,z,x-1.0,y+3.5,z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	dxf->writeLine(*dw,DL_LineData(x-1.0,y+3.5,z,x+1.0,y+3.5,z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	dxf->writeLine(*dw,DL_LineData(x+1.0,y+3.5,z,x+1.0,y+2.9,z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	//dw->sectionBlockEntryEnd();
	//dw->sectionEnd();
	//dxf->write3dFace();
	
}

void Cass::cassPoint()
{
	cout<<"points\n";
	Point pnt;
	pnt.input1(points);

	for (list<Point>::iterator it=points.begin();it!=points.end();++it)
	{
		drawPoint(it->x,it->y,it->z);
	}
}

void Cass::cassElecs()
{
	cout<<"ElecPoints\n";
	Point pnt;
	pnt.input1(points);

	for (list<Point>::iterator it=points.begin();it!=points.end();++it)
	{
		drawElec(it->x,it->y,it->z);
	}
}

void Cass::cassTrees()
{
	cout<<"TreePoints\n";
	Point pnt;
	pnt.input1(points);

	for (list<Point>::iterator it=points.begin();it!=points.end();++it)
	{
		drawTree(it->x,it->y,it->z);
	}
}

void Cass::cassLights()
{
	cout<<"LightsPoints\n";
	Point pnt;
	pnt.input1(points);

	for (list<Point>::iterator it=points.begin();it!=points.end();++it)
	{
		drawLight(it->x,it->y,it->z);
	}
}

void Cass::draw()
{
	ifstream ifile;
	cout<<"输入分类后数据文件：\n";
	string ifilePath;
	cin>>ifilePath;
	ifile.open(ifilePath);
	if (!ifile)
	{
		cout<<"error!"<<endl;
		return;
	}
	string tempStr;
	double tempX,tempY,tempZ;
	Point point;
	vector<Point> house;
	vector<Point> shoulder;
	while(!ifile.eof())
	{
		ifile>>tempStr;
		if (tempStr=="tree")
		{
			ifile>>tempX>>tempY>>tempZ;
			drawTree(tempX,tempY,tempZ);
		}else if (tempStr=="elec")
		{
			ifile>>tempX>>tempY>>tempZ;
			drawElec(tempX,tempY,tempZ);
		}else if (tempStr=="light")
		{
			ifile>>tempX>>tempY>>tempZ;
			drawLight(tempX,tempY,tempZ);
		}else if (tempStr=="other")
		{
			ifile>>tempX>>tempY>>tempZ;
			drawPoint(tempX,tempY,tempZ);
		}else if (tempStr=="point")
		{
			ifile>>tempX>>tempY>>tempZ;
			drawPoint(tempX,tempY,tempZ);
		}else if (tempStr=="house")
		{
			house.clear();
			int num;
			ifile >> num;
			house.resize(num);
			Point tempPoint;
			for (int i=0;i<num;++i)
			{
				ifile>>house[i].x>>house[i].y>>house[i].z;
			}
			drawRoom(house);
		}else if (tempStr=="shoulder")
		{
			shoulder.clear();
			int num;
			ifile >> num;
			shoulder.resize(num);
			for (int i = 0; i < num; ++i)
			{
				ifile >> shoulder[i].x >> shoulder[i].y >> shoulder[i].z;
			}
			drawRoad(shoulder);
		}

	}
	
	close();
}

void Cass::drawRoom( vector<Point> &_points )
{
	//dxf->writePolyline(dw,DL_PolylineData(),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	int col=5;
	//dxf->writePolylineSZW(*dw,SZW_PolylineData(_points,0),DL_Attributes("mainlayer", col, -1, "BYLAYER"));


	for (int i=0;i<_points.size();++i)
	{
		dxf->writePoint(*dw,DL_PointData(_points[i].x,_points[i].y,_points[i].z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	}
	

	for (int i=0;i<_points.size();++i)
	{
		if (i==(_points.size()-1))
		{
			dxf->writeLine(*dw,DL_LineData(_points[i].x,_points[i].y,_points[i].z,_points[0].x,_points[0].y,_points[0].z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
		}else
			dxf->writeLine(*dw,DL_LineData(_points[i].x,_points[i].y,_points[i].z,_points[i+1].x,_points[i+1].y,_points[i+1].z),DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	}
	/*double mx,my,mz;
	mx=(_points[0].x+_points[2].x)/2.0;
	my=(_points[0].y+_points[2].y)/2.0;
	mz=(_points[0].z+_points[2].z)/2.0;
	dxf->writeMText(*dw,DL_MTextData(mx,my,mz,10,10,10,10,10,10,"砼","0",0),DL_Attributes("mainlayer", col, -1, "BYLAYER"));*/


}

void Cass::drawRoad(vector<Point> &_points)
{
	int col = 1;

	for (int i = 0; i<_points.size(); ++i)
	{
		dxf->writePoint(*dw, DL_PointData(_points[i].x, _points[i].y, _points[i].z), DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	}
	
	for (int i = 0; i<_points.size()-1; ++i)
	{
		dxf->writeLine(*dw, DL_LineData(_points[i].x, _points[i].y, _points[i].z, _points[i + 1].x, _points[i + 1].y, _points[i + 1].z), DL_Attributes("mainlayer", col, -1, "BYLAYER"));
	}
}

void Cass::initialDxf()
{
	dxf = new DL_Dxf();
	exportVersion = DL_Codes::AC1015;
	//cout<<"Input dxf file save path :\n";
	//cin>>dxfFilePath;
	dw = dxf->out(dxfFilePath.c_str(), exportVersion);

	if (dw == NULL) {
		printf("Cannot open file 'myfile.dxf' \
			   			   			   for writing.");
		// abort function e.g. with return
	}

	dw->lineWeight(5);

	dxf->writeHeader(*dw);
	// int variable:
	dw->dxfString(9, "$INSUNITS");
	dw->dxfInt(70, 4);
	// real (double, float) variable:
	dw->dxfString(9, "$DIMEXE");
	dw->dxfReal(40, 1.25);
	// string variable:
	dw->dxfString(9, "$TEXTSTYLE");
	dw->dxfString(7, "Standard");
	// vector variable:
	dw->dxfString(9, "$LIMMIN");
	dw->dxfReal(10, 0.0);
	dw->dxfReal(20, 0.0);
	dw->sectionEnd();
	dw->sectionTables();
	dxf->writeVPort(*dw);
	dw->tableLineTypes(25);

	dxf->writeLineType(*dw, DL_LineTypeData("BYBLOCK", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("BYLAYER", 0));

	dxf->writeLineType(*dw, DL_LineTypeData("CONTINUOUS", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO02W100", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO03W100", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO04W100", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO05W100", 0));

	dxf->writeLineType(*dw, DL_LineTypeData("BORDER", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("BORDER2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("BORDERX2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("CENTER", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("CENTER2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("CENTERX2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DASHDOTX2", 0));

	dxf->writeLineType(*dw, DL_LineTypeData("DASHED", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DASHED2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DASHEDX2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DIVIDEX2", 0));

	dxf->writeLineType(*dw, DL_LineTypeData("DOT", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DOT2", 0));
	dxf->writeLineType(*dw, DL_LineTypeData("DOTX2", 0));
	dw->tableEnd();
	int numberOfLayers = 3;
	dw->tableLayers(numberOfLayers);

	dxf->writeLayer(*dw,
		DL_LayerData("0", 0),
		DL_Attributes(
		std::string(""),      // leave empty
		DL_Codes::black,        // default color
		100,                  // default width
		"CONTINUOUS"));       // default line style

	dxf->writeLayer(*dw,
		DL_LayerData("mainlayer", 0),
		DL_Attributes(
		std::string(""),
		DL_Codes::red,
		100,
		"CONTINUOUS"));

	dxf->writeLayer(*dw,
		DL_LayerData("anotherlayer", 0),
		DL_Attributes(
		std::string(""),
		DL_Codes::black,
		100,
		"CONTINUOUS"));

	dw->tableEnd();
	dxf->writeStyle(*dw);
	dxf->writeView(*dw);
	dxf->writeUcs(*dw);

	dw->tableAppid(1);
	dw->tableAppidEntry(0x12);
	dw->dxfString(2, "ACAD");
	dw->dxfInt(70, 0);
	dw->tableEnd();
	dxf->writeDimStyle(*dw,
		1,
		1,
		1,
		1,
		1);
	dxf->writeBlockRecord(*dw);
	dxf->writeBlockRecord(*dw, "myblock1");
	dxf->writeBlockRecord(*dw, "myblock2");
	dw->tableEnd();
	dw->sectionEnd();
	dw->sectionBlocks();

	dxf->writeBlock(*dw,
		DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
	dxf->writeEndBlock(*dw, "*Model_Space");

	dxf->writeBlock(*dw,
		DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
	dxf->writeEndBlock(*dw, "*Paper_Space");

	dxf->writeBlock(*dw,
		DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
	dxf->writeEndBlock(*dw, "*Paper_Space0");

	dxf->writeBlock(*dw,
		DL_BlockData("myblock1", 0, 0.0, 0.0, 0.0));
	// ...
	// write block entities e.g. with dxf->writeLine(), ..
	// ...
	dxf->writeEndBlock(*dw, "myblock1");

	dxf->writeBlock(*dw,
		DL_BlockData("myblock2", 0, 0.0, 0.0, 0.0));
	// ...
	// write block entities e.g. with dxf->writeLine(), ..
	// ...
	dxf->writeEndBlock(*dw, "myblock2");

	dw->sectionEnd();
	dw->sectionEntities();
}

void Cass::txt2dxf()
{
	ifstream ifile;
	//cout << "输入分类后数据文件：\n";
	//string ifilePath;
	//cin >> ifilePath;
	ifile.open(txtFilePath);
	if (!ifile)
	{
		cout << "error!" << endl;
		return;
	}
	string tempStr;
	double tempX, tempY, tempZ;
	Point point;
	vector<Point> house;
	vector<Point> shoulder;
	vector<Point> trees;
	vector<Point> elecs;
	vector<Point> lights;
	vector<Point> points;

	while (!ifile.eof())
	{
		ifile >> tempStr;
		if (tempStr == "tree")
		{
			trees.clear();
			int num;
			ifile >> num;
			trees.resize(num);
			Point tempPoint;
			for (int i = 0; i < num; ++i)
			{
				ifile >> trees[i].x >> trees[i].y >> trees[i].z;
			}
			drawTrees(trees);
		}
		else if (tempStr == "elec")
		{
			elecs.clear();
			int num;
			ifile >> num;
			elecs.resize(num);
			Point tempPoint;
			for (int i = 0; i < num; ++i)
			{
				ifile >> elecs[i].x >> elecs[i].y >> elecs[i].z;
			}
			drawElecs(elecs);
		}
		else if (tempStr == "light")
		{
			lights.clear();
			int num;
			ifile >> num;
			lights.resize(num);
			Point tempPoint;
			for (int i = 0; i < num; ++i)
			{
				ifile >> lights[i].x >> lights[i].y >> lights[i].z;
			}
			drawLights(lights);
		}
		else if (tempStr == "other")
		{
			points.clear();
			int num;
			ifile >> num;
			points.resize(num);
			Point tempPoint;
			for (int i = 0; i < num; ++i)
			{
				ifile >> points[i].x >> points[i].y >> points[i].z;
			}
			drawPoints(points);
		}
		else if (tempStr == "point")
		{
			points.clear();
			int num;
			ifile >> num;
			points.resize(num);
			Point tempPoint;
			for (int i = 0; i < num; ++i)
			{
				ifile >> points[i].x >> points[i].y >> points[i].z;
			}
			drawPoints(points);
		}
		else if (tempStr == "house")
		{
			house.clear();
			int num;
			ifile >> num;
			house.resize(num);
			Point tempPoint;
			for (int i = 0; i < num; ++i)
			{
				ifile >> house[i].x >> house[i].y >> house[i].z;
			}
			drawRoom(house);
		}
		else if (tempStr == "shoulder")
		{
			shoulder.clear();
			int num;
			ifile >> num;
			shoulder.resize(num);
			for (int i = 0; i < num; ++i)
			{
				ifile >> shoulder[i].x >> shoulder[i].y >> shoulder[i].z;
			}
			drawRoad(shoulder);
		}

	}

	close();
}

void Cass::drawPoints(vector<Point> &_points)
{
	for (int i = 0; i < _points.size(); ++i)
	{
		drawPoint(_points[i].x, _points[i].y, _points[i].z);
	}
}

void Cass::drawElecs(vector<Point> &_points)
{
	for (int i = 0; i < _points.size(); ++i)
	{
		drawElec(_points[i].x, _points[i].y, _points[i].z);
	}
}

void Cass::drawTrees(vector<Point> &_points)
{
	for (int i = 0; i < _points.size(); ++i)
	{
		drawTree(_points[i].x, _points[i].y, _points[i].z);
	}
}

void Cass::drawLights(vector<Point> &_points)
{
	for (int i = 0; i < _points.size(); ++i)
	{
		drawLight(_points[i].x, _points[i].y, _points[i].z);
	}
}
