/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QComboBox *accout;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *password;
    QPushButton *regist;
    QPushButton *login;
    QLabel *err_act;
    QLabel *err_pwd;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName("LoginWidget");
        LoginWidget->resize(320, 500);
        LoginWidget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color:white;\n"
"}\n"
""));
        label = new QLabel(LoginWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 120, 321, 20));
        label->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"color:white;\n"
""));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(LoginWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 140, 321, 20));
        label_2->setStyleSheet(QString::fromUtf8("color:white;"));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gridLayoutWidget = new QWidget(LoginWidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 180, 221, 131));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        accout = new QComboBox(gridLayoutWidget);
        accout->setObjectName("accout");
        accout->setEditable(true);
        accout->setDuplicatesEnabled(false);

        gridLayout->addWidget(accout, 0, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        password = new QLineEdit(gridLayoutWidget);
        password->setObjectName("password");
        password->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(password, 1, 1, 1, 1);

        regist = new QPushButton(LoginWidget);
        regist->setObjectName("regist");
        regist->setGeometry(QRect(210, 310, 56, 18));
        regist->setStyleSheet(QString::fromUtf8("#regist{\n"
"border:none;\n"
"color:#aaffff;\n"
"}"));
        login = new QPushButton(LoginWidget);
        login->setObjectName("login");
        login->setGeometry(QRect(140, 310, 61, 31));
        login->setStyleSheet(QString::fromUtf8("background-color:rgb(235, 235, 235);\n"
"color:rgb(50,50,50);"));
        err_act = new QLabel(LoginWidget);
        err_act->setObjectName("err_act");
        err_act->setGeometry(QRect(80, 230, 191, 16));
        err_act->setStyleSheet(QString::fromUtf8("color:red"));
        err_pwd = new QLabel(LoginWidget);
        err_pwd->setObjectName("err_pwd");
        err_pwd->setGeometry(QRect(80, 280, 191, 16));
        err_pwd->setStyleSheet(QString::fromUtf8("color:red"));

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "LoginWidget", nullptr));
        label->setText(QCoreApplication::translate("LoginWidget", "\346\254\242\350\277\216\344\275\277\347\224\250 MiniChat", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWidget", "\350\257\267\347\231\273\345\205\245...", nullptr));
        label_4->setText(QCoreApplication::translate("LoginWidget", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("LoginWidget", "\350\264\246\345\217\267\357\274\232", nullptr));
        password->setInputMask(QString());
        regist->setText(QCoreApplication::translate("LoginWidget", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        login->setText(QCoreApplication::translate("LoginWidget", "\347\231\273\345\205\245", nullptr));
        err_act->setText(QCoreApplication::translate("LoginWidget", "\350\264\246\345\217\267\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        err_pwd->setText(QCoreApplication::translate("LoginWidget", "\345\257\206\347\240\201\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
