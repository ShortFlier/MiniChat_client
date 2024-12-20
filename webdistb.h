#ifndef WEBDISTB_H
#define WEBDISTB_H

#include <QObject>
#include <QMap>

#include "websocketconnect.h"
#include <functional>

class Handler;

//Web消息接收类，负责接收并分发服务器消息
class WebDistb : public QObject
{
    typedef std::function<void(DataHead&,DataResult&)> FUN;
    typedef std::function<void(int code, QByteArray& data)> BFUN;
    Q_OBJECT
public:
    explicit WebDistb(WebSocketConnect* nt, QObject *parent = nullptr);
    void addHandler(const QString& path, Handler* handler);
    Handler* getHandler(const QString& path);
    //网络请求回调 在状态码为200时触发fun函数
    static void asyncWeb(WebSocketConnect* wc, DataHead& head, DataResult& result, FUN fun);
    //网络请求回调 二进制
    static void asyncBin(WebSocketConnect* wc, DataHead& head, QJsonDocument& json, QByteArray& data, BFUN fun);

    void addwsHandler(const QString& path, FUN fun){wshandler.insert(path, fun);}


private slots:
    void textHandler(const QString& msg);
    void binaryHandler(const QByteArray& data);

private:
    WebSocketConnect* cnect=nullptr;
    //消息处理对象
    QMap<QString, Handler*> path_handler;
    //消息推送处理
    QMap<QString, FUN> wshandler;

    static long id;

    //网络请求回调函数
    static QMap<long, FUN> id_fun;
    static FUN getFUN(const long& id);


    //网络请求回调函数 二进制
    static QMap<long, BFUN> id_bfun;
    static BFUN getBFUN(const long& id);


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
