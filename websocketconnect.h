#ifndef WEBSOCKETCONNECT_H
#define WEBSOCKETCONNECT_H

#include <QObject>
#include <QWebSocket>
#include "datahead.h"

#define HLENGTH 100

class WebSocketConnect : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketConnect(QObject *parent = nullptr);
    //移动构造
    explicit WebSocketConnect(WebSocketConnect&& wsc);
    virtual ~WebSocketConnect()=0;
    static QUrl loadServerAddresss();
    QWebSocket* getSocket(){ return socket; }
    //文本数据发送
    void sendText(DataHead& head, DataResult& result);
    //二进制数据发送
    void sendBinary(DataHead& head, QJsonDocument& jd, QByteArray& data);

signals:
    void connected();
    void closed();

protected:
    QWebSocket* socket;

private:
    void connectToServer();
};

#endif // WEBSOCKETCONNECT_H
