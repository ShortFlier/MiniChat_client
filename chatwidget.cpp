
#include "chatdisplayer.h"
#include "chatwidget.h"
#include "filemanager.h"
#include "mapper.h"
#include "ui_chatwidget.h"

#include <QInputDialog>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileDialog>

ChatWidget::ChatWidget(User& user, const bool& isfriend,const QString& rname, const bool& online, QWidget *parent)
    : QWidget(parent),user(user),isfriend(isfriend),online(online)
    , ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    img(user.imgPath);
    info();
    if(!rname.isEmpty())
        ui->friendname->setText(rname);

    layout=new QVBoxLayout();
    ui->contents->setLayout(layout);
    ui->scrollArea->setWidgetResizable(false);
    historymsg();
}



ChatWidget::~ChatWidget()
{
    delete ui;
    delete layout;
}

void ChatWidget::reciver(const QString &act, QJsonArray &data)
{
    if(act==user.account){
        qDebug()<<"msg count: "<<data.size();
        for(int i=0; i<data.size(); ++i){
            Information info=Information::enjson(data.at(i).toObject());
            dismsg(info);
        }
    }
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

    ui->send->setIcon(QIcon(":/img/send.png"));
    ui->sendimg->setIcon(QIcon(":/img/image.png"));
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
    if(isfriend){
        ui->chatdisplay->show();
        ui->input->show();
    }else{
        ui->chatdisplay->hide();
        ui->input->hide();
    }
}

void ChatWidget::dismsg(Information &info)
{
    ChatDisplayer* chat=new ChatDisplayer(info,ui->contents);
    layout->addWidget(chat);
    h+=chat->height();
    ui->contents->resize(ui->contents->width(), h);
    // 将滚动条滚动到最底部
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->value());
}

void ChatWidget::historymsg()
{
    std::vector<Information> infos=minstanse->getInfos(user.account);
    for(int i=0; i<infos.size(); ++i){
        dismsg(infos.at(i));
    }
}

void ChatWidget::on_pushButton_clicked()
{
    if(isfriend){//删除好友
        auto reply = QMessageBox::question(nullptr, "确认删除",
                                      "您确定要删除此好友吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
            DataHead head=DataHead::dataHead("dlefriend");
            QJsonObject jo;
            jo.insert("account", WApplication::getAccount());
            jo.insert("friend", user.account);
            DataResult result(0,QJsonDocument(jo));
            WApplication::getSocket()->sendText(head,result);
            isfriend=false;
            info();
        }
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


void ChatWidget::on_textEdit_textChanged()
{
    // 根据内容计算高度
    int maxh=100;
    QSize size = ui->textEdit->document()->size().toSize();
    int newHeight = size.height() + 10; // 额外加一些边距
    ui->textEdit->setFixedHeight(newHeight>maxh?maxh:newHeight);
}

//发送消息
void ChatWidget::on_send_clicked()
{
    QString msg=ui->textEdit->toPlainText();
    if(!msg.isEmpty()){
        DataHead head=DataHead::wsHead("send");
        Information info;
        info.sender=WApplication::getAccount();
        info.reciver=user.account;
        info.type=INFO_TEXT;
        info.msg=msg;
        DataResult result(0, QJsonDocument(info.json()));
        //发送服务器
        WApplication::getSocket()->sendText(head, result);
        //保存本地数据库
        Mapper::instance()->newmsg(info);
        //显示
        dismsg(info);
        ui->textEdit->setText(QString());
    }
}


void ChatWidget::on_sendimg_clicked()
{
    QString path=QFileDialog::getOpenFileName(nullptr, "选择图片", "", "图像文件 (*.png *.jpg *.bmp)");
    if(!path.isEmpty()){
        QByteArray* data=FileManager::sendimg(path);
        if(!data) return;
        Information info;
        info.sender=WApplication::getAccount();
        info.reciver=user.account;
        info.type=INFO_IMGE;
        info.msg=path;
        QJsonObject jo;
        jo.insert("reciver", user.account);
        jo.insert("sender", WApplication::getAccount());
        jo.insert("type", INFO_IMGE);
        QJsonDocument jd(jo);
        DataHead head=DataHead::wsHead("sendimg");
        //发送
        WApplication::getSocket()->sendBinary(head,jd,*data);
        //保存本地
        minstanse->newmsg(info);
        //显示
        dismsg(info);
        delete data;
    }
}

