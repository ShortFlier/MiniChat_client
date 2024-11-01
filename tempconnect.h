#ifndef TEMPCONNECT_H
#define TEMPCONNECT_H

#include "validconnect.h"
#include "websocketconnect.h"

class TempConnect : public WebSocketConnect
{
    Q_OBJECT
public:
    explicit TempConnect(QObject *parent = nullptr);
    ~TempConnect();

    ValidConnect* upgrade(QString account);


public slots:
    //功能函数
    //登入请求
    void login(QString account, QString password);
    //注册请求
    //请求发送验证码
    void register_email(QString email);
    //重新获取验证码
    void register_code(QString email);
    //填写验证码，确认注册
    void register_submit(QString email, QString code);
};

#endif // TEMPCONNECT_H
