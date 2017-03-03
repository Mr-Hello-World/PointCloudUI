/********************************************************************************
** Form generated from reading UI file 'regiongrowdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGIONGROWDIALOG_H
#define UI_REGIONGROWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RegionGrowDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *radiusDoubleSpinBox;
    QLabel *label_2;
    QSpinBox *kSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *thrDoubleSpinBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RegionGrowDialog)
    {
        if (RegionGrowDialog->objectName().isEmpty())
            RegionGrowDialog->setObjectName(QStringLiteral("RegionGrowDialog"));
        RegionGrowDialog->resize(292, 76);
        gridLayout = new QGridLayout(RegionGrowDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(RegionGrowDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        radiusDoubleSpinBox = new QDoubleSpinBox(RegionGrowDialog);
        radiusDoubleSpinBox->setObjectName(QStringLiteral("radiusDoubleSpinBox"));
        radiusDoubleSpinBox->setMinimum(0.1);
        radiusDoubleSpinBox->setMaximum(10);
        radiusDoubleSpinBox->setSingleStep(0.1);
        radiusDoubleSpinBox->setValue(0.5);

        gridLayout->addWidget(radiusDoubleSpinBox, 0, 1, 1, 1);

        label_2 = new QLabel(RegionGrowDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        kSpinBox = new QSpinBox(RegionGrowDialog);
        kSpinBox->setObjectName(QStringLiteral("kSpinBox"));
        kSpinBox->setMinimum(5);
        kSpinBox->setMaximum(200);
        kSpinBox->setValue(15);

        gridLayout->addWidget(kSpinBox, 0, 3, 1, 1);

        label_3 = new QLabel(RegionGrowDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        thrDoubleSpinBox = new QDoubleSpinBox(RegionGrowDialog);
        thrDoubleSpinBox->setObjectName(QStringLiteral("thrDoubleSpinBox"));
        thrDoubleSpinBox->setMinimum(0.01);
        thrDoubleSpinBox->setMaximum(1);
        thrDoubleSpinBox->setSingleStep(0.01);
        thrDoubleSpinBox->setValue(0.08);

        gridLayout->addWidget(thrDoubleSpinBox, 0, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(97, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(RegionGrowDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 3, 1, 3);


        retranslateUi(RegionGrowDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RegionGrowDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RegionGrowDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RegionGrowDialog);
    } // setupUi

    void retranslateUi(QDialog *RegionGrowDialog)
    {
        RegionGrowDialog->setWindowTitle(QApplication::translate("RegionGrowDialog", "RegionGrow", 0));
        label->setText(QApplication::translate("RegionGrowDialog", "Radius", 0));
        label_2->setText(QApplication::translate("RegionGrowDialog", "K", 0));
        label_3->setText(QApplication::translate("RegionGrowDialog", "Thre", 0));
    } // retranslateUi

};

namespace Ui {
    class RegionGrowDialog: public Ui_RegionGrowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGIONGROWDIALOG_H
