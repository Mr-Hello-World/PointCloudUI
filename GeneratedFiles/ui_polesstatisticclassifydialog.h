/********************************************************************************
** Form generated from reading UI file 'polesstatisticclassifydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLESSTATISTICCLASSIFYDIALOG_H
#define UI_POLESSTATISTICCLASSIFYDIALOG_H

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

class Ui_PolesDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *VoxelSideDoubleSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *H1DoubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *H2DoubleSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *H3DoubleSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PolesDialog)
    {
        if (PolesDialog->objectName().isEmpty())
            PolesDialog->setObjectName(QStringLiteral("PolesDialog"));
        PolesDialog->resize(270, 109);
        gridLayout = new QGridLayout(PolesDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(PolesDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        VoxelSideDoubleSpinBox = new QDoubleSpinBox(PolesDialog);
        VoxelSideDoubleSpinBox->setObjectName(QStringLiteral("VoxelSideDoubleSpinBox"));
        VoxelSideDoubleSpinBox->setMinimum(0.01);
        VoxelSideDoubleSpinBox->setMaximum(1);
        VoxelSideDoubleSpinBox->setSingleStep(0.01);
        VoxelSideDoubleSpinBox->setValue(0.3);

        gridLayout->addWidget(VoxelSideDoubleSpinBox, 0, 2, 1, 5);

        label_2 = new QLabel(PolesDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        H1DoubleSpinBox = new QDoubleSpinBox(PolesDialog);
        H1DoubleSpinBox->setObjectName(QStringLiteral("H1DoubleSpinBox"));
        H1DoubleSpinBox->setMinimum(0.1);
        H1DoubleSpinBox->setMaximum(4);
        H1DoubleSpinBox->setSingleStep(0.1);
        H1DoubleSpinBox->setValue(0.5);

        gridLayout->addWidget(H1DoubleSpinBox, 1, 1, 1, 2);

        label_3 = new QLabel(PolesDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 3, 1, 1);

        H2DoubleSpinBox = new QDoubleSpinBox(PolesDialog);
        H2DoubleSpinBox->setObjectName(QStringLiteral("H2DoubleSpinBox"));
        H2DoubleSpinBox->setMinimum(0.5);
        H2DoubleSpinBox->setMaximum(8);
        H2DoubleSpinBox->setSingleStep(0.1);
        H2DoubleSpinBox->setValue(4);

        gridLayout->addWidget(H2DoubleSpinBox, 1, 4, 1, 1);

        label_4 = new QLabel(PolesDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 5, 1, 1);

        H3DoubleSpinBox = new QDoubleSpinBox(PolesDialog);
        H3DoubleSpinBox->setObjectName(QStringLiteral("H3DoubleSpinBox"));
        H3DoubleSpinBox->setMinimum(4);
        H3DoubleSpinBox->setMaximum(20);
        H3DoubleSpinBox->setSingleStep(0.1);
        H3DoubleSpinBox->setValue(8);

        gridLayout->addWidget(H3DoubleSpinBox, 1, 6, 1, 1);

        buttonBox = new QDialogButtonBox(PolesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 7);


        retranslateUi(PolesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PolesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PolesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PolesDialog);
    } // setupUi

    void retranslateUi(QDialog *PolesDialog)
    {
        PolesDialog->setWindowTitle(QApplication::translate("PolesDialog", "Poles", 0));
        label->setText(QApplication::translate("PolesDialog", "VoxelSide", 0));
        label_2->setText(QApplication::translate("PolesDialog", "H1", 0));
        label_3->setText(QApplication::translate("PolesDialog", "H2", 0));
        label_4->setText(QApplication::translate("PolesDialog", "H3", 0));
    } // retranslateUi

};

namespace Ui {
    class PolesDialog: public Ui_PolesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLESSTATISTICCLASSIFYDIALOG_H
