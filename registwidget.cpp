#include "registwidget.h"
#include "ui_registwidget.h"

#include <QPainter>
#include <QRegularExpression>

RegistWidget::RegistWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegistWidget)
{
    ui->setupUi(this);

    //设置固定宽高
    setFixedSize(320,500);

    ui->error->close();
}

RegistWidget::~RegistWidget()
{
    delete ui;
}

void RegistWidget::error(const QString &msg)
{
    ui->error->setText(msg);
    ui->error->show();
    qDebug()<<msg;
}

void RegistWidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix(":/img/background.jpg");
    paint.drawPixmap(0,0,width(),height(),pix);
}

void RegistWidget::on_back_clicked()
{
    emit swap();
}


void RegistWidget::on_submit_clicked()
{
    ui->error->close();
    //验证邮箱格式合法性
    QString email=ui->email->text().trimmed();
    if(email.length()==0){
        error("邮箱不能为空");
        ui->email->setText("");
        return;
    }
    qDebug()<<email;
    // 定义邮箱的正则表达式
    QRegularExpression emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    QRegularExpressionMatch match = emailPattern.match(email);
    if(match.hasMatch()){
        qDebug()<<"有效的邮箱格式";
    }else{
        error("邮箱格式错误");
        return;
    }
    //注册程序开启
    emit submit(email);
}

