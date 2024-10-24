#ifndef TEMPCONNECT_H
#define TEMPCONNECT_H

#include "websocketconnect.h"

class TempConnect : public WebSocketConnect
{
public:
    explicit TempConnect(QObject *parent = nullptr);
    ~TempConnect();

public slots:
    //功能函数
    //登入请求
    void login(QString account, QString password, unsigned int id);
    //注册请求
    void register_email(QString email, unsigned int id);
    void register_code(QString email, unsigned int id);   //重新获取验证码
    void register_submit(QString email, QString code, unsigned int id);
};

#endif // TEMPCONNECT_H
