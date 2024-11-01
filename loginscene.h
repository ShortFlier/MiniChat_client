#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <QMainWindow>
#include <QLabel>

#include "loginwidget.h"
#include "registwidget.h"
#include "rgtcfmwidget.h"
#include "tempconnect.h"
#include "webdistb.h"

class LoginScene : public QMainWindow, public Handler
{
    Q_OBJECT
public:
    enum status{online, disonline};
    explicit LoginScene(QWidget *parent = nullptr);
    void setStatus(status s);
    //开启服务器连接
    void webstart();
    void reshow();
    //登入信息处理
    void handler(DataHead& head, DataResult& result) override;
    //登入成功
    void login(const QString& account);
    void save(const QString& account);

signals:
    void logined(ValidConnect* vc);

private:
    LoginWidget* loginWidget;
    RegistWidget* registWidget;
    RgtCfmWidget* rgtCfmWidget;

    QLabel* statusLabel;

    TempConnect* tempSocket;
    WebDistb* webdistb;


signals:

};

#endif // LOGINSCENE_H
