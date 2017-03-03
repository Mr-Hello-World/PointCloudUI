/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *openAction;
    QAction *saveAction;
    QAction *quitAction;
    QAction *actionRANSAC;
    QAction *actionSurfaceGrow;
    QAction *actionBaySAC;
    QAction *actionPointSize;
    QAction *actionBackgroundColor;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *DBTreeAction;
    QAction *propertiesAction;
    QAction *consoleAction;
    QAction *actionTranslate;
    QAction *actionPcdtoTxt;
    QAction *actionTxt2Pcd;
    QAction *actionLas2Txt;
    QAction *actionTxt2Las;
    QAction *actionTest;
    QAction *actionElevationGradient;
    QAction *actionRangeGradient;
    QAction *actionPureColor;
    QAction *actioPolesExtact;
    QAction *actionCylinder;
    QAction *actionPassThrough;
    QAction *actionStatisticalOutlierRemoval;
    QAction *actionAuto;
    QAction *actionNormal_2;
    QAction *actionAuto_2;
    QAction *actionSimple;
    QAction *actionTopView;
    QAction *actionFrontView;
    QAction *actionLeftSideView;
    QAction *actionRightSideView;
    QAction *actionBottomView;
    QAction *actionBackView;
    QAction *actionFullScreen;
    QAction *actionUnique_Color;
    QAction *actionContour;
    QAction *actionPCA;
    QAction *actionFeaturePoints;
    QAction *actionRadiusOutlier;
    QAction *actionTestTreeViewh;
    QAction *actionTestTreeViewcpp;
    QAction *actionDirectionX;
    QAction *actionDirectionY;
    QAction *actionDirectionZ;
    QAction *actionTestThread;
    QAction *actionDownSamplingVoxelGrid;
    QAction *actionS;
    QAction *actionEuclideanCluster;
    QAction *actionRegionGrowingRansac;
    QAction *actionBAYLMEDS;
    QAction *actionCloudResolution;
    QAction *actionEstimatingNormals;
    QAction *actionStatisticPolesNum;
    QAction *actionComputeCenterofPoles;
    QAction *actionClearAllData;
    QAction *actionGroundFilter;
    QAction *actionExtractCurb;
    QAction *actionAfterProgress1;
    QAction *actionAfterProgress2;
    QAction *actionBuildExtract;
    QAction *actionChouXi;
    QAction *actionSort;
    QAction *actionOutRoadPoints;
    QAction *actionAfterProgress3;
    QAction *actionComputeAnglePoints;
    QAction *actionOutAnglePoints;
    QAction *actionOutPolesPoints;
    QAction *actionPintYiXYZ;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuFilter;
    QMenu *menuFilter_2;
    QMenu *menuClusterExtraction;
    QMenu *menuSegment;
    QMenu *menuRegionGrowing;
    QMenu *menuOption;
    QMenu *menuPointColor;
    QMenu *menuGradient;
    QMenu *menuHelp;
    QMenu *menuDisplay;
    QMenu *menuTools;
    QMenu *menuPolesExtract;
    QMenu *menuPointCloudSimple_2;
    QMenu *menuGroundFilter_GetRoad;
    QMenu *menuBuildExtract;
    QStatusBar *statusBar;
    QDockWidget *ConsoleDockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QTreeWidget *consoleTreeWidget;
    QDockWidget *DBTreeDockWidget;
    QWidget *DBTreeWidget;
    QGridLayout *gridLayout;
    QTreeView *DBTreeView;
    QDockWidget *PropertiesDockWidget;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_2;
    QTreeView *propertiesTreeView;
    QToolBar *fileToolBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1062, 750);
        QIcon icon;
        icon.addFile(QStringLiteral("images/shishi.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        openAction = new QAction(MainWindowClass);
        openAction->setObjectName(QStringLiteral("openAction"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        openAction->setIcon(icon1);
        saveAction = new QAction(MainWindowClass);
        saveAction->setObjectName(QStringLiteral("saveAction"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveAction->setIcon(icon2);
        quitAction = new QAction(MainWindowClass);
        quitAction->setObjectName(QStringLiteral("quitAction"));
        actionRANSAC = new QAction(MainWindowClass);
        actionRANSAC->setObjectName(QStringLiteral("actionRANSAC"));
        actionRANSAC->setEnabled(false);
        actionSurfaceGrow = new QAction(MainWindowClass);
        actionSurfaceGrow->setObjectName(QStringLiteral("actionSurfaceGrow"));
        actionSurfaceGrow->setEnabled(false);
        actionBaySAC = new QAction(MainWindowClass);
        actionBaySAC->setObjectName(QStringLiteral("actionBaySAC"));
        actionBaySAC->setEnabled(false);
        actionPointSize = new QAction(MainWindowClass);
        actionPointSize->setObjectName(QStringLiteral("actionPointSize"));
        actionPointSize->setEnabled(false);
        actionBackgroundColor = new QAction(MainWindowClass);
        actionBackgroundColor->setObjectName(QStringLiteral("actionBackgroundColor"));
        actionBackgroundColor->setEnabled(true);
        aboutAction = new QAction(MainWindowClass);
        aboutAction->setObjectName(QStringLiteral("aboutAction"));
        aboutQtAction = new QAction(MainWindowClass);
        aboutQtAction->setObjectName(QStringLiteral("aboutQtAction"));
        DBTreeAction = new QAction(MainWindowClass);
        DBTreeAction->setObjectName(QStringLiteral("DBTreeAction"));
        propertiesAction = new QAction(MainWindowClass);
        propertiesAction->setObjectName(QStringLiteral("propertiesAction"));
        consoleAction = new QAction(MainWindowClass);
        consoleAction->setObjectName(QStringLiteral("consoleAction"));
        actionTranslate = new QAction(MainWindowClass);
        actionTranslate->setObjectName(QStringLiteral("actionTranslate"));
        actionTranslate->setEnabled(false);
        actionPcdtoTxt = new QAction(MainWindowClass);
        actionPcdtoTxt->setObjectName(QStringLiteral("actionPcdtoTxt"));
        actionTxt2Pcd = new QAction(MainWindowClass);
        actionTxt2Pcd->setObjectName(QStringLiteral("actionTxt2Pcd"));
        actionLas2Txt = new QAction(MainWindowClass);
        actionLas2Txt->setObjectName(QStringLiteral("actionLas2Txt"));
        actionTxt2Las = new QAction(MainWindowClass);
        actionTxt2Las->setObjectName(QStringLiteral("actionTxt2Las"));
        actionTest = new QAction(MainWindowClass);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionElevationGradient = new QAction(MainWindowClass);
        actionElevationGradient->setObjectName(QStringLiteral("actionElevationGradient"));
        actionElevationGradient->setEnabled(false);
        actionRangeGradient = new QAction(MainWindowClass);
        actionRangeGradient->setObjectName(QStringLiteral("actionRangeGradient"));
        actionRangeGradient->setEnabled(false);
        actionPureColor = new QAction(MainWindowClass);
        actionPureColor->setObjectName(QStringLiteral("actionPureColor"));
        actioPolesExtact = new QAction(MainWindowClass);
        actioPolesExtact->setObjectName(QStringLiteral("actioPolesExtact"));
        actioPolesExtact->setEnabled(false);
        actionCylinder = new QAction(MainWindowClass);
        actionCylinder->setObjectName(QStringLiteral("actionCylinder"));
        actionCylinder->setEnabled(false);
        actionPassThrough = new QAction(MainWindowClass);
        actionPassThrough->setObjectName(QStringLiteral("actionPassThrough"));
        actionPassThrough->setEnabled(false);
        actionStatisticalOutlierRemoval = new QAction(MainWindowClass);
        actionStatisticalOutlierRemoval->setObjectName(QStringLiteral("actionStatisticalOutlierRemoval"));
        actionStatisticalOutlierRemoval->setEnabled(false);
        actionAuto = new QAction(MainWindowClass);
        actionAuto->setObjectName(QStringLiteral("actionAuto"));
        actionAuto->setEnabled(false);
        actionNormal_2 = new QAction(MainWindowClass);
        actionNormal_2->setObjectName(QStringLiteral("actionNormal_2"));
        actionNormal_2->setEnabled(false);
        actionAuto_2 = new QAction(MainWindowClass);
        actionAuto_2->setObjectName(QStringLiteral("actionAuto_2"));
        actionAuto_2->setEnabled(false);
        actionSimple = new QAction(MainWindowClass);
        actionSimple->setObjectName(QStringLiteral("actionSimple"));
        actionSimple->setEnabled(false);
        actionTopView = new QAction(MainWindowClass);
        actionTopView->setObjectName(QStringLiteral("actionTopView"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/ccViewZpos.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTopView->setIcon(icon3);
        actionFrontView = new QAction(MainWindowClass);
        actionFrontView->setObjectName(QStringLiteral("actionFrontView"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/ccViewYpos.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFrontView->setIcon(icon4);
        actionLeftSideView = new QAction(MainWindowClass);
        actionLeftSideView->setObjectName(QStringLiteral("actionLeftSideView"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/ccViewXpos.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLeftSideView->setIcon(icon5);
        actionRightSideView = new QAction(MainWindowClass);
        actionRightSideView->setObjectName(QStringLiteral("actionRightSideView"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/ccViewXneg.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRightSideView->setIcon(icon6);
        actionBottomView = new QAction(MainWindowClass);
        actionBottomView->setObjectName(QStringLiteral("actionBottomView"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/ccViewZneg.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBottomView->setIcon(icon7);
        actionBackView = new QAction(MainWindowClass);
        actionBackView->setObjectName(QStringLiteral("actionBackView"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/ccViewYneg.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBackView->setIcon(icon8);
        actionFullScreen = new QAction(MainWindowClass);
        actionFullScreen->setObjectName(QStringLiteral("actionFullScreen"));
        actionUnique_Color = new QAction(MainWindowClass);
        actionUnique_Color->setObjectName(QStringLiteral("actionUnique_Color"));
        actionUnique_Color->setEnabled(false);
        actionContour = new QAction(MainWindowClass);
        actionContour->setObjectName(QStringLiteral("actionContour"));
        actionContour->setEnabled(false);
        actionPCA = new QAction(MainWindowClass);
        actionPCA->setObjectName(QStringLiteral("actionPCA"));
        actionPCA->setEnabled(false);
        actionFeaturePoints = new QAction(MainWindowClass);
        actionFeaturePoints->setObjectName(QStringLiteral("actionFeaturePoints"));
        actionFeaturePoints->setEnabled(false);
        actionRadiusOutlier = new QAction(MainWindowClass);
        actionRadiusOutlier->setObjectName(QStringLiteral("actionRadiusOutlier"));
        actionRadiusOutlier->setEnabled(false);
        actionTestTreeViewh = new QAction(MainWindowClass);
        actionTestTreeViewh->setObjectName(QStringLiteral("actionTestTreeViewh"));
        actionTestTreeViewcpp = new QAction(MainWindowClass);
        actionTestTreeViewcpp->setObjectName(QStringLiteral("actionTestTreeViewcpp"));
        actionDirectionX = new QAction(MainWindowClass);
        actionDirectionX->setObjectName(QStringLiteral("actionDirectionX"));
        actionDirectionX->setEnabled(false);
        actionDirectionY = new QAction(MainWindowClass);
        actionDirectionY->setObjectName(QStringLiteral("actionDirectionY"));
        actionDirectionY->setEnabled(false);
        actionDirectionZ = new QAction(MainWindowClass);
        actionDirectionZ->setObjectName(QStringLiteral("actionDirectionZ"));
        actionDirectionZ->setEnabled(false);
        actionTestThread = new QAction(MainWindowClass);
        actionTestThread->setObjectName(QStringLiteral("actionTestThread"));
        actionDownSamplingVoxelGrid = new QAction(MainWindowClass);
        actionDownSamplingVoxelGrid->setObjectName(QStringLiteral("actionDownSamplingVoxelGrid"));
        actionDownSamplingVoxelGrid->setEnabled(false);
        actionS = new QAction(MainWindowClass);
        actionS->setObjectName(QStringLiteral("actionS"));
        actionEuclideanCluster = new QAction(MainWindowClass);
        actionEuclideanCluster->setObjectName(QStringLiteral("actionEuclideanCluster"));
        actionEuclideanCluster->setEnabled(false);
        actionRegionGrowingRansac = new QAction(MainWindowClass);
        actionRegionGrowingRansac->setObjectName(QStringLiteral("actionRegionGrowingRansac"));
        actionRegionGrowingRansac->setEnabled(false);
        actionBAYLMEDS = new QAction(MainWindowClass);
        actionBAYLMEDS->setObjectName(QStringLiteral("actionBAYLMEDS"));
        actionBAYLMEDS->setEnabled(false);
        actionCloudResolution = new QAction(MainWindowClass);
        actionCloudResolution->setObjectName(QStringLiteral("actionCloudResolution"));
        actionCloudResolution->setEnabled(false);
        actionEstimatingNormals = new QAction(MainWindowClass);
        actionEstimatingNormals->setObjectName(QStringLiteral("actionEstimatingNormals"));
        actionEstimatingNormals->setEnabled(false);
        actionStatisticPolesNum = new QAction(MainWindowClass);
        actionStatisticPolesNum->setObjectName(QStringLiteral("actionStatisticPolesNum"));
        actionStatisticPolesNum->setEnabled(false);
        actionComputeCenterofPoles = new QAction(MainWindowClass);
        actionComputeCenterofPoles->setObjectName(QStringLiteral("actionComputeCenterofPoles"));
        actionComputeCenterofPoles->setEnabled(false);
        actionClearAllData = new QAction(MainWindowClass);
        actionClearAllData->setObjectName(QStringLiteral("actionClearAllData"));
        actionGroundFilter = new QAction(MainWindowClass);
        actionGroundFilter->setObjectName(QStringLiteral("actionGroundFilter"));
        actionExtractCurb = new QAction(MainWindowClass);
        actionExtractCurb->setObjectName(QStringLiteral("actionExtractCurb"));
        actionAfterProgress1 = new QAction(MainWindowClass);
        actionAfterProgress1->setObjectName(QStringLiteral("actionAfterProgress1"));
        actionAfterProgress2 = new QAction(MainWindowClass);
        actionAfterProgress2->setObjectName(QStringLiteral("actionAfterProgress2"));
        actionBuildExtract = new QAction(MainWindowClass);
        actionBuildExtract->setObjectName(QStringLiteral("actionBuildExtract"));
        actionChouXi = new QAction(MainWindowClass);
        actionChouXi->setObjectName(QStringLiteral("actionChouXi"));
        actionSort = new QAction(MainWindowClass);
        actionSort->setObjectName(QStringLiteral("actionSort"));
        actionOutRoadPoints = new QAction(MainWindowClass);
        actionOutRoadPoints->setObjectName(QStringLiteral("actionOutRoadPoints"));
        actionAfterProgress3 = new QAction(MainWindowClass);
        actionAfterProgress3->setObjectName(QStringLiteral("actionAfterProgress3"));
        actionComputeAnglePoints = new QAction(MainWindowClass);
        actionComputeAnglePoints->setObjectName(QStringLiteral("actionComputeAnglePoints"));
        actionOutAnglePoints = new QAction(MainWindowClass);
        actionOutAnglePoints->setObjectName(QStringLiteral("actionOutAnglePoints"));
        actionOutPolesPoints = new QAction(MainWindowClass);
        actionOutPolesPoints->setObjectName(QStringLiteral("actionOutPolesPoints"));
        actionPintYiXYZ = new QAction(MainWindowClass);
        actionPintYiXYZ->setObjectName(QStringLiteral("actionPintYiXYZ"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));

        gridLayout_4->addWidget(qvtkWidget, 0, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1062, 23));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuFilter = new QMenu(menuBar);
        menuFilter->setObjectName(QStringLiteral("menuFilter"));
        menuFilter_2 = new QMenu(menuFilter);
        menuFilter_2->setObjectName(QStringLiteral("menuFilter_2"));
        menuClusterExtraction = new QMenu(menuFilter);
        menuClusterExtraction->setObjectName(QStringLiteral("menuClusterExtraction"));
        menuSegment = new QMenu(menuBar);
        menuSegment->setObjectName(QStringLiteral("menuSegment"));
        menuRegionGrowing = new QMenu(menuSegment);
        menuRegionGrowing->setObjectName(QStringLiteral("menuRegionGrowing"));
        menuRegionGrowing->setEnabled(true);
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        menuPointColor = new QMenu(menuOption);
        menuPointColor->setObjectName(QStringLiteral("menuPointColor"));
        menuPointColor->setEnabled(true);
        menuGradient = new QMenu(menuPointColor);
        menuGradient->setObjectName(QStringLiteral("menuGradient"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuDisplay = new QMenu(menuBar);
        menuDisplay->setObjectName(QStringLiteral("menuDisplay"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuPolesExtract = new QMenu(menuBar);
        menuPolesExtract->setObjectName(QStringLiteral("menuPolesExtract"));
        menuPointCloudSimple_2 = new QMenu(menuBar);
        menuPointCloudSimple_2->setObjectName(QStringLiteral("menuPointCloudSimple_2"));
        menuGroundFilter_GetRoad = new QMenu(menuBar);
        menuGroundFilter_GetRoad->setObjectName(QStringLiteral("menuGroundFilter_GetRoad"));
        menuBuildExtract = new QMenu(menuBar);
        menuBuildExtract->setObjectName(QStringLiteral("menuBuildExtract"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        ConsoleDockWidget = new QDockWidget(MainWindowClass);
        ConsoleDockWidget->setObjectName(QStringLiteral("ConsoleDockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        consoleTreeWidget = new QTreeWidget(dockWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        consoleTreeWidget->setHeaderItem(__qtreewidgetitem);
        consoleTreeWidget->setObjectName(QStringLiteral("consoleTreeWidget"));

        gridLayout_3->addWidget(consoleTreeWidget, 0, 0, 1, 1);

        ConsoleDockWidget->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), ConsoleDockWidget);
        DBTreeDockWidget = new QDockWidget(MainWindowClass);
        DBTreeDockWidget->setObjectName(QStringLiteral("DBTreeDockWidget"));
        DBTreeDockWidget->setEnabled(true);
        DBTreeDockWidget->setMouseTracking(true);
        DBTreeDockWidget->setAcceptDrops(true);
        DBTreeDockWidget->setAutoFillBackground(false);
        DBTreeDockWidget->setFloating(false);
        DBTreeWidget = new QWidget();
        DBTreeWidget->setObjectName(QStringLiteral("DBTreeWidget"));
        gridLayout = new QGridLayout(DBTreeWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        DBTreeView = new QTreeView(DBTreeWidget);
        DBTreeView->setObjectName(QStringLiteral("DBTreeView"));
        DBTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
        DBTreeView->setDragEnabled(false);

        gridLayout->addWidget(DBTreeView, 0, 0, 1, 1);

        DBTreeDockWidget->setWidget(DBTreeWidget);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), DBTreeDockWidget);
        PropertiesDockWidget = new QDockWidget(MainWindowClass);
        PropertiesDockWidget->setObjectName(QStringLiteral("PropertiesDockWidget"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayout_2 = new QGridLayout(dockWidgetContents_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        propertiesTreeView = new QTreeView(dockWidgetContents_2);
        propertiesTreeView->setObjectName(QStringLiteral("propertiesTreeView"));

        gridLayout_2->addWidget(propertiesTreeView, 0, 0, 1, 1);

        PropertiesDockWidget->setWidget(dockWidgetContents_2);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), PropertiesDockWidget);
        fileToolBar = new QToolBar(MainWindowClass);
        fileToolBar->setObjectName(QStringLiteral("fileToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, fileToolBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuDisplay->menuAction());
        menuBar->addAction(menuFilter->menuAction());
        menuBar->addAction(menuSegment->menuAction());
        menuBar->addAction(menuPolesExtract->menuAction());
        menuBar->addAction(menuBuildExtract->menuAction());
        menuBar->addAction(menuGroundFilter_GetRoad->menuAction());
        menuBar->addAction(menuPointCloudSimple_2->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu_File->addAction(openAction);
        menu_File->addAction(saveAction);
        menu_File->addSeparator();
        menu_File->addAction(quitAction);
        menuFilter->addAction(menuFilter_2->menuAction());
        menuFilter->addAction(menuClusterExtraction->menuAction());
        menuFilter_2->addAction(actionPassThrough);
        menuFilter_2->addAction(actionStatisticalOutlierRemoval);
        menuFilter_2->addAction(actionRadiusOutlier);
        menuFilter_2->addSeparator();
        menuFilter_2->addAction(actionDownSamplingVoxelGrid);
        menuClusterExtraction->addAction(actionEuclideanCluster);
        menuSegment->addAction(actionRANSAC);
        menuSegment->addAction(actionSurfaceGrow);
        menuSegment->addSeparator();
        menuSegment->addAction(menuRegionGrowing->menuAction());
        menuRegionGrowing->addAction(actionRegionGrowingRansac);
        menuRegionGrowing->addAction(actionBaySAC);
        menuRegionGrowing->addAction(actionBAYLMEDS);
        menuOption->addAction(menuPointColor->menuAction());
        menuOption->addAction(actionPointSize);
        menuOption->addAction(actionBackgroundColor);
        menuOption->addSeparator();
        menuOption->addAction(actionClearAllData);
        menuPointColor->addAction(menuGradient->menuAction());
        menuPointColor->addSeparator();
        menuPointColor->addAction(actionUnique_Color);
        menuGradient->addAction(actionDirectionX);
        menuGradient->addAction(actionDirectionY);
        menuGradient->addAction(actionDirectionZ);
        menuHelp->addAction(aboutAction);
        menuDisplay->addAction(DBTreeAction);
        menuDisplay->addAction(propertiesAction);
        menuDisplay->addAction(consoleAction);
        menuDisplay->addSeparator();
        menuDisplay->addAction(actionFullScreen);
        menuDisplay->addSeparator();
        menuDisplay->addAction(actionTopView);
        menuDisplay->addAction(actionFrontView);
        menuDisplay->addAction(actionLeftSideView);
        menuDisplay->addAction(actionRightSideView);
        menuDisplay->addAction(actionBottomView);
        menuDisplay->addAction(actionBackView);
        menuDisplay->addSeparator();
        menuTools->addAction(actionTranslate);
        menuTools->addSeparator();
        menuTools->addAction(actionCloudResolution);
        menuTools->addSeparator();
        menuTools->addAction(actionEstimatingNormals);
        menuTools->addAction(actionPintYiXYZ);
        menuPolesExtract->addAction(actioPolesExtact);
        menuPolesExtract->addAction(actionStatisticPolesNum);
        menuPolesExtract->addAction(actionComputeCenterofPoles);
        menuPolesExtract->addSeparator();
        menuPolesExtract->addAction(actionOutPolesPoints);
        menuPointCloudSimple_2->addAction(actionContour);
        menuPointCloudSimple_2->addAction(actionPCA);
        menuPointCloudSimple_2->addSeparator();
        menuPointCloudSimple_2->addAction(actionFeaturePoints);
        menuPointCloudSimple_2->addSeparator();
        menuPointCloudSimple_2->addAction(actionSimple);
        menuGroundFilter_GetRoad->addAction(actionGroundFilter);
        menuGroundFilter_GetRoad->addSeparator();
        menuGroundFilter_GetRoad->addAction(actionExtractCurb);
        menuGroundFilter_GetRoad->addAction(actionAfterProgress1);
        menuGroundFilter_GetRoad->addAction(actionAfterProgress2);
        menuGroundFilter_GetRoad->addAction(actionAfterProgress3);
        menuGroundFilter_GetRoad->addSeparator();
        menuGroundFilter_GetRoad->addAction(actionChouXi);
        menuGroundFilter_GetRoad->addAction(actionSort);
        menuGroundFilter_GetRoad->addAction(actionOutRoadPoints);
        menuGroundFilter_GetRoad->addSeparator();
        menuBuildExtract->addAction(actionBuildExtract);
        menuBuildExtract->addAction(actionComputeAnglePoints);
        menuBuildExtract->addAction(actionOutAnglePoints);
        menuBuildExtract->addSeparator();

        retranslateUi(MainWindowClass);
        QObject::connect(quitAction, SIGNAL(triggered()), MainWindowClass, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "PointCloudUI", 0));
        openAction->setText(QApplication::translate("MainWindowClass", "&Open", 0));
#ifndef QT_NO_STATUSTIP
        openAction->setStatusTip(QApplication::translate("MainWindowClass", "Open", 0));
#endif // QT_NO_STATUSTIP
        openAction->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0));
        saveAction->setText(QApplication::translate("MainWindowClass", "&Save", 0));
#ifndef QT_NO_STATUSTIP
        saveAction->setStatusTip(QApplication::translate("MainWindowClass", "Save current entity", 0));
#endif // QT_NO_STATUSTIP
        saveAction->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", 0));
        quitAction->setText(QApplication::translate("MainWindowClass", "&Quit", 0));
#ifndef QT_NO_STATUSTIP
        quitAction->setStatusTip(QApplication::translate("MainWindowClass", "Quit", 0));
#endif // QT_NO_STATUSTIP
        quitAction->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Q", 0));
        actionRANSAC->setText(QApplication::translate("MainWindowClass", "MultRANSAC", 0));
        actionSurfaceGrow->setText(QApplication::translate("MainWindowClass", "SurfaceGrowing", 0));
        actionBaySAC->setText(QApplication::translate("MainWindowClass", "REBAYSAC", 0));
        actionPointSize->setText(QApplication::translate("MainWindowClass", "PointSize", 0));
        actionBackgroundColor->setText(QApplication::translate("MainWindowClass", "BackgroundColor", 0));
        aboutAction->setText(QApplication::translate("MainWindowClass", "About", 0));
        aboutQtAction->setText(QApplication::translate("MainWindowClass", "About Qt", 0));
        DBTreeAction->setText(QApplication::translate("MainWindowClass", "DB Tree", 0));
        DBTreeAction->setShortcut(QApplication::translate("MainWindowClass", "F7", 0));
        propertiesAction->setText(QApplication::translate("MainWindowClass", "Properties", 0));
        propertiesAction->setShortcut(QApplication::translate("MainWindowClass", "F8", 0));
        consoleAction->setText(QApplication::translate("MainWindowClass", "Console", 0));
        consoleAction->setShortcut(QApplication::translate("MainWindowClass", "F9", 0));
        actionTranslate->setText(QApplication::translate("MainWindowClass", "Translate", 0));
        actionPcdtoTxt->setText(QApplication::translate("MainWindowClass", "Pcd2Txt", 0));
        actionTxt2Pcd->setText(QApplication::translate("MainWindowClass", "Txt2Pcd", 0));
        actionLas2Txt->setText(QApplication::translate("MainWindowClass", "Las2Txt", 0));
        actionTxt2Las->setText(QApplication::translate("MainWindowClass", "Txt2Las", 0));
        actionTest->setText(QApplication::translate("MainWindowClass", "test", 0));
        actionElevationGradient->setText(QApplication::translate("MainWindowClass", "ElevationGradient", 0));
        actionRangeGradient->setText(QApplication::translate("MainWindowClass", "RangeGradient", 0));
        actionPureColor->setText(QApplication::translate("MainWindowClass", "PureColor", 0));
        actioPolesExtact->setText(QApplication::translate("MainWindowClass", "PolesExtract", 0));
        actionCylinder->setText(QApplication::translate("MainWindowClass", "Cylinder", 0));
        actionPassThrough->setText(QApplication::translate("MainWindowClass", "PassThrough", 0));
        actionStatisticalOutlierRemoval->setText(QApplication::translate("MainWindowClass", "StatisticalOutlier", 0));
        actionAuto->setText(QApplication::translate("MainWindowClass", "Auto", 0));
        actionNormal_2->setText(QApplication::translate("MainWindowClass", "Normal", 0));
        actionAuto_2->setText(QApplication::translate("MainWindowClass", "Auto", 0));
        actionSimple->setText(QApplication::translate("MainWindowClass", "Simple", 0));
        actionTopView->setText(QApplication::translate("MainWindowClass", "TopView", 0));
        actionFrontView->setText(QApplication::translate("MainWindowClass", "FrontView", 0));
        actionLeftSideView->setText(QApplication::translate("MainWindowClass", "LeftSideView", 0));
        actionRightSideView->setText(QApplication::translate("MainWindowClass", "RightSideView", 0));
        actionBottomView->setText(QApplication::translate("MainWindowClass", "BottomView", 0));
        actionBackView->setText(QApplication::translate("MainWindowClass", "BackView", 0));
        actionFullScreen->setText(QApplication::translate("MainWindowClass", "FullScreen", 0));
        actionFullScreen->setShortcut(QApplication::translate("MainWindowClass", "F10", 0));
        actionUnique_Color->setText(QApplication::translate("MainWindowClass", "Unique Color", 0));
        actionContour->setText(QApplication::translate("MainWindowClass", "Contour", 0));
        actionPCA->setText(QApplication::translate("MainWindowClass", "PCA", 0));
        actionFeaturePoints->setText(QApplication::translate("MainWindowClass", "FeaturePoints", 0));
        actionRadiusOutlier->setText(QApplication::translate("MainWindowClass", "RadiusOutlierRemoval", 0));
        actionTestTreeViewh->setText(QApplication::translate("MainWindowClass", "testTreeViewh", 0));
        actionTestTreeViewh->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+T", 0));
        actionTestTreeViewcpp->setText(QApplication::translate("MainWindowClass", "testTreeViewcpp", 0));
        actionTestTreeViewcpp->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Y", 0));
        actionDirectionX->setText(QApplication::translate("MainWindowClass", "DirectionX", 0));
        actionDirectionY->setText(QApplication::translate("MainWindowClass", "DirectionY", 0));
        actionDirectionZ->setText(QApplication::translate("MainWindowClass", "DirectionZ", 0));
        actionTestThread->setText(QApplication::translate("MainWindowClass", "testThread", 0));
        actionDownSamplingVoxelGrid->setText(QApplication::translate("MainWindowClass", "DownSamplingVoxelGrid", 0));
        actionS->setText(QApplication::translate("MainWindowClass", "S", 0));
        actionEuclideanCluster->setText(QApplication::translate("MainWindowClass", "EuclideanCluster", 0));
        actionRegionGrowingRansac->setText(QApplication::translate("MainWindowClass", "RERANSAC", 0));
        actionBAYLMEDS->setText(QApplication::translate("MainWindowClass", "REBAYLMEDS", 0));
        actionCloudResolution->setText(QApplication::translate("MainWindowClass", "CloudResolution", 0));
        actionEstimatingNormals->setText(QApplication::translate("MainWindowClass", "EstimatingNormals", 0));
        actionStatisticPolesNum->setText(QApplication::translate("MainWindowClass", "StatisticPolesNum", 0));
        actionComputeCenterofPoles->setText(QApplication::translate("MainWindowClass", "ComputeCenterofPoles", 0));
        actionClearAllData->setText(QApplication::translate("MainWindowClass", "ClearAllData", 0));
        actionGroundFilter->setText(QApplication::translate("MainWindowClass", "GroundFilter", 0));
        actionExtractCurb->setText(QApplication::translate("MainWindowClass", "ExtractCurb", 0));
        actionAfterProgress1->setText(QApplication::translate("MainWindowClass", "AfterProgressI", 0));
        actionAfterProgress2->setText(QApplication::translate("MainWindowClass", "AfterProgressII", 0));
        actionBuildExtract->setText(QApplication::translate("MainWindowClass", "BuildExtract", 0));
        actionChouXi->setText(QApplication::translate("MainWindowClass", "ChouXi", 0));
        actionSort->setText(QApplication::translate("MainWindowClass", "Sort", 0));
        actionOutRoadPoints->setText(QApplication::translate("MainWindowClass", "OutRoadPoints", 0));
        actionAfterProgress3->setText(QApplication::translate("MainWindowClass", "AfterProgressIII", 0));
        actionComputeAnglePoints->setText(QApplication::translate("MainWindowClass", "ComputeCornerPoints", 0));
        actionOutAnglePoints->setText(QApplication::translate("MainWindowClass", "OutCornerPoints", 0));
        actionOutPolesPoints->setText(QApplication::translate("MainWindowClass", "OutPolesPoints", 0));
        actionPintYiXYZ->setText(QApplication::translate("MainWindowClass", "PintYiXYZ", 0));
        menu_File->setTitle(QApplication::translate("MainWindowClass", "&File", 0));
        menuFilter->setTitle(QApplication::translate("MainWindowClass", "PCL", 0));
        menuFilter_2->setTitle(QApplication::translate("MainWindowClass", "Filter", 0));
        menuClusterExtraction->setTitle(QApplication::translate("MainWindowClass", "ClusterExtraction", 0));
        menuSegment->setTitle(QApplication::translate("MainWindowClass", "Segment", 0));
        menuRegionGrowing->setTitle(QApplication::translate("MainWindowClass", "RegionGrowing", 0));
        menuOption->setTitle(QApplication::translate("MainWindowClass", "Options", 0));
        menuPointColor->setTitle(QApplication::translate("MainWindowClass", "PointColor", 0));
        menuGradient->setTitle(QApplication::translate("MainWindowClass", "Gradient", 0));
        menuHelp->setTitle(QApplication::translate("MainWindowClass", "Help", 0));
        menuDisplay->setTitle(QApplication::translate("MainWindowClass", "Display", 0));
        menuTools->setTitle(QApplication::translate("MainWindowClass", "Tools", 0));
        menuPolesExtract->setTitle(QApplication::translate("MainWindowClass", "PolesExtract", 0));
        menuPointCloudSimple_2->setTitle(QApplication::translate("MainWindowClass", "PointCloudSimple", 0));
        menuGroundFilter_GetRoad->setTitle(QApplication::translate("MainWindowClass", "GetRoadInfo", 0));
        menuBuildExtract->setTitle(QApplication::translate("MainWindowClass", "BuildExtract", 0));
        ConsoleDockWidget->setWindowTitle(QApplication::translate("MainWindowClass", "Console", 0));
        DBTreeDockWidget->setWindowTitle(QApplication::translate("MainWindowClass", "Data", 0));
        PropertiesDockWidget->setWindowTitle(QApplication::translate("MainWindowClass", "Properties", 0));
        fileToolBar->setWindowTitle(QApplication::translate("MainWindowClass", "File", 0));
#ifndef QT_NO_STATUSTIP
        fileToolBar->setStatusTip(QApplication::translate("MainWindowClass", "File", 0));
#endif // QT_NO_STATUSTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
