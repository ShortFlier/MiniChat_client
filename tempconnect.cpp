#include "tempconnect.h"
#include "datahead.h"

TempConnect::TempConnect(QObject *parent)
    : WebSocketConnect{parent}
{}

TempConnect::~TempConnect()
{

}

void TempConnect::login(QString account, QString password, unsigned int id)
{
    qDebug()<<"login: "<<account<<" | "<<password;
    if(socket->state()==QAbstractSocket::ConnectedState){
        QString url=DataHead::getUrl(DataHead::http, DataHead::request, "login", QString::number(id));
        socket->sendTextMessage(url);
    }
}

void TempConnect::register_email(QString email, unsigned int id)
{
    qDebug()<<"register_email: "<<email;
    if(socket->state()==QAbstractSocket::ConnectedState){

    }
}

void TempConnect::register_code(QString email, unsigned int id)
{
    qDebug()<<"register_code";
    if(socket->state()==QAbstractSocket::ConnectedState){

    }
}

void TempConnect::register_submit(QString email, QString code, unsigned int id)
{
    qDebug()<<"register_submit: "<<code;
    if(socket->state()==QAbstractSocket::ConnectedState){

    }
}
