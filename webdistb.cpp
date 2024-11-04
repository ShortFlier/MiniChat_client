#include "webdistb.h"

long WebDistb::id=20;

QMap<long, WebDistb::FUN> WebDistb::id_fun=QMap<long, WebDistb::FUN>();

WebDistb::WebDistb(WebSocketConnect *nt, QObject *parent)
{
    cnect=nt;
    connect(cnect->getSocket(), &QWebSocket::textMessageReceived, this, &WebDistb::textHandler);
}

void WebDistb::addHandler(const QString &path, Handler *handler)
{
    path_handler.insert(path, handler);
}

Handler *WebDistb::getHandler(const QString &path)
{
    if(path_handler.contains(path)){
        return path_handler.value(path);
    }else
        return nullptr;
}

void WebDistb::asyncWeb(WebSocketConnect *wc, DataHead &head, DataResult &result, FUN fun)
{
    //设置通信id号
    QString _id=QString::number(id);
    head.setId(_id);
    //加入fun回调函数
    id_fun.insert(id, fun);

    wc->sendText(head, result);
    ++id;
}

void WebDistb::textHandler(const QString &msg)
{
    QString data=msg;
    QTextStream ts(&data);
    QString h=ts.readLine();
    DataHead head(h);
    QString d=ts.readAll();
    DataResult result(d);
    redirect(head, result);
}

WebDistb::FUN WebDistb::getFUN(const long &id)
{
    FUN fun=id_fun.value(id);
    id_fun.remove(id);
    return fun;
}

void WebDistb::redirect(DataHead &head, DataResult &result)
{
    if(result.code!=DataResult::code_success){
        ERROR
        return;
    }
    long id=(*head._tpid).toLong();
    if(id_fun.contains(id)){
        FUN fun=getFUN(id);
        fun(head, result);
        return;
    }
    Handler* hd=getHandler(*head._path);
    if(hd)
        hd->handler(head, result);
}
