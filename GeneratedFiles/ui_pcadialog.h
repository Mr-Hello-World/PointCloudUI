/********************************************************************************
** Form generated from reading UI file 'pcadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCADIALOG_H
#define UI_PCADIALOG_H

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

class Ui_PCADialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PCADialog)
    {
        if (PCADialog->objectName().isEmpty())
            PCADialog->setObjectName(QStringLiteral("PCADialog"));
        PCADialog->resize(242, 114);
        PCADialog->setMinimumSize(QSize(242, 114));
        PCADialog->setMaximumSize(QSize(242, 114));
        gridLayout = new QGridLayout(PCADialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(PCADialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(PCADialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(5);
        spinBox->setValue(30);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        label_2 = new QLabel(PCADialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(PCADialog);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMaximum(1);
        doubleSpinBox->setSingleStep(0.1);
        doubleSpinBox->setValue(0.3);

        gridLayout->addWidget(doubleSpinBox, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(PCADialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(PCADialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PCADialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PCADialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PCADialog);
    } // setupUi

    void retranslateUi(QDialog *PCADialog)
    {
        PCADialog->setWindowTitle(QApplication::translate("PCADialog", "PCA", 0));
        label->setText(QApplication::translate("PCADialog", "NeighborPoints:", 0));
        label_2->setText(QApplication::translate("PCADialog", "Planarity:", 0));
    } // retranslateUi

};

namespace Ui {
    class PCADialog: public Ui_PCADialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCADIALOG_H
