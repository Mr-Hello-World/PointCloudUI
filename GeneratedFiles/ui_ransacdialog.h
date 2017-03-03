/********************************************************************************
** Form generated from reading UI file 'ransacdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANSACDIALOG_H
#define UI_RANSACDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RansacDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *intSpinBox;
    QPushButton *okButton;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *cancelButton;

    void setupUi(QDialog *RansacDialog)
    {
        if (RansacDialog->objectName().isEmpty())
            RansacDialog->setObjectName(QStringLiteral("RansacDialog"));
        RansacDialog->resize(220, 79);
        RansacDialog->setMinimumSize(QSize(220, 79));
        RansacDialog->setMaximumSize(QSize(220, 79));
        gridLayout_2 = new QGridLayout(RansacDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(RansacDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        intSpinBox = new QSpinBox(RansacDialog);
        intSpinBox->setObjectName(QStringLiteral("intSpinBox"));
        intSpinBox->setMinimum(3);

        gridLayout->addWidget(intSpinBox, 0, 1, 1, 1);

        okButton = new QPushButton(RansacDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 0, 2, 1, 1);

        label_2 = new QLabel(RansacDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(RansacDialog);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMinimum(0.01);
        doubleSpinBox->setMaximum(5);
        doubleSpinBox->setSingleStep(0.01);
        doubleSpinBox->setValue(0.08);

        gridLayout->addWidget(doubleSpinBox, 1, 1, 1, 1);

        cancelButton = new QPushButton(RansacDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(RansacDialog);
        QObject::connect(okButton, SIGNAL(clicked()), RansacDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), RansacDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RansacDialog);
    } // setupUi

    void retranslateUi(QDialog *RansacDialog)
    {
        RansacDialog->setWindowTitle(QApplication::translate("RansacDialog", "RANSAC_Plane", 0));
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QApplication::translate("RansacDialog", "Random points num.", 0));
#endif // QT_NO_STATUSTIP
        label->setText(QApplication::translate("RansacDialog", "Num:", 0));
#ifndef QT_NO_STATUSTIP
        intSpinBox->setStatusTip(QApplication::translate("RansacDialog", "Random points num.", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_STATUSTIP
        okButton->setStatusTip(QApplication::translate("RansacDialog", "RANSAC_OK", 0));
#endif // QT_NO_STATUSTIP
        okButton->setText(QApplication::translate("RansacDialog", "OK", 0));
#ifndef QT_NO_STATUSTIP
        label_2->setStatusTip(QApplication::translate("RansacDialog", "Distance of point2plane.", 0));
#endif // QT_NO_STATUSTIP
        label_2->setText(QApplication::translate("RansacDialog", "Distance:", 0));
#ifndef QT_NO_STATUSTIP
        doubleSpinBox->setStatusTip(QApplication::translate("RansacDialog", "Distance of point2plane.", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_STATUSTIP
        cancelButton->setStatusTip(QApplication::translate("RansacDialog", "RANSAC_CANCEL", 0));
#endif // QT_NO_STATUSTIP
        cancelButton->setText(QApplication::translate("RansacDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class RansacDialog: public Ui_RansacDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANSACDIALOG_H
