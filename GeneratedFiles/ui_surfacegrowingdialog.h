/********************************************************************************
** Form generated from reading UI file 'surfacegrowingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SURFACEGROWINGDIALOG_H
#define UI_SURFACEGROWINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_SurfaceGrowingDialog
{
public:
    QGridLayout *gridLayout_4;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *seedRadiusDoubleSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *seedPlaneDistDoubleSpinBox;
    QLabel *label_9;
    QSpinBox *leastPointNumPinBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *growRadiusDoubleSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *growPlaneDistDoubleSpinBox;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QDoubleSpinBox *aDoubleSpinBox;
    QSpinBox *rmSpinBox;
    QDoubleSpinBox *dDoubleSpinBox;
    QLabel *label_7;
    QLabel *label_6;
    QSpinBox *vmSpinBox;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SurfaceGrowingDialog)
    {
        if (SurfaceGrowingDialog->objectName().isEmpty())
            SurfaceGrowingDialog->setObjectName(QStringLiteral("SurfaceGrowingDialog"));
        SurfaceGrowingDialog->resize(409, 209);
        SurfaceGrowingDialog->setMinimumSize(QSize(409, 209));
        SurfaceGrowingDialog->setMaximumSize(QSize(409, 209));
        gridLayout_4 = new QGridLayout(SurfaceGrowingDialog);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        splitter = new QSplitter(SurfaceGrowingDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        seedRadiusDoubleSpinBox = new QDoubleSpinBox(groupBox);
        seedRadiusDoubleSpinBox->setObjectName(QStringLiteral("seedRadiusDoubleSpinBox"));
        seedRadiusDoubleSpinBox->setMinimum(0.1);
        seedRadiusDoubleSpinBox->setMaximum(10);
        seedRadiusDoubleSpinBox->setSingleStep(0.1);
        seedRadiusDoubleSpinBox->setValue(0.3);

        gridLayout->addWidget(seedRadiusDoubleSpinBox, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        seedPlaneDistDoubleSpinBox = new QDoubleSpinBox(groupBox);
        seedPlaneDistDoubleSpinBox->setObjectName(QStringLiteral("seedPlaneDistDoubleSpinBox"));
        seedPlaneDistDoubleSpinBox->setMinimum(0.05);
        seedPlaneDistDoubleSpinBox->setMaximum(1);
        seedPlaneDistDoubleSpinBox->setSingleStep(0.02);
        seedPlaneDistDoubleSpinBox->setValue(0.1);

        gridLayout->addWidget(seedPlaneDistDoubleSpinBox, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 2, 0, 1, 1);

        leastPointNumPinBox = new QSpinBox(groupBox);
        leastPointNumPinBox->setObjectName(QStringLiteral("leastPointNumPinBox"));
        leastPointNumPinBox->setMinimum(3);
        leastPointNumPinBox->setMaximum(50);
        leastPointNumPinBox->setValue(10);

        gridLayout->addWidget(leastPointNumPinBox, 2, 1, 1, 1);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        growRadiusDoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        growRadiusDoubleSpinBox->setObjectName(QStringLiteral("growRadiusDoubleSpinBox"));
        growRadiusDoubleSpinBox->setMinimum(0.05);
        growRadiusDoubleSpinBox->setMaximum(1);
        growRadiusDoubleSpinBox->setSingleStep(0.02);
        growRadiusDoubleSpinBox->setValue(0.4);

        gridLayout_2->addWidget(growRadiusDoubleSpinBox, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        growPlaneDistDoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        growPlaneDistDoubleSpinBox->setObjectName(QStringLiteral("growPlaneDistDoubleSpinBox"));
        growPlaneDistDoubleSpinBox->setMinimum(0.05);
        growPlaneDistDoubleSpinBox->setMaximum(1);
        growPlaneDistDoubleSpinBox->setSingleStep(0.02);
        growPlaneDistDoubleSpinBox->setValue(0.2);

        gridLayout_2->addWidget(growPlaneDistDoubleSpinBox, 1, 1, 1, 1);

        splitter->addWidget(groupBox_2);

        gridLayout_4->addWidget(splitter, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(SurfaceGrowingDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_3->addWidget(label_8, 0, 6, 1, 1);

        aDoubleSpinBox = new QDoubleSpinBox(groupBox_3);
        aDoubleSpinBox->setObjectName(QStringLiteral("aDoubleSpinBox"));
        aDoubleSpinBox->setMinimum(2);
        aDoubleSpinBox->setMaximum(10);
        aDoubleSpinBox->setValue(3);

        gridLayout_3->addWidget(aDoubleSpinBox, 0, 1, 1, 1);

        rmSpinBox = new QSpinBox(groupBox_3);
        rmSpinBox->setObjectName(QStringLiteral("rmSpinBox"));
        rmSpinBox->setMinimum(10);
        rmSpinBox->setMaximum(10);
        rmSpinBox->setValue(10);

        gridLayout_3->addWidget(rmSpinBox, 0, 5, 1, 1);

        dDoubleSpinBox = new QDoubleSpinBox(groupBox_3);
        dDoubleSpinBox->setObjectName(QStringLiteral("dDoubleSpinBox"));
        dDoubleSpinBox->setMinimum(0.1);
        dDoubleSpinBox->setMaximum(0.1);
        dDoubleSpinBox->setValue(0.1);

        gridLayout_3->addWidget(dDoubleSpinBox, 0, 3, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 0, 4, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 0, 2, 1, 1);

        vmSpinBox = new QSpinBox(groupBox_3);
        vmSpinBox->setObjectName(QStringLiteral("vmSpinBox"));
        vmSpinBox->setMinimum(30);
        vmSpinBox->setMaximum(30);
        vmSpinBox->setValue(30);

        gridLayout_3->addWidget(vmSpinBox, 0, 7, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SurfaceGrowingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(SurfaceGrowingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SurfaceGrowingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SurfaceGrowingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SurfaceGrowingDialog);
    } // setupUi

    void retranslateUi(QDialog *SurfaceGrowingDialog)
    {
        SurfaceGrowingDialog->setWindowTitle(QApplication::translate("SurfaceGrowingDialog", "SurfaceGrowing", 0));
        groupBox->setTitle(QApplication::translate("SurfaceGrowingDialog", "SeedSeting", 0));
        label->setText(QApplication::translate("SurfaceGrowingDialog", "SeedRadius", 0));
        label_2->setText(QApplication::translate("SurfaceGrowingDialog", "SeedPlaneDist", 0));
        label_9->setText(QApplication::translate("SurfaceGrowingDialog", "LeastPointNum", 0));
        groupBox_2->setTitle(QApplication::translate("SurfaceGrowingDialog", "GrowingSeting", 0));
        label_3->setText(QApplication::translate("SurfaceGrowingDialog", "GrowRadius", 0));
        label_4->setText(QApplication::translate("SurfaceGrowingDialog", "GrowPlaneDist", 0));
        groupBox_3->setTitle(QApplication::translate("SurfaceGrowingDialog", "OrdinarySeting", 0));
        label_8->setText(QApplication::translate("SurfaceGrowingDialog", "vm", 0));
        label_7->setText(QApplication::translate("SurfaceGrowingDialog", "rm", 0));
        label_6->setText(QApplication::translate("SurfaceGrowingDialog", "d", 0));
        label_5->setText(QApplication::translate("SurfaceGrowingDialog", "a", 0));
    } // retranslateUi

};

namespace Ui {
    class SurfaceGrowingDialog: public Ui_SurfaceGrowingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SURFACEGROWINGDIALOG_H
