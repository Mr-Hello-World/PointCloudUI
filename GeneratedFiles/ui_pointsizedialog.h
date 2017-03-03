/********************************************************************************
** Form generated from reading UI file 'pointsizedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTSIZEDIALOG_H
#define UI_POINTSIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PointSizeDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PointSizeDialog)
    {
        if (PointSizeDialog->objectName().isEmpty())
            PointSizeDialog->setObjectName(QStringLiteral("PointSizeDialog"));
        PointSizeDialog->resize(286, 97);
        PointSizeDialog->setMinimumSize(QSize(286, 97));
        PointSizeDialog->setMaximumSize(QSize(286, 97));
        gridLayout = new QGridLayout(PointSizeDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(PointSizeDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSlider = new QSlider(PointSizeDialog);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(10);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        spinBox = new QSpinBox(PointSizeDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(10);

        horizontalLayout->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okButton = new QPushButton(PointSizeDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout_2->addWidget(okButton);

        cancelButton = new QPushButton(PointSizeDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(PointSizeDialog);
        QObject::connect(okButton, SIGNAL(clicked()), PointSizeDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), PointSizeDialog, SLOT(reject()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(PointSizeDialog);
    } // setupUi

    void retranslateUi(QDialog *PointSizeDialog)
    {
        PointSizeDialog->setWindowTitle(QApplication::translate("PointSizeDialog", "PointSize", 0));
        label->setText(QApplication::translate("PointSizeDialog", "PointSize:", 0));
        okButton->setText(QApplication::translate("PointSizeDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("PointSizeDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class PointSizeDialog: public Ui_PointSizeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTSIZEDIALOG_H
