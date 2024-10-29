#include "rgtcfmwidget.h"
#include "ui_rgtcfmwidget.h"

#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <QJsonObject>

RgtCfmWidget::RgtCfmWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RgtCfmWidget)
{
    ui->setupUi(this);

    //设置固定宽高
    setFixedSize(320,500);

    ui->error->close();
    ui->home->close();
    ui->label_7->close();
}

RgtCfmWidget::~RgtCfmWidget()
{
    delete ui;
}

void RgtCfmWidget::email(const QString &email)
{
    _email=email;
    ui->email->setText(_email);
    //发送验证码

}

void RgtCfmWidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix(":/img/background.jpg");
    paint.drawPixmap(0,0,width(),height(),pix);
}

void RgtCfmWidget::error(const QString &msg)
{
    ui->error->setText(msg);
    ui->error->show();
    qDebug()<<msg;
}

void RgtCfmWidget::handler(DataHead &head, DataResult &result)
{
    //注册成功跳转登入界面
    if(result.code==DataResult::code_success){
        on_home_clicked();
    }else
        QMessageBox::critical(nullptr, "错误", result.jsdata.object().value("msg").toString());
}

void RgtCfmWidget::on_back_clicked()
{
    emit back();
}


void RgtCfmWidget::on_home_clicked()
{
    ui->home->close();
    ui->label_7->close();
    emit home();
}


void RgtCfmWidget::on_again_clicked()
{
    ui->again->setDisabled(true);
    //设置一分钟后可用
    QTimer::singleShot(60*1000,[this](){
        ui->again->setDisabled(false);
    });
    //重新发送验证码
    emit again_code(_email);
}

//点击注册
void RgtCfmWidget::on_submit_clicked()
{
    ui->error->close();
    QString code=ui->code->text().trimmed();
    if(code.length()==0){
        error("验证码不能为空");
        return;
    }
    emit submit(_email, code);
}

