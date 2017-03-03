/********************************************************************************
** Form generated from reading UI file 'contourdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTOURDIALOG_H
#define UI_CONTOURDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ContourDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ContourDialog)
    {
        if (ContourDialog->objectName().isEmpty())
            ContourDialog->setObjectName(QStringLiteral("ContourDialog"));
        ContourDialog->resize(198, 67);
        ContourDialog->setMinimumSize(QSize(198, 67));
        ContourDialog->setMaximumSize(QSize(198, 67));
        gridLayout = new QGridLayout(ContourDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ContourDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(ContourDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(10);
        spinBox->setValue(30);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(ContourDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(ContourDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ContourDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ContourDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ContourDialog);
    } // setupUi

    void retranslateUi(QDialog *ContourDialog)
    {
        ContourDialog->setWindowTitle(QApplication::translate("ContourDialog", "SetContour", 0));
        label->setText(QApplication::translate("ContourDialog", "Neighbor points:", 0));
    } // retranslateUi

};

namespace Ui {
    class ContourDialog: public Ui_ContourDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTOURDIALOG_H
