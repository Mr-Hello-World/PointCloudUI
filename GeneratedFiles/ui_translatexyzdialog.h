/********************************************************************************
** Form generated from reading UI file 'translatexyzdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSLATEXYZDIALOG_H
#define UI_TRANSLATEXYZDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_TransXYZDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txLineEdit;
    QLabel *label_2;
    QLineEdit *tyLineEdit;
    QLabel *label_3;
    QLineEdit *tzLineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TransXYZDialog)
    {
        if (TransXYZDialog->objectName().isEmpty())
            TransXYZDialog->setObjectName(QStringLiteral("TransXYZDialog"));
        TransXYZDialog->resize(313, 87);
        gridLayout = new QGridLayout(TransXYZDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(133, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(TransXYZDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        txLineEdit = new QLineEdit(TransXYZDialog);
        txLineEdit->setObjectName(QStringLiteral("txLineEdit"));

        horizontalLayout->addWidget(txLineEdit);

        label_2 = new QLabel(TransXYZDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        tyLineEdit = new QLineEdit(TransXYZDialog);
        tyLineEdit->setObjectName(QStringLiteral("tyLineEdit"));

        horizontalLayout->addWidget(tyLineEdit);

        label_3 = new QLabel(TransXYZDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        tzLineEdit = new QLineEdit(TransXYZDialog);
        tzLineEdit->setObjectName(QStringLiteral("tzLineEdit"));

        horizontalLayout->addWidget(tzLineEdit);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 4);

        buttonBox = new QDialogButtonBox(TransXYZDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 2, 1, 2);


        retranslateUi(TransXYZDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TransXYZDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TransXYZDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TransXYZDialog);
    } // setupUi

    void retranslateUi(QDialog *TransXYZDialog)
    {
        TransXYZDialog->setWindowTitle(QApplication::translate("TransXYZDialog", "TransXYZ", 0));
        label->setText(QApplication::translate("TransXYZDialog", "TX", 0));
        label_2->setText(QApplication::translate("TransXYZDialog", "TY", 0));
        label_3->setText(QApplication::translate("TransXYZDialog", "TZ", 0));
    } // retranslateUi

};

namespace Ui {
    class TransXYZDialog: public Ui_TransXYZDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSLATEXYZDIALOG_H
