#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtGui/QMainWindow>
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "ui_openasciidialog.h"
#include "../PointClass/point.h"
#include "../ThreadClass/cloudthread.h"
#include "../CloudData/cloudmanage.h"
#include "../Transformate/transformate.h"
#include "ui_formatetransform.h"
#include "ui_afterprocess2.h"
#include "ui_extractbuild.h"
//typedef pcl::PointXYZ PointT;
//typedef pcl::PointCloud<PointT> PointCloudT;

class QStandardItemModel;
class QTreeWidget;
class QCloseEvent;
class QColorDialog;
class QStandardItemModel;
class QStandardItem;
class QAction;
class QToolBar;
class QButtonGroup;
class QTimer;
class QActionGroup;
class QNetworkReply;
class QDateTime;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~MainWindow();
protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);

signals:
	void ransacDialogValue(int _num, double _distance);
	
private slots:
	void open();
	bool save();

	void openTran();
	void saveTran();
	
	void ransac();
	void surfaceGrow();

	void setBackgroundColor();
	void setPointSize();
	void setPointColorGradientDirectionX();
	void setPointColorGradientDirectionY();
	void setPointColorGradientDirectionZ();
	void onClearAllData();

	void setPointUniqueColor();
	void about();
	void test();

	void setAsciiDialogSEP();
	void setAsciiDialogDou();
	void setAsciiDialogFen();
	void setAsciiTableView();

	void setFullScreen();
	void setTopView();
	void setBottomView();
	void setFrontView();
	void setBackView();
	void setRightView();
	void setLeftView();

	void setShowOrHideDBWidget();
	void setShowOrHideConsoleWidget();
	void setShowOrHidePropertyWidget();

	void contourPoints();
	void PCAPoints();
	void featurePoints();
	void simplePoints();

	void passThroughFilter();
	void statisticalOutLierFilter();
	void radiusOutlierFilter();
	void downSimplingFilter();

	void euclideanClusterExtract();

	void setActionTestEnable(bool _bool);
	void setActionRansacEnable(bool _bool);
	void setActionSurfaceGrowEnable(bool _bool);

	void setActionContourEnable(bool _bool);
	void setActionPCAEnable(bool _bool);
	void setActionFeatureEnable(bool _bool);
	void setActionSimaplePointEnable(bool _bool);

	void setActionPassThroughEnable(bool _bool);
	void setActionStatisticalOutlierEnable(bool _bool);
	void setActionRadiusOutlierEnable(bool _bool);
	void setActionDownSimplingEnable(bool _bool);
	//void setActionTestThread(bool _bool);

	void setActionEuclideanCluster(bool _bool);

	void on_treeView_customContextMenuRequested(const QPoint &pos);
	void on_treeView_currentItem_Clicked(const QModelIndex &index);
	
	//void setAllActionEnable(QActionGroup &actionGroup, bool _bool);

	void activateItem();
	void updateItem2View();
	void addItem2View();
	void deleteItem();
	void deleteAllItem();
	void exportItem();
	void exportAllItem();
	void import2Item();
	void uniItemAdd2MulItem();
	void newCreateMulItem();

	void transformate();
	void onTransXYZ();
	void computeResolution();
	void setActionResolution(bool _bool);

	void onEstimatingNormals();
	void onSetActionEstimateNormals(bool _bool);

	void onRegiongrowRansac();
	void onRegiongrowBaysac();
	void onRegiongrowBayLmeds();

	void setActionRegRansac(bool _bool);
	void setActionRegBaysac(bool _bool);
	void setActionRegBayLmeds(bool _bool);
	void readTime();

	void onPolesExtract();
	void onSetActionPolesExtract(bool _bool);
	void onStatisticPolesNum();
	void onSetActionStatisticPolesNum(bool _bool);
	void onComputeCenterofPoles();
	void onSetActionComputeCenterofPoles(bool _bool);
	void onOutPolesPoints();

	void onGroundFilter();
	void onExtractCurbPoints();
	void onAfterProgress1();
	void onAfterProgress2();
	void onAfterProgress3();
	void onChouXiRoadPoints();
	void onSortRoadPoints();
	void onOutRoadPoints();

	void onSetActionGroundFilter(bool _bool);
	void onSetActionExtractCurbPoints(bool _bool);
	void onSetActionAfterProgress1(bool _bool);
	void onSetActionAfterProgress2(bool _bool);

	void onAfterProcessButtonBoxOK();

	void onExtractBuild();
	void onSetActionExtractBuild(bool _bool);
	void onComputeCornerPoints();
	void onOutAnglePoints();

	
private:
	Ui::MainWindowClass ui;
	CloudManage cloudManage;
	QMenu* m_projectMenu;
	QMenu* m_itemMenu; //在构造函数中创建menu
	Ui::AfterProcess2Dialog *afterProcess2Dialog;
	QDialog *afterParentDialog;
	Ui::ExtractBuildDialog *extractBuildDialog;
	
	void initialVtkWidget();
	void initialViewer();
	void initialMainwindowWidget();
	void creatToolBar();
	void slotSingal();

	void initiaDBTree();
	void updateDBTree(const QString &name,const QString &str);
	void updatePropertiesTree();
	void enableAction(bool _bool);
	
	void initialConcoleTreeWidget();
	void addMessage(const QString &date, const QString &object, const QString &operate);
	bool okToContinue();
	bool loadFile(const QString &fileName);
	void saveFile(const QString &fileName);
	void openAscii(const QString &fileName);
	void openLAS(const QString &fileName);
	void saveAscii(const QString &fileName);
	void addUniColorItem(QString name=tr("uniqcolorcloud"));
	void addMulColorItem(QString name=tr("multcolorcloud"));
	
	void ransacPlane(int _num, double _dist);

	void eleGradient(float &z, int &r, int &g,int &b);
	void rangeGradient(float &x, int &r, int &g,int &b);

	void addOrientationMarKerWidgetAxes();
	void formatesTransform(int RAWFORMATE = 0);
	void appLock();
	void outBeforeDXF(int _ch);
	void out2Txt(QString &_classify);
		
	int pointsNum;
	QString pointCloudName;
	QString pointCloudCompleteBaseName;
	QString pointCloudSuffix;
	QString pointCloudFilePath;
	QString curFile;
	int pointCloudSize;
	float minZ,maxZ,minX,maxX,minY,maxY;
		
	vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget;
	vtkSmartPointer<vtkOrientationMarkerWidget> vtkAxesWidget;

	CloudThread testThread;
	CloudThread ransacThread;
	CloudThread surfaceGrowThread;
	CloudThread contourThread;
	CloudThread PCAThread;
	CloudThread featureThread;
	CloudThread simplePointThread;

	CloudThread passThroughThread;
	CloudThread statisticalThread;
	CloudThread radiusThread;
	CloudThread downSamplingThread;

	CloudThread euclideanClusterThread;
	
	//CloudThread;
	CloudThread *cloudThread;
	CloudThread resolutionThread;
	CloudThread estimateNormalsThread;

	CloudThread regionGrowRansacThread;
	CloudThread regionGrowBaysacThread;
	CloudThread regionGrowBayLmedsThread;

	CloudThread polesExtractThread;
	CloudThread statisticPolesNumThread;
	CloudThread computeCenterofPolesThread;

	CloudThread groundFilterThread;
	CloudThread extractCurbThread;
	CloudThread curbAfterProgress1Thread;
	CloudThread curbAfterProgress2Thread;

	CloudThread extractBuildThread;
	
	QStandardItemModel* getTreeModel();
	QList<QStandardItem*> getRoots();
	QStandardItem* getProjectFolder();
	QStandardItem* getCloudXYZFolder();
	QStandardItem* getCloudRGBFolder();
	QStandardItem* getCloudXYZItem();
	QStandardItem* getCloudRGBItem();

	int s_uniqcolor_count;
	int s_multcolor_count;
	QToolBar* viewToolBar;

	Transformate transfor;
	Ui::FormateTransformDialog *ftf;
	QButtonGroup *buttonsGroup;
	QButtonGroup *afterProcessButtonsGroup;
	double res;
	bool appLockb;
	QTimer *timer;
	bool firstRunFile();
	void writeCurrentDate(QString &fileName);
	void getNetDateTime();
	QNetworkReply *reply;
	QDateTime *netDateTime;
	QString appLockFileName;

	//QActionGroup *toolsActionGroup;
	//QActionGroup *pclActionGroup;
	//QActionGroup *segmentActionGroup;
	//QActionGroup *simpleActionGroup;
	//QActionGroup *optionsActionGroup;
	//QActionGroup *polesExtractActionGroup;
	//void addAction2Group();
	void enableActionThread(CloudThread &cloudThread, QAction &action);
	
};

#endif // MAINWINDOW_H
