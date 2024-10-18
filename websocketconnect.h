#ifndef WEBSOCKETCONNECT_H
#define WEBSOCKETCONNECT_H

#include <QObject>
#include <QWebSocket>

class WebSocketConnect : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketConnect(QObject *parent = nullptr);
    virtual ~WebSocketConnect()=0;
    static QUrl loadServerAddresss();

signals:
    void connected();
    void closed();

protected:
    QWebSocket* socket;
    bool active=true;

private:
    void connectToServer();
};

#endif // WEBSOCKETCONNECT_H
