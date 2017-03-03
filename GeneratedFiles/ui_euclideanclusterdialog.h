/********************************************************************************
** Form generated from reading UI file 'euclideanclusterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EUCLIDEANCLUSTERDIALOG_H
#define UI_EUCLIDEANCLUSTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EuclideanClusterDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *maxIterationsSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *distanceThrDoubleSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *percentDoubleSpinBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDoubleSpinBox *clusterToleranceDoubleSpinBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *minClusterSizeSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *maxClusterSizeSpinBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EuclideanClusterDialog)
    {
        if (EuclideanClusterDialog->objectName().isEmpty())
            EuclideanClusterDialog->setObjectName(QStringLiteral("EuclideanClusterDialog"));
        EuclideanClusterDialog->resize(364, 157);
        gridLayout_3 = new QGridLayout(EuclideanClusterDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(EuclideanClusterDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        maxIterationsSpinBox = new QSpinBox(groupBox);
        maxIterationsSpinBox->setObjectName(QStringLiteral("maxIterationsSpinBox"));
        maxIterationsSpinBox->setMaximum(1000);
        maxIterationsSpinBox->setValue(100);

        horizontalLayout->addWidget(maxIterationsSpinBox);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        distanceThrDoubleSpinBox = new QDoubleSpinBox(groupBox);
        distanceThrDoubleSpinBox->setObjectName(QStringLiteral("distanceThrDoubleSpinBox"));
        distanceThrDoubleSpinBox->setMinimum(0.01);
        distanceThrDoubleSpinBox->setMaximum(1);
        distanceThrDoubleSpinBox->setSingleStep(0.01);
        distanceThrDoubleSpinBox->setValue(0.02);

        horizontalLayout_2->addWidget(distanceThrDoubleSpinBox);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        percentDoubleSpinBox = new QDoubleSpinBox(groupBox);
        percentDoubleSpinBox->setObjectName(QStringLiteral("percentDoubleSpinBox"));
        percentDoubleSpinBox->setMinimum(0.1);
        percentDoubleSpinBox->setMaximum(0.9);
        percentDoubleSpinBox->setSingleStep(0.1);
        percentDoubleSpinBox->setValue(0.3);

        horizontalLayout_3->addWidget(percentDoubleSpinBox);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(EuclideanClusterDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        clusterToleranceDoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        clusterToleranceDoubleSpinBox->setObjectName(QStringLiteral("clusterToleranceDoubleSpinBox"));
        clusterToleranceDoubleSpinBox->setMinimum(0.01);
        clusterToleranceDoubleSpinBox->setMaximum(1);
        clusterToleranceDoubleSpinBox->setSingleStep(0.01);
        clusterToleranceDoubleSpinBox->setValue(0.02);

        horizontalLayout_4->addWidget(clusterToleranceDoubleSpinBox);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        minClusterSizeSpinBox = new QSpinBox(groupBox_2);
        minClusterSizeSpinBox->setObjectName(QStringLiteral("minClusterSizeSpinBox"));
        minClusterSizeSpinBox->setMaximum(10000);
        minClusterSizeSpinBox->setSingleStep(10);
        minClusterSizeSpinBox->setValue(100);

        horizontalLayout_5->addWidget(minClusterSizeSpinBox);


        gridLayout_2->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        maxClusterSizeSpinBox = new QSpinBox(groupBox_2);
        maxClusterSizeSpinBox->setObjectName(QStringLiteral("maxClusterSizeSpinBox"));
        maxClusterSizeSpinBox->setMaximum(1000000);
        maxClusterSizeSpinBox->setSingleStep(10);
        maxClusterSizeSpinBox->setValue(25000);

        horizontalLayout_6->addWidget(maxClusterSizeSpinBox);


        gridLayout_2->addLayout(horizontalLayout_6, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(155, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(EuclideanClusterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 1, 1, 1, 1);


        retranslateUi(EuclideanClusterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EuclideanClusterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EuclideanClusterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EuclideanClusterDialog);
    } // setupUi

    void retranslateUi(QDialog *EuclideanClusterDialog)
    {
        EuclideanClusterDialog->setWindowTitle(QApplication::translate("EuclideanClusterDialog", "EuclideanCluster", 0));
        groupBox->setTitle(QApplication::translate("EuclideanClusterDialog", "RANSAC", 0));
        label->setText(QApplication::translate("EuclideanClusterDialog", "MaxIterations", 0));
        label_2->setText(QApplication::translate("EuclideanClusterDialog", "DistanceThr", 0));
        label_3->setText(QApplication::translate("EuclideanClusterDialog", "Percent", 0));
        groupBox_2->setTitle(QApplication::translate("EuclideanClusterDialog", "Cluster", 0));
        label_4->setText(QApplication::translate("EuclideanClusterDialog", "ClusterTolerance", 0));
        label_5->setText(QApplication::translate("EuclideanClusterDialog", "MinClusterSize", 0));
        label_6->setText(QApplication::translate("EuclideanClusterDialog", "MaxClusterSize", 0));
    } // retranslateUi

};

namespace Ui {
    class EuclideanClusterDialog: public Ui_EuclideanClusterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EUCLIDEANCLUSTERDIALOG_H
