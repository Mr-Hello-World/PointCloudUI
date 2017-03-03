/********************************************************************************
** Form generated from reading UI file 'choiceout.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICEOUT_H
#define UI_CHOICEOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_ChoiceOutDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *treeRadioButton;
    QRadioButton *lightRadioButton;
    QRadioButton *electRadioButton;
    QRadioButton *othersRadioButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChoiceOutDialog)
    {
        if (ChoiceOutDialog->objectName().isEmpty())
            ChoiceOutDialog->setObjectName(QStringLiteral("ChoiceOutDialog"));
        ChoiceOutDialog->resize(268, 75);
        gridLayout = new QGridLayout(ChoiceOutDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        treeRadioButton = new QRadioButton(ChoiceOutDialog);
        treeRadioButton->setObjectName(QStringLiteral("treeRadioButton"));

        horizontalLayout->addWidget(treeRadioButton);

        lightRadioButton = new QRadioButton(ChoiceOutDialog);
        lightRadioButton->setObjectName(QStringLiteral("lightRadioButton"));

        horizontalLayout->addWidget(lightRadioButton);

        electRadioButton = new QRadioButton(ChoiceOutDialog);
        electRadioButton->setObjectName(QStringLiteral("electRadioButton"));

        horizontalLayout->addWidget(electRadioButton);

        othersRadioButton = new QRadioButton(ChoiceOutDialog);
        othersRadioButton->setObjectName(QStringLiteral("othersRadioButton"));

        horizontalLayout->addWidget(othersRadioButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ChoiceOutDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(false);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(ChoiceOutDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChoiceOutDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChoiceOutDialog, SLOT(reject()));
        QObject::connect(treeRadioButton, SIGNAL(clicked(bool)), buttonBox, SLOT(setEnabled(bool)));
        QObject::connect(lightRadioButton, SIGNAL(clicked(bool)), buttonBox, SLOT(setEnabled(bool)));
        QObject::connect(electRadioButton, SIGNAL(clicked(bool)), buttonBox, SLOT(setEnabled(bool)));
        QObject::connect(othersRadioButton, SIGNAL(clicked(bool)), buttonBox, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(ChoiceOutDialog);
    } // setupUi

    void retranslateUi(QDialog *ChoiceOutDialog)
    {
        ChoiceOutDialog->setWindowTitle(QApplication::translate("ChoiceOutDialog", "Choice", 0));
        treeRadioButton->setText(QApplication::translate("ChoiceOutDialog", "Trees", 0));
        lightRadioButton->setText(QApplication::translate("ChoiceOutDialog", "Lights", 0));
        electRadioButton->setText(QApplication::translate("ChoiceOutDialog", "Elects", 0));
        othersRadioButton->setText(QApplication::translate("ChoiceOutDialog", "Others", 0));
    } // retranslateUi

};

namespace Ui {
    class ChoiceOutDialog: public Ui_ChoiceOutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOICEOUT_H
