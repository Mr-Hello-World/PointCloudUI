/********************************************************************************
** Form generated from reading UI file 'afterprocess2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AFTERPROCESS2_H
#define UI_AFTERPROCESS2_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AfterProcess2Dialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QLineEdit *initialShoulderLineEdit;
    QDoubleSpinBox *voxelSidesDoubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *thr1DoubleSpinBox;
    QDialogButtonBox *buttonBox;
    QRadioButton *initalShoulderRadioButton;
    QLabel *label_5;
    QLineEdit *initialPointsLineEdit;
    QLabel *label_2;
    QDoubleSpinBox *thr2DoubleSpinBox;
    QRadioButton *initialPointsRadioButton;

    void setupUi(QDialog *AfterProcess2Dialog)
    {
        if (AfterProcess2Dialog->objectName().isEmpty())
            AfterProcess2Dialog->setObjectName(QStringLiteral("AfterProcess2Dialog"));
        AfterProcess2Dialog->resize(370, 119);
        gridLayout = new QGridLayout(AfterProcess2Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(AfterProcess2Dialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(186, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 4);

        label_4 = new QLabel(AfterProcess2Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 2);

        initialShoulderLineEdit = new QLineEdit(AfterProcess2Dialog);
        initialShoulderLineEdit->setObjectName(QStringLiteral("initialShoulderLineEdit"));

        gridLayout->addWidget(initialShoulderLineEdit, 1, 2, 1, 5);

        voxelSidesDoubleSpinBox = new QDoubleSpinBox(AfterProcess2Dialog);
        voxelSidesDoubleSpinBox->setObjectName(QStringLiteral("voxelSidesDoubleSpinBox"));
        voxelSidesDoubleSpinBox->setMinimum(0.01);
        voxelSidesDoubleSpinBox->setMaximum(1);
        voxelSidesDoubleSpinBox->setSingleStep(0.01);
        voxelSidesDoubleSpinBox->setValue(0.08);

        gridLayout->addWidget(voxelSidesDoubleSpinBox, 0, 1, 1, 1);

        label_3 = new QLabel(AfterProcess2Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        thr1DoubleSpinBox = new QDoubleSpinBox(AfterProcess2Dialog);
        thr1DoubleSpinBox->setObjectName(QStringLiteral("thr1DoubleSpinBox"));
        thr1DoubleSpinBox->setMinimum(0.01);
        thr1DoubleSpinBox->setMaximum(1);
        thr1DoubleSpinBox->setSingleStep(0.01);
        thr1DoubleSpinBox->setValue(0.08);

        gridLayout->addWidget(thr1DoubleSpinBox, 0, 3, 1, 2);

        buttonBox = new QDialogButtonBox(AfterProcess2Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 4, 1, 4);

        initalShoulderRadioButton = new QRadioButton(AfterProcess2Dialog);
        initalShoulderRadioButton->setObjectName(QStringLiteral("initalShoulderRadioButton"));

        gridLayout->addWidget(initalShoulderRadioButton, 1, 7, 1, 1);

        label_5 = new QLabel(AfterProcess2Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 2);

        initialPointsLineEdit = new QLineEdit(AfterProcess2Dialog);
        initialPointsLineEdit->setObjectName(QStringLiteral("initialPointsLineEdit"));

        gridLayout->addWidget(initialPointsLineEdit, 2, 2, 1, 5);

        label_2 = new QLabel(AfterProcess2Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 5, 1, 1);

        thr2DoubleSpinBox = new QDoubleSpinBox(AfterProcess2Dialog);
        thr2DoubleSpinBox->setObjectName(QStringLiteral("thr2DoubleSpinBox"));
        thr2DoubleSpinBox->setMinimum(0.01);
        thr2DoubleSpinBox->setMaximum(1);
        thr2DoubleSpinBox->setSingleStep(0.01);
        thr2DoubleSpinBox->setValue(0.08);

        gridLayout->addWidget(thr2DoubleSpinBox, 0, 6, 1, 2);

        initialPointsRadioButton = new QRadioButton(AfterProcess2Dialog);
        initialPointsRadioButton->setObjectName(QStringLiteral("initialPointsRadioButton"));

        gridLayout->addWidget(initialPointsRadioButton, 2, 7, 1, 1);


        retranslateUi(AfterProcess2Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AfterProcess2Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AfterProcess2Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AfterProcess2Dialog);
    } // setupUi

    void retranslateUi(QDialog *AfterProcess2Dialog)
    {
        AfterProcess2Dialog->setWindowTitle(QApplication::translate("AfterProcess2Dialog", "AfterProcess2", 0));
        label->setText(QApplication::translate("AfterProcess2Dialog", "VoxelSides", 0));
        label_4->setText(QApplication::translate("AfterProcess2Dialog", "InitialShoulderPoints", 0));
        label_3->setText(QApplication::translate("AfterProcess2Dialog", "Thr1", 0));
        initalShoulderRadioButton->setText(QString());
        label_5->setText(QApplication::translate("AfterProcess2Dialog", "InitialPoints", 0));
        label_2->setText(QApplication::translate("AfterProcess2Dialog", "Thr2", 0));
        initialPointsRadioButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AfterProcess2Dialog: public Ui_AfterProcess2Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AFTERPROCESS2_H
