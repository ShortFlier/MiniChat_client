#ifndef WAPPLICATION_H
#define WAPPLICATION_H

#include "loginscene.h"
#include "mainscene.h"

#include <QObject>

 //页面调度类
class WApplication : public QObject
{
    Q_OBJECT
private:
    explicit WApplication(QObject *parent = nullptr);
    ~WApplication();
public:
    static WApplication* getInstance();
    static void setSocket(WebSocketConnect* socket){sock=socket;}
    static WebSocketConnect* getSocket(){return sock;}
    static QString getAccount(){return account;}
    static QString name;
    static bool online();

signals:

private:
    LoginScene* loginScene=nullptr;
    MainScene* mainScene=nullptr;
    static WebSocketConnect* sock;
    static QString account;

};

#endif // WAPPLICATION_H
