/********************************************************************************
** Form generated from reading UI file 'radiusfilterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIUSFILTERDIALOG_H
#define UI_RADIUSFILTERDIALOG_H

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

class Ui_RadiusOutlterDialog
{
public:
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QDoubleSpinBox *radiusDoubleSpinBox;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *RadiusOutlterDialog)
    {
        if (RadiusOutlterDialog->objectName().isEmpty())
            RadiusOutlterDialog->setObjectName(QStringLiteral("RadiusOutlterDialog"));
        RadiusOutlterDialog->resize(263, 119);
        RadiusOutlterDialog->setMinimumSize(QSize(263, 119));
        RadiusOutlterDialog->setMaximumSize(QSize(270, 119));
        gridLayout = new QGridLayout(RadiusOutlterDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBox = new QSpinBox(RadiusOutlterDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(2);
        spinBox->setValue(5);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        radiusDoubleSpinBox = new QDoubleSpinBox(RadiusOutlterDialog);
        radiusDoubleSpinBox->setObjectName(QStringLiteral("radiusDoubleSpinBox"));
        radiusDoubleSpinBox->setMinimum(0.01);
        radiusDoubleSpinBox->setMaximum(10);
        radiusDoubleSpinBox->setSingleStep(0.1);
        radiusDoubleSpinBox->setValue(0.8);

        gridLayout->addWidget(radiusDoubleSpinBox, 1, 1, 1, 1);

        label_2 = new QLabel(RadiusOutlterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(87, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(RadiusOutlterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);

        label = new QLabel(RadiusOutlterDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(RadiusOutlterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RadiusOutlterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RadiusOutlterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RadiusOutlterDialog);
    } // setupUi

    void retranslateUi(QDialog *RadiusOutlterDialog)
    {
        RadiusOutlterDialog->setWindowTitle(QApplication::translate("RadiusOutlterDialog", "RadiusOutlier", 0));
        label_2->setText(QApplication::translate("RadiusOutlterDialog", "Radius:", 0));
        label->setText(QApplication::translate("RadiusOutlterDialog", "MinNeighbor:", 0));
    } // retranslateUi

};

namespace Ui {
    class RadiusOutlterDialog: public Ui_RadiusOutlterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIUSFILTERDIALOG_H
