/********************************************************************************
** Form generated from reading UI file 'openasciidialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENASCIIDIALOG_H
#define UI_OPENASCIIDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenAsciiDialog
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *filenameLineEdit;
    QLabel *label_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *OpenAsciiDialog)
    {
        if (OpenAsciiDialog->objectName().isEmpty())
            OpenAsciiDialog->setObjectName(QStringLiteral("OpenAsciiDialog"));
        OpenAsciiDialog->resize(473, 405);
        gridLayout_2 = new QGridLayout(OpenAsciiDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(OpenAsciiDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        filenameLineEdit = new QLineEdit(OpenAsciiDialog);
        filenameLineEdit->setObjectName(QStringLiteral("filenameLineEdit"));

        horizontalLayout->addWidget(filenameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(OpenAsciiDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);


        verticalLayout_2->addLayout(verticalLayout);

        widget = new QWidget(OpenAsciiDialog);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        verticalLayout_2->addWidget(widget);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 3);

        okButton = new QPushButton(OpenAsciiDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout_2->addWidget(okButton, 2, 1, 1, 1);

        cancelButton = new QPushButton(OpenAsciiDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout_2->addWidget(cancelButton, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(173, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);


        retranslateUi(OpenAsciiDialog);
        QObject::connect(okButton, SIGNAL(clicked()), OpenAsciiDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), OpenAsciiDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(OpenAsciiDialog);
    } // setupUi

    void retranslateUi(QDialog *OpenAsciiDialog)
    {
        OpenAsciiDialog->setWindowTitle(QApplication::translate("OpenAsciiDialog", "Open Ascii File", 0));
        label->setText(QApplication::translate("OpenAsciiDialog", "Filename:", 0));
        label_2->setText(QApplication::translate("OpenAsciiDialog", "Here are the first lines of this file.", 0));
        okButton->setText(QApplication::translate("OpenAsciiDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("OpenAsciiDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class OpenAsciiDialog: public Ui_OpenAsciiDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENASCIIDIALOG_H
