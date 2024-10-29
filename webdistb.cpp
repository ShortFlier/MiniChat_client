#include "webdistb.h"



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

void WebDistb::redirect(DataHead &head, DataResult &result)
{
    Handler* hd=getHandler(*head._path);
    if(hd)
        hd->handler(head, result);
}
