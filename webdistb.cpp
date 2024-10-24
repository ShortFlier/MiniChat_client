#include "webdistb.h"

WebDistb::WebDistb(WebSocketConnect *nt, QObject *parent)
{
    cnect=nt;
    connect(cnect->getSocket(), &QWebSocket::textMessageReceived, this, &WebDistb::textHandler);
}

void WebDistb::textHandler(const QString &msg)
{
    qDebug()<<msg;
}
