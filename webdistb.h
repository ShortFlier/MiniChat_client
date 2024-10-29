#ifndef WEBDISTB_H
#define WEBDISTB_H

#include <QObject>
#include <QMap>

#include "websocketconnect.h"

class Handler;

//Web消息接收类，负责接收并分发服务器消息
class WebDistb : public QObject
{
    Q_OBJECT
public:
    explicit WebDistb(WebSocketConnect* nt, QObject *parent = nullptr);
    void addHandler(const QString& path, Handler* handler);
    Handler* getHandler(const QString& path);

private slots:
    void textHandler(const QString& msg);

private:
    WebSocketConnect* cnect=nullptr;
    //消息处理对象
    QMap<QString, Handler*> path_handler;

    //消息转发
    void redirect(DataHead& head, DataResult& result);
signals:
};


//继承实现纯虚函数已收到消息转发
class Handler{
public:
    virtual void handler(DataHead& head, DataResult& result)=0;
};

#endif // WEBDISTB_H
