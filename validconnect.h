#ifndef VALIDCONNECT_H
#define VALIDCONNECT_H

#include "websocketconnect.h"


class ValidConnect:public WebSocketConnect
{
public:
    ValidConnect(WebSocketConnect& wsc, const QString& act);
    QString getAccount(){return account;}
    //获取用户信息
    void getUserInfo();

private:
    QString account;
};

#endif // VALIDCONNECT_H
