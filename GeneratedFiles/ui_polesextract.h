/********************************************************************************
** Form generated from reading UI file 'polesextract.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLESEXTRACT_H
#define UI_POLESEXTRACT_H

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
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_PolesExtractDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *voxelSidesDoubleSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *thrHDoubleSpinBox;
    QLabel *label_3;
    QSpinBox *spaceNumberSpinBox;
    QLabel *label_4;
    QSpinBox *pitchSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PolesExtractDialog)
    {
        if (PolesExtractDialog->objectName().isEmpty())
            PolesExtractDialog->setObjectName(QStringLiteral("PolesExtractDialog"));
        PolesExtractDialog->resize(260, 93);
        gridLayout = new QGridLayout(PolesExtractDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(PolesExtractDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        voxelSidesDoubleSpinBox = new QDoubleSpinBox(PolesExtractDialog);
        voxelSidesDoubleSpinBox->setObjectName(QStringLiteral("voxelSidesDoubleSpinBox"));
        voxelSidesDoubleSpinBox->setMinimum(0.05);
        voxelSidesDoubleSpinBox->setMaximum(1);
        voxelSidesDoubleSpinBox->setSingleStep(0.01);
        voxelSidesDoubleSpinBox->setValue(0.3);

        gridLayout->addWidget(voxelSidesDoubleSpinBox, 0, 1, 1, 1);

        label_2 = new QLabel(PolesExtractDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        thrHDoubleSpinBox = new QDoubleSpinBox(PolesExtractDialog);
        thrHDoubleSpinBox->setObjectName(QStringLiteral("thrHDoubleSpinBox"));
        thrHDoubleSpinBox->setMinimum(0.5);
        thrHDoubleSpinBox->setMaximum(100);
        thrHDoubleSpinBox->setSingleStep(0.01);
        thrHDoubleSpinBox->setValue(2);

        gridLayout->addWidget(thrHDoubleSpinBox, 0, 3, 1, 1);

        label_3 = new QLabel(PolesExtractDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        spaceNumberSpinBox = new QSpinBox(PolesExtractDialog);
        spaceNumberSpinBox->setObjectName(QStringLiteral("spaceNumberSpinBox"));
        spaceNumberSpinBox->setMinimum(1);
        spaceNumberSpinBox->setMaximum(200);
        spaceNumberSpinBox->setValue(80);
        spaceNumberSpinBox->setDisplayIntegerBase(10);

        gridLayout->addWidget(spaceNumberSpinBox, 1, 1, 1, 1);

        label_4 = new QLabel(PolesExtractDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        pitchSpinBox = new QSpinBox(PolesExtractDialog);
        pitchSpinBox->setObjectName(QStringLiteral("pitchSpinBox"));
        pitchSpinBox->setMinimum(1);
        pitchSpinBox->setValue(2);

        gridLayout->addWidget(pitchSpinBox, 1, 3, 1, 1);

        buttonBox = new QDialogButtonBox(PolesExtractDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 4);


        retranslateUi(PolesExtractDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PolesExtractDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PolesExtractDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PolesExtractDialog);
    } // setupUi

    void retranslateUi(QDialog *PolesExtractDialog)
    {
        PolesExtractDialog->setWindowTitle(QApplication::translate("PolesExtractDialog", "PolesExtract", 0));
        label->setText(QApplication::translate("PolesExtractDialog", "VoxelSides:", 0));
        label_2->setText(QApplication::translate("PolesExtractDialog", "H_thr:", 0));
        label_3->setText(QApplication::translate("PolesExtractDialog", "SpaceNumber:", 0));
        label_4->setText(QApplication::translate("PolesExtractDialog", "Pitch:", 0));
    } // retranslateUi

};

namespace Ui {
    class PolesExtractDialog: public Ui_PolesExtractDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLESEXTRACT_H
