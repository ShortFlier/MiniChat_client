/********************************************************************************
** Form generated from reading UI file 'registwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTWIDGET_H
#define UI_REGISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistWidget
{
public:
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *email;
    QLabel *error;
    QLabel *label_5;
    QPushButton *submit;
    QPushButton *back;

    void setupUi(QWidget *RegistWidget)
    {
        if (RegistWidget->objectName().isEmpty())
            RegistWidget->setObjectName("RegistWidget");
        RegistWidget->resize(320, 500);
        RegistWidget->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:rgb(235, 235, 235);\n"
"color:rgb(50,50,50);\n"
"}"));
        label_2 = new QLabel(RegistWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 60, 103, 78));
        label_2->setStyleSheet(QString::fromUtf8("color:white;\n"
"font-size:20px;"));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label = new QLabel(RegistWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 70, 51, 51));
        label->setMaximumSize(QSize(51, 51));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/app_icon.png")));
        label_3 = new QLabel(RegistWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 110, 121, 71));
        label_3->setStyleSheet(QString::fromUtf8("font-size:28px;\n"
"font-weight:bold;"));
        email = new QLineEdit(RegistWidget);
        email->setObjectName("email");
        email->setGeometry(QRect(20, 200, 271, 31));
        email->setStyleSheet(QString::fromUtf8("border-top:none;\n"
"border-right:none;\n"
"border-left:none;\n"
"border-color:rgb(255, 170, 255)"));
        error = new QLabel(RegistWidget);
        error->setObjectName("error");
        error->setGeometry(QRect(20, 170, 271, 16));
        error->setStyleSheet(QString::fromUtf8("color:red;"));
        label_5 = new QLabel(RegistWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 240, 271, 16));
        label_5->setStyleSheet(QString::fromUtf8("color:white"));
        submit = new QPushButton(RegistWidget);
        submit->setObjectName("submit");
        submit->setGeometry(QRect(230, 270, 56, 31));
        submit->setCursor(QCursor(Qt::PointingHandCursor));
        submit->setStyleSheet(QString::fromUtf8("background-color:rgb(235, 235, 235);\n"
"color:rgb(50,50,50);"));
        back = new QPushButton(RegistWidget);
        back->setObjectName("back");
        back->setGeometry(QRect(10, 40, 41, 21));
        back->setCursor(QCursor(Qt::PointingHandCursor));
        back->setStyleSheet(QString::fromUtf8("background-color:rgb(235, 235, 235);\n"
"color:rgb(50,50,50);"));

        retranslateUi(RegistWidget);

        QMetaObject::connectSlotsByName(RegistWidget);
    } // setupUi

    void retranslateUi(QWidget *RegistWidget)
    {
        RegistWidget->setWindowTitle(QCoreApplication::translate("RegistWidget", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("RegistWidget", "MiniChat", nullptr));
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("RegistWidget", "\345\210\233\345\273\272\350\264\246\346\210\267", nullptr));
        email->setInputMask(QString());
        email->setPlaceholderText(QCoreApplication::translate("RegistWidget", "someone@exmple.com", nullptr));
        error->setText(QCoreApplication::translate("RegistWidget", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        label_5->setText(QCoreApplication::translate("RegistWidget", "\344\275\277\347\224\250\346\234\211\346\225\210\347\232\204\351\202\256\347\256\261\345\217\267\344\273\245\345\256\214\346\210\220\346\263\250\345\206\214", nullptr));
        submit->setText(QCoreApplication::translate("RegistWidget", "\345\256\214\346\210\220", nullptr));
        back->setText(QCoreApplication::translate("RegistWidget", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistWidget: public Ui_RegistWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTWIDGET_H
