/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAbout
{
public:
    QLabel *label;

    void setupUi(QWidget *FormAbout)
    {
        if (FormAbout->objectName().isEmpty())
            FormAbout->setObjectName(QString::fromUtf8("FormAbout"));
        FormAbout->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ICO/Ico/about.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FormAbout->setWindowIcon(icon);
        label = new QLabel(FormAbout);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 371, 81));
        QFont font;
        font.setPointSize(48);
        label->setFont(font);

        retranslateUi(FormAbout);

        QMetaObject::connectSlotsByName(FormAbout);
    } // setupUi

    void retranslateUi(QWidget *FormAbout)
    {
        FormAbout->setWindowTitle(QApplication::translate("FormAbout", "Form", nullptr));
        label->setText(QApplication::translate("FormAbout", "Wave-viewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormAbout: public Ui_FormAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
