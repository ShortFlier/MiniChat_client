#include "tempconnect.h"
#include "datahead.h"

#include <QJsonObject>
#include <QJsonDocument>

TempConnect::TempConnect(QObject *parent)
    : WebSocketConnect{parent}
{}

TempConnect::~TempConnect()
{

}

void TempConnect::login(QString account, QString password)
{
    if(socket->state()==QAbstractSocket::ConnectedState){
        DataHead head=DataHead(DataHead::http, DataHead::request, "login", QString::number(11));
        QJsonObject data;
        data.insert("account", account);
        data.insert("password", password);
        DataResult result(0, QJsonDocument(data));
        sendText(head, result);
    }
}

void TempConnect::register_email(QString email)
{
    qDebug()<<"register_email: "<<email;
    if(socket->state()==QAbstractSocket::ConnectedState){
        DataHead head(DataHead::http, DataHead::request, "regist_code", QString::number(11));
        QJsonObject data;
        data.insert("email",email);
        DataResult result(0, QJsonDocument(data));
        sendText(head, result);
    }
}

void TempConnect::register_code(QString email)
{
    register_email(email);
}

void TempConnect::register_submit(QString email, QString code)
{
    qDebug()<<"register_submit: "<<code;
    if(socket->state()==QAbstractSocket::ConnectedState){
        DataHead head(DataHead::http, DataHead::request, "regist_confirm", QString::number(11));
        QJsonObject data;
        data.insert("email", email);
        data.insert("code", code);
        DataResult result(0, QJsonDocument(data));
        sendText(head, result);
    }
}
