/********************************************************************************
** Form generated from reading UI file 'extractbuild.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRACTBUILD_H
#define UI_EXTRACTBUILD_H

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

class Ui_ExtractBuildDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *GSDDoubleSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *erfaDoubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *betaDoubleSpinBox;
    QLabel *label_4;
    QSpinBox *numSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExtractBuildDialog)
    {
        if (ExtractBuildDialog->objectName().isEmpty())
            ExtractBuildDialog->setObjectName(QStringLiteral("ExtractBuildDialog"));
        ExtractBuildDialog->resize(232, 110);
        gridLayout = new QGridLayout(ExtractBuildDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ExtractBuildDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        GSDDoubleSpinBox = new QDoubleSpinBox(ExtractBuildDialog);
        GSDDoubleSpinBox->setObjectName(QStringLiteral("GSDDoubleSpinBox"));
        GSDDoubleSpinBox->setMinimum(0.01);
        GSDDoubleSpinBox->setMaximum(1);
        GSDDoubleSpinBox->setSingleStep(0.01);
        GSDDoubleSpinBox->setValue(0.3);

        gridLayout->addWidget(GSDDoubleSpinBox, 0, 1, 1, 1);

        label_2 = new QLabel(ExtractBuildDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        erfaDoubleSpinBox = new QDoubleSpinBox(ExtractBuildDialog);
        erfaDoubleSpinBox->setObjectName(QStringLiteral("erfaDoubleSpinBox"));
        erfaDoubleSpinBox->setMaximum(1);
        erfaDoubleSpinBox->setSingleStep(0.01);
        erfaDoubleSpinBox->setValue(0.6);

        gridLayout->addWidget(erfaDoubleSpinBox, 0, 3, 1, 1);

        label_3 = new QLabel(ExtractBuildDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        betaDoubleSpinBox = new QDoubleSpinBox(ExtractBuildDialog);
        betaDoubleSpinBox->setObjectName(QStringLiteral("betaDoubleSpinBox"));
        betaDoubleSpinBox->setMaximum(1);
        betaDoubleSpinBox->setSingleStep(0.01);
        betaDoubleSpinBox->setValue(0.6);

        gridLayout->addWidget(betaDoubleSpinBox, 1, 1, 1, 1);

        label_4 = new QLabel(ExtractBuildDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        numSpinBox = new QSpinBox(ExtractBuildDialog);
        numSpinBox->setObjectName(QStringLiteral("numSpinBox"));
        numSpinBox->setMaximum(200);
        numSpinBox->setValue(10);

        gridLayout->addWidget(numSpinBox, 1, 3, 1, 1);

        buttonBox = new QDialogButtonBox(ExtractBuildDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 4);


        retranslateUi(ExtractBuildDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExtractBuildDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExtractBuildDialog, SLOT(reject()));
        QObject::connect(erfaDoubleSpinBox, SIGNAL(valueChanged(double)), betaDoubleSpinBox, SLOT(setValue(double)));
        QObject::connect(betaDoubleSpinBox, SIGNAL(valueChanged(double)), erfaDoubleSpinBox, SLOT(setValue(double)));

        QMetaObject::connectSlotsByName(ExtractBuildDialog);
    } // setupUi

    void retranslateUi(QDialog *ExtractBuildDialog)
    {
        ExtractBuildDialog->setWindowTitle(QApplication::translate("ExtractBuildDialog", "ExtractBuild", 0));
        label->setText(QApplication::translate("ExtractBuildDialog", "GSD", 0));
        label_2->setText(QApplication::translate("ExtractBuildDialog", "Erfa", 0));
        label_3->setText(QApplication::translate("ExtractBuildDialog", "Beta", 0));
        label_4->setText(QApplication::translate("ExtractBuildDialog", "Num", 0));
    } // retranslateUi

};

namespace Ui {
    class ExtractBuildDialog: public Ui_ExtractBuildDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRACTBUILD_H
