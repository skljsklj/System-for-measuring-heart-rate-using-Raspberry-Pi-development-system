/********************************************************************************
** Form generated from reading UI file 'Hearbeats.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEARBEATS_H
#define UI_HEARBEATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLCDNumber *lcdNumber;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Start;
    QPushButton *End;
    QCheckBox *checkBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1345, 856);
        lcdNumber = new QLCDNumber(Dialog);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(540, 550, 271, 101));
        lcdNumber->setStyleSheet(QStringLiteral("font: 75 italic 22pt \"PibotoLt\";"));
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setDigitCount(5);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(0));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(330, 410, 881, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Start = new QPushButton(layoutWidget);
        Start->setObjectName(QStringLiteral("Start"));

        horizontalLayout->addWidget(Start);

        End = new QPushButton(layoutWidget);
        End->setObjectName(QStringLiteral("End"));

        horizontalLayout->addWidget(End);

        checkBox = new QCheckBox(Dialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(170, 570, 271, 41));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        Start->setText(QApplication::translate("Dialog", "Start", nullptr));
        End->setText(QApplication::translate("Dialog", "End", nullptr));
        checkBox->setText(QApplication::translate("Dialog", "Change rows on lcd display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEARBEATS_H
