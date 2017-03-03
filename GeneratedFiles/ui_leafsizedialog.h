/********************************************************************************
** Form generated from reading UI file 'leafsizedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEAFSIZEDIALOG_H
#define UI_LEAFSIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_LeafSizeDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *longDoubleSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *widthDoubleSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *highDoubleSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LeafSizeDialog)
    {
        if (LeafSizeDialog->objectName().isEmpty())
            LeafSizeDialog->setObjectName(QStringLiteral("LeafSizeDialog"));
        LeafSizeDialog->resize(296, 86);
        gridLayout = new QGridLayout(LeafSizeDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(LeafSizeDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        longDoubleSpinBox = new QDoubleSpinBox(LeafSizeDialog);
        longDoubleSpinBox->setObjectName(QStringLiteral("longDoubleSpinBox"));
        longDoubleSpinBox->setMinimum(0.01);
        longDoubleSpinBox->setMaximum(5);
        longDoubleSpinBox->setSingleStep(0.01);
        longDoubleSpinBox->setValue(0.1);

        horizontalLayout->addWidget(longDoubleSpinBox);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(LeafSizeDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        widthDoubleSpinBox = new QDoubleSpinBox(LeafSizeDialog);
        widthDoubleSpinBox->setObjectName(QStringLiteral("widthDoubleSpinBox"));
        widthDoubleSpinBox->setMinimum(0.01);
        widthDoubleSpinBox->setMaximum(5);
        widthDoubleSpinBox->setSingleStep(0.01);
        widthDoubleSpinBox->setValue(0.1);

        horizontalLayout_2->addWidget(widthDoubleSpinBox);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(LeafSizeDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        highDoubleSpinBox = new QDoubleSpinBox(LeafSizeDialog);
        highDoubleSpinBox->setObjectName(QStringLiteral("highDoubleSpinBox"));
        highDoubleSpinBox->setMinimum(0.01);
        highDoubleSpinBox->setMaximum(5);
        highDoubleSpinBox->setSingleStep(0.01);
        highDoubleSpinBox->setValue(0.1);

        horizontalLayout_3->addWidget(highDoubleSpinBox);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(LeafSizeDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(LeafSizeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LeafSizeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LeafSizeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LeafSizeDialog);
    } // setupUi

    void retranslateUi(QDialog *LeafSizeDialog)
    {
        LeafSizeDialog->setWindowTitle(QApplication::translate("LeafSizeDialog", "LeafSize", 0));
        label->setText(QApplication::translate("LeafSizeDialog", "Long", 0));
        label_2->setText(QApplication::translate("LeafSizeDialog", "Width", 0));
        label_3->setText(QApplication::translate("LeafSizeDialog", "High", 0));
    } // retranslateUi

};

namespace Ui {
    class LeafSizeDialog: public Ui_LeafSizeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEAFSIZEDIALOG_H
