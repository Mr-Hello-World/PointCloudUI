/********************************************************************************
** Form generated from reading UI file 'simpledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEDIALOG_H
#define UI_SIMPLEDIALOG_H

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

class Ui_SimpleDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QDoubleSpinBox *planarityDoubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *voxelSideDoubleSpinBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SimpleDialog)
    {
        if (SimpleDialog->objectName().isEmpty())
            SimpleDialog->setObjectName(QStringLiteral("SimpleDialog"));
        SimpleDialog->resize(263, 119);
        SimpleDialog->setMinimumSize(QSize(263, 119));
        SimpleDialog->setMaximumSize(QSize(270, 119));
        gridLayout = new QGridLayout(SimpleDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(SimpleDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(SimpleDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(5);
        spinBox->setValue(30);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        label_2 = new QLabel(SimpleDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        planarityDoubleSpinBox = new QDoubleSpinBox(SimpleDialog);
        planarityDoubleSpinBox->setObjectName(QStringLiteral("planarityDoubleSpinBox"));
        planarityDoubleSpinBox->setMaximum(1);
        planarityDoubleSpinBox->setSingleStep(0.1);
        planarityDoubleSpinBox->setValue(0.3);

        gridLayout->addWidget(planarityDoubleSpinBox, 1, 1, 1, 1);

        label_3 = new QLabel(SimpleDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        voxelSideDoubleSpinBox = new QDoubleSpinBox(SimpleDialog);
        voxelSideDoubleSpinBox->setObjectName(QStringLiteral("voxelSideDoubleSpinBox"));
        voxelSideDoubleSpinBox->setMaximum(1);
        voxelSideDoubleSpinBox->setSingleStep(0.1);
        voxelSideDoubleSpinBox->setValue(0.1);

        gridLayout->addWidget(voxelSideDoubleSpinBox, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(87, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SimpleDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 1, 1, 1);


        retranslateUi(SimpleDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SimpleDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SimpleDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SimpleDialog);
    } // setupUi

    void retranslateUi(QDialog *SimpleDialog)
    {
        SimpleDialog->setWindowTitle(QApplication::translate("SimpleDialog", "Simple", 0));
        label->setText(QApplication::translate("SimpleDialog", "NeighborPoints:", 0));
        label_2->setText(QApplication::translate("SimpleDialog", "Planarity:", 0));
        label_3->setText(QApplication::translate("SimpleDialog", "VoxelSide:", 0));
    } // retranslateUi

};

namespace Ui {
    class SimpleDialog: public Ui_SimpleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEDIALOG_H
