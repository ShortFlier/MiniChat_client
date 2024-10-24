#ifndef WEBDISTB_H
#define WEBDISTB_H

#include <QObject>

#include "websocketconnect.h"


//Web消息接收类，负责接收并分发服务器消息
class WebDistb : public QObject
{
    Q_OBJECT
public:
    explicit WebDistb(WebSocketConnect* nt, QObject *parent = nullptr);

private slots:
    void textHandler(const QString& msg);

private:
    WebSocketConnect* cnect=nullptr;

signals:
};

#endif // WEBDISTB_H
