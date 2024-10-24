#include "websocketconnect.h"

#include <QFile>

WebSocketConnect::WebSocketConnect(QObject *parent)
    : QObject{parent}
{
    socket=new QWebSocket("ws://example.com");
    connectToServer();
    connect(socket, &QWebSocket::connected, [this](){
        qDebug()<<"连接建立";
        emit connected();
    });
    connect(socket, &QWebSocket::disconnected, [this](){
        qDebug()<<"连接断开";
        emit closed();
        connectToServer();
    });
}

WebSocketConnect::WebSocketConnect(WebSocketConnect &&wsc)
{
    socket=wsc.socket;
    wsc.socket=nullptr;
}

QUrl WebSocketConnect::loadServerAddresss()
{
    QFile file(":/assets/server_address.txt");
    file.open(QIODeviceBase::ReadOnly);
    if(file.isOpen()){
        QString ip, port;
        QTextStream ts(&file);
        ip = ts.readLine();
        port=ts.readLine();
        QUrl address(ip+":"+port);
        qDebug()<<address;
        file.close();
        return address;
    }else
        file.close();
        qDebug()<<"文件打开出错";
        return QUrl("ws://localhost:10023");
}

void WebSocketConnect::connectToServer()
{
    socket->open(loadServerAddresss());
    qDebug()<<"尝试连接服务器";
}

WebSocketConnect::~WebSocketConnect(){
    if(socket!=nullptr){
        emit closed();
        socket->close();
        qDebug()<<"连接已关闭";
        socket->deleteLater();
    }
}
