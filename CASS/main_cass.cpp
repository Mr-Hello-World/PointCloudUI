#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "cass.h"

using namespace std;

void usage();

void testWriting();


int main_cass() 
{
    //testWriting();

	Cass cass;
	cass.draw();

	/*int ch;
	bool la=true;
	cout<<"输入选择：\n";
	cout<<"1 文件中是4个点或6个点.\n2 文件中是4的倍数个点.\n3 文件中是4个点面.\n4 文件中是4的倍数个点面.\n5 画圆弧.\n0 退出!\n";
	cin>>ch;
	switch(ch)
	{
	case 1:
	cass.test4or6points();
	break;
	case 2:
	cass.test4npoints();
	break;
	case 3:
	cass.test4pointsPlane();
	break;
	case 4:
	cass.test4npointsPlane();
	break;
	case 5:
	cass.testArc();
	break;
	case 0:
	break;
	default:
	break;
	}*/


    return 0;
}

void testWriting() {
    DL_Dxf* dxf = new DL_Dxf();
    DL_Codes::version exportVersion = DL_Codes::AC1015;
    DL_WriterA* dw = dxf->out("myfile.dxf", exportVersion);
    if (dw==NULL) {
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
    dxf->writeLineType(*dw,
                      DL_LineTypeData("CONTINUOUS", 0));
    dxf->writeLineType(*dw,
                      DL_LineTypeData("ACAD_ISO02W100", 0));
    dxf->writeLineType(*dw,
                      DL_LineTypeData("ACAD_ISO03W100", 0));
    dxf->writeLineType(*dw,
                      DL_LineTypeData("ACAD_ISO04W100", 0));
    dxf->writeLineType(*dw,
                      DL_LineTypeData("ACAD_ISO05W100", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("BORDER", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("BORDER2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("BORDERX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("CENTER", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("CENTER2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("CENTERX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT2", 0));
    dxf->writeLineType(*dw,
                      DL_LineTypeData("DASHDOTX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHED", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHED2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHEDX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE2", 0));
    dxf->writeLineType(*dw,
                      DL_LineTypeData("DIVIDEX2", 0));
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
	
	
    // write all your entities..
    /*dxf->writePoint(
        *dw,
        DL_PointData(10.0,
                     45.0,
                     0.0),
        DL_Attributes("mainlayer", 256, -1, "BYLAYER"));*/

	/*dxf->writePoint(*dw,DL_PointData(88.1756,-199.363,0),DL_Attributes("mainlayer", 256, -1, "BYLAYER"));*/

	//dw->lineWeight(-3);
 //   dxf->writeLine(
 //       *dw,
 //       DL_LineData(25.0,   // start point
 //                   30.0,
 //                   0.0,
 //                   100.0,   // end point
 //                   120.0,
 //                   0.0),
 //       DL_Attributes("mainlayer", 256, -1, "BYLAYER"));


	////begin
	ifstream ifile;
	cout<<"输入文件:\n";
	string ifilePath;
	cin>>ifilePath;
	ifile.open(ifilePath);
	if (!ifile)
	{
	cout<<"error！"<<endl;
	return;
	}
	string ID;
	double weightX,weightY,tempZ;
	while(!ifile.eof())
	{
		/*ifile>>ID>>weightX>>weightY;
		if (ID=="tree")
		{
		independentTree(dxffile,weightX,weightY);
		}else if (ID=="light")
		{
		streetLamp(dxffile,weightX,weightY);
		}else
		{
		electiralPole(dxffile,weightX,weightY);
		}*/

		ifile>>weightX>>weightY>>tempZ;
		//independentTree(dxffile,weightX,weightY);

		dxf->writePoint(*dw,DL_PointData(weightX,weightY,0),DL_Attributes("mainlayer", 256, -1, "BYLAYER"));
	}



	////end








	
    dw->sectionEnd();
    dxf->writeObjects(*dw);
    dxf->writeObjectsEnd(*dw);
    dw->dxfEOF();
    dw->close();
    delete dw;
    delete dxf;
}

