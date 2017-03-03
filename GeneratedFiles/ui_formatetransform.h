/********************************************************************************
** Form generated from reading UI file 'formatetransform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMATETRANSFORM_H
#define UI_FORMATETRANSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_FormateTransformDialog
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLineEdit *rawLineEdit;
    QPushButton *rawPushButton;
    QLabel *label_2;
    QLineEdit *transLineEdit;
    QPushButton *transPushButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *asciiRadioButton;
    QRadioButton *pcdRadioButton;
    QRadioButton *lasRadioButton;
    QRadioButton *lazRadioButton;
    QRadioButton *dxfRadioButton;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QPushButton *transformPushButton;
    QPushButton *cancelPushButton;

    void setupUi(QDialog *FormateTransformDialog)
    {
        if (FormateTransformDialog->objectName().isEmpty())
            FormateTransformDialog->setObjectName(QStringLiteral("FormateTransformDialog"));
        FormateTransformDialog->resize(395, 155);
        gridLayout_3 = new QGridLayout(FormateTransformDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(FormateTransformDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        rawLineEdit = new QLineEdit(FormateTransformDialog);
        rawLineEdit->setObjectName(QStringLiteral("rawLineEdit"));

        gridLayout_3->addWidget(rawLineEdit, 0, 1, 1, 2);

        rawPushButton = new QPushButton(FormateTransformDialog);
        rawPushButton->setObjectName(QStringLiteral("rawPushButton"));
        rawPushButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rawPushButton->sizePolicy().hasHeightForWidth());
        rawPushButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(rawPushButton, 0, 3, 1, 1);

        label_2 = new QLabel(FormateTransformDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        transLineEdit = new QLineEdit(FormateTransformDialog);
        transLineEdit->setObjectName(QStringLiteral("transLineEdit"));
        transLineEdit->setEnabled(false);

        gridLayout_3->addWidget(transLineEdit, 1, 1, 1, 2);

        transPushButton = new QPushButton(FormateTransformDialog);
        transPushButton->setObjectName(QStringLiteral("transPushButton"));
        transPushButton->setEnabled(false);
        sizePolicy.setHeightForWidth(transPushButton->sizePolicy().hasHeightForWidth());
        transPushButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(transPushButton, 1, 3, 1, 1);

        groupBox = new QGroupBox(FormateTransformDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        asciiRadioButton = new QRadioButton(groupBox);
        asciiRadioButton->setObjectName(QStringLiteral("asciiRadioButton"));
        asciiRadioButton->setEnabled(false);

        gridLayout->addWidget(asciiRadioButton, 0, 0, 1, 1);

        pcdRadioButton = new QRadioButton(groupBox);
        pcdRadioButton->setObjectName(QStringLiteral("pcdRadioButton"));
        pcdRadioButton->setEnabled(false);

        gridLayout->addWidget(pcdRadioButton, 0, 1, 1, 1);

        lasRadioButton = new QRadioButton(groupBox);
        lasRadioButton->setObjectName(QStringLiteral("lasRadioButton"));
        lasRadioButton->setEnabled(false);

        gridLayout->addWidget(lasRadioButton, 0, 2, 1, 1);

        lazRadioButton = new QRadioButton(groupBox);
        lazRadioButton->setObjectName(QStringLiteral("lazRadioButton"));
        lazRadioButton->setEnabled(false);

        gridLayout->addWidget(lazRadioButton, 0, 3, 1, 1);

        dxfRadioButton = new QRadioButton(groupBox);
        dxfRadioButton->setObjectName(QStringLiteral("dxfRadioButton"));
        dxfRadioButton->setEnabled(false);

        gridLayout->addWidget(dxfRadioButton, 0, 4, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(192, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 3, 0, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        transformPushButton = new QPushButton(FormateTransformDialog);
        transformPushButton->setObjectName(QStringLiteral("transformPushButton"));
        transformPushButton->setEnabled(false);
        sizePolicy.setHeightForWidth(transformPushButton->sizePolicy().hasHeightForWidth());
        transformPushButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(transformPushButton, 0, 0, 1, 1);

        cancelPushButton = new QPushButton(FormateTransformDialog);
        cancelPushButton->setObjectName(QStringLiteral("cancelPushButton"));
        sizePolicy.setHeightForWidth(cancelPushButton->sizePolicy().hasHeightForWidth());
        cancelPushButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(cancelPushButton, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 3, 2, 1, 2);


        retranslateUi(FormateTransformDialog);
        QObject::connect(cancelPushButton, SIGNAL(clicked()), FormateTransformDialog, SLOT(reject()));
        QObject::connect(transformPushButton, SIGNAL(clicked()), FormateTransformDialog, SLOT(accept()));
        QObject::connect(asciiRadioButton, SIGNAL(toggled(bool)), transformPushButton, SLOT(setEnabled(bool)));
        QObject::connect(pcdRadioButton, SIGNAL(toggled(bool)), transformPushButton, SLOT(setEnabled(bool)));
        QObject::connect(lasRadioButton, SIGNAL(toggled(bool)), transformPushButton, SLOT(setEnabled(bool)));
        QObject::connect(lazRadioButton, SIGNAL(toggled(bool)), transformPushButton, SLOT(setEnabled(bool)));
        QObject::connect(dxfRadioButton, SIGNAL(toggled(bool)), transformPushButton, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(FormateTransformDialog);
    } // setupUi

    void retranslateUi(QDialog *FormateTransformDialog)
    {
        FormateTransformDialog->setWindowTitle(QApplication::translate("FormateTransformDialog", "FormateTransform", 0));
        label->setText(QApplication::translate("FormateTransformDialog", "RawData:", 0));
        rawPushButton->setText(QApplication::translate("FormateTransformDialog", "....", 0));
        label_2->setText(QApplication::translate("FormateTransformDialog", "TransData:", 0));
        transPushButton->setText(QApplication::translate("FormateTransformDialog", "....", 0));
        groupBox->setTitle(QApplication::translate("FormateTransformDialog", "ChoiceFormate", 0));
        asciiRadioButton->setText(QApplication::translate("FormateTransformDialog", "Ascii", 0));
        pcdRadioButton->setText(QApplication::translate("FormateTransformDialog", "Pcd", 0));
        lasRadioButton->setText(QApplication::translate("FormateTransformDialog", "Las", 0));
        lazRadioButton->setText(QApplication::translate("FormateTransformDialog", "Laz", 0));
        dxfRadioButton->setText(QApplication::translate("FormateTransformDialog", "Dxf", 0));
        transformPushButton->setText(QApplication::translate("FormateTransformDialog", "Transform", 0));
        cancelPushButton->setText(QApplication::translate("FormateTransformDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class FormateTransformDialog: public Ui_FormateTransformDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMATETRANSFORM_H
