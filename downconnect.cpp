#include "downconnect.h"

#include "filemanager.h"
#include "wapplication.h"
#include "websocketconnect.h"
#include "datahead.h"
#include "entity.h"
#include "mapper.h"

#include <QFile>
#include <QJsonArray>
#include <QUuid>

DownConnect::DownConnect(const QString& account, QObject *parent)
    : QObject{parent}
{
    this->account=account;

    funset();

    socket=new QWebSocket();
    connectToServer();

    connect(socket, &QWebSocket::connected, this, [this](){
        qDebug()<<"down已连接";
        connect(socket, &QWebSocket::binaryMessageReceived, this, &DownConnect::BinayHandler);
        down();
    });
    connect(socket, &QWebSocket::disconnected,[this](){
        qDebug()<<"down断开连接";
        connectToServer();
    });
}

DownConnect::~DownConnect()
{
}



void DownConnect::sendBinay(QString &path, QJsonDocument jd, QByteArray &data)
{
    QString head=path+DataHead::sepe+jd.toJson();
    QByteArray h=head.toUtf8();
    if(h.length()>HLENGTH){
        QMessageBox::critical(nullptr, "error", "数据同步大于"+QString::number(HLENGTH)+"字节");
        qDebug()<<path;
        qDebug()<<path.length();
        return;
    }
    h.resize(HLENGTH);
    socket->sendBinaryMessage(h+data);
}

void DownConnect::reciverimg(QJsonDocument &jd, QByteArray &data)
{
    qDebug()<<"reciverimg";
    //保存数据库
    QJsonObject jo=jd.object();
    Information info;
    info.sender=jo.value("sender").toString();
    info.time=QDateTime::fromString(jo.value("time").toString(), "yyyy-MM-dd HH:mm:ss");
    info.reciver=WApplication::getAccount();
    info.type=INFO_IMGE;
    info.msg=QUuid::createUuid().toString()+USER_IMAGE_TAIL;
    //存储获取要保存的图片名
    if(minstanse->reciverimg(info)){
        //保存本地
        FileManager::savechatimg(info.msg, data);
        //通知
        QJsonArray ja;
        ja.append(info.json());
        emit newchatmsg(info.sender, ja);
    }
}

void DownConnect::sendimg(QJsonDocument &jd, QByteArray &data)
{
    qDebug()<<"downsendimg";
    QString name=jd.object().value("name").toString();
    qDebug()<<name;
    FileManager::savechatimg(name, data);
}

void DownConnect::funset()
{
    fmap.insert("reciverimg", &DownConnect::reciverimg);
    fmap.insert("sendimg", &DownConnect::sendimg);
}

void DownConnect::connectToServer()
{
    QUrl url=WebSocketConnect::loadServerAddresss();
    socket->open(url);
}

void DownConnect::down()
{
    DataHead head=DataHead::dataHead("down");
    QJsonObject jo;
    jo.insert("account", WApplication::getAccount());
    DataResult result(0,QJsonDocument(jo));
    sendText(head, result);
}

void DownConnect::BinayHandler(const QByteArray &data)
{
    //分离
    QByteArray h= data.mid(0, HLENGTH);
    //请求路径部分
    int i = h.indexOf(DataHead::sepe.toUtf8());
    QString path=h.left(i);
    qDebug()<<path;
    //json数据部分
    QByteArray js = h.mid(i+2);
    //提取有效json部分
    i=js.lastIndexOf('\n');
    js=js.left(i);
    qDebug()<<js;
    QJsonDocument json = QJsonDocument::fromJson(js);
    //数据部分
    QByteArray d=data.mid(HLENGTH);

    //回调函数使用
    void(DownConnect::*fun)(QJsonDocument&,QByteArray&)=fmap.value(path);
    (this->*fun)(json,d);
}

void DownConnect::sendText(DataHead &head, DataResult &result)
{
    socket->sendTextMessage(head.getUrl()+result.data());
}
