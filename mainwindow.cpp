#include <vtkVersion.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkPropAssembly.h>
#include <vtkSmartPointer.h>

#include <QMessageBox>
#include <QFileDialog>
#include <QTextCodec>
#include <QToolBar>
//#include <QTreeWidgetItem>
//#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QStringListIterator>
#include <QStringListModel>
#include <QStandardItem>
#include <QString>
#include <QTreeWidget>
#include <QStringList>
#include <QDateTime>
#include <QProgressDialog>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
#include <QColorDialog>
#include <QColor>
#include <QLinearGradient>
#include <QBrush>
#include <QPainter>
#include <QPalette>
#include <QVariant>
#include <QButtonGroup>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <string>
#include "mainwindow.h"
#include "../PointClass/point.h"
#include "../RansacClass/ransacplane.h"
#include "../SurfaceGrowing/surfacegrowing.h"
#include "../PCL/Filtering/pclfilter.h"
#include "../PCL/Clusters/clusters.h"
#include "../CASS/cass.h"
#include "../libLAS180/libLAS180.h"
#include "lasreader.hpp"
#include "laswriter.hpp"
//#include "extractbuildingfootpoints.h"
#include "../CoordinatePingYi/coordinate.h"

#include <pcl/PCLPointCloud2.h>
//#include <pcl/visualization/impl/image_viewer.hpp>
//#include <pcl/visualization/image_viewer.h>

#include "ui_ransacdialog.h"
#include "ui_pointsizedialog.h"
#include "ui_saveasciidialog.h"
#include "ui_surfacegrowingdialog.h"
#include "ui_contourdialog.h"
#include "ui_pcadialog.h"
#include "ui_simpledialog.h"
#include "ui_passthroughfilterdialog.h"
#include "ui_radiusfilterdialog.h"
#include "ui_statisticalfilterdialog.h"
#include "ui_leafsizedialog.h"
#include "ui_euclideanclusterdialog.h"
#include "ui_formatetransform.h"
#include "ui_regiongrowdialog.h"
#include "ui_radiussearchdialog.h"
#include "ui_polesextract.h"
#include "ui_polesstatisticclassifydialog.h"
#include "ui_extractshoulder.h"
#include "ui_choiceout.h"
#include "ui_translatexyzdialog.h"

#include <opencv2\opencv.hpp>

#define ROLE_MARK Qt::UserRole + 1
#define ROLE_MARK_FOLDER Qt::UserRole + 2
#define ROLE_MARK_ITEM Qt::UserRole + 3

#define MARK_PROJECT 1
#define MARK_FOLDER 2
#define MARK_ITEM 3

#define MARK_FOLDER_UNIQC 1 
#define MARK_FOLDER_MULTC 2 

#define MARK_ITEM_UNIQC 1
#define MARK_ITEM_MULTC 2

#define FORMATE_ASCII 0
#define FORMATE_PCD 1
#define FORMATE_LAS 2
#define FORMATE_LAZ 3
#define FORMATE_DXF 4

#define INITIAL_SHOULDER_POINTS 0
#define INITIAL_POINTS 1

#define SHOULDER_ 0
#define TREE_ 1
#define LIGHT_ 2
#define ELECT_ 3
#define OTHER_ 4
#define HOUSE_ 5

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	appLockb = true;
	initialVtkWidget();
	initialMainwindowWidget();
	initialConcoleTreeWidget();
	creatToolBar();
	slotSingal();
	
	//addFolder();
	ui.openAction->setIcon(QIcon(":/images/open.png"));
	ui.saveAction->setIcon(QIcon(":/images/save.png"));
	this->setWindowIcon(QIcon(":/images/shishi.png"));

	initiaDBTree();
	appLock();
	
}

MainWindow::~MainWindow()
{
	delete viewToolBar;
}

//************************************
// Method:    initialVtkWidget
// FullName:  MainWindow::initialVtkWidget
// Access:    private 
// Returns:   void
// Qualifier: 初始化vkt窗口,针对ui为操作对象
//************************************
void MainWindow::initialVtkWidget()
{
	ui.qvtkWidget->SetRenderWindow(cloudManage.viewer->getRenderWindow ());
	cloudManage.viewer->setupInteractor (ui.qvtkWidget->GetInteractor (), ui.qvtkWidget->GetRenderWindow ());
	
	//pcl::io::loadPCDFile("example.pcd",*cloudrgb);
	//viewer->addPointCloud (cloudrgb, "cloudrgb");
	pcl::io::loadPCDFile("example.pcd",*cloudManage.cloud);
	cloudManage.viewer->addPointCloud (cloudManage.cloud, "cloud");
	
	setBottomView();
	cloudManage.viewer->resetCamera ();
	addOrientationMarKerWidgetAxes();
	
	QColor color(170,170,255);
	cloudManage.viewer->setBackgroundColor(color.redF(),color.greenF(),color.blueF());
	cloudManage.viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud");
	//ui.qvtkWidget->setBackgroundRole(QPalette::ColorRole);
	ui.qvtkWidget->update ();	
}

void MainWindow::initialViewer()
{	
	cloudManage.viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
	ui.qvtkWidget->SetRenderWindow(cloudManage.viewer->getRenderWindow ());
	cloudManage.viewer->setupInteractor (ui.qvtkWidget->GetInteractor (), ui.qvtkWidget->GetRenderWindow ());	
}

void MainWindow::initialMainwindowWidget()
{
	QTextCodec* codec =QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForLocale(codec);
	//QTextCodec::setCodecForCStrings(codec);
	//QTextCodec::setCodecForTr(codec);

	//model=new QStandardItemModel(ui.DBTreeView);
	//ui.DBTreeView->setHeaderHidden(true);
	//ui.propertiesTreeView->setHeaderHidden(true);
	ui.saveAction->setEnabled(false);
	setWindowState(Qt::WindowMaximized);
	
	//cloudTreeView=new CloudProjectTreeview(*ui.DBTreeView);

	//addAction2Group();
	enableAction(false);
}

//************************************
// Method:    creatToolBar
// FullName:  MainWindow::creatToolBar
// Access:    private 
// Returns:   void
// Qualifier: 创建ui对象的工具栏
//************************************
void MainWindow::creatToolBar()
{
	ui.fileToolBar->addAction(ui.openAction);
	ui.fileToolBar->addAction(ui.saveAction);
	//ui.fileToolBar->addSeparator();

	viewToolBar=new QToolBar/*(this)*/;

	viewToolBar=addToolBar(tr("Views"));
	viewToolBar->addAction(ui.actionTopView);
	viewToolBar->addAction(ui.actionBottomView);
	viewToolBar->addAction(ui.actionFrontView);
	viewToolBar->addAction(ui.actionBackView);
	viewToolBar->addAction(ui.actionLeftSideView);
	viewToolBar->addAction(ui.actionRightSideView);
	//viewToolBar->addSeparator();
	
}

//************************************
// Method:    slotSingal
// FullName:  MainWindow::slotSingal
// Access:    private 
// Returns:   void
// Qualifier: 将动作和槽相连接
//************************************
void MainWindow::slotSingal()
{
	connect(ui.openAction,SIGNAL(triggered()),this,SLOT(open()));
	connect(ui.aboutAction, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui.saveAction,SIGNAL(triggered()),this,SLOT(save()));
	
	connect(ui.actionRANSAC,SIGNAL(triggered()),this,SLOT(ransac()));
	connect(ui.actionSurfaceGrow,SIGNAL(triggered()),this,SLOT(surfaceGrow()));

	connect(ui.actionPointSize,SIGNAL(triggered()),this,SLOT(setPointSize()));
	connect(ui.actionBackgroundColor,SIGNAL(triggered()),this,SLOT(setBackgroundColor()));
	
	connect(ui.actionDirectionX,SIGNAL(triggered()),this,SLOT(setPointColorGradientDirectionX()));
	connect(ui.actionDirectionY,SIGNAL(triggered()),this,SLOT(setPointColorGradientDirectionY()));
	connect(ui.actionDirectionZ,SIGNAL(triggered()),this,SLOT(setPointColorGradientDirectionZ()));
	connect(ui.actionUnique_Color,SIGNAL(triggered()),this,SLOT(setPointUniqueColor()));
	connect(ui.actionClearAllData, SIGNAL(triggered()), this, SLOT(onClearAllData()));

	connect(ui.actionFullScreen,SIGNAL(triggered()),this,SLOT(setFullScreen()));
	connect(ui.actionTopView,SIGNAL(triggered()),this,SLOT(setTopView()));
	connect(ui.actionBottomView,SIGNAL(triggered()),this,SLOT(setBottomView()));
	connect(ui.actionFrontView,SIGNAL(triggered()),this,SLOT(setFrontView()));
	connect(ui.actionBackView,SIGNAL(triggered()),this,SLOT(setBackView()));
	connect(ui.actionRightSideView,SIGNAL(triggered()),this,SLOT(setRightView()));
	connect(ui.actionLeftSideView,SIGNAL(triggered()),this,SLOT(setLeftView()));

	connect(ui.DBTreeAction,SIGNAL(triggered()),this,SLOT(setShowOrHideDBWidget()));
	connect(ui.consoleAction,SIGNAL(triggered()),this,SLOT(setShowOrHideConsoleWidget()));
	connect(ui.propertiesAction,SIGNAL(triggered()),this,SLOT(setShowOrHidePropertyWidget()));
	connect(ui.DBTreeView,SIGNAL(customContextMenuRequested ( const QPoint)),this,SLOT(on_treeView_customContextMenuRequested( const QPoint)));
	
	connect(ui.actionContour,SIGNAL(triggered()),this,SLOT(contourPoints()));
	connect(ui.actionPCA,SIGNAL(triggered()),this,SLOT(PCAPoints()));
	connect(ui.actionFeaturePoints,SIGNAL(triggered()),this,SLOT(featurePoints()));
	connect(ui.actionSimple,SIGNAL(triggered()),this,SLOT(simplePoints()));

	connect(ui.actionPassThrough,SIGNAL(triggered()),this,SLOT(passThroughFilter()));
	connect(ui.actionStatisticalOutlierRemoval,SIGNAL(triggered()),this,SLOT(statisticalOutLierFilter()));
	connect(ui.actionRadiusOutlier,SIGNAL(triggered()),this,SLOT(radiusOutlierFilter()));
	connect(ui.actionDownSamplingVoxelGrid,SIGNAL(triggered()),this,SLOT(downSimplingFilter()));

	connect(ui.actionEuclideanCluster, SIGNAL(triggered()), this, SLOT(euclideanClusterExtract()));

	connect(&ransacThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionRansacEnable(bool)));
	connect(&surfaceGrowThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionSurfaceGrowEnable(bool)));
	connect(&contourThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionContourEnable(bool)));
	connect(&PCAThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionPCAEnable(bool)));
	connect(&featureThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionFeatureEnable(bool)));
	connect(&simplePointThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionSimaplePointEnable(bool)));

	connect(&passThroughThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionPassThroughEnable(bool)));
	connect(&statisticalThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionStatisticalOutlierEnable(bool)));
	connect(&radiusThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionRadiusOutlierEnable(bool)));
	connect(&downSamplingThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionDownSimplingEnable(bool)));

	connect(&euclideanClusterThread, SIGNAL(setActionEnable(bool)), this, SLOT(setActionEuclideanCluster(bool)));

	connect(ui.actionTestTreeViewh,SIGNAL(triggered()),this,SLOT(addUniColorItem()));
	connect(ui.actionTestTreeViewcpp,SIGNAL(triggered()),this,SLOT(addMulColorItem()));
	
	//connect(ui.actionTestThread,SIGNAL(triggered()),this,SLOT(testThreadslot()));
	//connect(&testThread,SIGNAL(setActionEnable(bool)),this,SLOT(setActionTestThread(bool)));

	connect(ui.actionTranslate, SIGNAL(triggered()), this, SLOT(transformate()));

	connect(ui.actionCloudResolution,SIGNAL(triggered()), this, SLOT(computeResolution()));
	connect(&resolutionThread, SIGNAL(setActionEnable(bool)), this, SLOT(setActionResolution(bool)));

	connect(ui.actionEstimatingNormals, SIGNAL(triggered()), this, SLOT(onEstimatingNormals()));
	connect(&estimateNormalsThread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionEstimateNormals(bool)));

	connect(ui.actionRegionGrowingRansac, SIGNAL(triggered()), this, SLOT(onRegiongrowRansac()));
	connect(ui.actionBaySAC, SIGNAL(triggered()), this, SLOT(onRegiongrowBaysac()));
	connect(ui.actionBAYLMEDS, SIGNAL(triggered()), this, SLOT(onRegiongrowBayLmeds()));

	connect(&regionGrowRansacThread, SIGNAL(setActionEnable(bool)), this, SLOT(setActionRegRansac(bool)));
	connect(&regionGrowBaysacThread, SIGNAL(setActionEnable(bool)), this, SLOT(setActionRegBaysac(bool)));
	connect(&regionGrowBayLmedsThread, SIGNAL(setActionEnable(bool)), this, SLOT(setActionRegBayLmeds(bool)));
	
	connect(ui.actioPolesExtact, SIGNAL(triggered()), this, SLOT(onPolesExtract()));
	connect(ui.actionStatisticPolesNum, SIGNAL(triggered()), this, SLOT(onStatisticPolesNum()));
	connect(ui.actionComputeCenterofPoles, SIGNAL(triggered()), this, SLOT(onComputeCenterofPoles()));
	
	connect(&polesExtractThread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionPolesExtract(bool)));
	connect(&statisticPolesNumThread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionStatisticPolesNum(bool)));
	connect(&computeCenterofPolesThread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionComputeCenterofPoles(bool)));
	connect(ui.actionOutPolesPoints, SIGNAL(triggered()), this, SLOT(onOutPolesPoints()));

	connect(ui.actionGroundFilter, SIGNAL(triggered()), this, SLOT(onGroundFilter()));
	connect(ui.actionExtractCurb, SIGNAL(triggered()), this, SLOT(onExtractCurbPoints()));
	connect(ui.actionAfterProgress1, SIGNAL(triggered()), this, SLOT(onAfterProgress1()));
	connect(ui.actionAfterProgress2, SIGNAL(triggered()), this, SLOT(onAfterProgress2()));
	connect(ui.actionAfterProgress3, SIGNAL(triggered()), this, SLOT(onAfterProgress3()));
	connect(ui.actionChouXi, SIGNAL(triggered()), this, SLOT(onChouXiRoadPoints()));
	connect(ui.actionSort, SIGNAL(triggered()), this, SLOT(onSortRoadPoints()));
	connect(ui.actionOutRoadPoints, SIGNAL(triggered()), this, SLOT(onOutRoadPoints()));

	connect(&groundFilterThread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionGroundFilter(bool)));
	connect(&extractCurbThread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionExtractCurbPoints(bool)));
	connect(&curbAfterProgress1Thread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionAfterProgress1(bool)));
	connect(&curbAfterProgress2Thread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionAfterProgress2(bool)));

	connect(ui.actionBuildExtract, SIGNAL(triggered()), this, SLOT(onExtractBuild()));
	connect(ui.actionOutAnglePoints, SIGNAL(triggered()), this, SLOT(onOutAnglePoints()));
	connect(&extractBuildThread, SIGNAL(setActionEnable(bool)), this, SLOT(onSetActionExtractBuild(bool)));	
	
	connect(ui.actionPintYiXYZ, SIGNAL(triggered()), this, SLOT(onTransXYZ()));
}

//************************************
// Method:    saveAs
// FullName:  MainWindow::saveAs
// Access:    private 
// Returns:   void
// Qualifier: 槽
//************************************
bool MainWindow::save()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save PointClouds"), ".",
		tr("LAZ cloud(*.laz)\n"
		"LAS cloud(*.las)\n"		
		"Ascii cloud (*.txt)\n"
		"PointCloudLibary cloud(*.pcd)\n"
		"Save cloud(*.*)"));

	if (QFile::exists(fileName)) {
		int r = QMessageBox::warning(this, tr("PointCloudUI"),
			tr("File %1 already exists.\n"
			"Do you want to overwrite it?")
			.arg(QDir::toNativeSeparators(fileName)),
			QMessageBox::Yes | QMessageBox::No);
		if (r == QMessageBox::No)
			return true;
	}
	if (!fileName.isEmpty())
		saveFile(fileName);

	addMessage(" ","Save",fileName);
	return true;
}

//************************************
// Method:    ransacPlane
// FullName:  MainWindow::ransacPlane
// Access:    private 
// Returns:   void
// Qualifier: 定义模态对话框
//************************************
void MainWindow::ransac()
{	
	if (cloudManage.activateXYZNum>=0)
	{
		/*QDialog *dialog=new QDialog(this);
		Ui::RansacDialog ransac;
		ransac.setupUi(dialog);
		dialog->show();*/
		QDialog dialog(this);
		Ui::RansacDialog ransac;
		ransac.setupUi(&dialog);

		if (dialog.exec())
		{
			QString tempStr;
			addMessage("","RANSACSegment","Is Running... ...");
			ransacPlane(ransac.intSpinBox->value(),ransac.doubleSpinBox->value());
		}
	}
	ui.actionRANSAC->setEnabled(false);
	cloudManage.activateXYZNum=-1;
}
void MainWindow::ransacPlane( int num, double dist )
{	
	cloudManage.awaitingProcessCloudVXYZ.clear();
	cloudManage.cloudL2cloudV(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.awaitingProcessCloudVXYZ);

	ransacThread.process.setRansac.points=&cloudManage.awaitingProcessCloudVXYZ;
	ransacThread.process.setRansac.segments=&cloudManage.cloudLRGBData;
	cloudManage.cloudLRGBData.clear();

	ransacThread.process.choice_=RANSAC_SEGMENT_PLANE;
	ransacThread.process.setRansac.dist_=dist;
	ransacThread.process.setRansac.num_=num;

	if (ransacThread.isRunning())
	{

	}else
	{
		ransacThread.start();
		ui.actionRANSAC->setEnabled(false);
		addMessage("","RansacSegment","Is Running... ...");
	}

}

void MainWindow::surfaceGrow()
{
	if (cloudManage.activateXYZNum>=0)
	{
		surfaceGrowThread.process.setSurfaceGrow.points=cloudManage.awaitingProcessCloudLXYZ;
		surfaceGrowThread.process.setSurfaceGrow.segments=&cloudManage.cloudLRGBData;
		cloudManage.cloudLRGBData.clear();
		surfaceGrowThread.process.choice_=SURFAC_SEGMENT_PLANE;
		QDialog dialog(this);
		Ui::SurfaceGrowingDialog surfaceGrowDialog;
		surfaceGrowDialog.setupUi(&dialog);
		//
		if (dialog.exec())
		{
			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.rths_=surfaceGrowDialog.seedRadiusDoubleSpinBox->value();
			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.dths_=surfaceGrowDialog.seedPlaneDistDoubleSpinBox->value();
			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.n_=surfaceGrowDialog.leastPointNumPinBox->value();

			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.rthg_=surfaceGrowDialog.growRadiusDoubleSpinBox->value();
			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.dthg_=surfaceGrowDialog.growPlaneDistDoubleSpinBox->value();

			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.a_=surfaceGrowDialog.aDoubleSpinBox->value();
			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.d_=surfaceGrowDialog.dDoubleSpinBox->value();
			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.rm_=surfaceGrowDialog.rmSpinBox->value();
			surfaceGrowThread.process.setSurfaceGrow.surfaceGrow.vm_=surfaceGrowDialog.vmSpinBox->value();

			if (surfaceGrowThread.isRunning())
			{

			}else
			{
				surfaceGrowThread.start();
				ui.actionSurfaceGrow->setEnabled(false);
				addMessage("","SurfaceGrowSegment","Is Running... ...");
			}
		}
	}
	ui.actionSurfaceGrow->setEnabled(false);
	cloudManage.activateXYZNum=-1;
}

void MainWindow::contourPoints()
{
	if (cloudManage.activateXYZNum>=0)
	{
		contourThread.process.setContour.points=cloudManage.awaitingProcessCloudLXYZ;
		contourThread.process.setContour.contourPoints=&cloudManage.processCloudLXYZ;
		cloudManage.processCloudLXYZ.clear();
		contourThread.process.choice_=CONTOUR_POINTS;
		QDialog dialog(this);
		Ui::ContourDialog contourDialog;
		contourDialog.setupUi(&dialog);
		if (dialog.exec())
		{
			contourThread.process.setContour.contour.k_=contourDialog.spinBox->value();

			if (contourThread.isRunning())
			{

			}else
			{
				contourThread.start();
				ui.actionContour->setEnabled(false);
				addMessage("","ComputeContourPoints","Is Running... ...");
			}
		}
	}
	ui.actionContour->setEnabled(false);
	cloudManage.activateXYZNum=-1;
}

void MainWindow::PCAPoints()
{
	if (cloudManage.activateXYZNum>=0)
	{
		PCAThread.process.setPCA.points=cloudManage.awaitingProcessCloudLXYZ;
		PCAThread.process.setPCA.PCAPoints=&cloudManage.processCloudLXYZ;
		cloudManage.processCloudLXYZ.clear();
		PCAThread.process.choice_=PCA_POINTS;
		//addMessage("","ComputePCAPoints",QString::number(contourThread.process.setPCA.points->size()));
		QDialog dialog(this);
		Ui::PCADialog pcaDialog;
		pcaDialog.setupUi(&dialog);
		if (dialog.exec())
		{
			PCAThread.process.setPCA.PCA.k_=pcaDialog.spinBox->value();
			PCAThread.process.setPCA.PCA.planarity_=pcaDialog.doubleSpinBox->value();

			if (PCAThread.isRunning())
			{

			}else
			{
				PCAThread.start();
				ui.actionPCA->setEnabled(false);
				addMessage("","ComputePCAPoints","Is Running... ...");
			}
		}
	}
	ui.actionPCA->setEnabled(false);
	cloudManage.activateXYZNum=-1;
	
}
void MainWindow::featurePoints()
{
	if (cloudManage.activateXYZNum>=0)
	{
		featureThread.process.setFeature.points=cloudManage.awaitingProcessCloudLXYZ;
		featureThread.process.setFeature.featurePoints=&cloudManage.processCloudLXYZ;
		cloudManage.processCloudLXYZ.clear();
		featureThread.process.choice_=FEATURE_POINTS;

		QDialog dialog(this);
		Ui::PCADialog featureDialog;
		featureDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("Feature"));
		if (dialog.exec())
		{
			featureThread.process.setFeature.feature.k_=featureDialog.spinBox->value();
			featureThread.process.setFeature.feature.planarity_=featureDialog.doubleSpinBox->value();

			if (featureThread.isRunning())
			{

			}else
			{
				featureThread.start();
				ui.actionFeaturePoints->setEnabled(false);
				addMessage("","ComputeFeaturePoints","Is Running... ...");
			}
		}
	}
	ui.actionFeaturePoints->setEnabled(false);
	cloudManage.activateXYZNum=-1;
}

void MainWindow::simplePoints()
{
	if (cloudManage.activateXYZNum>=0)
	{
		simplePointThread.process.setSimple.points=cloudManage.awaitingProcessCloudLXYZ;
		simplePointThread.process.setSimple.simplePoints=&cloudManage.processCloudLXYZ;
		cloudManage.processCloudLXYZ.clear();
		simplePointThread.process.choice_=SIMPLE_POINTS;

		QDialog dialog(this);
		Ui::SimpleDialog simpleDialog;
		simpleDialog.setupUi(&dialog);
		if (dialog.exec())
		{
			simplePointThread.process.setSimple.simple.k_=simpleDialog.spinBox->value();
			simplePointThread.process.setSimple.simple.planarity_=simpleDialog.planarityDoubleSpinBox->value();
			simplePointThread.process.setSimple.simple.voxelSides_=simpleDialog.voxelSideDoubleSpinBox->value();

			if (simplePointThread.isRunning())
			{

			}else
			{
				simplePointThread.start();
				ui.actionFeaturePoints->setEnabled(false);
				addMessage("","ComputeSimplePoints","Is Running... ...");
			}
		}
	}
	ui.actionSimple->setEnabled(false);
	cloudManage.activateXYZNum=-1;
}

void MainWindow::passThroughFilter()
{
	QDialog dialog(this);
	Ui::PassThroughFilterDialog passDialog;
	passDialog.setupUi(&dialog);
	if (dialog.exec())
	{
		cloudManage.cloud->points.clear();
		cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);
		passThroughThread.process.setFilter.cloud=&cloudManage.cloud;
		passThroughThread.process.setFilter.cloud_filtered=&cloudManage.cloud_filtered;
		cloudManage.cloud_filtered->points.clear();
		passThroughThread.process.choice_=PASSTHROUGH_FILTER;
		passThroughThread.process.setFilter.pclFilter.passThroughUpLimit_=passDialog.upLimitDoubleSpinBox->value();
		passThroughThread.process.setFilter.pclFilter.passThroughDownLimit_=passDialog.downLimitDoubleSpinBox->value();
		passThroughThread.process.setFilter.pclFilter.passThroughFileName_=passDialog.comboBox->currentText().toStdString()/*"z"*/;
				
		if (passThroughThread.isRunning())
		{
		}else
		{
			passThroughThread.start();
			ui.actionPassThrough->setEnabled(false);
			addMessage("","PassThroughFilter","Is Running... ..."+QString::number(passDialog.upLimitDoubleSpinBox->value()));
		}
	}
}

void MainWindow::statisticalOutLierFilter()
{
	QDialog dialog(this);
	Ui::StatisticalDialog statisticDialog;
	statisticDialog.setupUi(&dialog);
	if (dialog.exec())
	{
		cloudManage.cloud->points.clear();
		cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);
		statisticalThread.process.setFilter.cloud=&cloudManage.cloud;
		statisticalThread.process.setFilter.cloud_filtered=&cloudManage.cloud_filtered;
		cloudManage.cloud_filtered->points.clear();
		statisticalThread.process.choice_=STATISTIC_FILTER;
		statisticalThread.process.setFilter.pclFilter.statisticOutliersMeanK_=statisticDialog.spinBox->value();
		statisticalThread.process.setFilter.pclFilter.statisticOutliersStddevmulThresh_=statisticDialog.stddevmulThreshDoubleSpinBox->value();

		if (statisticalThread.isRunning())
		{
		}else
		{
			statisticalThread.start();
			ui.actionStatisticalOutlierRemoval->setEnabled(false);
			addMessage("","StatisticalOutLierFilter","Is Running... ...");
		}
	}
}

void MainWindow::radiusOutlierFilter()
{
	QDialog dialog(this);
	Ui::RadiusOutlterDialog radiusDialog;
	radiusDialog.setupUi(&dialog);
	if (dialog.exec())
	{
		cloudManage.cloud->points.clear();
		cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);
		radiusThread.process.setFilter.cloud=&cloudManage.cloud;
		radiusThread.process.setFilter.cloud_filtered=&cloudManage.cloud_filtered;
		cloudManage.cloud_filtered->points.clear();
		radiusThread.process.choice_=RADIUS_FILTER;
		radiusThread.process.setFilter.pclFilter.conditionalRadius_=radiusDialog.radiusDoubleSpinBox->value();
		radiusThread.process.setFilter.pclFilter.conditionalMinNeighbors_=radiusDialog.spinBox->value();
		if (radiusThread.isRunning())
		{
		}else
		{
			radiusThread.start();
			ui.actionRadiusOutlier->setEnabled(false);
			addMessage("","RadiusOutlierFilter","Is Running... ...");
		}
	}
}


void MainWindow::downSimplingFilter()
{
	QDialog dialog(this);
	Ui::LeafSizeDialog leafDialog;
	leafDialog.setupUi(&dialog);
	if (dialog.exec())
	{
		cloudManage.cloud->points.clear();
		cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);
		downSamplingThread.process.setFilter.cloud=&cloudManage.cloud;
		downSamplingThread.process.setFilter.cloud_filtered=&cloudManage.cloud_filtered;
		cloudManage.cloud_filtered->points.clear();
		downSamplingThread.process.choice_=DOWNSAMPLINGVOXELGRID_FILTER;
		downSamplingThread.process.setFilter.pclFilter.long_=leafDialog.longDoubleSpinBox->value();
		downSamplingThread.process.setFilter.pclFilter.width_=leafDialog.widthDoubleSpinBox->value();
		downSamplingThread.process.setFilter.pclFilter.high_=leafDialog.highDoubleSpinBox->value();

		if (downSamplingThread.isRunning())
		{
		}else
		{
			downSamplingThread.start();
			ui.actionDownSamplingVoxelGrid->setEnabled(false);
			addMessage("","DownSamplingVoxelGrid","Is Running... ...");
		}
	}
}

void MainWindow::euclideanClusterExtract()
{
	QDialog dialog(this);
	Ui::EuclideanClusterDialog euclideanDialog;
	euclideanDialog.setupUi(&dialog);
	if (dialog.exec())
	{
		cloudManage.cloud->points.clear();
		cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ, cloudManage.cloud);
		euclideanClusterThread.process.setCluster.cloud = &cloudManage.cloud;
		euclideanClusterThread.process.setCluster.clusters = &cloudManage.cloudLRGBData;
		cloudManage.cloudLRGBData.clear();
		euclideanClusterThread.process.choice_ = CLUSTER_EXTRACT_EUCLIDEAN;
		euclideanClusterThread.process.setCluster.clusterExtract.clusterTolerance_ = euclideanDialog.clusterToleranceDoubleSpinBox->value();
		euclideanClusterThread.process.setCluster.clusterExtract.distanceThreshold_ = euclideanDialog.distanceThrDoubleSpinBox->value();
		euclideanClusterThread.process.setCluster.clusterExtract.maxClusterSize_ = euclideanDialog.maxClusterSizeSpinBox->value();
		euclideanClusterThread.process.setCluster.clusterExtract.maxIterations_ = euclideanDialog.maxIterationsSpinBox->value();
		euclideanClusterThread.process.setCluster.clusterExtract.minClusterSize_ = euclideanDialog.minClusterSizeSpinBox->value();
		euclideanClusterThread.process.setCluster.clusterExtract.percent_ = euclideanDialog.percentDoubleSpinBox->value();
		if (euclideanClusterThread.isRunning())
		{
		}
		else
		{
			euclideanClusterThread.start();
			ui.actionEuclideanCluster->setEnabled(false);
			addMessage("", "EuclideanCluster", "Is Running... ...");
		}
	}
}


void MainWindow::setBackgroundColor()
{
	QColorDialog colorDialog(this);
	colorDialog.setWindowTitle(tr("Select Background Color"));
	if (colorDialog.exec())
	{
		QColor color;
		color=colorDialog.currentColor();

		cloudManage.viewer->setBackgroundColor(color.redF(),color.greenF(),color.blueF());
		addMessage("","Seting background color.",tr("(R,G,B)")+tr("(")+QString::number(color.red())+tr(",")+QString::number(color.green())+tr(",")+ QString::number(color.blue())+tr(")"));
		ui.qvtkWidget->update();
	}
}


void MainWindow::setPointSize()
{
	QDialog dialog(this);
	Ui::PointSizeDialog pointSizeDialog;
	pointSizeDialog.setupUi(&dialog);

	if (dialog.exec())
	{
		QString tempStr;
		addMessage("","Set point size.","Point size: "+tempStr.setNum(pointSizeDialog.spinBox->value()));
		cloudManage.viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, pointSizeDialog.spinBox->value(), "cloud");
		ui.qvtkWidget->update ();
	}
}

void MainWindow::setPointUniqueColor()
{
	QColorDialog colorDialog(this);
	colorDialog.setWindowTitle(tr("Select Unique Color"));
	if (colorDialog.exec())
	{
		QColor color;
		color=colorDialog.currentColor();

		//addMessage("","Seting background color.",tr("(R,G,B)")+tr("(")+QString::number(color.red())+tr(",")+QString::number(color.green())+tr(",")+ QString::number(color.blue())+tr(")"));
		cloudManage.cloudrgb.reset (new pcl::PointCloud<pcl::PointXYZRGBA>);
		cloudManage.cloudrgb->resize(cloudManage.cloud->points.size());
		int r,g,b;
		for (int i=0;i<cloudManage.cloud->points.size();++i)
		{
			cloudManage.cloudrgb->points.at(i).x=cloudManage.cloud->points.at(i).x;
			cloudManage.cloudrgb->points.at(i).y=cloudManage.cloud->points.at(i).y;
			cloudManage.cloudrgb->points.at(i).z=cloudManage.cloud->points.at(i).z;
			cloudManage.cloudrgb->points.at(i).r=color.red();
			cloudManage.cloudrgb->points.at(i).g=color.green();
			cloudManage.cloudrgb->points.at(i).b=color.blue();
		}

		cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
		ui.qvtkWidget->update();
	}
}


void MainWindow::setAsciiDialogSEP()
{
	//openAsciiDialog.separatorLineEdit->setText(" ");
}

void MainWindow::setAsciiDialogFen()
{
	//openAsciiDialog.separatorLineEdit->setText(";");
}

void MainWindow::setAsciiDialogDou()
{
	//openAsciiDialog.separatorLineEdit->setText(",");
}

void MainWindow::setAsciiTableView()
{

}


//************************************
// Method:    open
// FullName:  MainWindow::open
// Access:    private 
// Returns:   void
// Qualifier: 槽函数
//************************************
void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open PointCloud"), ".",
		tr("Open all files(*.*)\n"
		"Open PointCloudLibary files(*.pcd)\n"
		"Open las files(*.las)\n"
		"Open laz files(*.laz)\n"
		"Open text files (*.txt)"));
	
	if (!fileName.isEmpty())
	{
		addMessage("","",fileName);
		if (!cloudManage.isItemLoadCloud)
		{
			deleteAllItem();
		}
		
		curFile=fileName;
		//enableAction();
		loadFile(fileName);	
	}
		
}
void MainWindow::about()
{
	QMessageBox::about(this, tr("About PointCloudUI"),
		tr("<h2>PointCloudUI 2.0</h2>"
		"<p>Copyright &copy; 2008 Software Inc."
		"<p>www.cugb.edu.cn"
		"<p>zzkang@cugb.edu.cn/shizhenwei@cugb.edu.cn"));
}

//************************************
// Method:    okToContinue
// FullName:  MainWindow::okToContinue
// Access:    private 
// Returns:   bool
// Qualifier:
//************************************
bool MainWindow::okToContinue()
{
	if (true/*isWindowModified()*/) {
		int r = QMessageBox::warning(this, tr("Quit"),
			tr("Are you sure you want to quit?"),
			QMessageBox::Ok | QMessageBox::Cancel);
		if (r == QMessageBox::Ok) {
			return true;
		} else if (r == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

//************************************
// Method:    loadFile
// FullName:  MainWindow::loadFile
// Access:    private 
// Returns:   bool
// Qualifier:
// Parameter: const QString & fileName
//************************************
bool MainWindow::loadFile( const QString &fileName )
{
	QTextCodec* codec =QTextCodec::codecForName("gb2312");
	QTextCodec::setCodecForLocale(codec);
	//QTextCodec::setCodecForCStrings(codec);
	//QTextCodec::setCodecForTr(codec);

	//std::string fileNameStd=fileName.toStdString();
	
	QFileInfo fileInfo=QFileInfo(fileName);
	QString fileSuffix=fileInfo.suffix();
	std::string fileSuffixStd=fileSuffix.toStdString();	
	pointCloudName=fileInfo.fileName();
	pointCloudCompleteBaseName=fileInfo.completeBaseName();
	pointCloudSuffix=fileInfo.suffix();
	pointCloudSize=fileInfo.size();
	pointCloudFilePath=fileInfo.absolutePath()/*fileInfo.filePath()*/;
	
	//updateDBTree(pointCloudName+"("+pointCloudFilePath+")",pointCloudCompleteBaseName);

	if(fileSuffix=="txt")
	{
		openAscii(fileName);
		addMessage(" ","Open",fileName);
		ui.saveAction->setEnabled(true);
		return true;
	}else if(fileSuffix=="pcd")
	{
		cloudManage.cloud->points.clear();
		std::string file_name=fileName.toStdString();		
		pcl::PCDReader reader;		
		reader.read(fileName.toStdString(), *cloudManage.cloud);
		
		cloudManage.processCloudLXYZ.clear();
		cloudManage.cloud2cloudL(cloudManage.cloud, cloudManage.processCloudLXYZ);		
		cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
		addUniColorItem(pointCloudCompleteBaseName);
		
		cloudManage.viewer->updatePointCloud(cloudManage.cloud, "cloud");
		cloudManage.viewer->resetCamera();
		ui.qvtkWidget->update();
		ui.saveAction->setEnabled(true);
		return true;
	}else if (fileSuffix == "las")
	{
		openLAS(fileName);
		addUniColorItem(pointCloudCompleteBaseName);
		ui.saveAction->setEnabled(true);
		return true;

	}
	else if (fileSuffix == "laz")
	{
		LASreadOpener lasreadopener;
		lasreadopener.set_file_name(fileName.toStdString().c_str());
		LASreader* lasreader = lasreadopener.open();
		cloudManage.processCloudLXYZ.clear();
		cloudManage.processCloudLXYZ.resize(lasreader->header.number_of_point_records);
		list<Point>::iterator it = cloudManage.processCloudLXYZ.begin();
		while (lasreader->read_point())
		{
			it->x = lasreader->point.get_x();
			it->y = lasreader->point.get_y();
			it->z = lasreader->point.get_z();
			++it;
		}
		cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
		addUniColorItem(pointCloudCompleteBaseName);
		cloudManage.cloud->points.clear();
		cloudManage.cloudL2cloud(cloudManage.processCloudLXYZ, cloudManage.cloud);
		cloudManage.viewer->updatePointCloud(cloudManage.cloud, "cloud");
		cloudManage.viewer->resetCamera();
		ui.qvtkWidget->update();	
		ui.saveAction->setEnabled(true);
		return true;
	}
	else if (fileSuffix == "jpg")
	{		
		cv::Mat img = cv::imread(fileName.toStdString(), -1);
		cv::imshow("Image", img);
		cvWaitKey();
		ui.saveAction->setEnabled(true);
		//pcl::visualization::imageViewer::addRGBImage(img.data,img.rows,img.cols,"images");
	}
	else
	{
		return false;
	}
	return true;
}


//************************************
// Method:    saveFile
// FullName:  MainWindow::saveFile
// Access:    private 
// Returns:   bool
// Qualifier:
// Parameter: const QString & fileName
//************************************
void MainWindow::saveFile( const QString &fileName )
{
	QTextCodec* codec =QTextCodec::codecForName("gb2312");
	QTextCodec::setCodecForLocale(codec);
	/*QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);*/

	QFileInfo fileInfo=QFileInfo(fileName);
	if (fileInfo.suffix()=="txt")
	{
		saveAscii(fileName);
	}else if (fileInfo.suffix()=="pcd")
	{
		cloudManage.cloud->points.clear();
		cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);
		pcl::PCDWriter writer;
		//writer.write<pcl::PointXYZ>(fileName.toStdString(), *cloudManage.cloud, false);

	}else if (fileInfo.suffix()=="las")
	{		
		std::ofstream ofs;
		ofs.open(fileName.toStdString(), ios::out | ios::binary);

		liblas::Header header;
		liblas::Writer writer(ofs, header);
		header.SetScale(0.00001,0.00001,0.00001);
		liblas::Point point(&header);
		
		for (list<Point>::iterator it = cloudManage.awaitingProcessCloudLXYZ->begin(); it != cloudManage.awaitingProcessCloudLXYZ->end(); ++it)
		{
			point.SetCoordinates(it->x, it->y, it->z);
			writer.WritePoint(point);
		}
		ofs.close();
	}
	else if (fileInfo.suffix() == "laz")
	{	
		LASwriteOpener laswriteopener;
		laswriteopener.set_file_name(fileName.toStdString().c_str());
		
		// init header
		LASheader lasheader;
		lasheader.x_scale_factor = 0.001;
		lasheader.y_scale_factor = 0.001;
		lasheader.z_scale_factor = 0.001;
		//lasheader.x_offset = 1000.0;
		//lasheader.y_offset = 2000.0;
		//lasheader.z_offset = 0.0;
		lasheader.point_data_format = 1;
		lasheader.point_data_record_length = 28;

		// init point 

		LASpoint laspoint;
		laspoint.init(&lasheader, lasheader.point_data_format, lasheader.point_data_record_length, 0);

		// open laswriter
		LASwriter* laswriter = laswriteopener.open(&lasheader);		
		// write points
		for (list<Point>::iterator it = cloudManage.awaitingProcessCloudLXYZ->begin(); it != cloudManage.awaitingProcessCloudLXYZ->end(); ++it)
		{
			laspoint.set_x(it->x);
			laspoint.set_y(it->y);
			laspoint.set_z(it->z);
			// write the point
			laswriter->write_point(&laspoint);
			// add it to the inventory
			laswriter->update_inventory(&laspoint);
		}
		laswriter->update_header(&lasheader, TRUE);
		// close the writer
		laswriter->close();
		delete laswriter;
	}else
	{

	}
}

void MainWindow::openAscii( const QString &fileName )
{
	QDialog asciiDialog(this);
	Ui::OpenAsciiDialog openAsciiDialog;
	openAsciiDialog.setupUi(&asciiDialog);
	openAsciiDialog.filenameLineEdit->setText(fileName);
	QStandardItemModel *openAsciiModel=new QStandardItemModel(this);
	QMap<int,QString> headerItemMap;
	headerItemMap[0]=tr("X");
	headerItemMap[1]=tr("Y");
	headerItemMap[2]=tr("Z");
	headerItemMap[3]=tr("R");
	headerItemMap[4]=tr("G");
	headerItemMap[5]=tr("B");
		
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		return ;
	}
	QTextStream infile(&file);
	QString lineData=infile.readLine();
	
	QMap<int,QStringList> splitLineDataMap;
	QMap<int,QString> splitStrMap;
	splitLineDataMap[0]=lineData.split(splitStrMap[0]=" ");
	splitLineDataMap[1]=lineData.split(splitStrMap[1]=",");
	splitLineDataMap[2]=lineData.split(splitStrMap[2]=";");
	QString splitStr;//
	int lineDataNum;//
	int formatNum=3;
	for (int i=0;i<formatNum;++i)
	{
		if (splitLineDataMap[i].size()>=3)
		{
			splitStr=splitStrMap[i];
			break;
		}		
	}
	
	QStringList lineDatas=lineData.split(splitStr);
	lineDataNum=lineDatas.size();
	for (int i=0;i<lineDatas.size();++i)
	{
		openAsciiModel->setHorizontalHeaderItem(i,new QStandardItem(headerItemMap[i]));
	}

	infile.seek(0);
	int lineNum=0;
	while(!infile.atEnd())
	{
		QString lineData=infile.readLine();
		QStringList lineDatas=lineData.split(splitStr);
		for (int i=0;i<lineDatas.size();++i)
		{
			//lineDatas.at(i).toFloat();
			openAsciiModel->setItem(lineNum,i,new QStandardItem(lineDatas.at(i)));
		}
		if (lineNum++>10)
		{
			break;
		}
	}
	file.close();
	openAsciiDialog.tableView->setModel(openAsciiModel);
	if (asciiDialog.exec())
	{
		if (lineDataNum==3)//x y z
		{
			cloudManage.loadCloudXYZ(fileName,splitStr);

			//initiaDBTree();
			addUniColorItem(pointCloudCompleteBaseName);

			cloudManage.viewer->updatePointCloud (cloudManage.cloud, "cloud");
			cloudManage.viewer->resetCamera ();
			ui.qvtkWidget->update();
		}

		if (lineDataNum==6)//x y z r g b
		{
			cloudManage.loadCloudRGB(fileName,splitStr);
			//pointsNum=cloudMange.cloudrgb->points.size();
			cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
			cloudManage.viewer->resetCamera ();
			ui.qvtkWidget->update();
			//updatePropertiesTree();
			file.close();
		}
	}
}

void MainWindow::openLAS(const QString &fileName)
{
	QProgressDialog *openProgress=new QProgressDialog(this);	
	openProgress->setWindowTitle(QObject::tr("Openning cloud"));		
	openProgress->setModal(true);
	openProgress->setCancelButtonText(QObject::tr("Cancel"));
	
	std::ifstream ifs;
	ifs.open(fileName.toStdString(), std::ios::in | std::ios::binary);
	if (!ifs)
	{
		return;
	}

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	liblas::Header const& header = reader.GetHeader();
	openProgress->setRange(0, header.GetPointRecordsCount());
	openProgress->setLabelText(QObject::tr("Approximate number of points: ") + QString::number(header.GetPointRecordsCount()));
	Point pnt;
	cloudManage.processCloudLXYZ.clear();
	int id = 0;
	int size = header.GetPointRecordsCount() / 100;
	cloudManage.processCloudLXYZ.resize(header.GetPointRecordsCount());
	
	list<Point>::iterator it = cloudManage.processCloudLXYZ.begin();
	while (reader.ReadNextPoint())
	{
		it->x = reader.GetPoint().GetX();
		it->y = reader.GetPoint().GetY();
		it->z = reader.GetPoint().GetZ();
		++it;
		addMessage("", "", QString::number(it->x));
		++id;
		if (id % size)
		{
			openProgress->setValue(id);
		}
		if (openProgress->wasCanceled())
		{
			break;
		}
	}
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	cloudManage.cloud->points.clear();
	cloudManage.cloudL2cloud(cloudManage.processCloudLXYZ, cloudManage.cloud);
	cloudManage.viewer->updatePointCloud(cloudManage.cloud, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();

}

void MainWindow::saveAscii( const QString &fileName )
{
	QDialog asciiDialog(this);
	Ui::SaveAsciiDialog saveAsciiDialog;
	saveAsciiDialog.setupUi(&asciiDialog);
	
	QProgressDialog saveProgress;
	saveProgress.setLabelText(tr("Number of points: ")+QString::number(cloudManage.awaitingProcessCloudLXYZ->size()));
	saveProgress.setWindowTitle(tr("Saving cloud")+tr("[")+pointCloudName+"]");

	saveProgress.setRange(0,cloudManage.awaitingProcessCloudLXYZ->size());
	saveProgress.setModal(true);
	saveProgress.setCancelButtonText(tr("Cancel"));

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		return ;
	}
	QTextStream outfile(&file);
	QString separatorStr;
	map<int,QString> separatorMap;
	separatorMap[0]=" ";
	separatorMap[1]=",";
	separatorMap[2]=";";
	
	if (asciiDialog.exec())
	{
		int i=0;
		separatorStr=separatorMap[saveAsciiDialog.separatorComboBox->currentIndex()];
		for (list<Point>::iterator it=cloudManage.awaitingProcessCloudLXYZ->begin();it!=cloudManage.awaitingProcessCloudLXYZ->end();++it)
		{
			outfile<<it->x<<separatorStr<<it->y<<separatorStr<<it->z<<endl;

			if (i%20==0)
			{
				saveProgress.setValue(i++);
			}
			if (saveProgress.wasCanceled())
			{
				break;
			}
		}
	}
	file.close();
}


void MainWindow::initiaDBTree()
{
	ui.DBTreeView->setHeaderHidden(true);
	QStandardItemModel *model = new QStandardItemModel(this);
	model->setHorizontalHeaderLabels(QStringList()<<QObject::tr(""));

	QStandardItem* root = new QStandardItem(QIcon(":/images/cloudproject.png"),QObject::tr("PointCloud"));
	root->setData(MARK_PROJECT,ROLE_MARK);//首先它是项目中目录
	root->setData(MARK_FOLDER,ROLE_MARK_FOLDER);//其次它属于文件夹
	root->setEditable(false);
	model->appendRow(root);

	QStandardItem* folder = new QStandardItem(QIcon(":/images/clouduniquecolor.png"),QObject::tr("UniColorCloud"));
	folder->setData(MARK_FOLDER,ROLE_MARK);//首先它是文件夹
	folder->setData(MARK_FOLDER_UNIQC,ROLE_MARK_FOLDER);//其次它属于头文件文件夹
	folder->setEditable(false);
	root->appendRow(folder);

	folder = new QStandardItem(QIcon(":/images/cloudmulticolor.png"),QObject::tr("MulColorCloud"));
	folder->setData(MARK_FOLDER,ROLE_MARK);//首先它是文件夹
	folder->setData(MARK_FOLDER_MULTC,ROLE_MARK_FOLDER);//其次它属于源文件文件夹
	folder->setEditable(false);
	root->appendRow(folder);
	//root->setData( tr("这是关于QStandardItemModel设定角色的教程详细介绍见：http://blog.csdn.net/czyt1988/article/details/26018513"),Qt::ToolTipRole);
	
	ui.DBTreeView->setModel(model);
	ui.DBTreeView->expandAll();
	
	m_projectMenu=new QMenu(this);	
	QAction* noAction1=new QAction(tr("noAction1"),this);
	QAction* noAction2=new QAction(tr("noAction2"),this);
	QAction* importItemAction=new QAction(tr("ImportCloud"),this);
	QAction* deleteAllItemAction=new QAction(tr("DeleteAllCloud"),this);
	QAction* exportAllItemAction=new QAction(tr("ExportAllCloud"),this);
	QAction* newCreateMulAction = new QAction(tr("CreateMult"), this);

	m_projectMenu->addAction(importItemAction);
	m_projectMenu->addAction(exportAllItemAction);
	m_projectMenu->addSeparator();
	m_projectMenu->addAction(deleteAllItemAction);
	m_projectMenu->addAction(newCreateMulAction);
	m_projectMenu->addSeparator();
	m_projectMenu->addAction(noAction1);
	m_projectMenu->addAction(noAction2);
	noAction1->setEnabled(false);
	noAction2->setEnabled(false);
	connect(importItemAction,SIGNAL(triggered()),this,SLOT(import2Item()));
	connect(deleteAllItemAction,SIGNAL(triggered()),this,SLOT(deleteAllItem()));
	connect(exportAllItemAction,SIGNAL(triggered()),this,SLOT(exportAllItem()));

	m_itemMenu=new QMenu(this);
	QAction* activateSelectAction=new QAction(tr("ActivateCloud"),this);
	QAction* updateItem2ViewAction=new QAction(tr("UpdateCloudToView"),this);
	QAction* addItem2ViewAction=new QAction(tr("AddCloudToView"),this);
	QAction* deleteItemAction=new QAction(tr("DeleteCloud"),this);
	QAction* exportItemAction=new QAction(tr("ExportCloud"),this);
	QAction* uniAdd2MulAction = new QAction(tr("UniAdd2Mult"), this);
	
	
	m_itemMenu->addAction(activateSelectAction);
	m_itemMenu->addSeparator();
	m_itemMenu->addAction(updateItem2ViewAction);	
	m_itemMenu->addAction(addItem2ViewAction);
	m_itemMenu->addSeparator();
	m_itemMenu->addAction(deleteItemAction);
	m_itemMenu->addSeparator();
	m_itemMenu->addAction(exportItemAction);
	m_itemMenu->addAction(uniAdd2MulAction);
	
		
	connect(activateSelectAction,SIGNAL(triggered()),this,SLOT(activateItem()));
	connect(updateItem2ViewAction,SIGNAL(triggered()),this,SLOT(updateItem2View()));
	connect(addItem2ViewAction,SIGNAL(triggered()),this,SLOT(addItem2View()));
	connect(deleteItemAction,SIGNAL(triggered()),this,SLOT(deleteItem()));
	connect(exportItemAction,SIGNAL(triggered()),this,SLOT(exportItem()));
	connect(uniAdd2MulAction, SIGNAL(triggered()), this, SLOT(uniItemAdd2MulItem()));
	connect(newCreateMulAction, SIGNAL(triggered()), this, SLOT(newCreateMulItem()));

	s_uniqcolor_count = 0;
	s_multcolor_count = 0;

	connect(ui.DBTreeView,SIGNAL(clicked(const QModelIndex)),this,SLOT(on_treeView_currentItem_Clicked( const QModelIndex)));
	//connect(ui.DBTreeView,SIGNAL(c))
}
void MainWindow::updateDBTree( const QString &name ,const QString &str)
{	
	//QStandardItem *parentFolder=new QStandardItem(name);
	//model->clear();
	//model->appendRow(parentFolder);

	//QStandardItem *childFolder=new QStandardItem(str);
	//parentFolder->appendRow(childFolder);

	//ui.DBTreeView->setModel(model);

	


}

void MainWindow::updatePropertiesTree()
{
	QStandardItemModel *proModel=new QStandardItemModel(this);
	proModel->setHorizontalHeaderLabels(QStringList()<<tr("Property")<<tr("value"));
	
	QStandardItem* itemPoints = new QStandardItem(QObject::tr("Points"));
	itemPoints->setEditable(false);
	proModel->setItem(0,0,itemPoints);

	QStandardItem* itemPointsNum = new QStandardItem(QString::number(cloudManage.awaitingProcessCloudLXYZ->size()));
	itemPointsNum->setEditable(false);
	proModel->setItem(0,1,itemPointsNum);

	proModel->setItem(1,0,new QStandardItem("Colors"));
	proModel->setItem(1,1,new QStandardItem(QObject::tr("None")));

	QStandardItem* itemColors=new QStandardItem;
	itemColors->appendRow(new QStandardItem("Green"));
	itemColors->appendRow(new QStandardItem("Red"));
	itemColors->appendRow(new QStandardItem("Blue"));
	proModel->setItem(2, 0, new QStandardItem("Colors"));
	proModel->setItem(2, 1, itemColors);


	/*proModel->setItem(0,0,new QStandardItem("Name"));
	proModel->setItem(0,1,new QStandardItem(pointCloudCompleteBaseName));
	QString temQS;
	proModel->setItem(1,0,new QStandardItem("Points"));
	proModel->setItem(1,1,new QStandardItem(temQS.setNum(pointsNum)));
	
	proModel->setItem(2.0,new QStandardItem("DataSize"));
	if (pointCloudSize/1024.0/1024.0>1)
	{
		proModel->setItem(2,1,new QStandardItem(temQS.setNum(pointCloudSize/1024.0/1024.0)+tr(" M")));
	}else
	{
		proModel->setItem(2,1,new QStandardItem(temQS.setNum(pointCloudSize/1024.0)+tr(" K")));
	}
	
	proModel->setItem(3,0,new QStandardItem(tr("Suffix")));
	proModel->setItem(3,1,new QStandardItem(pointCloudSuffix));

	proModel->setItem(4,0,new QStandardItem(tr("Path")));
	proModel->setItem(4,1,new QStandardItem(pointCloudFilePath));

	proModel->setItem(5,0,new QStandardItem(tr("minZ")));
	proModel->setItem(5,1,new QStandardItem(QString::number(minZ)));

	proModel->setItem(6,0,new QStandardItem(tr("maxZ")));
	proModel->setItem(6,1,new QStandardItem(QString::number(maxZ)));*/
	
	
	ui.propertiesTreeView->setModel(proModel);	
}


void MainWindow::enableAction(bool _bool)
{
	ui.actionTranslate->setEnabled(_bool);
	ui.actionCloudResolution->setEnabled(_bool);
	ui.actionEstimatingNormals->setEnabled(_bool);

	ui.actionPassThrough->setEnabled(_bool);
	ui.actionStatisticalOutlierRemoval->setEnabled(_bool);
	ui.actionRadiusOutlier->setEnabled(_bool);
	ui.actionDownSamplingVoxelGrid->setEnabled(_bool);
	ui.actionEuclideanCluster->setEnabled(_bool);

	ui.actionRANSAC->setEnabled(_bool);
	ui.actionRegionGrowingRansac->setEnabled(_bool);
	ui.actionBaySAC->setEnabled(_bool);
	ui.actionBAYLMEDS->setEnabled(_bool);
	ui.actionSurfaceGrow->setEnabled(_bool);

	ui.actionSimple->setEnabled(_bool);
	ui.actionFeaturePoints->setEnabled(_bool);
	ui.actionPCA->setEnabled(_bool);
	ui.actionContour->setEnabled(_bool);

	ui.actionPointSize->setEnabled(_bool);
	ui.actionDirectionX->setEnabled(_bool);
	ui.actionDirectionY->setEnabled(_bool);
	ui.actionDirectionZ->setEnabled(_bool);
	ui.actionUnique_Color->setEnabled(_bool);
	ui.actionPointSize->setEnabled(_bool);

	ui.actioPolesExtact->setEnabled(_bool);
	ui.actionComputeCenterofPoles->setEnabled(_bool);
	ui.actionStatisticPolesNum->setEnabled(_bool);
	ui.actionOutPolesPoints->setEnabled(_bool);

	ui.actionGroundFilter->setEnabled(_bool);
	ui.actionExtractCurb->setEnabled(_bool);
	ui.actionAfterProgress1->setEnabled(_bool);
	ui.actionAfterProgress2->setEnabled(_bool);
	ui.actionAfterProgress3->setEnabled(_bool);
	ui.actionChouXi->setEnabled(_bool);
	ui.actionSort->setEnabled(_bool);
	ui.actionOutRoadPoints->setEnabled(_bool);

	ui.actionBuildExtract->setEnabled(_bool);
	ui.actionComputeAnglePoints->setEnabled(_bool);
	ui.actionOutAnglePoints->setEnabled(_bool);

}

void MainWindow::initialConcoleTreeWidget()
{
	QStringList messageLabels;
	messageLabels << tr("Time") << tr("Operate") << tr("Object");
	ui.consoleTreeWidget->setHeaderLabels(messageLabels);

	addMessage(tr("Time"),tr("PointCloudUI Start"),tr(" "));
	ui.consoleTreeWidget->resizeColumnToContents(0);
	ui.consoleTreeWidget->resizeColumnToContents(1);

}

void MainWindow::addMessage( const QString &date, const QString &object, const QString &operate )
{
	QDateTime time=QDateTime::currentDateTime();
	QString temQS=time.toString("yyyy-MM-dd ddd hh:mm:ss:zzz");
	QTreeWidgetItem *newItem = new QTreeWidgetItem(ui.consoleTreeWidget);
	newItem->setText(0, temQS);
	newItem->setText(1, object);
	newItem->setText(2, operate);

	if (!ui.consoleTreeWidget->currentItem())
		ui.consoleTreeWidget->setCurrentItem(newItem);
}

void MainWindow::closeEvent( QCloseEvent *event )
{
	testThread.stop();
	testThread.wait();

	//ransacThread.stop();
	surfaceGrowThread.stop();
	contourThread.stop();
	PCAThread.stop();
	featureThread.stop();
	simplePointThread.stop();

	//ransacThread.wait();
	surfaceGrowThread.wait();
	contourThread.wait();
	PCAThread.wait();
	featureThread.wait();
	simplePointThread.wait();

	if (!appLockb)
	{
		event->accept();
	}
	else
	{
		if (okToContinue()) {
			this->close();
			event->accept();			
		}
		else {
			event->ignore();
		}
	}	
}

void MainWindow::resizeEvent( QResizeEvent *event )
{
	//QVTKWidget::resizeEvent(event);
	//double maxX=100.0 / width();
	//double maxY=100.0 / height();
	

}
void MainWindow::eleGradient( float &z, int &r, int &g,int &b )
{
	//blue
	int r1=0;
	int g1=0;
	int b1=255;
	//green
	int r2=0;
	int g2=255;
	int b2=0;
	//red
	int r3=255;
	int g3=0;
	int b3=0;
		
	/*r=r1+(r2-r1)*(z-minZ)/(maxZ-minZ);
	g=g1+(g2-g1)*(z-minZ)/(maxZ-minZ);
	b=b1+(b2-b1)*(z-minZ)/(maxZ-minZ);*/
	double midZ=(maxZ-minZ)/2.0+minZ;
	if (z<midZ)
	{
		r=r1+(r2-r1)*(z-minZ)/(midZ-minZ);
		g=g1+(g2-g1)*(z-minZ)/(midZ-minZ);
		b=b1+(b2-b1)*(z-minZ)/(midZ-minZ);
	}else
	{
		r=r2+(r3-r2)*(z-midZ)/(maxZ-midZ);
		g=g2+(g3-g2)*(z-midZ)/(maxZ-midZ);
		b=b2+(b3-b2)*(z-midZ)/(maxZ-midZ);
	}
}

void MainWindow::rangeGradient( float &x, int &r, int &g,int &b )
{
	//blue
	int r1=0;
	int g1=0;
	int b1=255;
	//green
	int r2=0;
	int g2=255;
	int b2=0;
	//red
	int r3=255;
	int g3=0;
	int b3=0;
		
	/*r=r1+(r2-r1)*(z-minZ)/(maxZ-minZ);
	g=g1+(g2-g1)*(z-minZ)/(maxZ-minZ);
	b=b1+(b2-b1)*(z-minZ)/(maxZ-minZ);*/
	double midX=(maxX-minX)/2.0+minX;
	if (x<midX)
	{
		r=r1+(r2-r1)*(x-minX)/(midX-minX);
		g=g1+(g2-g1)*(x-minX)/(midX-minX);
		b=b1+(b2-b1)*(x-minX)/(midX-minX);
	}else
	{
		r=r2+(r3-r2)*(x-midX)/(maxX-midX);
		g=g2+(g3-g2)*(x-midX)/(maxX-midX);
		b=b2+(b3-b2)*(x-midX)/(maxX-midX);
	}
}

void MainWindow::addOrientationMarKerWidgetAxes()
{
	vtkSmartPointer<vtkAxesActor> vtkAxes= vtkSmartPointer<vtkAxesActor>::New();
	vtkAxes->AxisLabelsOff();

	vtkAxesWidget=vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	vtkAxesWidget->SetInteractor(ui.qvtkWidget->GetRenderWindow()->GetInteractor());
	vtkAxesWidget->SetOrientationMarker(vtkAxes);
	vtkAxesWidget->SetEnabled(true);
	vtkAxesWidget->InteractiveOff();
	
}
void MainWindow::setFullScreen()
{	
	if (this->isFullScreen())
	{
		setWindowState(Qt::WindowMaximized);
	}else
	{
		this->showFullScreen();
	}
}


void MainWindow::setTopView()
{
	cloudManage.viewer->setCameraPosition(0, 0, 1, 0, 0, 0, 0, 1, 0);
	cloudManage.viewer->resetCamera ();
	ui.qvtkWidget->update ();
}

void MainWindow::setBottomView()
{
	cloudManage.viewer->setCameraPosition(0, 0, -1, 0, 0, 0, 0, -1, 0);
	cloudManage.viewer->resetCamera ();
	ui.qvtkWidget->update ();
}

void MainWindow::setFrontView()
{
	cloudManage.viewer->setCameraPosition(0, -1, 0, 0, 0, 0, 0, 0, 1);
	cloudManage.viewer->resetCamera ();
	ui.qvtkWidget->update ();
}

void MainWindow::setBackView()
{
	cloudManage.viewer->setCameraPosition(0, 1, 0, 0, 0, 0, 0, 0, 1);
	cloudManage.viewer->resetCamera ();
	ui.qvtkWidget->update ();
}

void MainWindow::setRightView()
{
	cloudManage.viewer->setCameraPosition(1, 0, 0, 0, 0, 0, 0, 0, 1);
	cloudManage.viewer->resetCamera ();
	ui.qvtkWidget->update ();
}

void MainWindow::setLeftView()
{
	cloudManage.viewer->setCameraPosition(-1, 0, 0, 0, 0, 0, 0, 0, 1);
	cloudManage.viewer->resetCamera ();
	ui.qvtkWidget->update ();
}

void MainWindow::setShowOrHideDBWidget()
{
	if (ui.DBTreeDockWidget->isHidden())
	{
		ui.DBTreeDockWidget->show();
	}else
	{		
		ui.DBTreeDockWidget->hide();
	}	
}

void MainWindow::setShowOrHideConsoleWidget()
{
	if (ui.ConsoleDockWidget->isHidden())
	{
		ui.ConsoleDockWidget->show();
	}else
	{
		ui.ConsoleDockWidget->hide();
	}
}

void MainWindow::setShowOrHidePropertyWidget()
{
	if (ui.PropertiesDockWidget->isHidden())
	{
		ui.PropertiesDockWidget->show();
	}else
	{
		ui.PropertiesDockWidget->hide();
	}
}

void MainWindow::setActionTestEnable(bool _bool )
{
	//ui.actionTest->setEnabled(_bool);
	//
	////addMessage("","test","complete!"+QString::number(testThread.process.setRansac.points.size()));
	////segments=&testThread.process.setRansac.segments;
	////addMessage("","test","complete!"+QString::number(testThread.process.setRansac.segments.size()));

	//cloudManage.cloudrgb.reset (new pcl::PointCloud<pcl::PointXYZRGBA>);
	//pcl::PointXYZRGBA pntXYZRGB;
	//int r,g,b;
	//srand((int)time(NULL));
	//for(list<Points>::iterator it1=segments.begin();it1!=segments.end();++it1)
	//{
	//	r=255 *(1024 * rand () / (RAND_MAX + 1.0f));
	//	g=255 *(1024 * rand () / (RAND_MAX + 1.0f));
	//	b=255 *(1024 * rand () / (RAND_MAX + 1.0f));
	//	for(list<Point>::iterator it2=it1->begin();it2!=it1->end();++it2)
	//	{
	//		//            cout<<it2->x<<" "<<it2->y<<" "<<it2->z<<endl;
	//		pntXYZRGB.x=it2->x;
	//		pntXYZRGB.y=it2->y;
	//		pntXYZRGB.z=it2->z;
	//		pntXYZRGB.r=r;
	//		pntXYZRGB.g=g;
	//		pntXYZRGB.b=b;
	//		//            cout<<it2->x<<" "<<it2->y<<" "<<it2->z<<endl;
	//		cloudManage.cloudrgb->points.push_back(pntXYZRGB);
	//		//            cout<<it2->x<<" "<<it2->y<<" "<<it2->z<<endl;
	//	}
	//}
	//cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
	//ui.qvtkWidget->update();

}

void MainWindow::setActionRansacEnable( bool _bool )
{
	ui.actionRANSAC->setEnabled(_bool);
	addMessage("","RansacSegment","Complete.");
	cloudManage.cloudsRGBData.push_back(cloudManage.cloudLRGBData);
	addMulColorItem("RANSACSEG_");
	cloudManage.cloudrgb->points.clear();
	cloudManage.cloudsL2cloudRGB(cloudManage.cloudLRGBData,cloudManage.cloudrgb);
	cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}
void MainWindow::setActionSurfaceGrowEnable( bool _bool )
{
	ui.actionSurfaceGrow->setEnabled(_bool);
	addMessage("","SurfaceGrowSegment","Complete.");
	cloudManage.cloudsRGBData.push_back(cloudManage.cloudLRGBData);
	addMulColorItem("SurfaceGrow");
	cloudManage.cloudrgb->points.clear();
	cloudManage.cloudsL2cloudRGB(cloudManage.cloudLRGBData,cloudManage.cloudrgb);
	cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}
void MainWindow::setActionContourEnable( bool _bool )
{
	ui.actionContour->setEnabled(_bool);
	addMessage("","ComputeContourPoints","Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	//cloudManage.cloudProperty.getProperty(cloudManage.processCloudLXYZ);
	//cloudManage.cloudXYZProp.push_back(cloudManage.cloudProperty);
	addUniColorItem("ContourPs_");
	cloudManage.cloud->points.clear();
	cloudManage.cloudL2cloud(cloudManage.processCloudLXYZ,cloudManage.cloud);
	cloudManage.viewer->updatePointCloud (cloudManage.cloud, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
	
}
void MainWindow::setActionPCAEnable( bool _bool )
{
	ui.actionPCA->setEnabled(_bool);
	addMessage("","ComputePCAPoints","Complete."/*+QString::number(PCAThread.process.setPCA.PCAPoints->size())*/);
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	/*cloudManage.cloudProperty.getProperty(cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZProp.push_back(cloudManage.cloudProperty);*/
	addUniColorItem("PCAPs_____");
	cloudManage.cloud->points.clear();
	cloudManage.cloudL2cloud(cloudManage.processCloudLXYZ,cloudManage.cloud);
	cloudManage.viewer->updatePointCloud (cloudManage.cloud, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

void MainWindow::setActionFeatureEnable( bool _bool )
{
	ui.actionFeaturePoints->setEnabled(_bool);
	addMessage("","ComputeFeaturePoints","Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	/*cloudManage.cloudProperty.getProperty(cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZProp.push_back(cloudManage.cloudProperty);*/
	addUniColorItem("FeaturePs_");
	cloudManage.cloud->points.clear();
	cloudManage.cloudL2cloud(cloudManage.processCloudLXYZ,cloudManage.cloud);
	cloudManage.viewer->updatePointCloud (cloudManage.cloud, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

void MainWindow::setActionSimaplePointEnable( bool _bool )
{
	ui.actionSimple->setEnabled(_bool);
	addMessage("","ComputeSimplePoints","Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("SimplePs__");
	cloudManage.cloud->points.clear();
	cloudManage.cloudL2cloud(cloudManage.processCloudLXYZ,cloudManage.cloud);
	cloudManage.viewer->updatePointCloud (cloudManage.cloud, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}
void MainWindow::setActionPassThroughEnable( bool _bool )
{
	ui.actionPassThrough->setEnabled(_bool);
	addMessage("","PassThroughFilter","Complete.");
	cloudManage.viewer->updatePointCloud (cloudManage.cloud_filtered, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();

	cloudManage.processCloudLXYZ.clear();
	cloudManage.cloud2cloudL(cloudManage.cloud_filtered,cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("PassThrPs_");
}

void MainWindow::setActionStatisticalOutlierEnable( bool _bool )
{
	ui.actionStatisticalOutlierRemoval->setEnabled(_bool);
	addMessage("","StatisticalOutlierFilter","Complete.");
	cloudManage.viewer->updatePointCloud (cloudManage.cloud_filtered, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();

	cloudManage.processCloudLXYZ.clear();
	cloudManage.cloud2cloudL(cloudManage.cloud_filtered,cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("StaOutlier");
}

void MainWindow::setActionRadiusOutlierEnable( bool _bool )
{
	ui.actionRadiusOutlier->setEnabled(_bool);
	addMessage("","RadiusOutlierFilter","Complete.");
	cloudManage.viewer->updatePointCloud (cloudManage.cloud_filtered, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();

	cloudManage.processCloudLXYZ.clear();
	cloudManage.cloud2cloudL(cloudManage.cloud_filtered,cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("RadOutlier");
}


void MainWindow::setActionDownSimplingEnable( bool _bool )
{
	ui.actionDownSamplingVoxelGrid->setEnabled(_bool);
	addMessage("","DownSamplingVoxelGridFilter","Complete.");
	cloudManage.viewer->updatePointCloud (cloudManage.cloud_filtered, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();

	cloudManage.processCloudLXYZ.clear();
	cloudManage.cloud2cloudL(cloudManage.cloud_filtered,cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("DownSimple");
}

void MainWindow::setActionEuclideanCluster(bool _bool)
{
	ui.actionEuclideanCluster->setEnabled(_bool);
	addMessage("", "EuclideanCluster", "Complete.");
	cloudManage.cloudsRGBData.push_back(cloudManage.cloudLRGBData);
	addMulColorItem();
	cloudManage.cloudrgb->points.clear();
	cloudManage.cloudsL2cloudRGB(cloudManage.cloudLRGBData, cloudManage.cloudrgb);
	cloudManage.viewer->updatePointCloud(cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

//void MainWindow::setActionTestThread( bool _bool )
//{
//	addMessage("","testThread","Complete.");
//}

QStandardItemModel* MainWindow::getTreeModel()
{
	return qobject_cast<QStandardItemModel*>(ui.DBTreeView->model());
}

QList<QStandardItem*> MainWindow::getRoots()
{
	QList<QStandardItem*> roots;
	QStandardItemModel* model = getTreeModel();
	for(int i=0;i < model->rowCount();++i)
	{
		roots.append(model->item(i));
	}
	return roots;
}

QStandardItem* MainWindow::getProjectFolder()
{
	QList<QStandardItem*> roots = getRoots();
	for(auto i=roots.begin();i!=roots.end();++i){
		if((*i)->data(ROLE_MARK) == MARK_PROJECT){
			return (*i);
		}
	}
	return nullptr;
}

QStandardItem* MainWindow::getCloudXYZFolder()
{
	QStandardItem* project = getProjectFolder();
	if(nullptr == project)
		return nullptr;
	for(int i=0;i < project->rowCount();++i)
	{
		QStandardItem* child = project->child(i);
		QVariant var = child->data(ROLE_MARK_FOLDER);
		if(!var.isValid())
			continue;//说明不是ROLE_MARK_FOLDER，有可能是一些项目，对应项目结构树那个xxx.pro就是一个非文件夹条目
		if(MARK_FOLDER_UNIQC == var.value<int>())
			return child;
	}
	return nullptr;
}

QStandardItem* MainWindow::getCloudRGBFolder()
{
	QStandardItem* project = getProjectFolder();
	if(nullptr == project)
		return nullptr;
	for(int i=0;i < project->rowCount();++i)
	{
		QStandardItem* child = project->child(i);
		QVariant var = child->data(ROLE_MARK_FOLDER);
		if(!var.isValid())
			continue;//说明不是ROLE_MARK_FOLDER，有可能是一些项目，对应项目结构树那个xxx.pro就是一个非文件夹条目
		if(MARK_FOLDER_MULTC == var.value<int>())
			return child;
	}
	return nullptr;
}

QStandardItem* MainWindow::getCloudXYZItem()
{
	QStandardItem* folder=getCloudXYZFolder();
	if(nullptr == folder)
		return nullptr;
	for(int i=0;i < folder->rowCount();++i)
	{
		QStandardItem* child = folder->child(i);
		QVariant var = child->data(ROLE_MARK_ITEM);
		if(!var.isValid())
			continue;//说明不是ROLE_MARK_FOLDER，有可能是一些项目，对应项目结构树那个xxx.pro就是一个非文件夹条目
		if(MARK_ITEM_MULTC == var.value<int>())
			return child;
	}
	return nullptr;
}

QStandardItem* MainWindow::getCloudRGBItem()
{
	QStandardItem* folder=getCloudRGBFolder();
	if(nullptr == folder)
		return nullptr;
	for(int i=0;i < folder->rowCount();++i)
	{
		QStandardItem* child = folder->child(i);
		QVariant var = child->data(ROLE_MARK_ITEM);
		if(!var.isValid())
			continue;//说明不是ROLE_MARK_FOLDER，有可能是一些项目，对应项目结构树那个xxx.pro就是一个非文件夹条目
		if(MARK_ITEM_UNIQC == var.value<int>())
			return child;
	}
	return nullptr;
}

void MainWindow::on_treeView_customContextMenuRequested( const QPoint &pos )
{
	QModelIndex index = ui.DBTreeView->indexAt(pos);
	QVariant var = index.data(ROLE_MARK);
	if(var.isValid())
	{
		if(MARK_FOLDER == var.toInt())
			m_projectMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
		else if(MARK_ITEM == var.toInt())
			m_itemMenu->exec(QCursor::pos());
	}
}
void MainWindow::on_treeView_currentItem_Clicked( const QModelIndex &index )
{
	activateItem();
}

void MainWindow::addUniColorItem(QString name)
{
	QStandardItem* cloudXYZFolder = getCloudXYZFolder();
	if(cloudXYZFolder)
	{
		QStandardItem* item = new QStandardItem(QIcon(":/images/clouduniquecolor.png"),name+tr("-%1_cloud").arg(s_uniqcolor_count));
		item->setData(MARK_ITEM,ROLE_MARK);//首先标定条目的类型 - 文件夹、项目、条目…
		item->setData(MARK_ITEM_UNIQC,ROLE_MARK_ITEM);//再次标定项目的类型
		cloudXYZFolder->appendRow(item);
		++s_uniqcolor_count;
	}
}

void MainWindow::addMulColorItem(QString name)
{
	QStandardItem* cloudRGBFolder = getCloudRGBFolder();
	if(cloudRGBFolder)
	{
		QStandardItem* item = new QStandardItem(QIcon(":/images/cloudmulticolor.png"),name+tr("-%1_cloud").arg(s_multcolor_count));
		item->setData(MARK_ITEM,ROLE_MARK);//首先标定条目的类型 - 文件夹、项目、条目…
		item->setData(MARK_ITEM_MULTC,ROLE_MARK_ITEM);//再次标定项目的类型
		cloudRGBFolder->appendRow(item);
		++s_multcolor_count;
	}
}
void MainWindow::test()
{
	//Clusters clust;
	//clust.main222();
}


void MainWindow::activateItem()
{
	QModelIndex curIndex=ui.DBTreeView->currentIndex();

	if (curIndex.parent().data().toString()=="UniColorCloud")
	{
		QStandardItem* cloudXYZFolder = getCloudXYZFolder();
		if(cloudXYZFolder)
		{
			enableAction(true);
			enableActionThread(ransacThread, *ui.actionRANSAC);
			enableActionThread(surfaceGrowThread, *ui.actionSurfaceGrow);
			enableActionThread(contourThread, *ui.actionContour);
			enableActionThread(PCAThread, *ui.actionPCA);
			enableActionThread(featureThread, *ui.actionFeaturePoints);
			enableActionThread(simplePointThread, *ui.actionSimple);
			enableActionThread(passThroughThread, *ui.actionPassThrough);
			enableActionThread(statisticalThread, *ui.actionStatisticalOutlierRemoval);
			enableActionThread(radiusThread, *ui.actionRadiusOutlier);
			enableActionThread(downSamplingThread, *ui.actionDownSamplingVoxelGrid);
			enableActionThread(euclideanClusterThread, *ui.actionEuclideanCluster);
			enableActionThread(resolutionThread, *ui.actionCloudResolution);
			enableActionThread(regionGrowRansacThread, *ui.actionRegionGrowingRansac);
			enableActionThread(regionGrowBaysacThread, *ui.actionBaySAC);
			enableActionThread(regionGrowBayLmedsThread, *ui.actionBAYLMEDS);
			enableActionThread(estimateNormalsThread, *ui.actionEstimatingNormals);
			enableActionThread(polesExtractThread, *ui.actioPolesExtact);
			enableActionThread(statisticPolesNumThread, *ui.actionStatisticPolesNum);
			enableActionThread(computeCenterofPolesThread, *ui.actionComputeCenterofPoles);
			enableActionThread(groundFilterThread, *ui.actionGroundFilter);
			enableActionThread(extractCurbThread, *ui.actionExtractCurb);
			enableActionThread(curbAfterProgress1Thread, *ui.actionAfterProgress1);
			enableActionThread(curbAfterProgress2Thread, *ui.actionAfterProgress2);
			enableActionThread(extractBuildThread, *ui.actionBuildExtract);

			cloudManage.activateCloudXYZ(curIndex.row());
			updatePropertiesTree();

			if (afterParentDialog&&!afterParentDialog->isHidden())
			{
				switch (afterProcessButtonsGroup->checkedId())
				{
				case INITIAL_SHOULDER_POINTS:
					afterProcess2Dialog->initialShoulderLineEdit->setText(curIndex.data().toString());
					curbAfterProgress2Thread.process.setShoulderAfterProcess2.points = cloudManage.awaitingProcessCloudLXYZ;
					break;
				case INITIAL_POINTS:
					afterProcess2Dialog->initialPointsLineEdit->setText(curIndex.data().toString());
					curbAfterProgress2Thread.process.setShoulderAfterProcess2.initialPoints = cloudManage.awaitingProcessCloudLXYZ;
					afterProcess2Dialog->buttonBox->setEnabled(true);
					break;
				default:
					break;
				}
			}
		}

	}else if (curIndex.parent().data().toString()=="MulColorCloud")
	{
		QStandardItem* cloudRGBFolder = getCloudRGBFolder();
		if(cloudRGBFolder)
		{
			//addMessage("","","activatemult"+QString::number(curIndex.row()));
			cloudManage.activateCloudRGB(curIndex.row());
		}
	}
}

void MainWindow::updateItem2View()
{
	QModelIndex curIndex=ui.DBTreeView->currentIndex();

	if (curIndex.parent().data().toString()=="UniColorCloud")
	{
		QStandardItem* xyzFolder = getCloudXYZFolder();
		if(xyzFolder)
		{
			cloudManage.activateCloudXYZ(curIndex.row());
			cloudManage.cloud->points.clear();
			cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);
			cloudManage.viewer->updatePointCloud (cloudManage.cloud, "cloud");
			cloudManage.viewer->resetCamera();
			ui.qvtkWidget->update();
		}

	}else if (curIndex.parent().data().toString()=="MulColorCloud")
	{
		QStandardItem* rgbFolder = getCloudRGBFolder();
		if(rgbFolder)
		{
			cloudManage.activateCloudRGB(curIndex.row());
			cloudManage.cloudrgb->points.clear();
			cloudManage.cloudsL2cloudRGB(*cloudManage.awaitingProcessCloudLRGB,cloudManage.cloudrgb);
			cloudManage.viewer->updatePointCloud(cloudManage.cloudrgb,"cloud");
			cloudManage.viewer->resetCamera();
			ui.qvtkWidget->update();
		}
	}	
}

void MainWindow::addItem2View()
{
	QModelIndex curIndex=ui.DBTreeView->currentIndex();

	if (curIndex.parent().data().toString()=="UniColorCloud")
	{
		QStandardItem* xyzFolder = getCloudXYZFolder();
		if(xyzFolder)
		{
			cloudManage.activateCloudXYZ(curIndex.row());
			cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);
			cloudManage.viewer->updatePointCloud (cloudManage.cloud, "cloud");
			cloudManage.viewer->resetCamera();
			ui.qvtkWidget->update();
		}

	}else if (curIndex.parent().data().toString()=="MulColorCloud")
	{
		QStandardItem* rgbFolder = getCloudRGBFolder();
		if(rgbFolder)
		{
			cloudManage.activateCloudRGB(curIndex.row());
			cloudManage.cloudrgb->points.clear();
			cloudManage.cloudsL2cloudRGB(*cloudManage.awaitingProcessCloudLRGB,cloudManage.cloudrgb);
			cloudManage.viewer->updatePointCloud(cloudManage.cloudrgb,"cloud");
			cloudManage.viewer->resetCamera();
			ui.qvtkWidget->update();
		}
	}		
}

void MainWindow::deleteItem()
{
	QModelIndex curIndex=ui.DBTreeView->currentIndex();
	
	if (curIndex.parent().data().toString()=="UniColorCloud")
	{
		QStandardItem* xyzFolder = getCloudXYZFolder();
		if(xyzFolder)
		{
			xyzFolder->removeRow(curIndex.row());
			cloudManage.removeCloudXYZ(curIndex.row());
		}

	}else if (curIndex.parent().data().toString()=="MulColorCloud")
	{
		QStandardItem* rgbFolder = getCloudRGBFolder();
		if(rgbFolder)
		{
			rgbFolder->removeRow(curIndex.row());
			cloudManage.removeCloudRGB(curIndex.row());
		}
	}	
}

void MainWindow::deleteAllItem()
{
	enableAction(false);
	QModelIndex curIndex=ui.DBTreeView->currentIndex();

	if (curIndex.data().toString()=="UniColorCloud")
	{
		QStandardItem* folder=getCloudXYZFolder();
		if(nullptr == folder)
			return ;
		for(int i=folder->rowCount()-1;i>=0;--i)
		{
			folder->removeRow(i);
			cloudManage.removeCloudXYZ(i);
		}

	}else if (curIndex.data().toString()=="MulColorCloud")
	{
		//addMessage("","","DeleteALLItem");
		QStandardItem* folder=getCloudRGBFolder();
		if(nullptr == folder)
			return ;
		for(int i=folder->rowCount()-1;i>=0;--i)
		{
			folder->removeRow(i);
			cloudManage.removeCloudRGB(i);
		}
	}	
}

void MainWindow::exportItem()
{
	QModelIndex curIndex=ui.DBTreeView->currentIndex();

	if (curIndex.parent().data().toString()=="UniColorCloud")
	{
		QStandardItem* xyzFolder = getCloudXYZFolder();
		if(xyzFolder)
		{
			cloudManage.activateCloudXYZ(curIndex.row());
			save();
		}

	}else if (curIndex.parent().data().toString()=="MulColorCloud")
	{
		QStandardItem* rgbFolder = getCloudRGBFolder();
		if(rgbFolder)
		{
			
		}
	}	
}

void MainWindow::exportAllItem()
{
	QModelIndex curIndex=ui.DBTreeView->currentIndex();

	if (curIndex.data().toString()=="UniColorCloud")
	{
		QStandardItem* folder=getCloudXYZFolder();
		if(nullptr == folder)
			return ;
		for(int i=folder->rowCount()-1;i>=0;--i)
		{
			//folder->removeRow(i);
			//cloudManage.removeCloudXYZ(i);
			//addMessage("","","exportUniq");
			cloudManage.activateCloudXYZ(i);
			save();
		}
	}else if (curIndex.data().toString()=="MulColorCloud")
	{
		//addMessage("","","DeleteALLItem");
		QStandardItem* folder=getCloudRGBFolder();
		if(nullptr == folder)
			return ;
		for(int i=folder->rowCount()-1;i>=0;--i)
		{
			//folder->removeRow(i);
			//cloudManage.removeCloudRGB(i);
			addMessage("","","exportMult");
		}
	}	
}

void MainWindow::import2Item()
{
	QModelIndex curIndex=ui.DBTreeView->currentIndex();

	if (curIndex.data().toString()=="UniColorCloud")
	{
		cloudManage.isItemLoadCloud=true;
		open();
		addMessage("","","improtUniq"+curIndex.data().toString());
	}else if (curIndex.data().toString()=="MulColorCloud")
	{
		//addMulColorItem();
		addMessage("","","improtMult"+curIndex.data().toString());
	}
}

void MainWindow::uniItemAdd2MulItem()
{
	QModelIndex curIndex = ui.DBTreeView->currentIndex();

	if (curIndex.data().toString() == "UniColorCloud")
	{
		cloudManage.awaitingProcessCloudLRGB->push_back(*cloudManage.awaitingProcessCloudLXYZ);
		addMessage("", "", "UniAdd2Mul");
	}
}

void MainWindow::newCreateMulItem()
{
	QModelIndex curIndex = ui.DBTreeView->currentIndex();

	if (curIndex.data().toString() == "MulColorCloud")
	{
		list<list<Point>> noPoints;
		cloudManage.cloudsRGBData.push_back(noPoints);
		addMulColorItem("NewMult___");
		addMessage("", "", "NewCreatMul");
	}
}

void MainWindow::setPointColorGradientDirectionX()
{
	cloudManage.setPointColorInX();
	cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

void MainWindow::setPointColorGradientDirectionY()
{
	cloudManage.setPointColorInY();
	cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

void MainWindow::setPointColorGradientDirectionZ()
{
	cloudManage.setPointColorInZ();
	cloudManage.viewer->updatePointCloud (cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}



void MainWindow::transformate()
{
	QDialog dialog(this);
	ftf = new Ui::FormateTransformDialog;
	ftf->setupUi(&dialog);

	connect(ftf->rawPushButton,SIGNAL(clicked()),this,SLOT(openTran()));
	connect(ftf->transPushButton, SIGNAL(clicked()), this, SLOT(saveTran()));
	
	buttonsGroup = new QButtonGroup(this);
	buttonsGroup->addButton(ftf->asciiRadioButton, FORMATE_ASCII);
	buttonsGroup->addButton(ftf->pcdRadioButton, FORMATE_PCD);
	buttonsGroup->addButton(ftf->lasRadioButton, FORMATE_LAS);
	buttonsGroup->addButton(ftf->lazRadioButton, FORMATE_LAZ);
	buttonsGroup->addButton(ftf->dxfRadioButton, FORMATE_DXF);
	
	if (dialog.exec())
	{
		QFileInfo fileInfo = QFileInfo(ftf->rawLineEdit->text());
		QString fileSuffix = fileInfo.suffix();
		
		if (fileSuffix=="txt")
		{
			formatesTransform(FORMATE_ASCII);
		}
		else if (fileSuffix == "pcd")
		{
			formatesTransform(FORMATE_PCD);
		}
		else if (fileSuffix == "las")
		{
			formatesTransform(FORMATE_LAS);
		}
		else if (fileSuffix == "laz")
		{
			formatesTransform(FORMATE_LAZ);
		}
	}
}

void MainWindow::openTran()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open PointCloud"), ".",
		tr("Open all files(*.*)\n"
		"Open PointCloudLibary files(*.pcd)\n"
		"Open las files(*.las)\n"
		"Open laz files(*.laz)\n"
		"Open text files (*.txt)"));
	if (!fileName.isEmpty())
	{
		transfor.fileName1 = fileName.toStdString();
		ftf->rawLineEdit->setText(fileName);
		ftf->transPushButton->setEnabled(true);
		ftf->transLineEdit->setEnabled(true);
	}
	else
	{
		transfor.fileName1 = "";
	}
}
void MainWindow::saveTran()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Save PointCloud"), ".",
		tr("Save all files(*.*)\n"
		"Save PointCloudLibary files(*.pcd)\n"
		"Save las files(*.las)\n"
		"Save laz files(*.laz)\n"
		"Save text files (*.txt)"));
	if (!fileName.isEmpty())
	{
		transfor.fileName2 = fileName.toStdString();
		ftf->transLineEdit->setText(fileName);
		ftf->asciiRadioButton->setEnabled(true);
		ftf->lasRadioButton->setEnabled(true);
		ftf->lazRadioButton->setEnabled(true);
		ftf->pcdRadioButton->setEnabled(true);
		ftf->dxfRadioButton->setEnabled(true);
	}
	else
	{
		transfor.fileName2 = "";
	}
}

void MainWindow::formatesTransform(int RAWFORMATE)
{
	switch (buttonsGroup->checkedId())
	{	
	case FORMATE_ASCII:
		{
			  switch (RAWFORMATE)
			  {
			  case FORMATE_ASCII:
				  addMessage("", "txt", "ascii");
				  break;
			  case FORMATE_PCD:
				  addMessage("", "pcd", "ascii");
				  break;
			  case FORMATE_LAS:
				  addMessage("", "las", "ascii");
				  break;
			  case FORMATE_LAZ:
				  addMessage("", "laz", "ascii");
				  break;
			  default:
				  break;
			  }
			  
			  break;
		}
	case FORMATE_PCD:
		{
			  switch (RAWFORMATE)
			  {
			  case FORMATE_ASCII:
				  addMessage("", "txt", "pcd");
				  break;
			  case FORMATE_PCD:
				  addMessage("", "pcd", "pcd");
				  break;
			  case FORMATE_LAS:
				  addMessage("", "las", "pcd");
				  break;
			  case FORMATE_LAZ:
				  addMessage("", "laz", "pcd");
				  break;
			  default:
				  break;
			  }

			  break;
		}
	case FORMATE_LAS:
		{
			  switch (RAWFORMATE)
			  {
			  case FORMATE_ASCII:
				  addMessage("", "txt", "las");
				  break;
			  case FORMATE_PCD:
				  addMessage("", "pcd", "las");
				  break;
			  case FORMATE_LAS:
				  addMessage("", "las", "las");
				  break;
			  case FORMATE_LAZ:
				  addMessage("", "laz", "las");
				  break;
			  default:
				  break;
			  }

			  break;
		}
	case FORMATE_LAZ:
		{
			  switch (RAWFORMATE)
			  {
			  case FORMATE_ASCII:
				  addMessage("", "txt", "laz");
				  break;
			  case FORMATE_PCD:
				  addMessage("", "pcd", "laz");
				  break;
			  case FORMATE_LAS:
				  addMessage("", "las", "laz");
				  break;
			  case FORMATE_LAZ:
				  addMessage("", "laz", "laz");
				  break;
			  default:
				  break;
			  }

			  break;
		}
	case FORMATE_DXF:
		{
			switch (RAWFORMATE)
			{
			case FORMATE_ASCII:
				//addMessage("", "txt", "dxf");
				//addMessage("", ftf->rawLineEdit->text(), ftf->transLineEdit->text());
			{
				Cass cass;
				cass.txtFilePath = ftf->rawLineEdit->text().toStdString();
				cass.dxfFilePath = ftf->transLineEdit->text().toStdString();
				cass.initialDxf();
				cass.txt2dxf();
				break;
			}
				
			default:
				break;
			}
		}
	default:
		break;
	}

}

void MainWindow::computeResolution()
{
	cloudManage.cloud->points.clear();
	cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.cloud);

	resolutionThread.process.setComResolution.cloud = &cloudManage.cloud;
	resolutionThread.process.choice_ = ClOUD_RESOLUTION;
	resolutionThread.process.setComResolution.res = &res;
	if (resolutionThread.isRunning())
	{
	}
	else
	{
		resolutionThread.start();
		ui.actionCloudResolution->setEnabled(false);
		addMessage("", "CloudResolution", "Is Running... ..." );
	}
}

void MainWindow::setActionResolution(bool _bool)
{
	ui.actionCloudResolution->setEnabled(_bool);
	addMessage("", "CloudResolution", "Complete.  "+QString("Resolution=[")+QString::number(res)+"]");	
}

void MainWindow::onEstimatingNormals()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::RadiusSearchDialog radiusSearchDialog;
		radiusSearchDialog.setupUi(&dialog);
		if (dialog.exec())
		{
			cloudManage.cloud->points.clear();
			cloudManage.cloudL2cloud(*cloudManage.awaitingProcessCloudLXYZ, cloudManage.cloud);
			estimateNormalsThread.process.setEstimateNormals.cloud = &cloudManage.cloud;
			estimateNormalsThread.process.choice_ = ESTIMAT_NORMALS;
			estimateNormalsThread.process.setEstimateNormals.cloud_normals = &cloudManage.cloud_normals;
			//cloudManage.cloud_normals->points.clear();
			estimateNormalsThread.process.setEstimateNormals.alg.radius = radiusSearchDialog.doubleSpinBox->value();
			cloudManage.levels = radiusSearchDialog.levelSpinBox->value();
			cloudManage.scales = radiusSearchDialog.scaleDoubleSpinBox->value();
			if (estimateNormalsThread.isRunning())
			{

			}
			else
			{
				estimateNormalsThread.start();
				ui.actionEstimatingNormals->setEnabled(false);
				addMessage("", "EstimatingTheNormals", "Is Running... ...");
			}
		}
	}
	ui.actionEstimatingNormals->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onSetActionEstimateNormals(bool _bool)
{
	ui.actionEstimatingNormals->setEnabled(_bool);
	addMessage("", "EstimatingTheNormals", "Complete.");
	
	//cloudManage.cloudsRGBData.push_back(cloudManage.cloudLRGBData);
	//addMulColorItem();
	
	cloudManage.viewer->addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloudManage.cloud, cloudManage.cloud_normals, cloudManage.levels, cloudManage.scales, "normals");
	ui.qvtkWidget->update();
	cloudManage.cloud_normals->points.clear();
	
}

void MainWindow::onRegiongrowRansac()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::RegionGrowDialog regionGrowDialog;
		regionGrowDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("RegionGrowRANSAC"));
		if (dialog.exec())
		{
			cloudManage.awaitingProecssCloudlzf.clear();
			cloudManage.cloudL2cloudlzf(*cloudManage.awaitingProcessCloudLXYZ, cloudManage.awaitingProecssCloudlzf);
			regionGrowRansacThread.process.choice_ = REGIONGROW_RANSAC;
			regionGrowRansacThread.process.setRegionGrow.seg.setInputCloud(cloudManage.awaitingProecssCloudlzf);
			regionGrowRansacThread.process.setRegionGrow.seg.setKNearest(regionGrowDialog.kSpinBox->value());
			regionGrowRansacThread.process.setRegionGrow.seg.setRadius(regionGrowDialog.radiusDoubleSpinBox->value());
			regionGrowRansacThread.process.setRegionGrow.seg.setThreshold(regionGrowDialog.thrDoubleSpinBox->value());
			if (regionGrowRansacThread.isRunning())
			{

			}
			else
			{
				regionGrowRansacThread.start();
				ui.actionRegionGrowingRansac->setEnabled(false);
				addMessage("", "RegionGrowingSegment", "Is Running... ...");
			}
		}
	}
	ui.actionRegionGrowingRansac->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onRegiongrowBaysac()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::RegionGrowDialog regionGrowDialog;
		regionGrowDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("RegionGrowBAYSAC"));
		if (dialog.exec())
		{
			cloudManage.awaitingProecssCloudlzf.clear();
			cloudManage.cloudL2cloudlzf(*cloudManage.awaitingProcessCloudLXYZ, cloudManage.awaitingProecssCloudlzf);
			regionGrowBaysacThread.process.choice_ = REGIONGROW_BAYSAC;
			regionGrowBaysacThread.process.setRegionGrow.seg.setInputCloud(cloudManage.awaitingProecssCloudlzf);
			regionGrowBaysacThread.process.setRegionGrow.seg.setKNearest(regionGrowDialog.kSpinBox->value());
			regionGrowBaysacThread.process.setRegionGrow.seg.setRadius(regionGrowDialog.radiusDoubleSpinBox->value());
			regionGrowBaysacThread.process.setRegionGrow.seg.setThreshold(regionGrowDialog.thrDoubleSpinBox->value());
			if (regionGrowBaysacThread.isRunning())
			{

			}
			else
			{
				regionGrowBaysacThread.start();
				ui.actionBaySAC->setEnabled(false);
				addMessage("", "RegionGrowingSegment", "Is Running... ...");
			}
		}
	}
	ui.actionBaySAC->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onRegiongrowBayLmeds()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::RegionGrowDialog regionGrowDialog;
		regionGrowDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("RegionGrowBAYLMEDS"));
		if (dialog.exec())
		{
			cloudManage.awaitingProecssCloudlzf.clear();
			cloudManage.cloudL2cloudlzf(*cloudManage.awaitingProcessCloudLXYZ, cloudManage.awaitingProecssCloudlzf);
			regionGrowBayLmedsThread.process.choice_ = REGIONGROW_BAYLMEDS;
			regionGrowBayLmedsThread.process.setRegionGrow.seg.setInputCloud(cloudManage.awaitingProecssCloudlzf);
			regionGrowBayLmedsThread.process.setRegionGrow.seg.setKNearest(regionGrowDialog.kSpinBox->value());
			regionGrowBayLmedsThread.process.setRegionGrow.seg.setRadius(regionGrowDialog.radiusDoubleSpinBox->value());
			regionGrowBayLmedsThread.process.setRegionGrow.seg.setThreshold(regionGrowDialog.thrDoubleSpinBox->value());
			if (regionGrowBayLmedsThread.isRunning())
			{

			}
			else
			{
				regionGrowBayLmedsThread.start();
				ui.actionBAYLMEDS->setEnabled(false);
				addMessage("", "RegionGrowingSegment", "Is Running... ...");
			}
		}
	}
	ui.actionBAYLMEDS->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::setActionRegRansac(bool _bool)
{
	ui.actionRegionGrowingRansac->setEnabled(_bool);
	addMessage("", "RegionGrowingSegment", "Complete.");
	cloudManage.cloudLRGBData.clear();
	cloudManage.cloudVRGB2cloudLRGB(regionGrowRansacThread.process.setRegionGrow.seg.indices,cloudManage.cloudLRGBData);
	regionGrowRansacThread.process.setRegionGrow.seg.indices.clear();
	cloudManage.cloudsRGBData.push_back(cloudManage.cloudLRGBData);
	addMulColorItem();
	cloudManage.cloudrgb->points.clear();
	cloudManage.cloudsL2cloudRGB(cloudManage.cloudLRGBData, cloudManage.cloudrgb);
	cloudManage.viewer->updatePointCloud(cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

void MainWindow::setActionRegBaysac(bool _bool)
{
	ui.actionBaySAC->setEnabled(_bool);
	addMessage("", "RegionGrowingSegment", "Complete.");
	cloudManage.cloudLRGBData.clear();
	cloudManage.cloudVRGB2cloudLRGB(regionGrowBaysacThread.process.setRegionGrow.seg.indices, cloudManage.cloudLRGBData);
	regionGrowBaysacThread.process.setRegionGrow.seg.indices.clear();
	cloudManage.cloudsRGBData.push_back(cloudManage.cloudLRGBData);
	addMulColorItem();
	cloudManage.cloudrgb->points.clear();
	cloudManage.cloudsL2cloudRGB(cloudManage.cloudLRGBData, cloudManage.cloudrgb);
	cloudManage.viewer->updatePointCloud(cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

void MainWindow::setActionRegBayLmeds(bool _bool)
{
	ui.actionBAYLMEDS->setEnabled(_bool);
	addMessage("", "RegionGrowingSegment", "Complete.");
	cloudManage.cloudLRGBData.clear();
	cloudManage.cloudVRGB2cloudLRGB(regionGrowBayLmedsThread.process.setRegionGrow.seg.indices, cloudManage.cloudLRGBData);
	regionGrowBayLmedsThread.process.setRegionGrow.seg.indices.clear();
	cloudManage.cloudsRGBData.push_back(cloudManage.cloudLRGBData);
	addMulColorItem();
	cloudManage.cloudrgb->points.clear();
	cloudManage.cloudsL2cloudRGB(cloudManage.cloudLRGBData, cloudManage.cloudrgb);
	cloudManage.viewer->updatePointCloud(cloudManage.cloudrgb, "cloud");
	cloudManage.viewer->resetCamera();
	ui.qvtkWidget->update();
}

void MainWindow::appLock()
{
	appLockFileName = "C:\\Windows\\winsystempcui.ini";
	
	getNetDateTime();
	QDateTime currentTime = QDateTime::currentDateTime();
	QDateTime endTime(QDate(2016, 6, 1));
	//addMessage("", "", QString::number(endTime.daysTo(currentTime)));
	if (currentTime.daysTo(endTime) >= 0&&firstRunFile()) //endTime-currentTime
	{
		this->setWindowTitle(QString("PointCloudUI2.0") + QString("  Final Date[") + QString::number(currentTime.daysTo(endTime)) + QString("]"));
		appLockb = true;	
	}
	else
	{
		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(close()));
		appLockb = false;
		int r = QMessageBox::warning(this, tr("UsingTimeEnd!"),
			tr("Please contact productor?"),
			QMessageBox::Close);
		if (r == QMessageBox::Close) {
			
			timer->start(2000);
		}
		else{
			timer->start(2000);
		}
	}
}

bool MainWindow::firstRunFile()
{	
	QFile file(appLockFileName);
	QDateTime firstRunTime;
	if (file.exists())
	{
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);
		in.setVersion(QDataStream::Qt_5_5);
		in >> firstRunTime;
		file.close();
		//addMessage("", "", firstRunTime.toString("yyyy|MM|dd"));

		if (firstRunTime.daysTo(QDateTime::currentDateTime())>=0)
		{
			writeCurrentDate(appLockFileName);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		writeCurrentDate(appLockFileName);
		return true;
	}
}

void MainWindow::writeCurrentDate(QString &fileName)
{
	QFile file(fileName);
	QDateTime firstRunTime = QDateTime::currentDateTime();
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_5_5);
	out << firstRunTime;
	file.close();
}

//void MainWindow::addAction2Group()
//{
	/*toolsActionGroup = new QActionGroup(this);
	toolsActionGroup->addAction(ui.actionTranslate);
	toolsActionGroup->addAction(ui.actionCloudResolution);
	toolsActionGroup->addAction(ui.actionEstimatingNormals);

	pclActionGroup = new QActionGroup(this);
	pclActionGroup->addAction(ui.actionPassThrough);
	pclActionGroup->addAction(ui.actionStatisticalOutlierRemoval);
	pclActionGroup->addAction(ui.actionRadiusOutlier);
	pclActionGroup->addAction(ui.actionDownSamplingVoxelGrid);
	pclActionGroup->addAction(ui.actionEuclideanCluster);

	segmentActionGroup = new QActionGroup(this);
	segmentActionGroup->addAction(ui.actionRANSAC);
	segmentActionGroup->addAction(ui.actionRegionGrowingRansac);
	segmentActionGroup->addAction(ui.actionBaySAC);
	segmentActionGroup->addAction(ui.actionBAYLMEDS);
	segmentActionGroup->addAction(ui.actionSurfaceGrow);

	simpleActionGroup = new QActionGroup(this);
	simpleActionGroup->addAction(ui.actionSimple);
	simpleActionGroup->addAction(ui.actionFeaturePoints);
	simpleActionGroup->addAction(ui.actionPCA);
	simpleActionGroup->addAction(ui.actionContour);

	optionsActionGroup = new QActionGroup(this);
	optionsActionGroup->addAction(ui.actionPointSize);
	optionsActionGroup->addAction(ui.actionDirectionX);
	optionsActionGroup->addAction(ui.actionDirectionY);
	optionsActionGroup->addAction(ui.actionDirectionZ);
	optionsActionGroup->addAction(ui.actionUnique_Color);
	optionsActionGroup->addAction(ui.actionPointSize);

	polesExtractActionGroup = new QActionGroup(this);
	polesExtractActionGroup->addAction(ui.actioPolesExtact);
	polesExtractActionGroup->addAction(ui.actionComputeCenterofPoles);
	polesExtractActionGroup->addAction(ui.actionStatisticPolesNum);*/
//}

void MainWindow::getNetDateTime()
{
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	reply = manager->get(QNetworkRequest(QUrl("http://open.baidu.com/special/time/")));
	connect(reply, SIGNAL(finished()), this, SLOT(readTime()));
}

void MainWindow::readTime()
{
	QRegExp rx("window.baidu_time\\((.+)\\)");
	do{
		int pos = QString::fromUtf8(reply->readLine()).indexOf(rx);
		if (pos >= 0){
			netDateTime = new QDateTime;
			*netDateTime = QDateTime::fromMSecsSinceEpoch(rx.cap(1).toLongLong());
			//addMessage("", "", netDateTime->toString("yyyy.MM.dd"));

			QFile file(appLockFileName);
			file.open(QIODevice::WriteOnly);
			QDataStream out(&file);
			out.setVersion(QDataStream::Qt_5_5);
			out << *netDateTime;
			file.close();

			break;
		}
	} while (!reply->atEnd());
	reply->deleteLater();
	reply = NULL;
}

void MainWindow::onPolesExtract()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::PolesExtractDialog polesExtractDialog;
		polesExtractDialog.setupUi(&dialog);
		if (dialog.exec())
		{
			polesExtractThread.process.setPolesExtract.points = cloudManage.awaitingProcessCloudLXYZ;
			cloudManage.processCloudLXYZ.clear();
			polesExtractThread.process.setPolesExtract.polesPoints = &cloudManage.processCloudLXYZ;
			polesExtractThread.process.choice_ = POLES_EXTRAT;
			polesExtractThread.process.setPolesExtract.polesExtract.a = polesExtractDialog.voxelSidesDoubleSpinBox->value();
			polesExtractThread.process.setPolesExtract.polesExtract.b = polesExtractDialog.voxelSidesDoubleSpinBox->value();
			polesExtractThread.process.setPolesExtract.polesExtract.c = polesExtractDialog.voxelSidesDoubleSpinBox->value();
			polesExtractThread.process.setPolesExtract.polesExtract.deta_h = polesExtractDialog.thrHDoubleSpinBox->value();
			polesExtractThread.process.setPolesExtract.polesExtract.spacenumber = polesExtractDialog.spaceNumberSpinBox->value();
			polesExtractThread.process.setPolesExtract.polesExtract.pitch = polesExtractDialog.pitchSpinBox->value();

			if (polesExtractThread.isRunning())
			{
			}
			else
			{
				polesExtractThread.start();
				ui.actioPolesExtact->setEnabled(false);
				addMessage("", "PolesExtract", "Is Running... ...");
			}
		}

	}
	ui.actioPolesExtact->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onSetActionPolesExtract(bool _bool)
{
	ui.actioPolesExtact->setEnabled(_bool);
	addMessage("", "PolesExtract", "Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	cloudManage.processCloudLXYZ.clear();
	addUniColorItem("ExtrPolesPs");
}

void MainWindow::onStatisticPolesNum()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::PolesDialog polesDialog;
		polesDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("StatisticPolesNum"));
		if (dialog.exec())
		{
			statisticPolesNumThread.process.setStatisticPolesNumClassify.points = cloudManage.awaitingProcessCloudLXYZ;
			cloudManage.processCloudLXYZ.clear();
			statisticPolesNumThread.process.setStatisticPolesNumClassify.polesPoints = &cloudManage.processCloudLRGB;
			statisticPolesNumThread.process.choice_ =STATISTIC_POLESNUM_CLASSIFY;
			statisticPolesNumThread.process.setStatisticPolesNumClassify.polesStatisticClassify.a = polesDialog.VoxelSideDoubleSpinBox->value();
			statisticPolesNumThread.process.setStatisticPolesNumClassify.polesStatisticClassify.b = polesDialog.VoxelSideDoubleSpinBox->value();
			statisticPolesNumThread.process.setStatisticPolesNumClassify.polesStatisticClassify.c = polesDialog.VoxelSideDoubleSpinBox->value();
			statisticPolesNumThread.process.setStatisticPolesNumClassify.polesStatisticClassify.h1 = polesDialog.H1DoubleSpinBox->value();
			statisticPolesNumThread.process.setStatisticPolesNumClassify.polesStatisticClassify.h2 = polesDialog.H2DoubleSpinBox->value();
			statisticPolesNumThread.process.setStatisticPolesNumClassify.polesStatisticClassify.h3 = polesDialog.H3DoubleSpinBox->value();
		
			if (statisticPolesNumThread.isRunning())
			{
			}
			else
			{
				statisticPolesNumThread.start();
				ui.actionStatisticPolesNum->setEnabled(false);
				addMessage("", "StatisticPolesNum", "Is Running... ...");
			}
		}

	}
	ui.actionStatisticPolesNum->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onSetActionStatisticPolesNum(bool _bool)
{
	ui.actionStatisticPolesNum->setEnabled(_bool);
	addMessage("", "StatisticPolesNum", "Complete.");
	for (list<list<Point>>::iterator it = cloudManage.processCloudLRGB.begin(); it != cloudManage.processCloudLRGB.end();++it)
	{
		cloudManage.cloudXYZData.push_back(*it);
		addUniColorItem("StaPoleNum");
	}
	
	cloudManage.processCloudLRGB.clear();
	
}

void MainWindow::onComputeCenterofPoles()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::PolesDialog polesDialog;
		polesDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("ComputeCenterofPoles"));
		if (dialog.exec())
		{
			
			computeCenterofPolesThread.process.setComputeCenter.points = cloudManage.awaitingProcessCloudLXYZ;
			cloudManage.processCloudLRGB.clear();
			computeCenterofPolesThread.process.setComputeCenter.polesPoints = &cloudManage.processCloudLRGB;
			computeCenterofPolesThread.process.choice_ = COMPUTE_COORDOFPOLES;
			computeCenterofPolesThread.process.setComputeCenter.polesComputeCenter.a = polesDialog.VoxelSideDoubleSpinBox->value();
			computeCenterofPolesThread.process.setComputeCenter.polesComputeCenter.b = polesDialog.VoxelSideDoubleSpinBox->value();
			computeCenterofPolesThread.process.setComputeCenter.polesComputeCenter.c = polesDialog.VoxelSideDoubleSpinBox->value();
			computeCenterofPolesThread.process.setComputeCenter.polesComputeCenter.h1 = polesDialog.H1DoubleSpinBox->value();
			computeCenterofPolesThread.process.setComputeCenter.polesComputeCenter.h2 = polesDialog.H2DoubleSpinBox->value();
			computeCenterofPolesThread.process.setComputeCenter.polesComputeCenter.h3 = polesDialog.H3DoubleSpinBox->value();

			if (computeCenterofPolesThread.isRunning())
			{
			}
			else
			{
				computeCenterofPolesThread.start();
				ui.actionComputeCenterofPoles->setEnabled(false);
				addMessage("", "StatisticPolesNum", "Is Running... ...");
			}
		}

	}
	ui.actionComputeCenterofPoles->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onSetActionComputeCenterofPoles(bool _bool)
{
	ui.actionComputeCenterofPoles->setEnabled(_bool);
	addMessage("", "ComputeCenterofPoles", "Complete.");
	for (list<list<Point>>::iterator it = cloudManage.processCloudLRGB.begin(); it != cloudManage.processCloudLRGB.end(); ++it)
	{
		cloudManage.cloudXYZData.push_back(*it);
		addUniColorItem("CompCenter");
	}
	cloudManage.processCloudLRGB.clear();
}

void MainWindow::enableActionThread(CloudThread &cloudThread, QAction &action)
{
	if (cloudThread.isRunning())
	{
		action.setEnabled(false);
	}
}

void MainWindow::onClearAllData()
{
	cloudManage.clearAllData();
}

void MainWindow::onGroundFilter()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::LeafSizeDialog uiDialog;
		uiDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("GroundFilter"));
		uiDialog.highDoubleSpinBox->setValue(1);
		uiDialog.longDoubleSpinBox->setValue(1);
		uiDialog.widthDoubleSpinBox->setValue(1);
		if (dialog.exec())
		{
			groundFilterThread.process.setGroundFilter.points = cloudManage.awaitingProcessCloudLXYZ;
			cloudManage.processCloudLXYZ.clear();
			cloudManage.processCloudLXYZ2.clear();
			groundFilterThread.process.setGroundFilter.groundPoints = &cloudManage.processCloudLXYZ;
			groundFilterThread.process.setGroundFilter.onGroundPoints = &cloudManage.processCloudLXYZ2;
			groundFilterThread.process.choice_ = GET_GROUND_INFO;
			groundFilterThread.process.setGroundFilter.groundfilter.h = uiDialog.highDoubleSpinBox->value();
			groundFilterThread.process.setGroundFilter.groundfilter.l = uiDialog.longDoubleSpinBox->value();
			groundFilterThread.process.setGroundFilter.groundfilter.w = uiDialog.widthDoubleSpinBox->value();

			if (groundFilterThread.isRunning())
			{
			}
			else
			{
				groundFilterThread.start();
				ui.actionGroundFilter->setEnabled(false);
				addMessage("", "GroundFilter", "Is Running... ...");
			}
		}
	}
	ui.actionGroundFilter->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onSetActionGroundFilter(bool _bool)
{
	ui.actionGroundFilter->setEnabled(_bool);
	addMessage("", "GroundFilter", "Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("GroundPs___");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ2);
	addUniColorItem("OnGroundPs");
	cloudManage.processCloudLXYZ.clear();
	cloudManage.processCloudLXYZ2.clear();
}

void MainWindow::onExtractCurbPoints()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::ExtractShoulderDialog uiDialog;
		uiDialog.setupUi(&dialog);
		if (dialog.exec())
		{
			extractCurbThread.process.setRoadShoulder.points = cloudManage.awaitingProcessCloudLXYZ;
			cloudManage.processCloudLXYZ.clear();
			extractCurbThread.process.setRoadShoulder.shoulderPoints = &cloudManage.processCloudLXYZ;
			extractCurbThread.process.choice_ = ROAD_SHOULDER;
			extractCurbThread.process.setRoadShoulder.roadShoulder.h = uiDialog.voxelSidesDoubleSpinBox->value();
			extractCurbThread.process.setRoadShoulder.roadShoulder.l = uiDialog.voxelSidesDoubleSpinBox->value();
			extractCurbThread.process.setRoadShoulder.roadShoulder.m = uiDialog.voxelSidesDoubleSpinBox->value();
			extractCurbThread.process.setRoadShoulder.roadShoulder.thr1 = uiDialog.thr1DoubleSpinBox->value();
			extractCurbThread.process.setRoadShoulder.roadShoulder.thr2 = uiDialog.thr2DoubleSpinBox->value();

			if (groundFilterThread.isRunning())
			{
			}
			else
			{
				extractCurbThread.start();
				ui.actionExtractCurb->setEnabled(false);
				addMessage("", "ExtractCurb", "Is Running... ...");
			}
		}
	}
	ui.actionExtractCurb->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onAfterProgress1()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		QDialog dialog(this);
		Ui::ExtractShoulderDialog uiDialog;
		uiDialog.setupUi(&dialog);
		dialog.setWindowTitle(tr("AfterProgress1"));
		uiDialog.voxelSidesDoubleSpinBox->setValue(0.2);
		uiDialog.voxelSidesDoubleSpinBox->setValue(0.2);
		uiDialog.voxelSidesDoubleSpinBox->setValue(0.2);
		if (dialog.exec())
		{
			curbAfterProgress1Thread.process.setShoulderAfterProcess1.points = cloudManage.awaitingProcessCloudLXYZ;
			cloudManage.processCloudLXYZ.clear();
			curbAfterProgress1Thread.process.setShoulderAfterProcess1.shoulderPoints = &cloudManage.processCloudLXYZ;
			curbAfterProgress1Thread.process.choice_ = SHOULD_AFTER_PROCESS1;
			curbAfterProgress1Thread.process.setShoulderAfterProcess1.roadShoulder.h = uiDialog.voxelSidesDoubleSpinBox->value();
			curbAfterProgress1Thread.process.setShoulderAfterProcess1.roadShoulder.l = uiDialog.voxelSidesDoubleSpinBox->value();
			curbAfterProgress1Thread.process.setShoulderAfterProcess1.roadShoulder.m = uiDialog.voxelSidesDoubleSpinBox->value();
			curbAfterProgress1Thread.process.setShoulderAfterProcess1.roadShoulder.thr1 = uiDialog.thr1DoubleSpinBox->value();
			curbAfterProgress1Thread.process.setShoulderAfterProcess1.roadShoulder.thr2 = uiDialog.thr2DoubleSpinBox->value();

			if (curbAfterProgress1Thread.isRunning())
			{
			}
			else
			{
				curbAfterProgress1Thread.start();
				ui.actionAfterProgress1->setEnabled(false);
				addMessage("", "AfterProgress1", "Is Running... ...");
			}
		}
	}
	ui.actionAfterProgress1->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onAfterProgress2()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		if (!afterParentDialog)
		{
			afterParentDialog = new QDialog(this);
			afterProcess2Dialog = new Ui::AfterProcess2Dialog;
			afterProcess2Dialog->setupUi(afterParentDialog);
			afterProcessButtonsGroup = new QButtonGroup(this);
			afterProcessButtonsGroup->addButton(afterProcess2Dialog->initalShoulderRadioButton, INITIAL_SHOULDER_POINTS);
			afterProcessButtonsGroup->addButton(afterProcess2Dialog->initialPointsRadioButton, INITIAL_POINTS);
			//afterProcessButtonsGroup->checkedId();
			afterProcess2Dialog->buttonBox->setEnabled(false);
		}
		afterParentDialog->show();
		afterParentDialog->raise();
		afterParentDialog->activateWindow();
		curbAfterProgress2Thread.process.setShoulderAfterProcess2.points;
		curbAfterProgress2Thread.process.setShoulderAfterProcess2.initialPoints;
		connect(afterProcess2Dialog->buttonBox, SIGNAL(accepted()), this, SLOT(onAfterProcessButtonBoxOK()));
				
	}
	ui.actionAfterProgress2->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onSetActionExtractCurbPoints(bool _bool)
{
	ui.actionExtractCurb->setEnabled(_bool);
	addMessage("", "ExtractCurb", "Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("ExtrCurPs_");	
	cloudManage.processCloudLXYZ.clear();
}

void MainWindow::onSetActionAfterProgress1(bool _bool)
{
	ui.actionAfterProgress1->setEnabled(_bool);
	addMessage("", "AfterProgress1", "Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("AfterProceI");
	cloudManage.processCloudLXYZ.clear();
}

void MainWindow::onSetActionAfterProgress2(bool _bool)
{
	ui.actionAfterProgress2->setEnabled(_bool);
	addMessage("", "AfterProgressII", "Complete.");
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addUniColorItem("AfterProceII");
	cloudManage.processCloudLXYZ.clear();
}

void MainWindow::onAfterProcessButtonBoxOK()
{
	cloudManage.processCloudLXYZ.clear();
	curbAfterProgress2Thread.process.setShoulderAfterProcess2.shoulderPoints = &cloudManage.processCloudLXYZ;
	curbAfterProgress2Thread.process.choice_ = SHOULD_AFTER_PROCESS2;
	curbAfterProgress2Thread.process.setShoulderAfterProcess2.roadShoulder.h = afterProcess2Dialog->voxelSidesDoubleSpinBox->value();
	curbAfterProgress2Thread.process.setShoulderAfterProcess2.roadShoulder.l = afterProcess2Dialog->voxelSidesDoubleSpinBox->value();
	curbAfterProgress2Thread.process.setShoulderAfterProcess2.roadShoulder.m = afterProcess2Dialog->voxelSidesDoubleSpinBox->value();
	curbAfterProgress2Thread.process.setShoulderAfterProcess2.roadShoulder.thr1 = afterProcess2Dialog->thr1DoubleSpinBox->value();
	curbAfterProgress2Thread.process.setShoulderAfterProcess2.roadShoulder.thr2 = afterProcess2Dialog->thr2DoubleSpinBox->value();

	if (curbAfterProgress2Thread.isRunning())
	{
	}
	else
	{
		curbAfterProgress2Thread.start();
		ui.actionAfterProgress2->setEnabled(false);
		addMessage("", "AfterProgressII", "Is Running... ...");
	}
}

void MainWindow::onExtractBuild()
{
	if (cloudManage.activateXYZNum >= 0)
	{
		if (!extractBuildDialog)
		{
			extractBuildDialog = new Ui::ExtractBuildDialog;
			
		}
		QDialog dialog(this);
		extractBuildDialog->setupUi(&dialog);
		if (dialog.exec())
		{
			extractBuildThread.process.setExtractBuild.points = cloudManage.awaitingProcessCloudLXYZ;
			extractBuildThread.process.setExtractBuild.buildPoints = &cloudManage.processCloudLRGB;
			cloudManage.processCloudLRGB.clear();
			extractBuildThread.process.choice_ = EXTRACT_BUILDING;
			extractBuildThread.process.setExtractBuild.extractBuild.GSD_ = extractBuildDialog->GSDDoubleSpinBox->value();
			extractBuildThread.process.setExtractBuild.extractBuild.erfa_ = extractBuildDialog->erfaDoubleSpinBox->value();
			extractBuildThread.process.setExtractBuild.extractBuild.beta_ = 1 - extractBuildDialog->erfaDoubleSpinBox->value();
			
			if (!extractBuildThread.isRunning())
			{
				extractBuildThread.start();
				ui.actionBuildExtract->setEnabled(false);
				addMessage("", "BuildExtract", "Is Running... ...");
			}
		}
	}
	ui.actionBuildExtract->setEnabled(false);
	cloudManage.activateXYZNum = -1;
}

void MainWindow::onSetActionExtractBuild(bool _bool)
{
	ui.actionBuildExtract->setEnabled(_bool);
	addMessage("", "BuildExtract", "Complete.");
	cloudManage.cloudsRGBData.push_back(cloudManage.processCloudLRGB);
	addMulColorItem();

	for (list<list<Point>>::iterator it = cloudManage.processCloudLRGB.begin(); it != cloudManage.processCloudLRGB.end();++it)
	{
		cloudManage.cloudXYZData.push_back(*it);
		addUniColorItem("ExtraBuild");
	}
	cloudManage.processCloudLRGB.clear();
}

void MainWindow::onAfterProgress3()
{
	RoadShoulder rs;
	cloudManage.processCloudLXYZ.clear();
	addMessage("", "AfterProgressIII", "Is Running... ...");
	rs.cassRoad(*cloudManage.awaitingProcessCloudLXYZ, cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addMessage("", "AfterProgressIII", "Complete.");
	addUniColorItem("AfterProceIII");
	cloudManage.processCloudLXYZ.clear();
}

void MainWindow::onChouXiRoadPoints()
{
	RoadShoulder rs;
	cloudManage.processCloudLXYZ.clear();
	addMessage("", "ChouXi", "Is Running... ...");
	rs.chouxi(*cloudManage.awaitingProcessCloudLXYZ, cloudManage.processCloudLXYZ);
	cloudManage.cloudXYZData.push_back(cloudManage.processCloudLXYZ);
	addMessage("", "ChouXi", "Complete.");
	addUniColorItem("ChouXiPs__");
	cloudManage.processCloudLXYZ.clear();
}

void MainWindow::onSortRoadPoints()
{
	RoadShoulder rs;
	cloudManage.processCloudLXYZ.clear();
	addMessage("", "Sort", "Is Running... ...");
	rs.sortPointClouds(*cloudManage.awaitingProcessCloudLXYZ);
	cloudManage.cloudXYZData.push_back(*cloudManage.awaitingProcessCloudLXYZ);
	addMessage("", "Sort", "Complete.");
	addUniColorItem("SortRoadPs");
}

void MainWindow::onOutRoadPoints()
{
	outBeforeDXF(SHOULDER_);
}

void MainWindow::onComputeCornerPoints()
{
	//ExtractBuildFootPoints extractFootPoints;

	//cloudManage.awaitingProcessCloudVXYZ.clear();
	//cloudManage.awaitingProcessCloudVXYZ2.clear();
	//cloudManage.cloudL2cloudV(*cloudManage.awaitingProcessCloudLXYZ,cloudManage.awaitingProcessCloudVXYZ);
	//extractFootPoints.extractFootPoints(cloudManage.awaitingProcessCloudVXYZ, cloudManage.awaitingProcessCloudVXYZ2);
	//cloudManage.processCloudLXYZ.clear();
	//cloudManage.cloudV2cloudL(cloudManage.awaitingProcessCloudVXYZ2, cloudManage.processCloudLXYZ);
	//cloudManage.awaitingProcessCloudVXYZ2.clear();
	//addUniColorItem("BuildFoots");
}

void MainWindow::onOutAnglePoints()
{
	outBeforeDXF(HOUSE_);
}

void MainWindow::onOutPolesPoints()
{
	QDialog dialog(this);
	Ui::ChoiceOutDialog uiDialog;
	uiDialog.setupUi(&dialog);
	QButtonGroup buttonsGroups;
	if (dialog.exec())
	{
		buttonsGroups.addButton(uiDialog.treeRadioButton, TREE_);
		buttonsGroups.addButton(uiDialog.lightRadioButton, LIGHT_);
		buttonsGroups.addButton(uiDialog.electRadioButton, ELECT_);
		buttonsGroups.addButton(uiDialog.othersRadioButton, OTHER_);
		switch (buttonsGroups.checkedId())
		{
		case TREE_:
			outBeforeDXF(TREE_);
			break;
		case LIGHT_:
			outBeforeDXF(LIGHT_);
			break;
		case ELECT_:
			outBeforeDXF(ELECT_);
			break;
		case OTHER_:
			outBeforeDXF(OTHER_);
			break;
		default:
			break;
		}
	}	
}

void MainWindow::outBeforeDXF(int _ch)
{
	QMap<int, QString> index;
	index[SHOULDER_] = "shoulder ";
	index[TREE_] = "tree ";
	index[LIGHT_] = "light ";
	index[ELECT_] = "elec ";
	index[OTHER_] = "other ";
	index[HOUSE_] = "house ";

	switch (_ch)
	{
	case SHOULDER_:
		out2Txt(index[SHOULDER_]);
		break;
	case TREE_:
		out2Txt(index[TREE_]);
		break;
	case LIGHT_:
		out2Txt(index[LIGHT_]);
		break;
	case ELECT_:
		out2Txt(index[ELECT_]);
		break;
	case OTHER_:
		out2Txt(index[OTHER_]);
		break;
	case HOUSE_:
		out2Txt(index[HOUSE_]);
		break;
	default:
		break;
	}	
}

void MainWindow::out2Txt(QString &_classify)
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save BeforeDXF"), ".",
		tr("Ascii cloud (*.txt)\n"
		"Save cloud(*.*)"));

	if (QFile::exists(fileName)) {
		int r = QMessageBox::warning(this, tr("PointCloudUI"),
			tr("File %1 already exists.\n"
			"Do you want to overwrite it?")
			.arg(QDir::toNativeSeparators(fileName)),
			QMessageBox::Yes | QMessageBox::No);
		if (r == QMessageBox::No)
			return;
	}
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly))
		{
			return;
		}
		QTextStream out(&file);
		out << _classify << cloudManage.awaitingProcessCloudLXYZ->size() << endl;
		for (list<Point>::iterator it = cloudManage.awaitingProcessCloudLXYZ->begin(); it != cloudManage.awaitingProcessCloudLXYZ->end();++it)
		{
			out << it->x << " " << it->y << " " << it->z << endl;
		}
		file.close();
	}
}

void MainWindow::onTransXYZ()
{
	QDialog dialog(this);
	Ui::TransXYZDialog uiDialog;
	//uiDialog.txLineEdit->setValidator(new QDoubleValidator(this));
	//uiDialog.tyLineEdit->setValidator(new QDoubleValidator(this));
	//uiDialog.tzLineEdit->setValidator(new QDoubleValidator(this));
	uiDialog.setupUi(&dialog);
	double tx, ty, tz;

	if (dialog.exec())
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open PointCloud"), ".",
			tr("Open all files(*.*)\n"
			"Open text files (*.txt)"));
		if (!fileName.isEmpty())
		{			
			QString fileName2 = QFileDialog::getOpenFileName(this,
				tr("Save PointCloud"), ".",
				tr("Save all files(*.*)\n"
				"Save text files (*.txt)"));
			if (!fileName2.isEmpty())
			{
				//QFile file(fileName);
				//if (!file.open(QIODevice::ReadOnly))
				//{
				//	return;
				//}
				//QTextStream infile(&file);

				//QFile file2(fileName2);
				//if (!file2.open(QIODevice::WriteOnly))
				//{
				//	return;
				//}
				//QTextStream outfile(&file2);
				//double xx, yy, zz;
				//QProgressDialog openProgress;
				//openProgress.setWindowTitle(QObject::tr("PingYi cloud"));

				//openProgress.setRange(0, file.size());
				//openProgress.setModal(true);
				//openProgress.setCancelButtonText(QObject::tr("Cancel"));
				//			
				//infile >> tx;
				//infile >> ty;
				//uiDialog.txLineEdit->setText(QString::number((int)tx));
				//uiDialog.tyLineEdit->setText(QString::number((int)tx));
				//uiDialog.tzLineEdit->setText(QString::number((int)tx));
				//tx = uiDialog.txLineEdit->text().toDouble();
				//ty = uiDialog.tyLineEdit->text().toDouble();
				//tz = uiDialog.tzLineEdit->text().toDouble();

				//infile.seek(0);
				////outfile.setRealNumberPrecision(8);
				//while (!infile.atEnd())
				//{
				//	infile >> xx >> yy >> zz;
				//	//outfile << xx - tx << " " << yy - ty << " " << zz - tz << endl;
				//	outfile << QString::number(xx - tx, 'g', 8) << " " << QString::number(yy - ty, 'g', 8) << " " << QString::number(zz/* - tz*/, 'g', 8) << endl;
				//	if (file.pos() % 20)
				//	{
				//		openProgress.setValue(file.pos());
				//	}
				//	if (openProgress.wasCanceled())
				//	{
				//		break;
				//	}
				//}
				//file.close();
				//file2.close();
				
				//addMessage("", "CoordinatePY ", "Is Running... ...");
				//Coordinate coordinate;
				//coordinate.inFilePath = fileName.toStdString();
				//coordinate.outFilePath = fileName2.toStdString();
				//coordinate.translate(10);
				//addMessage("", "CoordinatePY ", "Complete.");
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}		
	}
}
