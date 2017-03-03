/********************************************************************************
** Form generated from reading UI file 'statisticalfilterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICALFILTERDIALOG_H
#define UI_STATISTICALFILTERDIALOG_H

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

class Ui_StatisticalDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QDoubleSpinBox *stddevmulThreshDoubleSpinBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *StatisticalDialog)
    {
        if (StatisticalDialog->objectName().isEmpty())
            StatisticalDialog->setObjectName(QStringLiteral("StatisticalDialog"));
        StatisticalDialog->resize(263, 119);
        StatisticalDialog->setMinimumSize(QSize(263, 119));
        StatisticalDialog->setMaximumSize(QSize(270, 119));
        gridLayout = new QGridLayout(StatisticalDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(StatisticalDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(StatisticalDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(5);
        spinBox->setValue(50);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        label_2 = new QLabel(StatisticalDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        stddevmulThreshDoubleSpinBox = new QDoubleSpinBox(StatisticalDialog);
        stddevmulThreshDoubleSpinBox->setObjectName(QStringLiteral("stddevmulThreshDoubleSpinBox"));
        stddevmulThreshDoubleSpinBox->setMaximum(5);
        stddevmulThreshDoubleSpinBox->setSingleStep(0.1);
        stddevmulThreshDoubleSpinBox->setValue(0.5);

        gridLayout->addWidget(stddevmulThreshDoubleSpinBox, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(87, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(StatisticalDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);


        retranslateUi(StatisticalDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StatisticalDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StatisticalDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StatisticalDialog);
    } // setupUi

    void retranslateUi(QDialog *StatisticalDialog)
    {
        StatisticalDialog->setWindowTitle(QApplication::translate("StatisticalDialog", "Statistical", 0));
        label->setText(QApplication::translate("StatisticalDialog", "MeanK", 0));
        label_2->setText(QApplication::translate("StatisticalDialog", "StddevmulThresh:", 0));
    } // retranslateUi

};

namespace Ui {
    class StatisticalDialog: public Ui_StatisticalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICALFILTERDIALOG_H
