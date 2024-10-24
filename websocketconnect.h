#ifndef WEBSOCKETCONNECT_H
#define WEBSOCKETCONNECT_H

#include <QObject>
#include <QWebSocket>

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

signals:
    void connected();
    void closed();

protected:
    QWebSocket* socket;

private:
    void connectToServer();
};

#endif // WEBSOCKETCONNECT_H
