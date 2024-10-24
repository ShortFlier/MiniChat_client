/********************************************************************************
** Form generated from reading UI file 'rgtcfmwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RGTCFMWIDGET_H
#define UI_RGTCFMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RgtCfmWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_6;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *email;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *code;
    QPushButton *again;
    QLabel *error;
    QPushButton *back;
    QPushButton *submit;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *tip;
    QLabel *label_7;
    QPushButton *home;

    void setupUi(QWidget *RgtCfmWidget)
    {
        if (RgtCfmWidget->objectName().isEmpty())
            RgtCfmWidget->setObjectName("RgtCfmWidget");
        RgtCfmWidget->resize(320, 500);
        RgtCfmWidget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color:white;\n"
"}"));
        label = new QLabel(RgtCfmWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 70, 51, 51));
        label->setMaximumSize(QSize(51, 51));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/app_icon.png")));
        label_2 = new QLabel(RgtCfmWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 60, 103, 78));
        label_2->setStyleSheet(QString::fromUtf8("color:white;\n"
"font-size:20px;"));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3 = new QLabel(RgtCfmWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 110, 121, 71));
        label_3->setStyleSheet(QString::fromUtf8("font-size:28px;\n"
"font-weight:bold;\n"
"color:black;"));
        label_6 = new QLabel(RgtCfmWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 200, 291, 16));
        horizontalLayoutWidget = new QWidget(RgtCfmWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 170, 291, 23));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout->addWidget(label_4);

        email = new QLabel(horizontalLayoutWidget);
        email->setObjectName("email");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(email->sizePolicy().hasHeightForWidth());
        email->setSizePolicy(sizePolicy);
        email->setStyleSheet(QString::fromUtf8("color:#b5e5ff;\n"
"font-size:16px;"));

        horizontalLayout->addWidget(email);

        horizontalLayoutWidget_2 = new QWidget(RgtCfmWidget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(20, 220, 231, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        code = new QLineEdit(horizontalLayoutWidget_2);
        code->setObjectName("code");

        horizontalLayout_2->addWidget(code);

        again = new QPushButton(horizontalLayoutWidget_2);
        again->setObjectName("again");
        again->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(again);

        error = new QLabel(RgtCfmWidget);
        error->setObjectName("error");
        error->setGeometry(QRect(60, 250, 251, 16));
        error->setStyleSheet(QString::fromUtf8("color:red;"));
        back = new QPushButton(RgtCfmWidget);
        back->setObjectName("back");
        back->setGeometry(QRect(10, 40, 41, 21));
        back->setCursor(QCursor(Qt::PointingHandCursor));
        submit = new QPushButton(RgtCfmWidget);
        submit->setObjectName("submit");
        submit->setGeometry(QRect(20, 270, 41, 31));
        submit->setCursor(QCursor(Qt::PointingHandCursor));
        verticalLayoutWidget = new QWidget(RgtCfmWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 320, 191, 31));
        tip = new QVBoxLayout(verticalLayoutWidget);
        tip->setObjectName("tip");
        tip->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName("label_7");

        tip->addWidget(label_7);

        home = new QPushButton(verticalLayoutWidget);
        home->setObjectName("home");
        home->setCursor(QCursor(Qt::PointingHandCursor));
        home->setStyleSheet(QString::fromUtf8("border:none;\n"
"color:#aaffff;"));

        tip->addWidget(home);


        retranslateUi(RgtCfmWidget);

        QMetaObject::connectSlotsByName(RgtCfmWidget);
    } // setupUi

    void retranslateUi(QWidget *RgtCfmWidget)
    {
        RgtCfmWidget->setWindowTitle(QCoreApplication::translate("RgtCfmWidget", "Form", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("RgtCfmWidget", "MiniChat", nullptr));
        label_3->setText(QCoreApplication::translate("RgtCfmWidget", "\345\210\233\345\273\272\350\264\246\346\210\267", nullptr));
        label_6->setText(QCoreApplication::translate("RgtCfmWidget", "\345\217\221\351\200\201\351\252\214\350\257\201\351\202\256\344\273\266\357\274\214\350\257\267\345\241\253\345\206\231\346\224\266\345\210\260\347\232\204\351\252\214\350\257\201\344\277\241\346\201\257\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("RgtCfmWidget", "\346\210\221\344\273\254\345\267\262\345\220\221\357\274\232 ", nullptr));
        email->setText(QCoreApplication::translate("RgtCfmWidget", "someone@exmple.com", nullptr));
        label_5->setText(QCoreApplication::translate("RgtCfmWidget", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        again->setText(QCoreApplication::translate("RgtCfmWidget", "\351\207\215\346\226\260\345\217\221\351\200\201", nullptr));
        error->setText(QCoreApplication::translate("RgtCfmWidget", "\351\252\214\350\257\201\347\240\201\351\224\231\350\257\257", nullptr));
        back->setText(QCoreApplication::translate("RgtCfmWidget", "\350\277\224\345\233\236", nullptr));
        submit->setText(QCoreApplication::translate("RgtCfmWidget", "\346\263\250\345\206\214", nullptr));
        label_7->setText(QCoreApplication::translate("RgtCfmWidget", "\344\275\240\345\267\262\345\256\214\346\210\220\346\263\250\345\206\214\357\274\214\350\264\246\345\217\267\345\267\262\345\217\221\351\200\201\350\207\263\351\202\256\347\256\261", nullptr));
        home->setText(QCoreApplication::translate("RgtCfmWidget", "\347\202\271\346\210\221\350\277\224\345\233\236\347\231\273\345\205\245\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RgtCfmWidget: public Ui_RgtCfmWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RGTCFMWIDGET_H
