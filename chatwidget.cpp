#include "chatwidget.h"
#include "filemanager.h"
#include "ui_chatwidget.h"

#include <QInputDialog>

ChatWidget::ChatWidget(User& user, const bool& isfriend,const QString& rname, const bool& online, QWidget *parent)
    : QWidget(parent),user(user),isfriend(isfriend),online(online)
    , ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    img(user.imgPath);
    info();
    if(!rname.isEmpty())
        ui->friendname->setText(rname);
}



ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::img(const QString &name)
{

    //头像
    QString imgname=getImage(name);
    QImage image(imgname);
    // 计算缩放比例
    image = image.scaled(QSize(ui->img->width(), ui->img->height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // 创建图标
    QIcon icon(QPixmap::fromImage(image));
    ui->img->setIcon(icon);
    ui->img->setIconSize(QSize(ui->img->width(), ui->img->height()));
}

void ChatWidget::info()
{
    ui->friendname->setText(user.name);
    ui->act->setText(user.account);
    ui->change->setIcon(QIcon(":/img/edit.png"));
    ui->change->setDisabled(!isfriend);
    if(online){
        ui->status->setText("在线");
        ui->status->setStyleSheet("#status{color:green}");
    }else{
        ui->status->setText("离线");
    }
    if(isfriend){
        ui->pushButton->setText("删除好友");
        ui->pushButton->setStyleSheet("#pushButton{color:red;}");
    }else{
        ui->pushButton->setText("加为好友");
        ui->pushButton->setStyleSheet("#pushButton{color:green;}");
    }
}

void ChatWidget::on_pushButton_clicked()
{
    if(isfriend){//删除好友
        DataHead head=DataHead::dataHead("dlefriend");
        QJsonObject jo;
        jo.insert("account", WApplication::getAccount());
        jo.insert("friend", user.account);
        DataResult result(0,QJsonDocument(jo));
        WApplication::getSocket()->sendText(head,result);
        isfriend=false;
        info();
    }else{//加为好友
        bool ok=false;
        QString note=QInputDialog::getText(nullptr, "加为好友", "备注", QLineEdit::Normal, QString(), &ok);
        if(ok){
            DataHead head=DataHead::dataHead("invite");
            QJsonObject jo;
            jo.insert("inviter", WApplication::getAccount());//邀请人，自己
            jo.insert("invitees", user.account);//被邀请人
            jo.insert("note", note);
            DataResult result(0, QJsonDocument(jo));
            WApplication::getSocket()->sendText(head, result);
            ui->pushButton->setDisabled(true);
        }
    }
}

