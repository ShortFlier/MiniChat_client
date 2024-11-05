#include "validconnect.h"

#include <QJsonObject>

ValidConnect::ValidConnect(WebSocketConnect& wsc, const QString& act):WebSocketConnect(std::move(wsc)) {
    account=act;
}

void ValidConnect::getUserInfo()
{
    if(socket->state()==QAbstractSocket::ConnectedState){
        DataHead head=DataHead(DataHead::http, DataHead::request, "userinfo", QString::number(11));
        QJsonObject jo;
        jo.insert("account", account);
        DataResult result(0, QJsonDocument(jo));
        sendText(head, result);
    }
}

void ValidConnect::uimgload(const QString &account, QByteArray &imgdata)
{
    DataHead head = DataHead::dataHead("uimgload");
    QJsonObject jo;
    jo.insert("account", account);
    QJsonDocument jd(jo);
    sendBinary(head, jd, imgdata);
}

