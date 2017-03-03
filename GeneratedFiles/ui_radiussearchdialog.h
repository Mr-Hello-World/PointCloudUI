/********************************************************************************
** Form generated from reading UI file 'radiussearchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIUSSEARCHDIALOG_H
#define UI_RADIUSSEARCHDIALOG_H

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

class Ui_RadiusSearchDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;
    QSpinBox *levelSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *scaleDoubleSpinBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RadiusSearchDialog)
    {
        if (RadiusSearchDialog->objectName().isEmpty())
            RadiusSearchDialog->setObjectName(QStringLiteral("RadiusSearchDialog"));
        RadiusSearchDialog->resize(375, 90);
        gridLayout = new QGridLayout(RadiusSearchDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(RadiusSearchDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(RadiusSearchDialog);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMinimum(0.01);
        doubleSpinBox->setMaximum(10);
        doubleSpinBox->setSingleStep(0.01);
        doubleSpinBox->setValue(0.1);

        gridLayout->addWidget(doubleSpinBox, 0, 1, 1, 1);

        label_2 = new QLabel(RadiusSearchDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        levelSpinBox = new QSpinBox(RadiusSearchDialog);
        levelSpinBox->setObjectName(QStringLiteral("levelSpinBox"));
        levelSpinBox->setMinimum(1);
        levelSpinBox->setValue(5);

        gridLayout->addWidget(levelSpinBox, 0, 3, 1, 2);

        label_3 = new QLabel(RadiusSearchDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 5, 1, 1);

        scaleDoubleSpinBox = new QDoubleSpinBox(RadiusSearchDialog);
        scaleDoubleSpinBox->setObjectName(QStringLiteral("scaleDoubleSpinBox"));
        scaleDoubleSpinBox->setMinimum(0.03);
        scaleDoubleSpinBox->setMaximum(1);
        scaleDoubleSpinBox->setSingleStep(0.01);
        scaleDoubleSpinBox->setValue(0.1);

        gridLayout->addWidget(scaleDoubleSpinBox, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(192, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 4);

        buttonBox = new QDialogButtonBox(RadiusSearchDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 4, 1, 3);


        retranslateUi(RadiusSearchDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RadiusSearchDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RadiusSearchDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RadiusSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *RadiusSearchDialog)
    {
        RadiusSearchDialog->setWindowTitle(QApplication::translate("RadiusSearchDialog", "RadiusSearch", 0));
        label->setText(QApplication::translate("RadiusSearchDialog", "RadiusSearch", 0));
        label_2->setText(QApplication::translate("RadiusSearchDialog", "Level", 0));
        label_3->setText(QApplication::translate("RadiusSearchDialog", "Scales", 0));
    } // retranslateUi

};

namespace Ui {
    class RadiusSearchDialog: public Ui_RadiusSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIUSSEARCHDIALOG_H
