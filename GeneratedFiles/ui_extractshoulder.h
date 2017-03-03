/********************************************************************************
** Form generated from reading UI file 'extractshoulder.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRACTSHOULDER_H
#define UI_EXTRACTSHOULDER_H

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

QT_BEGIN_NAMESPACE

class Ui_ExtractShoulderDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *voxelSidesDoubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *thr1DoubleSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *thr2DoubleSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExtractShoulderDialog)
    {
        if (ExtractShoulderDialog->objectName().isEmpty())
            ExtractShoulderDialog->setObjectName(QStringLiteral("ExtractShoulderDialog"));
        ExtractShoulderDialog->resize(330, 67);
        gridLayout = new QGridLayout(ExtractShoulderDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ExtractShoulderDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        voxelSidesDoubleSpinBox = new QDoubleSpinBox(ExtractShoulderDialog);
        voxelSidesDoubleSpinBox->setObjectName(QStringLiteral("voxelSidesDoubleSpinBox"));
        voxelSidesDoubleSpinBox->setMinimum(0.01);
        voxelSidesDoubleSpinBox->setMaximum(1);
        voxelSidesDoubleSpinBox->setSingleStep(0.01);
        voxelSidesDoubleSpinBox->setValue(0.08);

        gridLayout->addWidget(voxelSidesDoubleSpinBox, 0, 1, 1, 1);

        label_3 = new QLabel(ExtractShoulderDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        thr1DoubleSpinBox = new QDoubleSpinBox(ExtractShoulderDialog);
        thr1DoubleSpinBox->setObjectName(QStringLiteral("thr1DoubleSpinBox"));
        thr1DoubleSpinBox->setMinimum(0.01);
        thr1DoubleSpinBox->setMaximum(1);
        thr1DoubleSpinBox->setSingleStep(0.01);
        thr1DoubleSpinBox->setValue(0.08);

        gridLayout->addWidget(thr1DoubleSpinBox, 0, 3, 1, 1);

        label_2 = new QLabel(ExtractShoulderDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 4, 1, 1);

        thr2DoubleSpinBox = new QDoubleSpinBox(ExtractShoulderDialog);
        thr2DoubleSpinBox->setObjectName(QStringLiteral("thr2DoubleSpinBox"));
        thr2DoubleSpinBox->setMinimum(0.01);
        thr2DoubleSpinBox->setMaximum(1);
        thr2DoubleSpinBox->setSingleStep(0.01);
        thr2DoubleSpinBox->setValue(0.08);

        gridLayout->addWidget(thr2DoubleSpinBox, 0, 5, 1, 1);

        buttonBox = new QDialogButtonBox(ExtractShoulderDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 6);


        retranslateUi(ExtractShoulderDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExtractShoulderDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExtractShoulderDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExtractShoulderDialog);
    } // setupUi

    void retranslateUi(QDialog *ExtractShoulderDialog)
    {
        ExtractShoulderDialog->setWindowTitle(QApplication::translate("ExtractShoulderDialog", "ExtractShoulder", 0));
        label->setText(QApplication::translate("ExtractShoulderDialog", "VoxelSides", 0));
        label_3->setText(QApplication::translate("ExtractShoulderDialog", "Thr1", 0));
        label_2->setText(QApplication::translate("ExtractShoulderDialog", "Thr2", 0));
    } // retranslateUi

};

namespace Ui {
    class ExtractShoulderDialog: public Ui_ExtractShoulderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRACTSHOULDER_H
