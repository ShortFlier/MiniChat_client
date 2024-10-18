#include "loginwidget.h"
#include "./ui_loginwidget.h"

#include <QPainter>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    //设置固定宽高
    setFixedSize(320,500);

    //注册按钮
    ui->regist->setCursor(Qt::PointingHandCursor);
    ui->regist->move((ui->regist->pos())+QPoint(10,-20));

    //登入按钮
    ui->login->setCursor(Qt::PointingHandCursor);

    ui->err_act->close();
    ui->err_pwd->close();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

//背景图绘制
void LoginWidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix(":/img/background.jpg");
    paint.drawPixmap(0,0,width(),height(),pix);
}

void LoginWidget::on_regist_clicked()
{
    emit swap();
}


void LoginWidget::on_login_clicked()
{
    ui->err_act->close();
    ui->err_pwd->close();
    //账号
    QString account=ui->accout->currentText().trimmed();
    if(account.length()==0){
        actErr("账号不能为空");
        return;
    }
    //格式匹配
    QRegularExpression actPattern(R"(^[1-9][0-9]{8,10}$)");
    QRegularExpressionMatch match = actPattern.match(account);
    if(match.hasMatch()){
        qDebug()<<"账号格式正确";
    }else{
        actErr("账号格式错误");
        return;
    }
    //密码
    QString password=ui->password->text().trimmed();
    if(password.length()==0){
        pwdErr("密码不能为空");
        return;
    }
    //格式匹配
    QRegularExpression pwdPattern(R"(^[1-9a-zA-Z]{7,10}$)");
    match=pwdPattern.match(password);
    if(match.hasMatch()){
        qDebug()<<"密码格式正确";
    }else{
        pwdErr("密码格式错误");
        return;
    }
    qDebug()<<account<<":"<<password;
}

void LoginWidget::actErr(const QString& msg)
{
    ui->err_act->setText(msg);
    ui->err_act->show();
    qDebug()<<msg;
}

void LoginWidget::pwdErr(const QString& msg)
{
    ui->err_pwd->setText(msg);
    ui->err_pwd->show();
    qDebug()<<msg;
}

