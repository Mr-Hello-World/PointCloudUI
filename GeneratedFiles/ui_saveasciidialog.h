/********************************************************************************
** Form generated from reading UI file 'saveasciidialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEASCIIDIALOG_H
#define UI_SAVEASCIIDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SaveAsciiDialog
{
public:
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *cooPrecisionPinBox;
    QLabel *label_2;
    QComboBox *separatorComboBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SaveAsciiDialog)
    {
        if (SaveAsciiDialog->objectName().isEmpty())
            SaveAsciiDialog->setObjectName(QStringLiteral("SaveAsciiDialog"));
        SaveAsciiDialog->resize(331, 124);
        gridLayout_3 = new QGridLayout(SaveAsciiDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        splitter = new QSplitter(SaveAsciiDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cooPrecisionPinBox = new QSpinBox(layoutWidget);
        cooPrecisionPinBox->setObjectName(QStringLiteral("cooPrecisionPinBox"));
        cooPrecisionPinBox->setMinimum(0);
        cooPrecisionPinBox->setMaximum(16);
        cooPrecisionPinBox->setValue(8);

        gridLayout->addWidget(cooPrecisionPinBox, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        separatorComboBox = new QComboBox(layoutWidget);
        separatorComboBox->setObjectName(QStringLiteral("separatorComboBox"));

        gridLayout->addWidget(separatorComboBox, 1, 1, 1, 1);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(194, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        okButton = new QPushButton(layoutWidget1);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout_2->addWidget(okButton, 0, 0, 1, 1);

        cancelButton = new QPushButton(layoutWidget1);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout_2->addWidget(cancelButton, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        splitter->addWidget(layoutWidget1);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(SaveAsciiDialog);
        QObject::connect(okButton, SIGNAL(clicked()), SaveAsciiDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SaveAsciiDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SaveAsciiDialog);
    } // setupUi

    void retranslateUi(QDialog *SaveAsciiDialog)
    {
        SaveAsciiDialog->setWindowTitle(QApplication::translate("SaveAsciiDialog", "Save Ascii Cloud", 0));
        label->setText(QApplication::translate("SaveAsciiDialog", "coordinates precision", 0));
        label_2->setText(QApplication::translate("SaveAsciiDialog", "separator", 0));
        separatorComboBox->clear();
        separatorComboBox->insertItems(0, QStringList()
         << QApplication::translate("SaveAsciiDialog", "blank ", 0)
         << QApplication::translate("SaveAsciiDialog", "comma,", 0)
         << QApplication::translate("SaveAsciiDialog", "semicolon;", 0)
        );
        okButton->setText(QApplication::translate("SaveAsciiDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("SaveAsciiDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SaveAsciiDialog: public Ui_SaveAsciiDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEASCIIDIALOG_H
