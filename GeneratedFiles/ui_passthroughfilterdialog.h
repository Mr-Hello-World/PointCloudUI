/********************************************************************************
** Form generated from reading UI file 'passthroughfilterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSTHROUGHFILTERDIALOG_H
#define UI_PASSTHROUGHFILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_PassThroughFilterDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *upLimitDoubleSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *downLimitDoubleSpinBox;
    QLabel *label_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *PassThroughFilterDialog)
    {
        if (PassThroughFilterDialog->objectName().isEmpty())
            PassThroughFilterDialog->setObjectName(QStringLiteral("PassThroughFilterDialog"));
        PassThroughFilterDialog->resize(263, 143);
        PassThroughFilterDialog->setMinimumSize(QSize(263, 119));
        PassThroughFilterDialog->setMaximumSize(QSize(270, 200));
        gridLayout = new QGridLayout(PassThroughFilterDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(PassThroughFilterDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        upLimitDoubleSpinBox = new QDoubleSpinBox(PassThroughFilterDialog);
        upLimitDoubleSpinBox->setObjectName(QStringLiteral("upLimitDoubleSpinBox"));
        upLimitDoubleSpinBox->setMinimum(-1000);
        upLimitDoubleSpinBox->setMaximum(1000);
        upLimitDoubleSpinBox->setSingleStep(1);
        upLimitDoubleSpinBox->setValue(100);

        gridLayout->addWidget(upLimitDoubleSpinBox, 0, 1, 1, 2);

        label_2 = new QLabel(PassThroughFilterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        downLimitDoubleSpinBox = new QDoubleSpinBox(PassThroughFilterDialog);
        downLimitDoubleSpinBox->setObjectName(QStringLiteral("downLimitDoubleSpinBox"));
        downLimitDoubleSpinBox->setMinimum(-1000);
        downLimitDoubleSpinBox->setMaximum(1000);
        downLimitDoubleSpinBox->setSingleStep(1);
        downLimitDoubleSpinBox->setValue(-100);

        gridLayout->addWidget(downLimitDoubleSpinBox, 1, 1, 1, 2);

        label_3 = new QLabel(PassThroughFilterDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        comboBox = new QComboBox(PassThroughFilterDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 2, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(87, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        pushButton = new QPushButton(PassThroughFilterDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);

        pushButton_2 = new QPushButton(PassThroughFilterDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 3, 2, 1, 1);


        retranslateUi(PassThroughFilterDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), PassThroughFilterDialog, SLOT(accept()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), PassThroughFilterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PassThroughFilterDialog);
    } // setupUi

    void retranslateUi(QDialog *PassThroughFilterDialog)
    {
        PassThroughFilterDialog->setWindowTitle(QApplication::translate("PassThroughFilterDialog", "PassThrough", 0));
        label->setText(QApplication::translate("PassThroughFilterDialog", "UpLimit:", 0));
        label_2->setText(QApplication::translate("PassThroughFilterDialog", "DownLimit:", 0));
        label_3->setText(QApplication::translate("PassThroughFilterDialog", "FilterName:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PassThroughFilterDialog", "z", 0)
         << QApplication::translate("PassThroughFilterDialog", "y", 0)
         << QApplication::translate("PassThroughFilterDialog", "x", 0)
        );
        pushButton->setText(QApplication::translate("PassThroughFilterDialog", "OK", 0));
        pushButton_2->setText(QApplication::translate("PassThroughFilterDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class PassThroughFilterDialog: public Ui_PassThroughFilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSTHROUGHFILTERDIALOG_H
